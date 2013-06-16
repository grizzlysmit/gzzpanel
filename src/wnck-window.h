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

#ifndef _WNCK_WINDOW_H_
#define _WNCK_WINDOW_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include "wnck-application.h"
#include "wnck-class-group.h"
#include "common.h"

namespace Wnck {

	class Window : public Glib::Object 
	{
		public:
			enum Type {
				NORMAL       = WNCK_WINDOW_NORMAL,       /* document/app window */
				DESKTOP      = WNCK_WINDOW_DESKTOP,      /* desktop background */
				DOCK         = WNCK_WINDOW_DOCK,         /* panel */
				DIALOG       = WNCK_WINDOW_DIALOG,       /* dialog */
				TOOLBAR      = WNCK_WINDOW_TOOLBAR,      /* tearoff toolbar */
				MENU         = WNCK_WINDOW_MENU,         /* tearoff menu */
				UTILITY      = WNCK_WINDOW_UTILITY,      /* palette/toolbox window */
				SPLASHSCREEN = WNCK_WINDOW_SPLASHSCREEN  /* splash screen */
			};

			enum State {
				STATE_MINIMIZED              = WNCK_WINDOW_STATE_MINIMIZED,
				STATE_MAXIMIZED_HORIZONTALLY = WNCK_WINDOW_STATE_MAXIMIZED_HORIZONTALLY,
				STATE_MAXIMIZED_VERTICALLY   = WNCK_WINDOW_STATE_MAXIMIZED_VERTICALLY,
				STATE_SHADED                 = WNCK_WINDOW_STATE_SHADED,
				STATE_SKIP_PAGER             = WNCK_WINDOW_STATE_SKIP_PAGER,
				STATE_SKIP_TASKLIST          = WNCK_WINDOW_STATE_SKIP_TASKLIST,
				STATE_STICKY                 = WNCK_WINDOW_STATE_STICKY,
				STATE_HIDDEN                 = WNCK_WINDOW_STATE_HIDDEN,
				STATE_FULLSCREEN             = WNCK_WINDOW_STATE_FULLSCREEN,
				STATE_DEMANDS_ATTENTION      = WNCK_WINDOW_STATE_DEMANDS_ATTENTION,
				STATE_URGENT                 = WNCK_WINDOW_STATE_URGENT,
				STATE_ABOVE                  = WNCK_WINDOW_STATE_ABOVE,
				STATE_BELOW                  = WNCK_WINDOW_STATE_BELOW
			};

			enum Actions {
				ACTION_MOVE                    = WNCK_WINDOW_ACTION_MOVE,
				ACTION_RESIZE                  = WNCK_WINDOW_ACTION_RESIZE,
				ACTION_SHADE                   = WNCK_WINDOW_ACTION_SHADE,
				ACTION_STICK                   = WNCK_WINDOW_ACTION_STICK,
				ACTION_MAXIMIZE_HORIZONTALLY   = WNCK_WINDOW_ACTION_MAXIMIZE_HORIZONTALLY,
				ACTION_MAXIMIZE_VERTICALLY     = WNCK_WINDOW_ACTION_MAXIMIZE_VERTICALLY,
				ACTION_CHANGE_WORKSPACE        = WNCK_WINDOW_ACTION_CHANGE_WORKSPACE, /* includes pin/unpin */
				ACTION_CLOSE                   = WNCK_WINDOW_ACTION_CLOSE,
				ACTION_UNMAXIMIZE_HORIZONTALLY = WNCK_WINDOW_ACTION_UNMAXIMIZE_HORIZONTALLY,
				ACTION_UNMAXIMIZE_VERTICALLY   = WNCK_WINDOW_ACTION_UNMAXIMIZE_VERTICALLY,
				ACTION_UNSHADE                 = WNCK_WINDOW_ACTION_UNSHADE,
				ACTION_UNSTICK                 = WNCK_WINDOW_ACTION_UNSTICK,
				ACTION_MINIMIZE                = WNCK_WINDOW_ACTION_MINIMIZE,
				ACTION_UNMINIMIZE              = WNCK_WINDOW_ACTION_UNMINIMIZE,
				ACTION_MAXIMIZE                = WNCK_WINDOW_ACTION_MAXIMIZE,
				ACTION_UNMAXIMIZE              = WNCK_WINDOW_ACTION_UNMAXIMIZE,
				ACTION_FULLSCREEN              = WNCK_WINDOW_ACTION_FULLSCREEN,
				ACTION_ABOVE                   = WNCK_WINDOW_ACTION_ABOVE,
				ACTION_BELOW                   = WNCK_WINDOW_ACTION_BELOW
			};

			
			Window(WnckWindow* win);
			Window(gulong xwindow);
			~Window();

			///Provides access to the underlying C GtkObject.
			WnckWindow* gobj() { return reinterpret_cast<WnckWindow*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const WnckWindow* gobj() const { return reinterpret_cast<WnckWindow*>(gobject_); };

			bool is_valid_xwindow_id(gulong xwindow) const;

			// WnckWindow stuff //
			Screen *get_screen();
			bool has_name() const;
			const Glib::ustring get_name() const;
			bool has_icon_name() const;
			const Glib::ustring get_icon_name() const;
			bool get_icon_is_fallback() const;
			Glib::RefPtr<Gdk::Pixbuf> get_icon() const;
			Glib::RefPtr<Gdk::Pixbuf> get_mini_icon() const;
			Application *get_application();
			bool has_transient() const;
			Window *get_transient();
			gulong get_group_leader();
			gulong get_xid();
			ClassGroup *get_class_group();
			const Glib::ustring get_class_group_name() const;
			const Glib::ustring get_class_instance_name() const;
			bool has_class_instance() const;
			const Glib::ustring get_session_id() const;
			const Glib::ustring get_session_id_utf8() const;
			int get_pid();
			gint get_sort_order() const;
			void set_sort_order(gint order);
			Type get_window_type() const;
			void set_window_type(Type wintype);
			State get_state() const;
			bool is_minimized() const;
			bool is_maximized_horizontally() const;
			bool is_maximized_vertically() const;
			bool is_maximized() const;
			bool is_shaded() const;
			bool is_pinned() const;
			bool is_sticky() const;
			bool is_above() const;
			bool is_below() const;
			bool is_skip_pager() const;
			bool is_skip_tasklist() const;
			bool is_fullscreen() const;
			bool needs_attention() const;
			bool self_or_transient_needs_attention() const;
			Actions get_actions() const;
			void minimize();
			void unminimize(guint32 timestamp);
			void maximize_horizontally();
			void unmaximize_horizontally();
			void maximize_vertically();
			void unmaximize_vertically();
			void maximize();
		protected:

		private:

	};
	
}; //  namespace Wnck  //




#endif // _WNCK_WINDOW_H_

