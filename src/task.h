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

#ifndef _TASK_H_
#define _TASK_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "wnck-screen.h"
#include "wnck-action-menu.h"

namespace gzz {

	class Task : public Gtk::Button 
	{
		public:
			typedef sigc::signal<bool> type_signal_right_clicked;

			//Task();
			Task(Wnck::Window* win);
			Task(Wnck::Window* win, Wnck::ClassGroup* class_group,
			     std::vector<Wnck::Window*> vec);
			~Task();

			void remove_window(Wnck::Window* win);
			int count();
			void add_window(Wnck::Window* win, Wnck::ClassGroup* class_group);
			void refresh_state();
			bool contains(Wnck::Window* win);
			Wnck::ClassGroup* get_class_group();
			
			// signal handling //
			type_signal_right_clicked signal_right_clicked();
		protected:
			type_signal_right_clicked m_signal_right_clicked;
			Wnck::Window* m_wnck_window;
			Wnck::ClassGroup* m_wnck_classgroup = 0;
			std::vector<Wnck::Window*> m_wnck_windows;
			Gtk::Box *m_hbox = 0;
			Gtk::Label *m_label = 0;
			Gtk::Image *m_image = 0;
			Gtk::Arrow *m_arrow = 0;
			Wnck::ActionMenu* m_menu_right_click = 0;
			Gtk::Menu* m_menu = 0;

			virtual bool on_button_press_event(GdkEventButton *event);
			virtual void on_clicked();
			int find_pos(std::vector<Wnck::Window*> vec, Wnck::Window* win);

			// handlers //
			void on_popup_menu_right_click(int& x, int& y, bool& push_in);
			void on_menu_item_activate(Wnck::Window* win);
			void on_popup_menu_left_click(int& x, int& y, bool& push_in);
		private:

	};

}; // namespace gzz //

#endif // _TASK_H_

