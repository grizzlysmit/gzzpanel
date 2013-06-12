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

class Task : public Gtk::Button 
{
	public:
		typedef sigc::signal<bool> type_signal_right_clicked;
		
		Task();
		~Task();

		type_signal_right_clicked signal_right_clicked();
	protected:
		type_signal_right_clicked m_signal_right_clicked;

		virtual bool on_button_press_event(GdkEventButton *event);
	private:

};

#endif // _TASK_H_

