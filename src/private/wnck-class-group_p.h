// private/wnck-class-group_p.h
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
#ifndef _WNCK_CLASSGROUP_P_H
#define _WNCK_CLASSGROUP_P_H

#include <glibmm/private/object_p.h>
#include <glibmm/class.h>

namespace Wnck
{

	class ClassGroup_Class : public Glib::Class
	{
		public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
			typedef ClassGroup CppObjectType;
			typedef WnckClassGroup BaseObjectType;
			typedef WnckClassGroupClass BaseClassType;
			typedef Glib::Object_Class CppClassParent;
			typedef GObjectClass BaseClassParent;

			friend class ClassGroup;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

			const Glib::Class& init();


			static void class_init_function(void* g_class, void* class_data);

			static Glib::ObjectBase* wrap_new(GObject*);

		protected:

		    //Callbacks (default signal handlers):
			//These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
			//You could prevent the original default signal handlers being called by overriding the *_impl method.
			static void icon_changed_callback(WnckClassGroup* self);
			static void name_changed_callback(WnckClassGroup* self);

		    //Callbacks (virtual functions):
			//static void dispose_vfunc_callback(GObject* self);
	};
	

} // namespace Wnck


#endif // _WNCK_CLASSGROUP_P_H //
