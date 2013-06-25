/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gzzpanel
 * Copyright (C) 2013 Francis (Grizzly) Smit <grizzlysmit@smit.id.au>
 * 
 * gzzpanel is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gzzpanel is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "taskbar.h"
#include <limits>

namespace gzz {

	Taskbar::Taskbar(Wnck::Screen &screen, Gtk::Orientation orientation/* = Gtk::ORIENTATION_HORIZONTAL*/)
		: Gtk::Box(orientation, 2), Applet(), m_wnck_screen(screen)
	{
		//set_layout(Gtk::BUTTONBOX_START);
		set_homogeneous(true);
		m_wnck_screen.signal_showing_desktop_changed().connect( sigc::mem_fun(*this, &Taskbar::on_showing_desktop_changed) );
		m_wnck_screen.signal_viewports_changed().connect( sigc::mem_fun(*this, &Taskbar::on_showing_desktop_changed) );
		//m_wnck_screen.signal_viewports_changed().connect( sigc::mem_fun(*this, &Taskbar::on_showing_desktop_changed) );
		m_wnck_screen.signal_window_closed().connect( sigc::mem_fun(*this, &Taskbar::on_widow_closed) );
	}

	Taskbar::~Taskbar()
	{
	}

	void Taskbar::refreshbar()
	{
        //m_max_class_group = nullptr;
		m_max_group_size  = 0;
		Wnck::Workspace* workspace = m_wnck_screen.get_active_workspace();
		int cnt = 0;
		while(!workspace){ 
			if(cnt > 10){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
        				  << " bailing could not get active workspace " << std::endl;
				return;
			}
			cnt++;
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " trying to get active workspace " << std::endl;
			workspace = m_wnck_screen.get_active_workspace();
		}
		if(!m_min_buttons_too_small && m_buttons_can_expand){
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << "\t m_buttons_can_expand  == " << std::boolalpha << m_buttons_can_expand << std::endl;
			WnckClassGroup* class_group = min_count_task();
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << "\t class_group  == " << class_group << std::endl;
			if(class_group){
				Task *task = m_class_group_mappings[class_group];
				// remove Task smallest no of widows (but > 1)  //
				// and and let the rest of the refresh put them //
				// back as single Tasks                         //
				remove(*task);
				delete task; 
				m_class_group_mappings.erase(class_group);  
			}
			m_buttons_can_expand = false;
		}
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " got active workspace " << std::endl;*/
		std::vector<Wnck::Window*> lst = m_wnck_screen.get_windows();
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " lst.size() == " << lst.size() << std::endl;*/
		for(auto win : lst){
			if(!win->is_skip_tasklist() && win->is_on_workspace(*workspace) && win->is_in_viewport(*workspace) && m_mappings.find(win) == m_mappings.end()){
			    /*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " putting into bar " << std::endl;*/
				Wnck::ClassGroup *class_group = win->get_class_group();
				std::vector<Wnck::Window*> vec = class_group->get_windows();
				std::vector<Wnck::Window*> vec2 = get_windows_on_viewport(vec, workspace);
				if(m_class_group_mappings.find(class_group->gobj()) == m_class_group_mappings.end() && m_max_group_size < vec2.size()){
					m_max_class_group = class_group;
					m_max_group_size  = vec2.size();
				}else if(m_class_group_mappings.find(class_group->gobj()) != m_class_group_mappings.end()){
					Task* task = m_class_group_mappings[class_group->gobj()];
					task->add_window(win, class_group);
					continue;
				}
				//win->signal_state_changed().connect( sigc::mem_fun(*this, &Taskbar::on_widow_state_changed) ); // crashes program still not sure why //
				Task *task = Gtk::manage(new Task(win));
				m_mappings[win] = task;
				//pack_start(*task, Gtk::PACK_SHRINK|Gtk::PACK_EXPAND_WIDGET, 0);
				task->signal_size_allocate().connect( sigc::bind<Task*>(sigc::mem_fun(*this, &Taskbar::on_task_size_allocate), task) );
				pack_start(*task, true, true, 0);
				task->show_all();
			    /*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << "\t task->get_width()  == " << task->get_width() << std::endl;*/
			}else if(!win->is_skip_tasklist() && win->is_on_workspace(*workspace) && win->is_in_viewport(*workspace) && m_mappings.find(win) != m_mappings.end()){
				Wnck::ClassGroup *class_group = win->get_class_group();
				std::vector<Wnck::Window*> vec = class_group->get_windows();
				std::vector<Wnck::Window*> vec2 = get_windows_on_viewport(vec, workspace);
				if(m_class_group_mappings.find(class_group->gobj()) == m_class_group_mappings.end() && m_max_group_size < vec2.size()){
					m_max_class_group = class_group;
					m_max_group_size  = vec2.size();
				}
				if(m_mappings.find(win) != m_mappings.end()){
					Task* task = m_mappings[win];
					task->refresh_state();
				}
			}else if(m_mappings.find(win) != m_mappings.end()){
				Task* task = m_mappings[win];
				task->remove_window(win);
				if(task->count() == 0){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						<< " deleting Task " << std::endl;
					remove(*task);
					delete task;
				}
				m_mappings.erase(win);
			}else{
				Wnck::ClassGroup *class_group = win->get_class_group();
				if(m_class_group_mappings.find(class_group->gobj()) != m_class_group_mappings.end()){
					Task* task = m_class_group_mappings[class_group->gobj()];
					task->remove_window(win);
					if(task->count() == 0){
						std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
							<< " deleting Task " << std::endl;
						remove(*task);
						delete task;
						m_class_group_mappings.erase(class_group->gobj());
					}
				}
			}
		} // for(auto win : lst) //
		if(m_min_buttons_too_small && m_max_class_group && m_max_group_size > 1){
			std::vector<Wnck::Window*> vec = m_max_class_group->get_windows();
			std::vector<Wnck::Window*> vec2 = get_windows_on_viewport(vec, workspace);
			if(vec2.size() <= 1) return;
			if(m_class_group_mappings.find(m_max_class_group->gobj()) != m_class_group_mappings.end()){
				Task* task = m_class_group_mappings[m_max_class_group->gobj()];
				for(auto win : vec2){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						      << " adding win->get_name() == " << win->get_name() << ": to task" << std::endl;
					task->add_window(win, m_max_class_group);
				}
				m_max_class_group = nullptr;
				return;
			}else{
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< " got here " << std::endl;
				for(auto win : vec2){
					if(m_mappings.find(win) == m_mappings.end()) continue;
					Task* task = m_mappings[win];
					task->remove_window(win);
					if(task->count() == 0){
						std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
							<< " deleting Task " << std::endl;
						remove(*task);
						delete task;
					}
					m_mappings.erase(win);
				}
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< " adding Task: m_max_class_group->get_name() == " 
					<< m_max_class_group->get_name() << std::endl;
				if(m_class_group_mappings.find(m_max_class_group->gobj()) != m_class_group_mappings.end()){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						<< " WTF how did I get here: m_max_class_group->get_name() == " 
						<< m_max_class_group->get_name() << std::endl;
					return;
				}
				Task *task = Gtk::manage(new Task(vec2[0], m_max_class_group, vec2));
				m_class_group_mappings[m_max_class_group->gobj()] = task;
				m_min_buttons_too_small = false;
				m_max_class_group       = nullptr;
				m_max_group_size        = 0;
				//pack_start(*task, Gtk::PACK_SHRINK|Gtk::PACK_EXPAND_WIDGET, 0);
				//task->signal_size_allocate().connect( sigc::mem_fun(*this, &Taskbar::on_task_size_allocate) );
				task->signal_size_allocate().connect( sigc::bind<Task*>(sigc::mem_fun(*this, &Taskbar::on_task_size_allocate), task) );
				pack_start(*task, true, true, 0);
				task->show_all();
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< "\t task->get_width()  == " << task->get_width() << std::endl;
			}
		}
	}

	void Taskbar::on_showing_desktop_changed()
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " got here " << std::endl;
		clearbar();
		refreshbar();
	}

	void Taskbar::clearbar()
	{
		if(m_mappings.size() == 0) return;
		for(auto p : m_mappings){
			p.second->remove_window(p.first);
			if(p.second->count() == 0){
				remove(*p.second);
				delete p.second;
			}
		}
		m_mappings.clear();
	}

	std::vector<Wnck::Window*> Taskbar::get_windows_on_viewport(const std::vector<Wnck::Window*> & vec, Wnck::Workspace* workspace)
	{
		std::vector<Wnck::Window*> result;
		for(auto win : vec){
			if(!win->is_skip_tasklist() && win->is_on_workspace(*workspace) && win->is_in_viewport(*workspace)){
			    /*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " putting into vec " << std::endl;*/
				result.insert(result.end(), win);
			}
		}
		return result;
	}

	void Taskbar::on_widow_closed(Wnck::Window* win)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " entering: win == " << win << std::endl;
		Task* task = nullptr;
		Wnck::ClassGroup *class_group = win->get_class_group();
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " entering: class_group == " << class_group << std::endl;
		if(class_group){
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " entering: class_group->gobj() == " << class_group->gobj() << std::endl;
		}
		if(m_mappings.find(win) != m_mappings.end()){
			task = m_mappings[win];
		}else if(class_group && m_class_group_mappings.find(class_group->gobj()) != m_class_group_mappings.end()){
			task = m_class_group_mappings[class_group->gobj()];
		}else{
			task = get_task_from_class_group_mappings(win);
			if(!task){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " bailing not found: win == " << win << std::endl;
				return;
			}
			if(!class_group) class_group = task->get_class_group();
		}
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " removing: win == " << win << std::endl;
		task->remove_window(win);
		if(task->count() == 0){
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " deleting Task " << std::endl;
			remove(*task);
			delete task;
			if(m_mappings.find(win) != m_mappings.end()){
				m_mappings.erase(win);
			}else if(class_group && m_class_group_mappings.find(class_group->gobj()) != m_class_group_mappings.end()){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< " removing  " << class_group->get_name() << " from m_class_group_mappings" << std::endl;
				m_class_group_mappings.erase(class_group->gobj());
			}
		}
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << " exiting " << std::endl;
	}

	void Taskbar::on_task_size_allocate(Gtk::Allocation& allocation, Task* task)
	{
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << "\t allocation.get_widith() == " << allocation.get_width() << std::endl;*/
		m_min_buttons_too_small = (m_min_button_size > allocation.get_width());
		if(!m_min_buttons_too_small){
			int m = task->count();
			if(m > 1){
			    std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << "\t m  == " << m << std::endl;
				m_buttons_can_expand = m_buttons_can_expand 
					                       || ((get_children().size())*(allocation.get_width() - m_min_button_size) >= (m - 1)*(m_min_button_size + get_spacing()));
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << "\t done caculating resize : m_buttons_can_expand  == " << std::boolalpha << m_buttons_can_expand << std::endl;
			}
		}
	}

	/*void Taskbar::on_widow_state_changed(Wnck::Window* win, Wnck::Window::State changed_mask, Wnck::Window::State new_state)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " got here " << std::endl;
		Wnck::Workspace* workspace = m_wnck_screen.get_active_workspace();
		int cnt = 0;
		while(!workspace){ 
			if(cnt > 10){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
        				  << " bailing could not get active workspace " << std::endl;
				return;
			}
			cnt++;
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " trying to get active workspace " << std::endl;
			workspace = m_wnck_screen.get_active_workspace();
		}
		Task* task = nullptr;
		Wnck::ClassGroup *class_group = win->get_class_group();
		if(m_mappings.find(win) != m_mappings.end()){
			task = m_mappings[win];
		}else if(m_class_group_mappings.find(class_group) != m_class_group_mappings.end()){
			task = m_class_group_mappings[class_group];
		}else{
			return; // nothing to do //
		}
		if(!win->is_skip_tasklist() && win->is_on_workspace(*workspace) && win->is_in_viewport(*workspace)){
			task->refresh_state();
		}else{
			task->remove_window(win);
			if(task->count() == 0){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< " deleting Task " << std::endl;
				remove(*task);
				delete task;
			}
			if(m_mappings.find(win) != m_mappings.end()){
				m_mappings.erase(win);
			}else if(m_class_group_mappings.find(class_group) != m_class_group_mappings.end()){
				m_class_group_mappings.erase(class_group);
			}
			//clearbar();
			//refreshbar();
		}
	}*/

	Task* Taskbar::get_task_from_class_group_mappings(Wnck::Window* win)
	{
		for(auto p : m_class_group_mappings){
			if(p.second->contains(win)) return p.second;
		}
		return 0;
	}

	WnckClassGroup* Taskbar::min_count_task()
	{
		int mincount = std::numeric_limits<int>::max();
		WnckClassGroup* min_class_group = nullptr;
		for(auto p : m_class_group_mappings){
			if(p.second->count() < mincount){
				mincount = p.second->count();
				min_class_group  = p.first;
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << "\t found new min : min_class_group  == " << min_class_group << "\t mincount == " << mincount << std::endl;
			}
		}
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t done caculating min:\t min_class_group  == " << min_class_group << "\t mincount == " << mincount << std::endl;
		return min_class_group;
	}

	int Taskbar::get_min_button_size()
	{
		return m_min_button_size;
	}

	void Taskbar::set_min_button_size(int sz)
	{
		m_min_button_size = sz;
	}


	
	

}; // namespace gzz //

