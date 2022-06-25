// wrap_init.cc
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
#include "wrap_init.h"
#include <gtkmm.h>
#include <glibmm/error.h>
#include <glibmm/object.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "wnck-window.h"
#include "wnck-workspace.h"
#include "wnck-application.h"
#include "wnck-class-group.h"
#include "common.h"
#include "wnck-screen.h"

extern "C" {


}; // extern "C" //

namespace Wnck {  class Screen_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Wnck {  class Application_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Wnck {  class Window_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Wnck {  class Workspace_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Wnck {  class ClassGroup_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }

namespace Wnck {

	void wrap_init()
	{
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
        		  << " start of fun " << std::endl;*/
		// Map gtypes to gtkmm wrapper-creation functions: //
		Glib::wrap_register(wnck_screen_get_type(), &Wnck::Screen_Class::wrap_new);
		Glib::wrap_register(wnck_application_get_type(), &Wnck::Application_Class::wrap_new);
		Glib::wrap_register(wnck_window_get_type(), &Wnck::Window_Class::wrap_new);
		Glib::wrap_register(wnck_workspace_get_type(), &Wnck::Workspace_Class::wrap_new);
		Glib::wrap_register(wnck_class_group_get_type(), &Wnck::ClassGroup_Class::wrap_new);

		// Register the gtkmm gtypes: //
		Wnck::Screen::get_type();
		Wnck::Application::get_type();
		Wnck::Window::get_type();
		Wnck::Workspace::get_type();
		Wnck::ClassGroup::get_type();
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
        		  << " end of fun " << std::endl;*/
	}  // wrap_init() //

}; // namespace Wnck //



