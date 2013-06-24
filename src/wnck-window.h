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
#include "wnck-workspace.h"

namespace Wnck {

	class Window : public Glib::Object 
	{
		public:
			typedef Window CppObjectType;
			typedef Window_Class CppClassType;
			typedef WnckWindow BaseObjectType;
			typedef WnckWindowClass BaseClassType;
			
			enum class Type {
				NORMAL       = WNCK_WINDOW_NORMAL,       /* document/app window */
				DESKTOP      = WNCK_WINDOW_DESKTOP,      /* desktop background */
				DOCK         = WNCK_WINDOW_DOCK,         /* panel */
				DIALOG       = WNCK_WINDOW_DIALOG,       /* dialog */
				TOOLBAR      = WNCK_WINDOW_TOOLBAR,      /* tearoff toolbar */
				MENU         = WNCK_WINDOW_MENU,         /* tearoff menu */
				UTILITY      = WNCK_WINDOW_UTILITY,      /* palette/toolbox window */
				SPLASHSCREEN = WNCK_WINDOW_SPLASHSCREEN  /* splash screen */
			};

			enum class State {
				MINIMIZED              = WNCK_WINDOW_STATE_MINIMIZED,
				MAXIMIZED_HORIZONTALLY = WNCK_WINDOW_STATE_MAXIMIZED_HORIZONTALLY,
				MAXIMIZED_VERTICALLY   = WNCK_WINDOW_STATE_MAXIMIZED_VERTICALLY,
				SHADED                 = WNCK_WINDOW_STATE_SHADED,
				SKIP_PAGER             = WNCK_WINDOW_STATE_SKIP_PAGER,
				SKIP_TASKLIST          = WNCK_WINDOW_STATE_SKIP_TASKLIST,
				STICKY                 = WNCK_WINDOW_STATE_STICKY,
				HIDDEN                 = WNCK_WINDOW_STATE_HIDDEN,
				FULLSCREEN             = WNCK_WINDOW_STATE_FULLSCREEN,
				DEMANDS_ATTENTION      = WNCK_WINDOW_STATE_DEMANDS_ATTENTION,
				URGENT                 = WNCK_WINDOW_STATE_URGENT,
				ABOVE                  = WNCK_WINDOW_STATE_ABOVE,
				BELOW                  = WNCK_WINDOW_STATE_BELOW
			};

			enum class Actions {
				MOVE                    = WNCK_WINDOW_ACTION_MOVE,
				RESIZE                  = WNCK_WINDOW_ACTION_RESIZE,
				SHADE                   = WNCK_WINDOW_ACTION_SHADE,
				STICK                   = WNCK_WINDOW_ACTION_STICK,
				MAXIMIZE_HORIZONTALLY   = WNCK_WINDOW_ACTION_MAXIMIZE_HORIZONTALLY,
				MAXIMIZE_VERTICALLY     = WNCK_WINDOW_ACTION_MAXIMIZE_VERTICALLY,
				CHANGE_WORKSPACE        = WNCK_WINDOW_ACTION_CHANGE_WORKSPACE, /* includes pin/unpin */
				CLOSE                   = WNCK_WINDOW_ACTION_CLOSE,
				UNMAXIMIZE_HORIZONTALLY = WNCK_WINDOW_ACTION_UNMAXIMIZE_HORIZONTALLY,
				UNMAXIMIZE_VERTICALLY   = WNCK_WINDOW_ACTION_UNMAXIMIZE_VERTICALLY,
				UNSHADE                 = WNCK_WINDOW_ACTION_UNSHADE,
				UNSTICK                 = WNCK_WINDOW_ACTION_UNSTICK,
				MINIMIZE                = WNCK_WINDOW_ACTION_MINIMIZE,
				UNMINIMIZE              = WNCK_WINDOW_ACTION_UNMINIMIZE,
				MAXIMIZE                = WNCK_WINDOW_ACTION_MAXIMIZE,
				UNMAXIMIZE              = WNCK_WINDOW_ACTION_UNMAXIMIZE,
				FULLSCREEN              = WNCK_WINDOW_ACTION_FULLSCREEN,
				ABOVE                   = WNCK_WINDOW_ACTION_ABOVE,
				BELOW                   = WNCK_WINDOW_ACTION_BELOW
			};

			enum class Gravity {
				CURRENT   = WNCK_WINDOW_GRAVITY_CURRENT,
				NORTHWEST = WNCK_WINDOW_GRAVITY_NORTHWEST,
				NORTH     = WNCK_WINDOW_GRAVITY_NORTH,
				NORTHEAST = WNCK_WINDOW_GRAVITY_NORTHEAST,
				WEST      = WNCK_WINDOW_GRAVITY_WEST,
				CENTER    = WNCK_WINDOW_GRAVITY_CENTER,
				EAST      = WNCK_WINDOW_GRAVITY_EAST,
				SOUTHWEST = WNCK_WINDOW_GRAVITY_SOUTHWEST,
				SOUTH     = WNCK_WINDOW_GRAVITY_SOUTH,
				SOUTHEAST = WNCK_WINDOW_GRAVITY_SOUTHEAST,
				STATIC    = WNCK_WINDOW_GRAVITY_STATIC
			};

			enum class MoveResizeMask {
				CHANGE_X              = WNCK_WINDOW_CHANGE_X,
				CHANGE_Y              = WNCK_WINDOW_CHANGE_Y,
				CHANGE_X_Y            = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_Y,
				CHANGE_WIDTH          = WNCK_WINDOW_CHANGE_WIDTH,
				CHANGE_X_WIDTH        = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_WIDTH,
				CHANGE_Y_WIDTH        = WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_WIDTH,
				CHANGE_X_Y_WIDTH      = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_WIDTH,
				CHANGE_HEIGHT         = WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_X_HEIGHT       = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_Y_HEIGHT       = WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_X_Y_HEIGHT     = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_WIDTH_HEIGHT   = WNCK_WINDOW_CHANGE_WIDTH|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_X_WIDTH_HEIGHT = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_WIDTH|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_Y_WIDTH_HEIGHT = WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_WIDTH|WNCK_WINDOW_CHANGE_HEIGHT,
				CHANGE_ALL            = WNCK_WINDOW_CHANGE_X|WNCK_WINDOW_CHANGE_Y|WNCK_WINDOW_CHANGE_WIDTH|WNCK_WINDOW_CHANGE_HEIGHT,
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
			void unmaximize();
			void shade();
			void unshade();
			void pin();
			void unpin();
			void stick();
			void unstick();
			void make_above();
			void unmake_above();
			void make_below();
			void unmake_below();
			void set_skip_pager(bool skip = true);
			void set_skip_tasklist(bool skip = true);
			void set_fullscreen(bool fullscreen = true);
			void close(guint32 timestamp);
			Wnck::Workspace *get_workspace() const;
			bool is_on_workspace(Wnck::Workspace &workspace) const;
			bool is_visible_on_workspace(Wnck::Workspace &workspace) const;
			void move_to_workspace(Wnck::Workspace &space);
			bool is_in_viewport(Wnck::Workspace &workspace) const;
			void activate(guint32 timestamp);
			bool is_active() const;
			bool is_most_recently_activated() const;
			void activate_transient(guint32 timestamp);
			bool transient_is_most_recently_activated() const;
			void set_icon_geometry(int x, int y, int width, int height);
			void get_client_window_geometry(int &x, int &y, int &width, int &height) const;
			void get_geometry(int &x, int &y, int &width, int &height) const;
			void set_geometry(Gravity gravity, MoveResizeMask geometry_mask,
                              int x, int y, int width, int height);
			void keyboard_move();
			void keyboard_size();
			Glib::SignalProxy3<void, Window*, Actions, Actions> signal_actions_changed();
			Glib::SignalProxy0<void> signal_geometry_changed();
			Glib::SignalProxy0<void> signal_icon_changed();
			Glib::SignalProxy0<void> signal_name_changed();
			Glib::SignalProxy3<void, Window*, State, State> signal_state_changed();
			Glib::SignalProxy0<void> signal_workspace_changed();
		protected:
			void on_actions_changed(WnckWindowActions changed_mask, WnckWindowActions new_state);
			void on_geometry_changed();
			void on_icon_changed();
			void on_name_changed();
			void on_state_changed(State changed_mask, State new_state);
			void on_workspace_changed();

		private:
			friend class Window_Class;

	};
	
	Window::MoveResizeMask operator|(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs);
	
	Window::MoveResizeMask operator&(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs);
	
	Window::MoveResizeMask operator^(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs);

	
	
}; //  namespace Wnck  //




#endif // _WNCK_WINDOW_H_

