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

#ifndef _WNCK_WINDOW_H_
#define _WNCK_WINDOW_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "wnck-application.h"
#include "wnck-class-group.h"
#include "common.h"

namespace Wnck {

	class Window : public Glib::Object 
	{
		public:
			Window(WnckWindow* win);
			Window(gulong xwindow);
			~Window();

			///Provides access to the underlying C GtkObject.
			WnckWindow* gobj() { return reinterpret_cast<WnckWindow*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const WnckWindow* gobj() const { return reinterpret_cast<WnckWindow*>(gobject_); };

			bool is_valid_xwindow_id(gulong xwindow) const;

			// WnckWindow stuff //
			Screen *get_screen();
			bool has_name() const;
			const Glib::ustring get_name() const;
			bool has_icon_name() const;
			const Glib::ustring get_icon_name() const;
			bool get_icon_is_fallback() const;
			Glib::RefPtr<Gdk::Pixbuf> get_icon() const;
			Glib::RefPtr<Gdk::Pixbuf> get_mini_icon() const;
			Application *get_application();
			bool has_transient() const;
			Window *get_transient();
			gulong get_group_leader();
			gulong get_xid();
			ClassGroup *get_class_group();
			const Glib::ustring get_class_group_name() const;
			const Glib::ustring get_class_instance_name() const;
			bool has_class_instance() const;
		protected:

		private:

	};
	
}; //  namespace Wnck  //




#endif // _WNCK_WINDOW_H_

