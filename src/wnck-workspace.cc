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

#include "wnck-workspace.h"
#include "private/wnck-workspace_p.h"

namespace Wnck {

	Workspace::Workspace(WnckWorkspace* space)
		: Glib::Object(reinterpret_cast<GObject*>(space))
	{
	}

	Workspace::~Workspace()
	{
	}

	Screen *Workspace::get_screen()
	{
		return Glib::wrap(wnck_workspace_get_screen(reinterpret_cast<WnckWorkspace*>(gobj())));
	}

	int Workspace::get_number() const
	{
		return wnck_workspace_get_number(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	const Glib::ustring Workspace::get_name() const
	{
		return wnck_workspace_get_name(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	void Workspace::change_name(const Glib::ustring &name)
	{
		wnck_workspace_change_name(reinterpret_cast<WnckWorkspace*>(gobj()), name.c_str());
	}

	int Workspace::get_width() const
	{
		return wnck_workspace_get_width(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	int Workspace::get_height() const
	{
		return wnck_workspace_get_height(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	int Workspace::get_viewport_x() const
	{
		return wnck_workspace_get_viewport_x(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	int Workspace::get_viewport_y() const
	{
		return wnck_workspace_get_viewport_y(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	bool Workspace::is_virtual() const
	{
		return wnck_workspace_is_virtual(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	int Workspace::get_layout_row() const
	{
		return wnck_workspace_get_layout_row(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	int Workspace::get_layout_column() const
	{
		return wnck_workspace_get_layout_column(const_cast<WnckWorkspace*>(reinterpret_cast<const WnckWorkspace*>(gobj())));
	}

	Workspace *Workspace::get_neighbor(MotionDirection direction)
	{
		return Glib::wrap(wnck_workspace_get_neighbor(reinterpret_cast<WnckWorkspace*>(gobj()), static_cast<WnckMotionDirection>(direction)));
	}

	void Workspace::activate(guint32 timestamp)
	{
		wnck_workspace_activate(reinterpret_cast<WnckWorkspace*>(gobj()), timestamp);
	}

	void Workspace::on_name_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->name_changed)
			(*base->name_changed)(gobj());
		
	}


	
}; // namespace Wnck //

namespace {
	
	static void Workspace_signal_name_changed_callback(WnckWorkspace* self, WnckWorkspace* p0, void* data)
	{
		using namespace Wnck;
		typedef sigc::slot< void, Workspace* > SlotType;

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

	static const Glib::SignalProxyInfo Workspace_signal_name_changed_info =
	{
		"name-changed",
		(GCallback) &Workspace_signal_name_changed_callback,
		(GCallback) &Workspace_signal_name_changed_callback
	};

}; // anonymous namespace //

namespace Wnck {

	Glib::SignalProxy1<void,Workspace*> Workspace::signal_name_changed()
	{
		return Glib::SignalProxy1<void, Workspace*>(this, &Workspace_signal_name_changed_info);
	}
	
	

}; // namespace Wnck //


namespace Glib
{

	Wnck::Workspace* wrap(WnckWorkspace* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::Workspace*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}

} // namespace Glib //



namespace Wnck {


	/* The *_Class implementation: */

	const Glib::Class& Workspace_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &Workspace_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_workspace_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:

		}

		return *this;
	}


	void Workspace_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//reinterpret_cast<GObjectClass*>(klass)->dispose = &dispose_vfunc_callback;

		klass->name_changed = &name_changed_callback;
	}


	void Workspace_Class::name_changed_callback(WnckWorkspace* self)
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


	Glib::ObjectBase* Workspace_Class::wrap_new(GObject* object)
	{
		return new Workspace((WnckWorkspace*)object);
	}

	

	
	
}; // namespace Wnck //














