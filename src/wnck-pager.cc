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

#include "wnck-pager.h"

Wnck::Pager::Pager()
  : Gtk::Widget(wnck_pager_new())
{
}

Wnck::Pager::~Pager()
{
}

Gtk::SizeRequestMode Wnck::Pager::get_request_mode_vfunc() const
{
	//Accept the default value supplied by the base class.
	return Gtk::Widget::get_request_mode_vfunc();
}

//Discover the total amount of minimum space and natural space needed by
//this widget.
//Let's make this simple example widget always need minimum 60 by 50 and
//natural 100 by 70.
void Wnck::Pager::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
	minimum_width = 16;
	natural_width = 32;
}

void Wnck::Pager::get_preferred_height_for_width_vfunc(int width,
                                int& minimum_height, int& natural_height) const
{
	minimum_height = 16;
	natural_height = 32;
}

void Wnck::Pager::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
	minimum_height = 16;
	natural_height = 32;
}

void Wnck::Pager::get_preferred_width_for_height_vfunc(int height,
                                int& minimum_width, int& natural_width) const
{
	minimum_width = 16;
	natural_width = 32;
}

void Wnck::Pager::on_size_allocate(Gtk::Allocation& allocation)
{
	//Do something with the space that we have actually been given:
	//(We will not be given heights or widths less than we have requested, though
	//we might get more)

	//Use the offered allocation for this container:
	set_allocation(allocation);
}

void Wnck::Pager::on_map()
{
	//Call base class:
	Gtk::Widget::on_map();
}

void Wnck::Pager::on_unmap()
{
	//Call base class:
	Gtk::Widget::on_unmap();
}

void Wnck::Pager::on_realize()
{
	//Do not call base class Gtk::Widget::on_realize().
	//It's intended only for widgets that set_has_window(false).

	set_realized();

}

void Wnck::Pager::on_unrealize()
{
  //m_refGdkWindow.reset();

  //Call base class:
  Gtk::Widget::on_unrealize();
}

bool Wnck::Pager::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	return Gtk::Widget::on_draw(cr);
}

bool Wnck::Pager::set_n_rows(int n_rows)
{
	return wnck_pager_set_n_rows(reinterpret_cast<WnckPager*>(gobj()), n_rows);
}

void Wnck::Pager::set_display_mode(DisplayMode mode)
{
	wnck_pager_set_display_mode(reinterpret_cast<WnckPager*>(gobj()), static_cast<WnckPagerDisplayMode>(mode));
}

void Wnck::Pager::set_show_all(bool show_all_workspaces)
{
	wnck_pager_set_show_all(reinterpret_cast<WnckPager*>(gobj()), show_all_workspaces);
}

void Wnck::Pager::set_shadow_type(Gtk::ShadowType shadow_type)
{
	wnck_pager_set_shadow_type(reinterpret_cast<WnckPager*>(gobj()), static_cast<GtkShadowType>(shadow_type));
}

bool Wnck::Pager::set_orientation(Gtk::Orientation orientation)
{
	wnck_pager_set_orientation(reinterpret_cast<WnckPager*>(gobj()), static_cast<GtkOrientation>(orientation));
}








