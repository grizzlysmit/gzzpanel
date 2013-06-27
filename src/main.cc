/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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

#include <gtkmm.h>
#include <iostream>

#include "config.h"
#include "mainwindow.h"


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif
#include "wrap_init.h"



/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/gzzpanel.ui" */
#define UI_FILE "src/gzzpanel.ui"

   
int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	Wnck::wrap_init();
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
        		  << " after Wnck::wrap_init() " << std::endl;


	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	//Gtk::Window* main_win = 0;
	Main_window* main_win = nullptr;
	//builder->get_widget("main_window", main_win);
	builder->get_widget_derived("main_window", main_win);

	main_win->set_progname(basename(argv[0]));
	main_win->set_up_config_file();
	main_win->apply_defaults();


	if(main_win)
	{
		kit.run(*main_win);
	}
	return 0;
}

