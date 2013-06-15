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

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "wnck-pager.h"
//#include "taskbar.h"
#include "wnck-screen.h"
#include "wnck-tasklist.h"

class Main_window: public Gtk::Window 
{
	public:
		Main_window(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
		~Main_window();

	protected:
		const Glib::RefPtr<Gtk::Builder>& m_builder;

		// the components //
		Gtk::Button *m_buttonMenu;
		Gtk::Menu *m_menuPanel;
		Gtk::ImageMenuItem *m_imagemenuitemExit;
		Gtk::Label *m_labelClock;
		Gtk::Label *m_labelDate;
		Gtk::Box *m_boxDeskTop;
		Wnck::Pager *m_pagerDeskTop;
		//Taskbar *m_buttonboxTaskBar;
		Gtk::Box *m_boxTaskBar;
		Wnck::Tasklist *m_taskbar;

		//std::vector<Gtk::Button*> DesktopButtons;
		//std::vector<Gtk::DrawingArea*> DesktopDrawingAreas;
		 Glib::RefPtr<Gtk::IconTheme> m_icontheme;

		Glib::ustring m_clockformat;
		Glib::ustring m_dateformat;
		
		// timer connection //
		sigc::connection m_conn;

		// virtual destop stuff //
		int m_desktop_rows;
		int m_desktop_cols;
		Glib::RefPtr<Gdk::Screen> m_refscreen;
		Wnck::Screen *m_wnck_screen;
		unsigned long long m_counter;
		
		// a time out handler  //
		bool on_timeout();
		
		// callbacks //
		void on_button_Menu();
		void on_menuitem_Exit();
		void on_popup_menu_position(int& x, int& y, bool& push_in);
		GdkPixbuf* on_load_icon(const Glib::ustring& icon_name, int size, unsigned flags);
		void on_window_mapped();
		void on_allocate(Gtk::Allocation& allocation);

		// ancillary //
		void setup_desktops();
	private:

};

#endif // _MAINWINDOW_H_

