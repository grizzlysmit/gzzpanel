/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gzzpanel
 * Copyright (C) 2013 Francis (Grizzly) Smit <grizzlysmit@rakbat>
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

#ifndef _APPLET_H_
#define _APPLET_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "wnck-screen.h"

namespace gzz {

	class Applet
	{
		public:
			Applet();
			Applet(Glib::ustring _name);
			Applet(const Applet& applet) = delete;
			virtual Applet& operator=(const Applet& applet) = delete;
			~Applet();

			virtual std::istream& xml_in(std::istream& in, Applet& value);
			virtual std::ostream& xml_out(std::ostream& out, const Glib::ustring indentation);
		protected:
			Glib::ustring m_name;

		private:

	};
	
}; // namespace gzz //

#endif // _APPLET_H_

