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

#ifndef _WNCK_SCREEN_P_H
#define _WNCK_SCREEN_P_H

#include <glibmm/private/object_p.h>
#include <glibmm/class.h>

namespace Wnck
{

	class Screen_Class : public Glib::Class
	{
		public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
			typedef Screen CppObjectType;
			typedef WnckScreen BaseObjectType;
			typedef WnckScreenClass BaseClassType;
			typedef Glib::Object_Class CppClassParent;
			typedef GObjectClass BaseClassParent;

			friend class Screen;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

			const Glib::Class& init();


			static void class_init_function(void* g_class, void* class_data);

			static Glib::ObjectBase* wrap_new(GObject*);

		protected:

		    //Callbacks (default signal handlers):
			//These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
			//You could prevent the original default signal handlers being called by overriding the *_impl method.
			static void active_window_changed_callback(WnckScreen* self, WnckWindow* window);
			static void active_workspace_changed_callback(WnckScreen* self, WnckWorkspace* space);
			static void application_closed_callback(WnckScreen* self, WnckApplication* application);
			static void application_opened_callback(WnckScreen* self, WnckApplication* application);
			static void background_changed_callback(WnckScreen* self);
			static void class_group_closed_callback(WnckScreen* self, WnckClassGroup *class_group);
			static void class_group_opened_callback(WnckScreen* self, WnckClassGroup *class_group);
			static void showing_desktop_changed_callback(WnckScreen* self);
			static void viewports_changed_callback(WnckScreen* self);
			static void window_closed_callback(WnckScreen* self, WnckWindow* window);
			static void window_manager_changed_callback(WnckScreen* self);
			static void window_opened_callback(WnckScreen* self, WnckWindow* window);
			static void window_stacking_changed_callback(WnckScreen* self);
			static void workspace_created_callback(WnckScreen* self, WnckWorkspace* space);
			static void workspace_destroyed_callback(WnckScreen* self, WnckWorkspace* space);

		    //Callbacks (virtual functions):
			//static void dispose_vfunc_callback(GObject* self);
	};
	

} // namespace Wnck


#endif // _WNCK_SCREEN_P_H //

