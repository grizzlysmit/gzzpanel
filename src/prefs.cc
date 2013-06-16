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

#include "prefs.h"

Prefs::Prefs(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Dialog(cobject), m_builder(builder), 
    m_fontbuttonPrefesGlobal(0) 
{
	// m_fontbuttonPrefesGlobal //
	m_builder->get_widget("fontbuttonPrefesGlobal", m_fontbuttonPrefesGlobal);
	if(m_fontbuttonPrefesGlobal){
		//m_fontbuttonPrefesGlobal->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
		m_fontbuttonPrefesGlobal->set_use_font(true);
	}
}

Prefs::~Prefs()
{
}

Glib::ustring Prefs::get_font_name() const
{
	return m_fontbuttonPrefesGlobal->get_font_name();
}



