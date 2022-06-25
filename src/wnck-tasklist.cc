/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gzzpanel
 * Copyright (C) 2013 Francis (Grizzly) Smit <grizzlysmit@rakbat>
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

#include "wnck-tasklist.h"
#include "private/wnck-tasklist_p.h"
#include <glib.h>
#include <gtk/gtk.h>

static GdkPixbuf *load_icon_func_thunk(const char *icon_name, int size,
                                       unsigned int flags, void *data)
{
	return reinterpret_cast<Wnck::Tasklist*>(data)->signal_load_icon_emit(Glib::convert_const_gchar_ptr_to_ustring(icon_name), size, flags);
}

static void free_data_func_thunk(gpointer data)
{
}
/*
Wnck::Tasklist::Tasklist()
  : Gtk::Container(reinterpret_cast<GtkContainer*>(wnck_tasklist_new()))
{
	wnck_tasklist_set_icon_loader(reinterpret_cast<WnckTasklist*>(gobj()),
                                  load_icon_func_thunk, this, free_data_func_thunk);
}
*/
/*Wnck::Tasklist::~Tasklist()
{
}
*/
void Wnck::Tasklist::set_grouping(GroupingType grouping)
{
	wnck_tasklist_set_grouping(reinterpret_cast<WnckTasklist*>(gobj()), static_cast<WnckTasklistGroupingType>(grouping));
}

void Wnck::Tasklist::set_grouping_limit(gint limit)
{
	wnck_tasklist_set_grouping_limit(reinterpret_cast<WnckTasklist*>(gobj()), limit);
}

void Wnck::Tasklist::set_include_all_workspaces(bool include_all_workspaces)
{
	wnck_tasklist_set_include_all_workspaces(reinterpret_cast<WnckTasklist*>(gobj()), include_all_workspaces);
}

void Wnck::Tasklist::set_switch_workspace_on_unminimize(bool switch_workspace_on_unminimize)
{
	wnck_tasklist_set_switch_workspace_on_unminimize(reinterpret_cast<WnckTasklist*>(gobj()), switch_workspace_on_unminimize);
}

void Wnck::Tasklist::set_button_relief(Gtk::ReliefStyle relief)
{
	wnck_tasklist_set_button_relief(reinterpret_cast<WnckTasklist*>(gobj()), static_cast<GtkReliefStyle>(relief));
}

Wnck::Tasklist::type_signal_load_icon Wnck::Tasklist::signal_load_icon()
{
	return m_signal_load_icon;
}

GdkPixbuf* Wnck::Tasklist::signal_load_icon_emit(const Glib::ustring icon_name, int size, unsigned flags)
{
	return m_signal_load_icon.emit(icon_name, size, flags);
}


const std::vector<int> Wnck::Tasklist::get_size_hint_list()
{
	int n_elements;
	const int *res = wnck_tasklist_get_size_hint_list(reinterpret_cast<WnckTasklist*>(gobj()), &n_elements);
	//std::cout << __FILE__ << '[' << __LINE__ << "] n_elements == " << n_elements << std::endl;
	std::vector<int> result;
	for(int i = 0; i < n_elements; i++){
		result.insert(result.end(), res[i]);
	}
	return result;
}
/*
Gtk::SizeRequestMode Wnck::Tasklist::get_request_mode_vfunc() const
{
	//Accept the default value supplied by the base class.
	return Gtk::Container::get_request_mode_vfunc();
}

//Discover the total amount of minimum space and natural space needed by
//this Container.
//Let's make this simple example Container always need minimum 60 by 50 and
//natural 100 by 70.
void Wnck::Tasklist::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
	minimum_width = 800;
	natural_width = 1024;
}

void Wnck::Tasklist::get_preferred_height_for_width_vfunc(int width,
                                int& minimum_height, int& natural_height) const
{
	minimum_height = 36;
	natural_height = 38;
}

void Wnck::Tasklist::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
	minimum_height = 36;
	natural_height = 38;
}

void Wnck::Tasklist::get_preferred_width_for_height_vfunc(int height,
                                int& minimum_width, int& natural_width) const
{
	minimum_width = 800;
	natural_width = 1024;
}
*/
void Wnck::Tasklist::on_size_allocate(Gtk::Allocation& allocation)
{
	//Do something with the space that we have actually been given:
	//(We will not be given heights or widths less than we have requested, though
	//we might get more)

	//Use the offered allocation for this container:
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	m_signal_allocation.emit(allocation);
	set_allocation(allocation);
}

Wnck::Tasklist::type_signal_allocation Wnck::Tasklist::signal_allocation()
{
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	return m_signal_allocation;
}

void Wnck::Tasklist::on_map()
{
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	//Call base class:
	Gtk::Container::on_map();
}

void Wnck::Tasklist::on_unmap()
{
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	//Call base class:
	Gtk::Container::on_unmap();
}

void Wnck::Tasklist::on_realize()
{
	//Do not call base class Gtk::Container::on_realize().
	//It's intended only for Containers that set_has_window(false).
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << __FILE__ << '[' << __LINE__ << "] get_width() == " << get_width() << std::endl;
	//std::cout << __FILE__ << '[' << __LINE__ << "] get_height() == " << get_height() << std::endl;

	Gtk::Container::on_realize();
	set_realized();
	//std::cout << __FILE__ << '[' << __LINE__ << "] get_width() == " << get_width() << std::endl;
	//std::cout << __FILE__ << '[' << __LINE__ << "] get_height() == " << get_height() << std::endl;

}

void Wnck::Tasklist::on_unrealize()
{
	//m_refGdkWindow.reset();
	//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;


	//Call base class:
	Gtk::Container::on_unrealize();
}

bool Wnck::Tasklist::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	return Gtk::Container::on_draw(cr);
}


namespace {

	


}; // anonymous namespace //


namespace Glib {

	Wnck::Tasklist* wrap(WnckTasklist* object, bool take_copy)
	{
		return dynamic_cast<Wnck::Tasklist *> (Glib::wrap_auto ((GObject*)(object), take_copy));
	}
	
} /* namespace Glib */

namespace Wnck {

	/* The *_Class implementation: */

	const Glib::Class& Tasklist_Class::init()
	{
		if(!gtype_) // create the GType if necessary
		{
			// Glib::Class has to know the class init function to clone custom types.
			class_init_func_ = &Tasklist_Class::class_init_function;

			// This is actually just optimized away, apparently with no harm.
			// Make sure that the parent type has been created.
			//CppClassParent::CppObjectType::get_type();

			// Create the wrapper type, with the same class/instance size as the base type.
			register_derived_type(wnck_tasklist_get_type());

			// Add derived versions of interfaces, if the C type implements any interfaces:
			Gtk::ToolShell::add_interface(get_type());

		}

		return *this;
	}


	void Tasklist_Class::class_init_function(void* g_class, void* class_data)
	{
		BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
		CppClassParent::class_init_function(klass, class_data);

		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;

		//reinterpret_cast<CppClassParent::CppClassParent::BaseClassType*>(klass)->size_allocate = &size_allocate_callback;
		//klass->orientation_changed = &orientation_changed_callback;
		//klass->style_changed = &style_changed_callback;
		//klass->popup_context_menu = &popup_context_menu_callback;
	}



	Glib::ObjectBase* Tasklist_Class::wrap_new(GObject* o)
	{
		return manage(new Tasklist((WnckTasklist*)(o)));

	}


	/* The implementation: */

	Tasklist::Tasklist(const Glib::ConstructParams& construct_params)
		:
		Gtk::Container(construct_params)
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		wnck_tasklist_set_icon_loader(reinterpret_cast<WnckTasklist*>(gobj()),
		                              load_icon_func_thunk, this, free_data_func_thunk);
	}

	Tasklist::Tasklist(WnckTasklist* castitem)
		:
	Gtk::Container((GtkContainer*)(castitem))
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		wnck_tasklist_set_icon_loader(reinterpret_cast<WnckTasklist*>(gobj()),
		                              load_icon_func_thunk, this, free_data_func_thunk);
	}

	Tasklist::~Tasklist()
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		destroy_();
	}

	Tasklist::CppClassType Tasklist::tasklist_class_; // initialize static member

	GType Tasklist::get_type()
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		return tasklist_class_.init().get_type();
	}


	GType Tasklist::get_base_type()
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		return wnck_tasklist_get_type();
	}


	Tasklist::Tasklist()
		:
		// Mark this class as non-derived to allow C++ vfuncs to be skipped.
		Glib::ObjectBase(0),
		Gtk::Container(Glib::ConstructParams(tasklist_class_.init()))
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		wnck_tasklist_set_icon_loader(reinterpret_cast<WnckTasklist*>(gobj()),
		                              load_icon_func_thunk, this, free_data_func_thunk);
	}

/*	void Tasklist::insert(ToolItem& item, int pos)
	{
		gtk_Tasklist_insert(gobj(), (item).gobj(), pos); 
	}

		int Tasklist::get_item_index(const ToolItem& item) const
	{
		return gtk_Tasklist_get_item_index(const_cast<WnckTasklist*>(gobj()), const_cast<GtkToolItem*>((item).gobj()));
	}

		int Tasklist::get_n_items() const
	{
		return gtk_Tasklist_get_n_items(const_cast<WnckTasklist*>(gobj()));
	}

		ToolItem* Tasklist::get_nth_item(int n)
	{
		return Glib::wrap(gtk_Tasklist_get_nth_item(gobj(), n));
	}

		const ToolItem* Tasklist::get_nth_item(int n) const
	{
		return const_cast<Tasklist*>(this)->get_nth_item(n);
	}

		bool Tasklist::get_show_arrow() const
	{
		return gtk_Tasklist_get_show_arrow(const_cast<WnckTasklist*>(gobj()));
	}

		void Tasklist::set_show_arrow(bool show_arrow)
	{
		gtk_Tasklist_set_show_arrow(gobj(), static_cast<int>(show_arrow)); 
	}

		void Tasklist::set_Tasklist_style(TasklistStyle style)
	{
		gtk_Tasklist_set_style(gobj(), ((WnckTasklistStyle)(style))); 
	}

		TasklistStyle Tasklist::get_Tasklist_style() const
	{
		return ((TasklistStyle)(gtk_Tasklist_get_style(const_cast<WnckTasklist*>(gobj()))));
	}

		void Tasklist::unset_Tasklist_style()
	{
		gtk_Tasklist_unset_style(gobj()); 
	}

		void Tasklist::set_icon_size(IconSize icon_size)
	{
		gtk_Tasklist_set_icon_size(gobj(), static_cast<GtkIconSize>(int(icon_size))); 
	}

		void Tasklist::unset_icon_size()
	{
		gtk_Tasklist_unset_icon_size(gobj()); 
	}

		IconSize Tasklist::get_icon_size() const
	{
		return IconSize(static_cast<int>(gtk_Tasklist_get_icon_size(const_cast<WnckTasklist*>(gobj()))));
	}

		ReliefStyle Tasklist::get_relief_style() const
	{
		return ((ReliefStyle)(gtk_Tasklist_get_relief_style(const_cast<WnckTasklist*>(gobj()))));
	}

		int Tasklist::get_drop_index(int x, int y) const
	{
		return gtk_Tasklist_get_drop_index(const_cast<WnckTasklist*>(gobj()), x, y);
	}

		void Tasklist::set_drop_highlight_item(ToolItem& tool_item, int index)
	{
		gtk_Tasklist_set_drop_highlight_item(gobj(), (tool_item).gobj(), index); 
	}*/


/*		Glib::SignalProxy1< void,Orientation > Tasklist::signal_orientation_changed()
	{
		return Glib::SignalProxy1< void,Orientation >(this, &Tasklist_signal_orientation_changed_info);
	}


		Glib::SignalProxy1< void,TasklistStyle > Tasklist::signal_Tasklist_style_changed()
	{
		return Glib::SignalProxy1< void,TasklistStyle >(this, &Tasklist_signal_Tasklist_style_changed_info);
	}


		Glib::SignalProxy3< bool,int,int,int > Tasklist::signal_popup_context_menu()
	{
		return Glib::SignalProxy3< bool,int,int,int >(this, &Tasklist_signal_popup_context_menu_info);
	}
*/

/*#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy<TasklistStyle> Tasklist::property_tasklist_style() 
	{
		return Glib::PropertyProxy<TasklistStyle>(this, "Tasklist-style");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy_ReadOnly<TasklistStyle> Tasklist::property_tasklist_style() const
	{
		return Glib::PropertyProxy_ReadOnly<TasklistStyle>(this, "tasklist-style");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy<bool> Tasklist::property_show_arrow() 
	{
		return Glib::PropertyProxy<bool>(this, "show-arrow");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy_ReadOnly<bool> Tasklist::property_show_arrow() const
	{
		return Glib::PropertyProxy_ReadOnly<bool>(this, "show-arrow");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy<IconSize> Tasklist::property_icon_size() 
	{
		return Glib::PropertyProxy<IconSize>(this, "icon-size");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy_ReadOnly<IconSize> Tasklist::property_icon_size() const
	{
		return Glib::PropertyProxy_ReadOnly<IconSize>(this, "icon-size");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy<bool> Tasklist::property_icon_size_set() 
	{
		return Glib::PropertyProxy<bool>(this, "icon-size-set");
	}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
		Glib::PropertyProxy_ReadOnly<bool> Tasklist::property_icon_size_set() const
	{
		return Glib::PropertyProxy_ReadOnly<bool>(this, "icon-size-set");
	}
#endif //GLIBMM_PROPERTIES_ENABLED


	void Gtk::Tasklist::on_orientation_changed(Orientation orientation)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->orientation_changed)
			(*base->orientation_changed)(gobj(),((GtkOrientation)(orientation)));
	}
	void Gtk::Tasklist::on_Tasklist_style_changed(TasklistStyle style)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->style_changed)
			(*base->style_changed)(gobj(),((WnckTasklistStyle)(style)));
	}
	bool Gtk::Tasklist::on_popup_context_menu(int x, int y, int button_number)
	{
		BaseClassType *const base = static_cast<BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		if(base && base->popup_context_menu)
			return (*base->popup_context_menu)(gobj(),x,y,button_number);

		typedef bool RType;
		return RType();
	}
*/

	void Tasklist_Class::size_allocate_callback(GtkWidget* self, GdkRectangle* p0)
	{
		//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
		Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(
		                                                                  Glib::ObjectBase::_get_current_wrapper((GObject*)self));

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
					obj->on_size_allocate((Gtk::Allocation&)(Glib::wrap(p0))
					                      );
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

		CppClassParent::CppClassParent::BaseClassType *const base = static_cast<CppClassParent::CppClassParent::BaseClassType*>(
		                                                        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
		                                                        );

		// Call the original underlying C function:
		if(base && base->size_allocate){
			//std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << std::endl;
			(*base->size_allocate)(self, p0);
		}
	}
		


		

}; // namespace Wnck //





