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

#include "wnck-screen.h"

namespace Wnck {

	Screen::Screen()
		: Glib::Object(reinterpret_cast<GObject*>(wnck_screen_get_default()))
	{
	}

	Screen::Screen(int index)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_screen_get(index)))
	{
	}

	Screen::Screen(gulong root_window_id)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_screen_get_for_root(root_window_id)))
	{
	}

	Screen::~Screen()
	{
	}

	int Screen::get_number() const
	{
		return wnck_screen_get_number(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

	int Screen::get_width() const
	{
		return wnck_screen_get_width(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

	int Screen::get_height() const
	{
		return wnck_screen_get_height(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

	void Screen::force_update()
	{
		wnck_screen_force_update(reinterpret_cast<WnckScreen*>(gobj()));
	}

	const Glib::ustring Screen::get_window_manager_name() const
	{
		Glib::ustring result;
		const char *res = wnck_screen_get_window_manager_name(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		if(res){
			result = res;
		}
		return result;
	}

	bool Screen::net_wm_supports(const Glib::ustring &atom) const
	{
		return wnck_screen_net_wm_supports(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())), atom.c_str());
	}

	Window *Screen::get_active_window() const
	{
		return Glib::wrap(wnck_screen_get_active_window(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj()))));
	}

	Window *Screen::get_previously_active_window() const
	{
		return Glib::wrap(wnck_screen_get_previously_active_window(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj()))));
	}

	std::vector<Window*> Screen::get_windows() const
	{
		std::vector<Window*> result;
		GList * lst = wnck_screen_get_windows(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWindow*>(i->data)));
		}
		return result;
	}

	std::vector<Window*> Screen::get_windows_stacked() const
	{
		std::vector<Window*> result;
		GList * lst = wnck_screen_get_windows_stacked(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWindow*>(i->data)));
		}
		return result;
	}

	Workspace *Screen::get_active_workspace() const
	{
		return Glib::wrap(wnck_screen_get_active_workspace(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj()))));
	}

	std::vector<Workspace*> Screen::get_workspaces() const
	{
		std::vector<Workspace*> result;
		GList *lst = wnck_screen_get_workspaces(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWorkspace*>(i->data)));
		}
		return result;
	}

	Workspace *Screen::get_workspace(int workspace) const
	{
		return Glib::wrap(wnck_screen_get_workspace(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())), workspace));
	}

	int Screen::get_workspace_count() const
	{
		return wnck_screen_get_workspace_count(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

}; // namespace Wnck  //


namespace Glib
{

	Wnck::Screen* wrap(WnckScreen* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::Screen*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}
	
} // namespace Glib //




