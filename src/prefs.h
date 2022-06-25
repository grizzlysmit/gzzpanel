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
		Pango::Weight get_font_weight() const;
		void set_font_weight(Pango::Weight weight);
		Gdk::RGBA get_global_colour() const;
		void set_global_colour(Gdk::RGBA colour);
		Glib::ustring get_clock_font_name() const;
		void set_clock_font_name(Glib::ustring font);
		Pango::Weight get_clock_font_weight() const;
		void set_clock_font_weight(Pango::Weight weight);
		Gdk::RGBA get_clock_colour() const;
		void set_clock_colour(Gdk::RGBA colour);
		int get_HistoryLimit() const;
		void set_HistoryLimit(int hl);
		int get_DeltaX() const;
		void set_DeltaX(int hl);
		int get_DeltaClearance() const;
		void set_DeltaClearance(int hl);
		Glib::ustring get_taskbar_font_name() const;
		void set_taskbar_font_name(Glib::ustring font);
		Pango::Weight get_taskbar_font_weight() const;
		void set_taskbar_font_weight(Pango::Weight weight);
		Gdk::RGBA get_taskbar_font_colour() const;
		void set_taskbar_font_colour(Gdk::RGBA colour);
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
		Gtk::ComboBoxText* m_comboboxtextFontWeight;
		Gtk::ColorButton* m_colorbuttonPrefsFontColour;
		Gtk::FontButton* m_fontbuttonClock;
		Gtk::ComboBoxText* m_comboboxtextClockFontWeight;
		Gtk::ColorButton* m_colorbuttonClockFontColour;
		Gtk::SpinButton* m_spinbuttonHistoryLimit;
		Glib::RefPtr<Gtk::Adjustment> m_adjustmentHistoryLimit;
		Gtk::SpinButton* m_spinbuttonDeltaX;
		Glib::RefPtr<Gtk::Adjustment> m_adjustmentDeltaX;
		Gtk::SpinButton* m_spinbuttonDeltaClearance;
		Glib::RefPtr<Gtk::Adjustment> m_adjustmentDeltaClearance;
		Gtk::FontButton* m_fontbuttonTaskbar;
		Gtk::ComboBoxText* m_comboboxtextFontWeightTaskbar;
		Gtk::ColorButton* m_colorbuttonFontColourTaskbar;
		
	private:

};

#endif // _PREFS_H_

