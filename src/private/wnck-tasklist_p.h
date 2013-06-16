// private/wnck-tasklist_p.h
//
// Copyright (C) 2013 - Francis (Grizzly) Smit
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef _WNCK_TASKLIST_P_H
#define _WNCK_TASKLIST_P_H

#include <gtkmm/private/container_p.h>

#include <glibmm/class.h>


namespace Wnck
{

	class Tasklist_Class : public Glib::Class
	{
		public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
			typedef Tasklist CppObjectType;
			typedef WnckTasklist BaseObjectType;
			typedef WnckTasklistClass BaseClassType;
			typedef Gtk::Container_Class CppClassParent;
			typedef GtkContainerClass BaseClassParent;

			friend class Tasklist;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

			const Glib::Class& init();


			static void class_init_function(void* g_class, void* class_data);
			static void size_allocate_callback(GtkWidget* self, GdkRectangle* p0);

			static Glib::ObjectBase* wrap_new(GObject*);

		protected:

		//Callbacks (default signal handlers):
			//These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
			//You could prevent the original default signal handlers being called by overriding the *_impl method.
			//static void style_changed_callback(WnckTasklist* self, WnckTasklistStyle p0);
			//static gboolean popup_context_menu_callback(WnckTasklist* self, gint p0, gint p1, gint p2);

		//Callbacks (virtual functions):
	};

	
} // namespace Wnck


#endif /* _WNCK_TASKLIST_P_H */
