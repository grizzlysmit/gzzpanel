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

#ifndef _PREFS_H_
#define _PREFS_H_
#include <gtkmm.h>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "lvt.h"

class Prefs: public Gtk::Dialog 
{
	public:
		Prefs(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
		~Prefs();

		Glib::ustring get_font_name() const;
		void set_font_name(Glib::ustring font);
		int get_min_button_size() const;
		void set_min_button_size(int sz);
		Glib::ustring get_entryTimeFormatTopln() const;
		void set_entryTimeFormatTopln(Glib::ustring format);
		Glib::ustring get_entryTimeFormatBottomln() const;
		void set_entryTimeFormatBottomln(Glib::ustring format);
	protected:
		const Glib::RefPtr<Gtk::Builder>& m_builder;

		// gui stuff in the ui file //
		Gtk::FontButton *m_fontbuttonPrefesGlobal;
		Gtk::SpinButton *m_spinbuttonMinTaskWidth;
		Glib::RefPtr<Gtk::Adjustment> m_adjustmentMinTaskWidth;
		Gtk::Entry *m_entryTimeFormatTopln;
		Gtk::Entry *m_entryTimeFormatBottomln;
		Gtk::ScrolledWindow *m_scrolledwindowPrefsClockHelp;
		LVT* m_lvtPrefsClockHelp;
	private:

};

#endif // _PREFS_H_

