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

#ifndef _WNCK_WORKSPACE_H_
#define _WNCK_WORKSPACE_H_
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

	class Workspace: public Glib::Object 
	{
		public:
			typedef Workspace CppObjectType;
			typedef Workspace_Class CppClassType;
			typedef WnckWorkspace BaseObjectType;
			typedef WnckWorkspaceClass BaseClassType;
			
			enum MotionDirection {
				MOTION_UP = WNCK_MOTION_UP,
				MOTION_DOWN = WNCK_MOTION_DOWN,
				MOTION_LEFT = WNCK_MOTION_LEFT,
				MOTION_RIGHT = WNCK_MOTION_RIGHT
			};
			
			Workspace(WnckWorkspace* space);
			~Workspace();

			///Provides access to the underlying C GtkObject.
			WnckWorkspace* gobj() { return reinterpret_cast<WnckWorkspace*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const WnckWorkspace* gobj() const { return reinterpret_cast<WnckWorkspace*>(gobject_); };

			// the Workspace problem //
			Screen *get_screen();
			int get_number() const;
			const Glib::ustring get_name() const;
			void change_name(const Glib::ustring &name);
			int get_width() const;
			int get_height() const;
			int get_viewport_x() const;
			int get_viewport_y() const;
			bool is_virtual() const;
			int get_layout_row() const;
			int get_layout_column() const;
			Workspace *get_neighbor(MotionDirection direction);
			void activate(guint32 timestamp);
			Glib::SignalProxy1<void, Workspace*> signal_name_changed();
		protected:
			void on_name_changed();

		private:
			friend class Workspace_Class;

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
	Wnck::Workspace* wrap(WnckWorkspace* object/*, bool take_copy = false*/);
} // namespace Glib //


#endif // _WNCK_WORKSPACE_H_

