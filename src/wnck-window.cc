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

#include "wnck-window.h"

namespace Wnck {

	Window::Window(WnckWindow* win)
		: Glib::Object(reinterpret_cast<GObject*>(win))
	{
	}

	Window::~Window()
	{
	}

}; //  namespace Wnck  //


namespace Glib
{

	Wnck::Window* wrap(WnckWindow* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::Window*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}
	
} // namespace Glib //



