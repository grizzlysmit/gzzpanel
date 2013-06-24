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
#include "private/wnck-screen_p.h"
#include <gtkmm/widget.h>
#include <gtk/gtk.h>

namespace Wnck {

	Screen::Screen()
		: Glib::Object(reinterpret_cast<GObject*>(wnck_screen_get_default()))
	{
	}

	Screen::Screen(WnckScreen *screen)
		: Glib::Object(reinterpret_cast<GObject*>(screen))
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
		WnckWindow* win = wnck_screen_get_active_window(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		if(win){
			return Glib::wrap(win);
		}
		return nullptr;
	}

	Window *Screen::get_previously_active_window() const
	{
		WnckWindow* win = wnck_screen_get_previously_active_window(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		if(win){
			return Glib::wrap(win);
		}
		return nullptr;
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
		WnckWorkspace* space = wnck_screen_get_active_workspace(const_cast<WnckScreen*>(reinterpret_cast<const WnckScreen*>(gobj())));
		if(space){
			return Glib::wrap(space);
		}
		return nullptr;
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

	void Screen::on_active_window_changed(Window* window)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->active_window_changed)
			(*base->active_window_changed)(gobj(), window->gobj());
		
	}

	void Screen::on_active_workspace_changed(Workspace* space)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->active_workspace_changed)
			(*base->active_workspace_changed)(gobj(), space->gobj());
		
	}

	void Screen::on_application_closed(Application* application)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->application_closed)
			(*base->application_closed)(gobj(), application->gobj());
		
	}

	void Screen::on_application_opened(Application* application)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->application_opened)
			(*base->application_opened)(gobj(), application->gobj());
		
	}

	void Screen::on_background_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->background_changed)
			(*base->background_changed)(gobj());
		
	}

	void Screen::on_class_group_closed(ClassGroup* class_group)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->class_group_closed)
			(*base->class_group_closed)(gobj(), class_group->gobj());
		
	}

	void Screen::on_class_group_opened(ClassGroup* class_group)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->class_group_opened)
			(*base->class_group_opened)(gobj(), class_group->gobj());
		
	}

	void Screen::on_showing_desktop_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here " << std::endl;
		if(base && base->showing_desktop_changed)
			(*base->showing_desktop_changed)(gobj());
	}

	void Screen::on_viewports_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here " << std::endl;
		if(base && base->viewports_changed)
			(*base->viewports_changed)(gobj());
	}

	void Screen::on_window_closed(Window* window)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->window_closed)
			(*base->window_closed)(gobj(), window->gobj());
		
	}

	void Screen::on_window_manager_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->window_manager_changed)
			(*base->window_manager_changed)(gobj());
		
	}

	void Screen::on_window_opened(Window* window)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->window_opened)
			(*base->window_opened)(gobj(), window->gobj());
		
	}

	void Screen::on_window_stacking_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->window_stacking_changed)
			(*base->window_stacking_changed)(gobj());
		
	}

	void Screen::on_workspace_created(Workspace* space)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->workspace_created)
			(*base->workspace_created)(gobj(), space->gobj());
		
	}

	void Screen::on_workspace_destroyed(Workspace* space)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->workspace_destroyed)
			(*base->workspace_destroyed)(gobj(), space->gobj());
		
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
		"active-window-changed",
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
		"active-workspace-changed",
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
		"application-closed",
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
		"application-opened",
		(GCallback) &Screen_signal_application_opened_callback,
		(GCallback) &Screen_signal_application_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_background_changed_info =
	{
		"background-changed",
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
		"class-group-closed",
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
		"class-group-opened",
		(GCallback) &Screen_signal_class_group_opened_callback,
		(GCallback) &Screen_signal_class_group_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_showing_desktop_changed_info =
	{
		"showing-desktop-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_viewports_changed_info =
	{
		"viewports-changed",
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
		"window-closed",
		(GCallback) &Screen_signal_window_closed_callback,
		(GCallback) &Screen_signal_window_closed_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_window_manager_changed_info =
	{
		"window-manager-changed",
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
		"window-opened",
		(GCallback) &Screen_signal_window_opened_callback,
		(GCallback) &Screen_signal_window_opened_callback
	};

	static const Glib::SignalProxyInfo Screen_signal_window_stacking_changed_info =
	{
		"window-stacking-changed",
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
		"workspace-created",
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
		"workspace-destroyed",
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

	Wnck::Screen* wrap(WnckScreen* object, bool take_copy)
	{
		if(object){
			return dynamic_cast<Wnck::Screen*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
		}
		return nullptr;
	}
	
} // namespace Glib //


namespace Wnck {


	/* The *_Class implementation: */

	const Glib::Class& Screen_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &Screen_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_screen_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:

		}

		return *this;
	}


	void Screen_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//reinterpret_cast<GObjectClass*>(klass)->dispose = &dispose_vfunc_callback;

		klass->active_window_changed    = &active_window_changed_callback;
		klass->active_workspace_changed = &active_workspace_changed_callback;
		klass->application_closed       = &application_closed_callback;
		klass->application_opened       = &application_opened_callback;
		klass->background_changed       = &background_changed_callback;
		klass->class_group_closed       = &class_group_closed_callback;
		klass->class_group_opened       = &class_group_opened_callback;
		klass->showing_desktop_changed  = &showing_desktop_changed_callback;
		klass->viewports_changed        = &viewports_changed_callback;
		klass->window_closed            = &window_closed_callback;
		klass->window_manager_changed   = &window_manager_changed_callback;
		klass->window_opened            = &window_opened_callback;
		klass->window_stacking_changed  = &window_stacking_changed_callback;
		klass->workspace_created        = &workspace_created_callback;
		klass->workspace_destroyed      = &workspace_destroyed_callback;
	}


	void Screen_Class::active_window_changed_callback(WnckScreen* self, WnckWindow* window)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_active_window_changed(Glib::wrap(window));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->active_window_changed)
			(*base->active_window_changed)(self, window);
	}
	
	void Screen_Class::active_workspace_changed_callback(WnckScreen* self, WnckWorkspace* space)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_active_workspace_changed(Glib::wrap(space));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->active_workspace_changed)
			(*base->active_workspace_changed)(self, space);
	}

	void Screen_Class::application_closed_callback(WnckScreen* self, WnckApplication* application)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_application_closed(Glib::wrap(application));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->application_closed)
			(*base->application_closed)(self, application);
	}

	void Screen_Class::application_opened_callback(WnckScreen* self, WnckApplication* application)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_application_opened(Glib::wrap(application));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->application_opened)
			(*base->application_opened)(self, application);
	}

	void Screen_Class::background_changed_callback(WnckScreen* self)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_background_changed();
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->background_changed)
			(*base->background_changed)(self);
	}

	void Screen_Class::class_group_closed_callback(WnckScreen* self, WnckClassGroup* class_group)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_class_group_closed(Glib::wrap(class_group));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->class_group_closed)
			(*base->class_group_closed)(self, class_group);
	}

	void Screen_Class::class_group_opened_callback(WnckScreen* self, WnckClassGroup* class_group)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_class_group_opened(Glib::wrap(class_group));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->class_group_opened)
			(*base->class_group_opened)(self, class_group);
	}


	void Screen_Class::showing_desktop_changed_callback(WnckScreen* self)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_showing_desktop_changed();
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->showing_desktop_changed)
			(*base->showing_desktop_changed)(self);
	}

	void Screen_Class::viewports_changed_callback(WnckScreen* self)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here " << std::endl;

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_viewports_changed();
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->viewports_changed)
			(*base->viewports_changed)(self);
	}

	void Screen_Class::window_closed_callback(WnckScreen* self, WnckWindow* window)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_window_closed(Glib::wrap(window));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->window_closed)
			(*base->window_closed)(self, window);
	}

	void Screen_Class::window_manager_changed_callback(WnckScreen* self)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_window_manager_changed();
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->window_manager_changed)
			(*base->window_manager_changed)(self);
	}

	void Screen_Class::window_opened_callback(WnckScreen* self, WnckWindow* window)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_window_opened(Glib::wrap(window));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->window_opened)
			(*base->window_opened)(self, window);
	}

	void Screen_Class::window_stacking_changed_callback(WnckScreen* self)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_window_stacking_changed();
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->window_stacking_changed)
			(*base->window_stacking_changed)(self);
	}

	void Screen_Class::workspace_created_callback(WnckScreen* self, WnckWorkspace* space)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_workspace_created(Glib::wrap(space));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->workspace_created)
			(*base->workspace_created)(self, space);
	}

	void Screen_Class::workspace_destroyed_callback(WnckScreen* self, WnckWorkspace* space)
	{
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));

		// Non-gtkmmproc-generated custom classes implicitly call the default
		// Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
		// generated classes can use this optimisation, which avoids the unnecessary
		// parameter conversions if there is no possibility of the virtual function
		// being overridden:
		if(obj_base && obj_base->is_derived_())
		{
			CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
			if(obj) // This can be NULL during destruction.
			{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				try // Trap C++ exceptions which would normally be lost because this is a C callback.
				{
#endif //GLIBMM_EXCEPTIONS_ENABLED
					// Call the virtual member method, which derived classes might override.
					obj->on_workspace_destroyed(Glib::wrap(space));
					return;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
				}
				catch(...)
				{
					Glib::exception_handlers_invoke();
				}
#endif //GLIBMM_EXCEPTIONS_ENABLED
			}
		}

		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->workspace_destroyed)
			(*base->workspace_destroyed)(self, space);
	}


	Glib::ObjectBase* Screen_Class::wrap_new(GObject* object)
	{
		return new Screen((WnckScreen*)object);
	}

	

	
	
}; // namespace Wnck //











