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

static GdkPixbuf *load_icon_func_thunk(const char *icon_name, int size,
                                       unsigned int flags, void *data)
{
	return reinterpret_cast<Wnck::Tasklist*>(data)->signal_load_icon_emit(Glib::convert_const_gchar_ptr_to_ustring(icon_name), size, flags);
}

static void free_data_func_thunk(gpointer data)
{
}

Wnck::Tasklist::Tasklist()
  : Gtk::Container(reinterpret_cast<GtkContainer*>(wnck_tasklist_new()))
{
	wnck_tasklist_set_icon_loader(reinterpret_cast<WnckTasklist*>(gobj()),
                                  load_icon_func_thunk, this, free_data_func_thunk);
}

Wnck::Tasklist::~Tasklist()
{
}

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
	std::cout << __FILE__ << '[' << __LINE__ << "] n_elements == " << n_elements << std::endl;
	std::vector<int> result;
	for(int i = 0; i < n_elements; i++){
		result.insert(result.end(), res[i]);
	}
	return result;
}

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

void Wnck::Tasklist::on_size_allocate(Gtk::Allocation& allocation)
{
	//Do something with the space that we have actually been given:
	//(We will not be given heights or widths less than we have requested, though
	//we might get more)

	//Use the offered allocation for this container:
	set_allocation(allocation);
}

void Wnck::Tasklist::on_map()
{
	//Call base class:
	Gtk::Container::on_map();
}

void Wnck::Tasklist::on_unmap()
{
	//Call base class:
	Gtk::Container::on_unmap();
}

void Wnck::Tasklist::on_realize()
{
	//Do not call base class Gtk::Container::on_realize().
	//It's intended only for Containers that set_has_window(false).
	std::cout << __FILE__ << '[' << __LINE__ << "] get_width() == " << get_width() << std::endl;
	std::cout << __FILE__ << '[' << __LINE__ << "] get_height() == " << get_height() << std::endl;

	Gtk::Container::on_realize();
	set_realized();
	std::cout << __FILE__ << '[' << __LINE__ << "] get_width() == " << get_width() << std::endl;
	std::cout << __FILE__ << '[' << __LINE__ << "] get_height() == " << get_height() << std::endl;

}

void Wnck::Tasklist::on_unrealize()
{
  //m_refGdkWindow.reset();

  //Call base class:
  Gtk::Container::on_unrealize();
}

bool Wnck::Tasklist::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	return Gtk::Container::on_draw(cr);
}











