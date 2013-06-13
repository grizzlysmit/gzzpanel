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

	void Screen::change_workspace_count(int count)
	{
		wnck_screen_change_workspace_count(reinterpret_cast<WnckScreen*>(gobj()), count);
	}

	int Screen::try_set_workspace_layout(int current_token, int rows, int columns)
	{
		return wnck_screen_try_set_workspace_layout(reinterpret_cast<WnckScreen*>(gobj()), current_token, rows, columns);
	}

	void Screen::release_workspace_layout(int current_token)
	{
		wnck_screen_release_workspace_layout(reinterpret_cast<WnckScreen*>(gobj()), current_token);
	}

    void Screen::move_viewport(int x, int y)
	{
		wnck_screen_move_viewport(reinterpret_cast<WnckScreen*>(gobj()), x, y);
	}

	gulong Screen::get_background_pixmap() const
	{
		return wnck_screen_get_background_pixmap(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

	bool Screen::get_showing_desktop() const
	{
		return wnck_screen_get_showing_desktop(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
	}

	void Screen::toggle_showing_desktop(bool show)
	{
		wnck_screen_toggle_showing_desktop(reinterpret_cast<WnckScreen*>(gobj()), show);
	}
	

}; // namespace Wnck  //

namespace {

	static void Screen_signal_active_window_changed_callback(WnckScreen* self, WnckScreen* p0, WnckWindow* p1, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot< void, Screen*, Window*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0), Glib::wrap(p1));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_active_window_changed_info =
	{
		"active_window_changed",
		(GCallback) &Screen_signal_active_window_changed_callback,
		(GCallback) &Screen_signal_active_window_changed_callback
	};

	static void Screen_signal_active_workspace_changed_callback(WnckScreen* self, WnckScreen* p0, WnckWorkspace* p1, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot< void, Screen*, Workspace*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0), Glib::wrap(p1));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_active_workspace_changed_info =
	{
		"active_workspace_changed",
		(GCallback) &Screen_signal_active_workspace_changed_callback,
		(GCallback) &Screen_signal_active_workspace_changed_callback
	};

	static void Screen_signal_application_closed_callback(WnckScreen* self, WnckApplication* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Application*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_application_closed_info =
	{
		"application_closed",
		(GCallback) &Screen_signal_application_closed_callback,
		(GCallback) &Screen_signal_application_closed_callback
	};

	static void Screen_signal_application_opened_callback(WnckScreen* self, WnckApplication* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Application*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_application_opened_info =
	{
		"application_opened",
		(GCallback) &Screen_signal_application_opened_callback,
		(GCallback) &Screen_signal_application_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_background_changed_info =
	{
		"background_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static void Screen_signal_class_group_closed_callback(WnckScreen* self, WnckClassGroup* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, ClassGroup*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_class_group_closed_info =
	{
		"class_group_closed",
		(GCallback) &Screen_signal_class_group_closed_callback,
		(GCallback) &Screen_signal_class_group_closed_callback
	};

	static void Screen_signal_class_group_opened_callback(WnckScreen* self, WnckClassGroup* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, ClassGroup*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_class_group_opened_info =
	{
		"class_group_opened",
		(GCallback) &Screen_signal_class_group_opened_callback,
		(GCallback) &Screen_signal_class_group_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_showing_desktop_changed_info =
	{
		"showing_desktop_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_viewports_changed_info =
	{
		"viewports_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static void Screen_signal_window_closed_callback(WnckScreen* self, WnckWindow* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Window*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_window_closed_info =
	{
		"window_closed",
		(GCallback) &Screen_signal_window_closed_callback,
		(GCallback) &Screen_signal_window_closed_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_window_manager_changed_info =
	{
		"window_manager_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static void Screen_signal_window_opened_callback(WnckScreen* self, WnckWindow* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Window*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_window_opened_info =
	{
		"window_opened",
		(GCallback) &Screen_signal_window_opened_callback,
		(GCallback) &Screen_signal_window_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_window_stacking_changed_info =
	{
		"window_stacking_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static void Screen_signal_workspace_created_callback(WnckScreen* self, WnckWorkspace* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Workspace*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_workspace_created_info =
	{
		"workspace_created",
		(GCallback) &Screen_signal_workspace_created_callback,
		(GCallback) &Screen_signal_workspace_created_callback
	};

	static void Screen_signal_workspace_destroyed_callback(WnckScreen* self, WnckWorkspace* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void, Workspace*> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Screen_signal_workspace_destroyed_info =
	{
		"workspace_destroyed",
		(GCallback) &Screen_signal_workspace_destroyed_callback,
		(GCallback) &Screen_signal_workspace_destroyed_callback
	};

}; // anonymous namespace //

namespace Wnck {

	Glib::SignalProxy2<void, Screen*, Window*> Screen::signal_active_window_changed()
	{
		return Glib::SignalProxy2<void, Screen*, Window*>(this, &Screen_signal_active_window_changed_info);
	}

	Glib::SignalProxy2<void, Screen*, Workspace*> Screen::signal_active_workspace_changed()
	{
		return Glib::SignalProxy2<void, Screen*, Workspace*>(this, &Screen_signal_active_workspace_changed_info);
	}
	
	Glib::SignalProxy1<void, Application*> Screen::signal_application_closed()
	{
		return Glib::SignalProxy1<void, Application*>(this, &Screen_signal_application_closed_info);
	}
	
	Glib::SignalProxy1<void, Application*> Screen::signal_application_opened()
	{
		return Glib::SignalProxy1<void, Application*>(this, &Screen_signal_application_opened_info);
	}
	
	Glib::SignalProxy0<void> Screen::signal_background_changed()
	{
		return Glib::SignalProxy0<void>(this, &Screen_signal_background_changed_info);
	}
	
	Glib::SignalProxy1<void, ClassGroup*> Screen::signal_class_group_closed()
	{
		return Glib::SignalProxy1<void, ClassGroup*>(this, &Screen_signal_class_group_closed_info);
	}
	
	Glib::SignalProxy1<void, ClassGroup*> Screen::signal_class_group_opened()
	{
		return Glib::SignalProxy1<void, ClassGroup*>(this, &Screen_signal_class_group_opened_info);
	}
	
	Glib::SignalProxy0<void> Screen::signal_showing_desktop_changed()
	{
		return Glib::SignalProxy0<void>(this, &Screen_signal_showing_desktop_changed_info);
	}
	
	Glib::SignalProxy0<void> Screen::signal_viewports_changed()
	{
		return Glib::SignalProxy0<void>(this, &Screen_signal_viewports_changed_info);
	}
	
	Glib::SignalProxy1<void, Window*> Screen::signal_window_closed()
	{
		return Glib::SignalProxy1<void, Window*>(this, &Screen_signal_window_closed_info);
	}
	
	Glib::SignalProxy0<void> Screen::signal_window_manager_changed()
	{
		return Glib::SignalProxy0<void>(this, &Screen_signal_window_manager_changed_info);
	}
	
	Glib::SignalProxy1<void, Window*> Screen::signal_window_opened()
	{
		return Glib::SignalProxy1<void, Window*>(this, &Screen_signal_window_opened_info);
	}
	
	Glib::SignalProxy0<void> Screen::signal_window_stacking_changed()
	{
		return Glib::SignalProxy0<void>(this, &Screen_signal_window_stacking_changed_info);
	}
	
	Glib::SignalProxy1<void, Workspace*> Screen::signal_workspace_created()
	{
		return Glib::SignalProxy1<void, Workspace*>(this, &Screen_signal_workspace_created_info);
	}
	
	Glib::SignalProxy1<void, Workspace*> Screen::signal_workspace_destroyed()
	{
		return Glib::SignalProxy1<void, Workspace*>(this, &Screen_signal_workspace_destroyed_info);
	}
	
	
}; // namespace Wnck //


namespace Glib
{

	Wnck::Screen* wrap(WnckScreen* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::Screen*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}
	
} // namespace Glib //




