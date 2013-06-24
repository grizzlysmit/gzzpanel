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

#ifndef _TASKBAR_H_
#define _TASKBAR_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "task.h"
#include "applet.h"
#include "wnck-screen.h"
#include <map>

namespace gzz {

	class Taskbar : public Gtk::Box, public Applet 
	{
		public:
			Taskbar(Wnck::Screen &screen, Gtk::Orientation orientation = Gtk::ORIENTATION_HORIZONTAL);
			~Taskbar();

			// interface //
			virtual void refreshbar();
			virtual void clearbar();
			virtual std::vector<Wnck::Window*> get_windows_on_viewport(const std::vector<Wnck::Window*> & vec, Wnck::Workspace* workspace);
		protected:
			Wnck::Screen &m_wnck_screen;
			std::map<Wnck::Window*, Task*> m_mappings;
			int m_min_button_size = 150;
			bool m_min_buttons_too_small = false;
			int m_max_group_size = 0;
			std::map<WnckClassGroup*, Task*> m_class_group_mappings;
			Wnck::ClassGroup* m_max_class_group = nullptr;
			bool m_buttons_can_expand = false;

			Task* get_task_from_class_group_mappings(Wnck::Window* win);
			WnckClassGroup* min_count_task();

			// handlers //
			void on_showing_desktop_changed();
			void on_widow_closed(Wnck::Window* win);
			void on_task_size_allocate(Gtk::Allocation& allocation, Task* task);
			//void on_widow_state_changed(Wnck::Window* win, Wnck::Window::State changed_mask, Wnck::Window::State new_state);
		private:

	};
	
}; // namespace gzz //

#endif // _TASKBAR_H_

