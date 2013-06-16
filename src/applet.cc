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
#include <boost/format.hpp>
#include <limits>       // std::numeric_limits

namespace gzz{

	Applet::Applet()
		: m_max_width(std::numeric_limits<int>::max()), 
	      m_max_height(std::numeric_limits<int>::max())
	{
	}
	
	Applet::~Applet()
	{
	}

	std::istream& Applet::xml_params_in(std::istringstream& in)
	{
		// TODO put something here //
	}
	
	std::istream& Applet::xml_body_in(std::istringstream& in)
	{
		// TODO put something here //
	}

	std::ostream& Applet::xml_params_out(std::ostream& out, bool &body_following)
	{
		body_following = false;
		out << "" << std::endl;
		return out;
	}

	Glib::ustring Applet::xml_body_out()
	{
		/*boost::format bf("<font>\n    <size>%d</size>\n    <style>%s</style>\n</font>");
		bf % m_fontsize % fontstyle.to_string();*/
		return "";
	}

	int Applet::get_max_width()
	{
		return m_max_width;
	}

	void Applet::set_max_width(int wid)
	{
		if(wid > 0){
			m_max_width = wid;
		}
	}
	
	int Applet::get_max_height()
	{
		return m_max_height;
	}
	
	void Applet::set_max_height(int hght)
	{
		if(hght > 0){
			m_max_height = hght;
		}
	}
	
	
}; // namespace gzz //

