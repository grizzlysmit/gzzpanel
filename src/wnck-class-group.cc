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

#include "wnck-class-group.h"
#include "private/wnck-class-group_p.h"

namespace Wnck {

	ClassGroup::ClassGroup(WnckClassGroup *cg)
		: Glib::Object(reinterpret_cast<GObject*>(cg))
	{
	}

	ClassGroup::ClassGroup(const Glib::ustring &id)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_class_group_get(id.c_str())))
	{
	}

	ClassGroup::~ClassGroup()
	{
	}

	bool ClassGroup::class_group_id_valid(const Glib::ustring &id) const
	{
		return wnck_class_group_get(id.c_str());
	}

	const Glib::ustring ClassGroup::get_id() const
	{
		return Glib::ustring(wnck_class_group_get_id(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	const Glib::ustring ClassGroup::get_name() const
	{
		return Glib::ustring(wnck_class_group_get_name(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	Glib::RefPtr<Gdk::Pixbuf> ClassGroup::get_icon() const
	{
		return Glib::wrap(wnck_class_group_get_icon(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))), true);
	}

	Glib::RefPtr<Gdk::Pixbuf> ClassGroup::get_mini_icon() const
	{
		return Glib::wrap(wnck_class_group_get_mini_icon(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))), true);
	}

	std::vector<Window*> ClassGroup::get_windows()
	{
		std::vector<Window*> result;
		GList *lst = wnck_class_group_get_windows(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj())));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWindow*>(i->data)));
		}
		return result;
	}
	
	void ClassGroup::on_icon_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->icon_changed)
			(*base->icon_changed)(gobj());
	}

	void ClassGroup::on_name_changed()
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->name_changed)
			(*base->name_changed)(gobj());
	}



}; // namespace Wnck //

namespace {

	static const Glib::SignalProxyInfo ClassGroup_signal_icon_changed_info =
	{
		"icon-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo ClassGroup_signal_name_changed_info =
	{
		"name-changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};


}; // anonymous namespace  //

namespace Wnck {

	Glib::SignalProxy0<void> ClassGroup::signal_icon_changed()
	{
		return Glib::SignalProxy0<void>(this, &ClassGroup_signal_icon_changed_info);
	}

	Glib::SignalProxy0<void> ClassGroup::signal_name_changed()
	{
		return Glib::SignalProxy0<void>(this, &ClassGroup_signal_name_changed_info);
	}
	
}; // namespace Wnck //


namespace Glib
{

	Wnck::ClassGroup* wrap(WnckClassGroup* object, bool take_copy)
	{
		if(object){
			return dynamic_cast<Wnck::ClassGroup*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), take_copy));
		}
		return nullptr;
	}
	
} // namespace Glib //



namespace Wnck {


	/* The *_Class implementation: */

	const Glib::Class& ClassGroup_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &ClassGroup_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_class_group_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:

		}

		return *this;
	}


	void ClassGroup_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//reinterpret_cast<GObjectClass*>(klass)->dispose = &dispose_vfunc_callback;

		klass->icon_changed = &icon_changed_callback;
		klass->name_changed = &name_changed_callback;
	}


	void ClassGroup_Class::icon_changed_callback(WnckClassGroup* self)
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

	void ClassGroup_Class::name_changed_callback(WnckClassGroup* self)
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


	Glib::ObjectBase* ClassGroup_Class::wrap_new(GObject* object)
	{
		return new ClassGroup((WnckClassGroup*)object);
	}

	

	
	
}; // namespace Wnck //







