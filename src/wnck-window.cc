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

	Window::Window(gulong xwindow)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_window_get(xwindow)))
	{
	}

	Window::~Window()
	{
	}

	bool Window::is_valid_xwindow_id(gulong xwindow) const
	{
		try {  // not sure if it returns a NULL or throw on a bad id //
			   // either way I have it covered                       //
			return wnck_window_get(xwindow);    
		}
		catch(...){
			return false;
		}
	}

	Screen *Window::get_screen()
	{
		return Glib::wrap(wnck_window_get_screen(reinterpret_cast<WnckWindow*>(gobj())));
	}

	bool Window::has_name() const
	{
		return wnck_window_has_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
	}

	const Glib::ustring Window::get_name() const
	{
		return Glib::ustring(wnck_window_get_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	bool Window::has_icon_name() const
	{
		return wnck_window_has_icon_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
	}

	const Glib::ustring Window::get_icon_name() const
	{
		return Glib::ustring(wnck_window_get_icon_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	bool Window::get_icon_is_fallback() const
	{
		return wnck_window_get_icon_is_fallback(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
	}

	Glib::RefPtr<Gdk::Pixbuf> Window::get_icon() const
	{
		return Glib::wrap(wnck_window_get_icon(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	Glib::RefPtr<Gdk::Pixbuf> Window::get_mini_icon() const
	{
		return Glib::wrap(wnck_window_get_mini_icon(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	Application *Window::get_application()
	{
		return Glib::wrap(wnck_window_get_application(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	bool Window::has_transient() const
	{
		// returns a NULL if there is no transient //
		return wnck_window_get_transient(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
	}

	Window *Window::get_transient()
	{
		return Glib::wrap(wnck_window_get_transient(reinterpret_cast<WnckWindow*>(gobj())));
	}

	gulong Window::get_group_leader()
	{
		return wnck_window_get_group_leader(reinterpret_cast<WnckWindow*>(gobj()));
	}

	gulong Window::get_xid()
	{
		return wnck_window_get_xid(reinterpret_cast<WnckWindow*>(gobj()));
	}

	ClassGroup *Window::get_class_group()
	{
		return Glib::wrap(wnck_window_get_class_group(reinterpret_cast<WnckWindow*>(gobj())));
	}

	const Glib::ustring Window::get_class_group_name() const
	{
		return Glib::ustring(wnck_window_get_class_group_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj()))));
	}

	const Glib::ustring Window::get_class_instance_name() const
	{
		Glib::ustring result;
		const char *name = wnck_window_get_class_instance_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
		if(name){
			result = name;
		}
		return result;
	}

	bool Window::has_class_instance() const
	{
		// returns NULL if there is no class instance //
		return wnck_window_get_class_instance_name(const_cast<WnckWindow*>(reinterpret_cast<const WnckWindow*>(gobj())));
	}
	
}; //  namespace Wnck  //


namespace Glib
{

	Wnck::Window* wrap(WnckWindow* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::Window*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}

} // namespace Glib //



