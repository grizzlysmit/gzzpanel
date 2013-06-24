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

#include "wnck-application.h"
#include "private/wnck-application_p.h"

namespace Wnck {

	Application::Application(WnckApplication* app)
		: Glib::Object(reinterpret_cast<GObject*>(app))
	{
	}

	Application::Application(gulong xwindow)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_application_get(xwindow)))
	{
	}

	Application::~Application()
	{
	}

	gulong Application::get_xid()  
	{
		return wnck_application_get_xid(reinterpret_cast<WnckApplication*>(gobj()));
	}

	const Glib::ustring Application::get_name() const
	{
		return Glib::ustring(wnck_application_get_name(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj()))));
	}

	const Glib::ustring Application::get_icon_name() const
	{
		return Glib::ustring(wnck_application_get_icon_name(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj()))));
	}

	int Application::get_pid()
	{
		return wnck_application_get_pid(reinterpret_cast<WnckApplication*>(gobj()));
	}

	bool Application::get_icon_is_fallback() const
	{
		return wnck_application_get_icon_is_fallback(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj())));
	}

	Glib::RefPtr<Gdk::Pixbuf> Application::get_icon() const
	{
		return Glib::wrap(wnck_application_get_icon(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj()))));
	}

	Glib::RefPtr<Gdk::Pixbuf> Application::get_mini_icon() const
	{
		return Glib::wrap(wnck_application_get_mini_icon(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj()))));
	}

	const Glib::ustring Application::get_startup_id() const
	{
		return Glib::ustring(wnck_application_get_startup_id(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj()))));
	}

	std::vector<Window*> Application::get_windows()
	{
		std::vector<Window*> result;
		GList *lst = wnck_application_get_windows(reinterpret_cast<WnckApplication*>(gobj()));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWindow*>(i->data)));
		}
		return result;
	}

	int Application::get_n_windows() const
	{
		return wnck_application_get_n_windows(const_cast<WnckApplication*>(reinterpret_cast<const WnckApplication*>(gobj())));
	}

	void Application::on_name_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->name_changed)
			(*base->name_changed)(gobj());
	}

	void Application::on_icon_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->icon_changed)
			(*base->icon_changed)(gobj());
	}

}; // namespace Wnck //


namespace {

	static void Application_signal_name_changed_callback(WnckApplication* self, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))();
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Application_signal_name_changed_info =
	{
		"name-changed",
		(GCallback) &Application_signal_name_changed_callback,
		(GCallback) &Application_signal_name_changed_callback
	};

	static void Application_signal_icon_changed_callback(WnckApplication* self, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot<void> SlotType;

		// Do not try to call a signal on a disassociated wrapper.
		if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
		{
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			try {
#endif //GLIBMM_EXCEPTIONS_ENABLED
				if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
					(*static_cast<SlotType*>(slot))();
#ifdef GLIBMM_EXCEPTIONS_ENABLED
			}
			catch(...)
			{
				Glib::exception_handlers_invoke();
			}
#endif //GLIBMM_EXCEPTIONS_ENABLED
		}
	}

	static const Glib::SignalProxyInfo Application_signal_icon_changed_info =
	{
		"icon-changed",
		(GCallback) &Application_signal_icon_changed_callback,
		(GCallback) &Application_signal_icon_changed_callback
	};

}; // anonymous namespace //

namespace Wnck {

	Glib::SignalProxy0<void> Application::signal_name_changed()
	{
		return Glib::SignalProxy0<void>(this, &Application_signal_name_changed_info);
	}

	Glib::SignalProxy0<void> Application::signal_icon_changed()
	{
		return Glib::SignalProxy0<void>(this, &Application_signal_icon_changed_info);
	}
	
	
}; // namespace Wnck //


namespace Glib
{

	Wnck::Application* wrap(WnckApplication* object, bool take_copy)
	{
		if(object){
			return dynamic_cast<Wnck::Application*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), take_copy));
		}
		return nullptr;
	}
	
} // namespace Glib //



namespace Wnck {


	/* The *_Class implementation: */

	const Glib::Class& Application_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &Application_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_application_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:

		}

		return *this;
	}


	void Application_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//reinterpret_cast<GObjectClass*>(klass)->dispose = &dispose_vfunc_callback;

		klass->name_changed = &name_changed_callback;
		klass->icon_changed = &icon_changed_callback;
	}


	void Application_Class::name_changed_callback(WnckApplication* self)
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

	void Application_Class::icon_changed_callback(WnckApplication* self)
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


	Glib::ObjectBase* Application_Class::wrap_new(GObject* object)
	{
		return new Application((WnckApplication*)object);
	}

	

	
	
}; // namespace Wnck //





