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

#include "applet.h"

namespace gzz{

	Applet::Applet()
	{
	}

	Applet::Applet(Glib::ustring _name)
		: m_name(_name)
	{
	}

	std::istream& Applet::xml_in(std::istream& in, Applet& value)
	{
		// TODO put something here //
	}

	std::ostream& Applet::xml_out(std::ostream& out, const Glib::ustring indentation)
	{
		out << '<' << m_name << " />" << std::endl;
	}


}; // namespace gzz //

