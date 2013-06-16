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

#ifndef _WNCK_APPLICATION_H_
#define _WNCK_APPLICATION_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "common.h"

namespace Wnck {

	class Application : public Glib::Object 
	{
		public:
			Application(WnckApplication* app);
			Application(gulong xwindow);
			~Application();

			///Provides access to the underlying C GtkObject.
			WnckApplication* gobj() { return reinterpret_cast<WnckApplication*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const WnckApplication* gobj() const { return reinterpret_cast<WnckApplication*>(gobject_); };

			// Application stuff //
			gulong get_xid();
			const Glib::ustring get_name() const;
			const Glib::ustring get_icon_name() const;
			int get_pid();
			bool get_icon_is_fallback() const;
			Glib::RefPtr<Gdk::Pixbuf> get_icon() const;
			Glib::RefPtr<Gdk::Pixbuf> get_mini_icon() const;
			const Glib::ustring get_startup_id() const;
			std::vector<Window*> get_windows();
			int get_n_windows() const;
			Glib::SignalProxy0<void> signal_icon_changed();
			Glib::SignalProxy0<void> signal_name_changed();
		protected:

		private:

	};
	
}; // namespace Wnck //

namespace Glib
{
	/** A Glib::wrap() method for this object.
		* 
	 * @param object The C instance.
	 * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
	 * @result A C++ instance that wraps this C instance.
	 *
	 * @relates Gtk::AboutDialog
	 */
	Wnck::Application* wrap(WnckApplication* object/*, bool take_copy = false*/);

} // namespace Glib //


#endif // _WNCK_APPLICATION_H_

