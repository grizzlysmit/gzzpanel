// common.h
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
#ifndef _WNCK_COMMON_H_
#define _WNCK_COMMON_H_

#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>

namespace Wnck {

	class Screen;
	
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
	Wnck::Screen* wrap(WnckScreen* object/*, bool take_copy = false*/);
} // namespace Glib //

#endif // _WNCK_COMMON_H_

