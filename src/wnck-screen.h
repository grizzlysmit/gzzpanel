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

#ifndef _WNCK_SCREEN_H_
#define _WNCK_SCREEN_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "wnck-window.h"
#include "wnck-workspace.h"
#include "common.h"

namespace Wnck {

	class Screen : public Glib::Object 
	{
		public:
			Screen();
			Screen(int index);
			Screen(gulong root_window_id);
			~Screen();

			///Provides access to the underlying C GtkObject.
			Screen* gobj() { return reinterpret_cast<Screen*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const Screen* gobj() const { return reinterpret_cast<Screen*>(gobject_); };

			// Screen stuff //
			int get_number() const;
			int get_width() const;
			int get_height() const;
			void force_update();
			const Glib::ustring get_window_manager_name() const;
			bool net_wm_supports(const Glib::ustring &atom) const;
			Window *get_active_window() const;
			Window *get_previously_active_window() const;
			std::vector<Window*> get_windows() const;
			std::vector<Window*> get_windows_stacked() const;
			Workspace *get_active_workspace()  const;
			std::vector<Workspace*> get_workspaces() const;
			Workspace *get_workspace(int workspace) const;
			int get_workspace_count() const;
		protected:

		private:

	};
	
}; // namespace Wnck  //

#endif // _WNCK_SCREEN_H_

