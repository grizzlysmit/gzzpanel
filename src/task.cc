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

#include "task.h"
#include <exception>      // std::exception

namespace gzz {

	/*Task::Task()
		: Gtk::Button(), m_wnck_window(0), m_repgroup(false)
	{
	}*/

	Task::Task(Wnck::Window* win)
		: Gtk::Button(), m_wnck_window(win), m_wnck_classgroup(0), 
	      m_wnck_windows({win}), m_constructed(false)
	{
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t starting m_wnck_window->get_name()" << m_wnck_window->get_name() << std::endl;*/
		m_hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
		m_image = Gtk::manage(new Gtk::Image(m_wnck_window->get_icon()));
		m_hbox->pack_start(*m_image, false, true, 2);
		m_image->show();
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << " m_wnck_window->get_name()" << m_wnck_window->get_name() << std::endl;*/
		m_label = Gtk::manage(new Gtk::Label(m_wnck_window->get_name()));
		m_label->set_ellipsize(Pango::ELLIPSIZE_END);
		m_label->set_justify(Gtk::JUSTIFY_LEFT);
		m_label->set_margin_left(5);
		//m_hbox->pack_start(*m_label, Gtk::PACK_SHRINK|Gtk::PACK_EXPAND_WIDGET, 2);
		m_hbox->pack_start(*m_label, true, true, 0);
		m_label->show();
		add(*m_hbox);
		m_hbox->show_all();
		m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t finished construction m_wnck_window->get_name()" << m_wnck_window->get_name() << std::endl;*/
		m_constructed = true;
	}

	Task::Task(Wnck::Window* win, Wnck::ClassGroup* class_group,
			   std::vector<Wnck::Window*> vec)
		: Gtk::Button(), m_wnck_window(win), m_wnck_classgroup(class_group), 
	      m_wnck_windows(vec.begin(), vec.end()), m_constructed(false)
	{
		m_hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
		if(m_wnck_windows.size()  > 1){
			m_arrow = Gtk::manage(new Gtk::Arrow(Gtk::ARROW_DOWN, Gtk::SHADOW_ETCHED_IN));
			m_hbox->pack_start(*m_arrow, false, false, 0);
			m_arrow->show();
		}
		m_image = Gtk::manage(new Gtk::Image(m_wnck_classgroup->get_icon()));
		m_hbox->pack_start(*m_image, false, true, 2);
		m_image->show();
		m_label = Gtk::manage(new Gtk::Label(m_wnck_classgroup->get_name()));
		m_label->set_ellipsize(Pango::ELLIPSIZE_END);
		m_label->set_justify(Gtk::JUSTIFY_LEFT);
		m_label->set_margin_left(5);
		//m_hbox->pack_start(*m_label, Gtk::PACK_SHRINK|Gtk::PACK_EXPAND_WIDGET, 2);
		m_hbox->pack_start(*m_label, true, true, 0);
		m_label->show();
		add(*m_hbox);
		m_hbox->show_all();
		m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
		m_constructed = true;
	}

	Task::~Task()
	{
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << " destructor called " << std::endl;*/
		if(m_menu_right_click){
			delete m_menu_right_click;
			m_menu_right_click = 0;
		}
		m_destructed = true;
	}

	bool Task::on_button_press_event(GdkEventButton *event)
	{
		if(event->button == 3 && event->type == GDK_BUTTON_PRESS){
			if(m_wnck_windows.size() == 1){
				if(!m_menu_right_click){
					if(!m_wnck_window) m_wnck_window = m_wnck_windows[0];
					m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
				}
				m_menu_right_click->popup(sigc::mem_fun(*this, &Task::on_popup_menu_right_click), 0, gtk_get_current_event_time());
			}else{
			}
			return m_signal_right_clicked.emit();
		}
		return Gtk::Button::on_button_press_event(event);
	}

	void Task::on_clicked()
	{
		if(m_wnck_windows.size() == 1){
			std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " entering 1 window " << std::endl;
			if(!m_wnck_window) return;
			/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << "\t past return m_wnck_window == " << m_wnck_window << std::endl;
			std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << "\t m_wnck_window->get_name() == " << m_wnck_window->get_name() << std::endl;*/
			if(m_wnck_window->is_minimized()){
				m_wnck_window->unminimize(gtk_get_current_event_time());
			}else if(m_wnck_window->is_below()){
				m_wnck_window->unmake_below();
			}else if(m_wnck_window->is_above()){
				//m_wnck_window->unmake_above();
				std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " minimizing " << std::endl;
				m_wnck_window->minimize();
			}else{
				m_wnck_window->activate(gtk_get_current_event_time());
			}
		}else if(m_wnck_windows.size() > 1){
			std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " entering > 1 window " << std::endl;
			if(m_menu){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " deleting m_menu == " << m_menu << std::endl;
				delete m_menu;
				m_menu = 0;
			}
			m_menu = new Gtk::Menu();
			Gtk::ImageMenuItem* item;
			Gtk::Image* image;
			for(auto win : m_wnck_windows){
				std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						  << " adding menuitem win == " << win << std::endl;
				try {
					image = Gtk::manage(new Gtk::Image(win->get_icon()));
					item = Gtk::manage(new Gtk::ImageMenuItem(*image, win->get_name()));
					item->signal_activate().connect(
					                                sigc::bind<Wnck::Window*>(sigc::mem_fun(*this,
					                                                                        &Task::on_menu_item_activate), win));
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						      << " adding menuitem " << std::endl;
					m_menu->append(*item);
					item->show_all();
				}
				catch(std::exception& e){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						      << " error exception caught: " << e.what() << std::endl;
				}
				catch(...){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					          << " unknown eception caught " << std::endl;
				}
			}

			m_menu->popup(sigc::mem_fun(*this, &Task::on_popup_menu_left_click), 0, gtk_get_current_event_time());
			Gtk::Button::on_clicked();
		}
	}

	int Task::count()
	{
		return m_wnck_windows.size();
	}

	void Task::remove_window(Wnck::Window* win)
	{
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << " entering win == " << win << std::endl;*/
        auto pos = find(m_wnck_windows.begin(), m_wnck_windows.end(), win);
		if(pos == m_wnck_windows.end()){
		    /*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " win not found win == " << win << "\t at *pos == " << *pos << std::endl;*/
		}else{
		    /*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << " erasing win == " << win << "\t at *pos == " << *pos << std::endl;*/
			m_wnck_windows.erase(pos);
		}
		if(m_wnck_window == win && !m_wnck_windows.empty()){
			m_wnck_window = m_wnck_windows[0];
			delete m_menu_right_click;
			m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
		}else if(m_wnck_windows.empty()){
			m_wnck_window = 0;
			if(m_menu_right_click){
				delete m_menu_right_click;
				m_menu_right_click = 0;
			}
		}
		if(m_wnck_windows.size() == 1){
			refresh_state();
		}
	}

	int Task::find_pos(std::vector<Wnck::Window*> vec, Wnck::Window* win)
	{
		for(int p = 0; p < vec.size(); p++){
			if(vec[p] == win){
				return p;
			}
		}
		return -1;
	}

	void Task::add_window(Wnck::Window* win, Wnck::ClassGroup* class_group)
	{
		auto pos = find(m_wnck_windows.begin(), m_wnck_windows.end(), win);
		if(pos == m_wnck_windows.end()){
			m_wnck_windows.insert(m_wnck_windows.end(), win);
		}
		if(!m_wnck_window){
			m_wnck_window = win;
			if(m_menu_right_click){
				delete m_menu_right_click;
			}
			m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
		}
		if(!m_wnck_classgroup){
			m_wnck_classgroup = class_group;
		}else if(m_wnck_classgroup != class_group){
			throw std::runtime_error("conflicting classgroups");
		}
	}

	void Task::on_popup_menu_right_click(int& x, int& y, bool& push_in)
	{
	}

	void Task::refresh_state()
	{
		/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					<< " refreshhing Task: m_constructed == " << std::boolalpha 
			        << m_constructed << std::endl;*/
		if(m_wnck_windows.size() == 1){
			/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					  << " m_arrow == " << m_arrow << std::endl;*/
			if(m_arrow){
				m_hbox->remove(*m_arrow);
				delete m_arrow;
				m_arrow = 0;
			}
			if(!m_wnck_window){ 
				/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " m_menu_right_click == " << m_menu_right_click << std::endl;*/
				m_wnck_window = m_wnck_windows[0];
				if(m_menu_right_click){
					delete m_menu_right_click;
				}
				m_menu_right_click = new Wnck::ActionMenu(*m_wnck_window);
			}
			/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					  << " m_wnck_window->has_icon_name() == " << std::boolalpha 
				      << m_wnck_window->has_icon_name() << std::endl;
			std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					  << " m_image == " << m_image << std::endl;*/
			/*if(!m_image){
				m_image = 
			}*/
			/*if(m_wnck_window->has_icon_name()){
				m_image->set(m_wnck_window->get_icon());
			}else{
				m_image->set(Gtk::StockID("gtk-missing-image"), Gtk::IconSize(32));
			}*/
			m_image->set(m_wnck_window->get_icon());
			/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " m_wnck_window->has_name() == " << std::boolalpha 
					      << m_wnck_window->has_name() << std::endl;*/
			if(m_wnck_window->is_minimized()){
				/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " m_wnck_window->has_name() == " << std::boolalpha 
					      << m_wnck_window->has_name() << std::endl;*/
				m_label->set_text("[ " + m_wnck_window->get_name() + " ]");
			}else{
				/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " about to look at name" << std::endl;
				std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					      << " m_wnck_window->has_name() == " << std::boolalpha 
					      << m_wnck_window->has_name() << std::endl;*/
				m_label->set_text(m_wnck_window->get_name());
			}
		}else if(m_wnck_windows.size() > 1){
			if(!m_arrow){
				m_arrow = Gtk::manage(new Gtk::Arrow(Gtk::ARROW_DOWN, Gtk::SHADOW_ETCHED_IN));
				m_hbox->pack_start(*m_arrow, false, false, 0);
				m_hbox->reorder_child(*m_arrow, 0);
				m_arrow->show();
			}
			if(!m_wnck_classgroup) return;
			/*std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
					  << " got here" << std::endl;*/
			m_image->set(m_wnck_classgroup->get_icon());
			m_label->set_text(m_wnck_classgroup->get_name());
		}else{
		}
	}

	void Task::on_menu_item_activate(Wnck::Window* win)
	{
		if(win->is_minimized()){
			win->unminimize(gtk_get_current_event_time());
		}else if(win->is_below()){
			win->unmake_below();
		}else if(win->is_above()){
			//win->unmake_above();
			win->minimize();
		}else{
			win->activate(gtk_get_current_event_time());
		}
	}

	void Task::on_popup_menu_left_click(int& x, int& y, bool& push_in)
	{
	}

	bool Task::contains(Wnck::Window* win)
	{
		auto pos = find(m_wnck_windows.begin(), m_wnck_windows.end(), win);
		return pos != m_wnck_windows.end();
	}

	Wnck::ClassGroup* Task::get_class_group()
	{
		return m_wnck_classgroup;
	}

	void Task::set_fontdescription(Pango::FontDescription fd)
	{
		if(m_label) m_label->override_font(fd);
	}

	void Task::set_colour(Gdk::RGBA rgba)
	{
		if(m_label) m_label->override_color(rgba);
	}

	bool Task::get_constructed() const
	{
		return m_constructed;
	}

	bool Task::get_destructed() const
	{
		return m_destructed;
	}
	

}; // namespace gzz //


