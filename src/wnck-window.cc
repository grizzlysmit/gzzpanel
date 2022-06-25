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
#include "private/wnck-window_p.h"

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
		WnckScreen* screen = wnck_window_get_screen(gobj());
		if(screen){
			return Glib::wrap(screen);
		}
		return nullptr;
	}

	bool Window::has_name() const
	{
		return wnck_window_has_name(const_cast<WnckWindow*>(gobj()));
	}

	const Glib::ustring Window::get_name() const
	{
		return Glib::ustring(wnck_window_get_name(const_cast<WnckWindow*>(gobj())));
	}

	bool Window::has_icon_name() const
	{
		return wnck_window_has_icon_name(const_cast<WnckWindow*>(gobj()));
	}

	const Glib::ustring Window::get_icon_name() const
	{
		return Glib::ustring(wnck_window_get_icon_name(const_cast<WnckWindow*>(gobj())));
	}

	bool Window::get_icon_is_fallback() const
	{
		return wnck_window_get_icon_is_fallback(const_cast<WnckWindow*>(gobj()));
	}

	Glib::RefPtr<Gdk::Pixbuf> Window::get_icon() const
	{
		GdkPixbuf *pb = wnck_window_get_icon(const_cast<WnckWindow*>(gobj()));
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here pb == " << pb << std::endl;
		Glib::RefPtr<Gdk::Pixbuf> result;
		try {
			result = Glib::wrap(pb, true);
			return result;
		}
		catch(...){
			//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here error caught " << std::endl;
			return Glib::RefPtr<Gdk::Pixbuf>();
		}
		return Glib::RefPtr<Gdk::Pixbuf>();
	}

	Glib::RefPtr<Gdk::Pixbuf> Window::get_mini_icon() const
	{
		GdkPixbuf *pb = wnck_window_get_mini_icon(const_cast<WnckWindow*>(gobj()));
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here pb == " << pb << std::endl;
		Glib::RefPtr<Gdk::Pixbuf> result;
		try {
			result = Glib::wrap(pb, true);
			return result;
		}
		catch(...){
			//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " got here error caught " << std::endl;
			return Glib::RefPtr<Gdk::Pixbuf>();
		}
		return Glib::RefPtr<Gdk::Pixbuf>();
	}

	Application *Window::get_application()
	{
		WnckApplication* app = wnck_window_get_application(const_cast<WnckWindow*>(gobj()));
		if(app){
			return Glib::wrap(app);
		}
		return nullptr;
	}

	bool Window::has_transient() const
	{
		// returns a NULL if there is no transient //
		return wnck_window_get_transient(const_cast<WnckWindow*>(gobj()));
	}

	Window *Window::get_transient()
	{
		WnckWindow* win =wnck_window_get_transient(gobj());
		if(win){
			return Glib::wrap(win);
		}
		return nullptr;
	}

	gulong Window::get_group_leader()
	{
		return wnck_window_get_group_leader(gobj());
	}

	gulong Window::get_xid()
	{
		return wnck_window_get_xid(gobj());
	}

	ClassGroup *Window::get_class_group()
	{
		WnckClassGroup* cg = wnck_window_get_class_group(gobj());
		/*std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				          << " middle: cg == " << cg << std::endl;*/
		if(!cg) return nullptr;
		return Glib::wrap(cg);
	}

	const Glib::ustring Window::get_class_group_name() const
	{
		return Glib::ustring(wnck_window_get_class_group_name(const_cast<WnckWindow*>(gobj())));
	}

	const Glib::ustring Window::get_class_instance_name() const
	{
		Glib::ustring result;
		const char *name = wnck_window_get_class_instance_name(const_cast<WnckWindow*>(gobj()));
		if(name){
			result = name;
		}
		return result;
	}

	bool Window::has_class_instance() const
	{
		// returns NULL if there is no class instance //
		return wnck_window_get_class_instance_name(const_cast<WnckWindow*>(gobj()));
	}

	const Glib::ustring Window::get_session_id() const
	{
		Glib::ustring result;
		const char *id = wnck_window_get_session_id(const_cast<WnckWindow*>(gobj()));
		if(id) result = id;
		return result;
	}

	const Glib::ustring Window::get_session_id_utf8() const
	{
		Glib::ustring result;
		const char *id = wnck_window_get_session_id_utf8(const_cast<WnckWindow*>(gobj()));
		if(id) result = id;
		return result;
	}

    int Window::get_pid()
	{
		return wnck_window_get_pid(gobj());
	}

	gint Window::get_sort_order() const
	{
		return wnck_window_get_sort_order(const_cast<WnckWindow*>(gobj()));
	}

	void Window::set_sort_order(gint order)
	{
		wnck_window_set_sort_order(gobj(), order);
	}

	Window::Type Window::get_window_type() const
	{
		return static_cast<Type>(wnck_window_get_window_type(const_cast<WnckWindow*>(gobj())));
	}

	void Window::set_window_type(Type wintype)
	{
		wnck_window_set_window_type(gobj(), static_cast<WnckWindowType>(wintype));
	}

	Window::State Window::get_state() const
	{
		return static_cast<State>(wnck_window_get_state(const_cast<WnckWindow*>(gobj())));
	}

	bool Window::is_minimized() const
	{
		return wnck_window_is_minimized(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_maximized_horizontally() const
	{
		return wnck_window_is_maximized_horizontally(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_maximized_vertically() const
	{
		return wnck_window_is_maximized_vertically(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_maximized() const
	{
		return wnck_window_is_maximized(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_shaded() const
	{
		return wnck_window_is_shaded(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_pinned() const
	{
		return wnck_window_is_pinned(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_sticky() const
	{
		return wnck_window_is_sticky(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_above() const
	{
		return wnck_window_is_above(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_below() const
	{
		return wnck_window_is_below(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_skip_pager() const
	{
		return wnck_window_is_skip_pager(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_skip_tasklist() const
	{
		return wnck_window_is_skip_tasklist(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_fullscreen() const
	{
		return wnck_window_is_fullscreen(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::needs_attention() const
	{
		return wnck_window_needs_attention(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::self_or_transient_needs_attention() const
	{
		return wnck_window_or_transient_needs_attention(const_cast<WnckWindow*>(gobj()));
	}

	Window::Actions Window::get_actions() const
	{
		return static_cast<Actions>(wnck_window_get_actions(const_cast<WnckWindow*>(gobj())));
	}

	void Window::minimize()
	{
		wnck_window_minimize(gobj());
	}

	void Window::unminimize(guint32 timestamp)
	{
		wnck_window_unminimize(gobj(),  timestamp);
	}

	void Window::maximize_horizontally()
	{
		wnck_window_maximize_horizontally(gobj());
	}

	void Window::unmaximize_horizontally()
	{
		wnck_window_unmaximize_horizontally(gobj());
	}

	void Window::maximize_vertically()
	{
		wnck_window_maximize_vertically(gobj());
	}

	void Window::unmaximize_vertically()
	{
		wnck_window_unmaximize_vertically(gobj());
	}

	void Window::maximize()
	{
		wnck_window_maximize(gobj());
	}

	void Window::unmaximize()
	{
		wnck_window_unmaximize(gobj());
	}

	void Window::shade()
	{
		wnck_window_shade(gobj());
	}

	void Window::unshade()
	{
		wnck_window_unshade(gobj());
	}

	void Window::pin()
	{
		wnck_window_pin(gobj());
	}

	void Window::unpin()
	{
		wnck_window_unpin(gobj());
	}

	void Window::stick()
	{
		wnck_window_stick(gobj());
	}

	void Window::unstick()
	{
		wnck_window_unstick(gobj());
	}

	void Window::make_above()
	{
		wnck_window_make_above(gobj());
	}

	void Window::unmake_above()
	{
		wnck_window_unmake_above(gobj());
	}

	void Window::make_below()
	{
		wnck_window_make_below(gobj());
	}

	void Window::unmake_below()
	{
		wnck_window_unmake_below(gobj());
	}

	void Window::set_skip_pager(bool skip)
	{
		wnck_window_set_skip_pager(gobj(), skip);
	}

	void Window::set_skip_tasklist(bool skip)
	{
		wnck_window_set_skip_tasklist(gobj(), skip);
	}

	void Window::set_fullscreen(bool fullscreen)
	{
		wnck_window_set_fullscreen(gobj(), fullscreen);
	}

	void Window::close(guint32 timestamp)
	{
		wnck_window_close(gobj(), timestamp);
	}

	Wnck::Workspace *Window::get_workspace() const
	{
		WnckWorkspace* space = wnck_window_get_workspace(const_cast<WnckWindow*>(gobj()));
		if(space){
			return Glib::wrap(space);
		}
		return nullptr;
	}

	bool Window::is_on_workspace(Wnck::Workspace &workspace) const
	{
		return wnck_window_is_on_workspace(const_cast<WnckWindow*>(gobj()), workspace.gobj());
	}

	bool Window::is_visible_on_workspace(Wnck::Workspace &workspace) const
	{
		return wnck_window_is_visible_on_workspace(const_cast<WnckWindow*>(gobj()), workspace.gobj());
	}

	void Window::move_to_workspace(Wnck::Workspace &space)
	{
		wnck_window_move_to_workspace(gobj(), space.gobj());
	}

	bool Window::is_in_viewport(Wnck::Workspace &workspace) const
	{
		return wnck_window_is_in_viewport(const_cast<WnckWindow*>(gobj()), workspace.gobj());
	}

	void Window::activate(guint32 timestamp)
	{
		wnck_window_activate(gobj(), timestamp);
	}

	bool Window::is_active() const
	{
		return wnck_window_is_active(const_cast<WnckWindow*>(gobj()));
	}

	bool Window::is_most_recently_activated() const
	{
		return wnck_window_is_most_recently_activated(const_cast<WnckWindow*>(gobj()));
	}

	void Window::activate_transient(guint32 timestamp)
	{
		wnck_window_activate_transient(gobj(), timestamp);
	}

	bool Window::transient_is_most_recently_activated() const
	{
		return wnck_window_transient_is_most_recently_activated(const_cast<WnckWindow*>(gobj()));
	}

	void Window::set_icon_geometry(int x, int y, int width, int height)
	{
		wnck_window_set_icon_geometry(gobj(),  x, y, width, height);
	}

	Window::MoveResizeMask operator|(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs)
	{
		return static_cast<Window::MoveResizeMask>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	
	Window::MoveResizeMask operator&(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs)
	{
		return static_cast<Window::MoveResizeMask>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
	
	Window::MoveResizeMask operator^(Window::MoveResizeMask lhs, Window::MoveResizeMask rhs)
	{
		return static_cast<Window::MoveResizeMask>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
	}

	void Window::get_client_window_geometry(int &x, int &y, int &width, int &height) const
	{
		wnck_window_get_client_window_geometry(const_cast<WnckWindow*>(gobj()), 
		                                       &x, &y, &width, &height);
	}

	void Window::get_geometry(int &x, int &y, int &width, int &height) const
	{
		wnck_window_get_geometry(const_cast<WnckWindow*>(gobj()), &x, &y, &width, &height);
	}

	void Window::set_geometry(Window::Gravity gravity, Window::MoveResizeMask geometry_mask,
                              int x, int y, int width, int height)
	{
		wnck_window_set_geometry(gobj(), static_cast<WnckWindowGravity>(gravity),
                                 static_cast<WnckWindowMoveResizeMask>(geometry_mask),
                                 x, y, width, height);
	}

	void Window::keyboard_move()
	{
		wnck_window_keyboard_move(gobj());
	}

	void Window::keyboard_size()
	{
		wnck_window_keyboard_size(gobj());
	}

	void Window::on_actions_changed(WnckWindowActions changed_mask, WnckWindowActions new_state)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->actions_changed)
			(*base->actions_changed)(gobj(), changed_mask, new_state);
		
	}

	void Window::on_geometry_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->geometry_changed)
			(*base->geometry_changed)(gobj());
		
	}

	void Window::on_icon_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->icon_changed)
			(*base->icon_changed)(gobj());
		
	}

	void Window::on_name_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->name_changed)
			(*base->name_changed)(gobj());
		
	}

	void Window::on_state_changed(State changed_mask, State new_state)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t entering " << std::endl;
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->state_changed)
			(*base->state_changed)(gobj(), static_cast<WnckWindowState>(changed_mask), static_cast<WnckWindowState>(new_state));
		
	}

	void Window::on_workspace_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->workspace_changed)
			(*base->workspace_changed)(gobj());
		
	}
	

	
	
}; //  namespace Wnck  //

namespace {

	static void Window_signal_actions_changed_callback(WnckWindow* self, WnckWindow* p0, WnckWindowActions p1, WnckWindowActions p2, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot< void, Window*, Wnck::Window::Actions, Wnck::Window::Actions> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0), static_cast<Wnck::Window::Actions>(p1), static_cast<Wnck::Window::Actions>(p2));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Window_signal_actions_changed_info =
	{
		"actions-changed",
		(GCallback) &Window_signal_actions_changed_callback,
		(GCallback) &Window_signal_actions_changed_callback
	};

	static const Glib::SignalProxyInfo Window_signal_geometry_changed_info =
	{
		"geometry-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo Window_signal_icon_changed_info =
	{
		"icon-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo Window_signal_name_changed_info =
	{
		"name-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static void Window_signal_state_changed_callback(WnckWindow* self, WnckWindow* p0, WnckWindowState p1, WnckWindowState p2, void* data)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t self == " << self << std::endl;
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t p0 == " << p0 << std::endl;
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t data == " << data << std::endl;
		using namespace Wnck;
		typedef sigc::slot< void, Window*, Wnck::Window::State, Wnck::Window::State> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				      << "\t self == " << self << std::endl;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data)){
					std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						      << "\t slot == " << slot << std::endl;
					(*static_cast<SlotType*>(slot))(Glib::wrap(p0), static_cast<Wnck::Window::State>(p1), static_cast<Wnck::Window::State>(p2));
				}
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Window_signal_state_changed_info =
	{
		"state-changed",
		(GCallback) &Window_signal_state_changed_callback,
		(GCallback) &Window_signal_state_changed_callback
	};

	static const Glib::SignalProxyInfo Window_signal_workspace_changed_info =
	{
		"workspace-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

}; // anonymous namespace //

namespace Wnck {

	Glib::SignalProxy3<void, Window*, Window::Actions, Window::Actions> Window::signal_actions_changed()
	{
		return Glib::SignalProxy3<void, Window*, Actions, Actions>(this, &Window_signal_actions_changed_info);
	}
	
	Glib::SignalProxy0<void> Window::signal_geometry_changed()
	{
		return Glib::SignalProxy0<void>(this, &Window_signal_geometry_changed_info);
	}
	
	Glib::SignalProxy0<void> Window::signal_icon_changed()
	{
		return Glib::SignalProxy0<void>(this, &Window_signal_icon_changed_info);
	}
	
	Glib::SignalProxy0<void> Window::signal_name_changed()
	{
		return Glib::SignalProxy0<void>(this, &Window_signal_name_changed_info);
	}

	Glib::SignalProxy3<void, Window*, Window::State, Window::State> Window::signal_state_changed()
	{
		return Glib::SignalProxy3<void, Window*, State, State>(this, &Window_signal_state_changed_info);
	}
	
	Glib::SignalProxy0<void> Window::signal_workspace_changed()
	{
		return Glib::SignalProxy0<void>(this, &Window_signal_workspace_changed_info);
	}


}; // namespace Wnck //


namespace Glib
{

	Wnck::Window* wrap(WnckWindow* object, bool take_copy)
	{
		if(object){
			return dynamic_cast<Wnck::Window*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
		}
		return nullptr;
	}

} // namespace Glib //


namespace Wnck {


	/* The *_Class implementation: */

	const Glib::Class& Window_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &Window_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_window_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:

		}

		return *this;
	}


	void Window_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//reinterpret_cast<GObjectClass*>(klass)->dispose = &dispose_vfunc_callback;

		klass->actions_changed   = &actions_changed_callback;
		klass->geometry_changed  = &geometry_changed_callback;
		klass->icon_changed      = &icon_changed_callback;
		klass->name_changed      = &name_changed_callback;
		klass->state_changed     = &state_changed_callback;
		klass->workspace_changed = &workspace_changed_callback;
		//klass->actions_changed = &actions_changed_callback;
	}


	void Window_Class::actions_changed_callback(WnckWindow* self, WnckWindowActions changed_mask, WnckWindowActions new_state)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
						      << "\t self == " << self << std::endl;
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
					obj->on_actions_changed(changed_mask, new_state);
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
		if(base && base->actions_changed)
			(*base->actions_changed)(self, changed_mask, new_state);
	}

	void Window_Class::geometry_changed_callback(WnckWindow* self)
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
					obj->on_geometry_changed();
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
		if(base && base->geometry_changed)
			(*base->geometry_changed)(self);
	}

	void Window_Class::icon_changed_callback(WnckWindow* self)
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
					obj->on_icon_changed();
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
		if(base && base->icon_changed)
			(*base->icon_changed)(self);
	}

	void Window_Class::name_changed_callback(WnckWindow* self)
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
					obj->on_name_changed();
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
		if(base && base->name_changed)
			(*base->name_changed)(self);
	}

	void Window_Class::state_changed_callback(WnckWindow* self, WnckWindowState changed_mask, WnckWindowState new_state)
	{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ 
				  << "\t self == " << self << std::endl;
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
					obj->on_state_changed(static_cast<Wnck::Window::State>(changed_mask), static_cast<Wnck::Window::State>(new_state));
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
		if(base && base->state_changed)
			(*base->state_changed)(self, changed_mask, new_state);
	}

	void Window_Class::workspace_changed_callback(WnckWindow* self)
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
					obj->on_workspace_changed();
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
		if(base && base->workspace_changed)
			(*base->workspace_changed)(self);
	}


	Glib::ObjectBase* Window_Class::wrap_new(GObject* object)
	{
		return new Window((WnckWindow*)object);
	}

	

	
	
}; // namespace Wnck //







