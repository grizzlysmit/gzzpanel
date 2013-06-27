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
#include <ios>

Prefs::Prefs(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Dialog(cobject), m_builder(builder), 
    m_fontbuttonPrefesGlobal(nullptr), m_spinbuttonMinTaskWidth(nullptr), 
    m_entryTimeFormatTopln(nullptr), m_entryTimeFormatBottomln(nullptr), 
    m_scrolledwindowPrefsClockHelp(nullptr), m_lvtPrefsClockHelp(nullptr), 
    m_comboboxtextFontWeight(nullptr), m_colorbuttonPrefsFontColour(nullptr), 
    m_fontbuttonClock(nullptr), m_comboboxtextClockFontWeight(nullptr), 
    m_colorbuttonClockFontColour(nullptr)
{
	// m_fontbuttonPrefesGlobal //
	m_builder->get_widget("fontbuttonPrefesGlobal", m_fontbuttonPrefesGlobal);
	if(m_fontbuttonPrefesGlobal){
		//m_fontbuttonPrefesGlobal->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
		m_fontbuttonPrefesGlobal->set_use_font(true);
	}
	// m_comboboxtextFontWeight //
	m_builder->get_widget("comboboxtextFontWeight", m_comboboxtextFontWeight);
	if(m_comboboxtextFontWeight){
		//m_comboboxtextFontWeight->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_colorbuttonPrefsFontColour //
	m_builder->get_widget("colorbuttonPrefsFontColour", m_colorbuttonPrefsFontColour);
	if(m_colorbuttonPrefsFontColour){
		//m_colorbuttonPrefsFontColour->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}

	// Taskbar stuff //
	// m_spinbuttonMinTaskWidth //
	m_builder->get_widget("spinbuttonMinTaskWidth", m_spinbuttonMinTaskWidth);
	if(m_spinbuttonMinTaskWidth){
		//m_spinbuttonMinTaskWidth->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
		m_adjustmentMinTaskWidth = m_spinbuttonMinTaskWidth->get_adjustment();
	}

	// clock stuff //
	// m_entryTimeFormatTopln //
	m_builder->get_widget("entryTimeFormatTopln", m_entryTimeFormatTopln);
	if(m_entryTimeFormatTopln){
		//m_entryTimeFormatTopln->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_entryTimeFormatBottomln //
	m_builder->get_widget("entryTimeFormatBottomln", m_entryTimeFormatBottomln);
	if(m_entryTimeFormatBottomln){
		//m_entryTimeFormatBottomln->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_scrolledwindowPrefsClockHelp //
	m_builder->get_widget("scrolledwindowPrefsClockHelp", m_scrolledwindowPrefsClockHelp);
	if(m_scrolledwindowPrefsClockHelp){
		//m_scrolledwindowPrefsClockHelp->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
		m_lvtPrefsClockHelp = new LVT(2);
		m_scrolledwindowPrefsClockHelp->add(*m_lvtPrefsClockHelp);
		m_lvtPrefsClockHelp->show();
		m_lvtPrefsClockHelp->set_hexpand();
		m_lvtPrefsClockHelp->set_vexpand();
		m_lvtPrefsClockHelp->set_column_title(0, "format chars");
		m_lvtPrefsClockHelp->set_column_title(1, "Meaning");
		int row = m_lvtPrefsClockHelp->append("%a");
		m_lvtPrefsClockHelp->set_text(row, 1, "The abbreviated weekday name according to the current locale.");
		row = m_lvtPrefsClockHelp->append("%A");
		m_lvtPrefsClockHelp->set_text(row, 1, "The full weekday name according to the current locale.");
		row = m_lvtPrefsClockHelp->append("%b");
		m_lvtPrefsClockHelp->set_text(row, 1, "The abbreviated month name according to the current locale.");
		row = m_lvtPrefsClockHelp->append("%B");
		m_lvtPrefsClockHelp->set_text(row, 1, "The full month name according to the current locale.");
		row = m_lvtPrefsClockHelp->append("%c");
		m_lvtPrefsClockHelp->set_text(row, 1, "The preferred date and time representation for the current locale.");
		row = m_lvtPrefsClockHelp->append("%C");
		m_lvtPrefsClockHelp->set_text(row, 1, "The century number (year/100) as a 2-digit integer.");
		row = m_lvtPrefsClockHelp->append("%d");
		m_lvtPrefsClockHelp->set_text(row, 1, "The day of the month as a decimal number (range 01 to 31).");
		row = m_lvtPrefsClockHelp->append("%D");
		m_lvtPrefsClockHelp->set_text(row, 1, "Equivalent  to  %m/%d/%y.  (Yecch—for Americans only.  Americans should\n"
		                                      "note that in other countries %d/%m/%y is rather common. This means that\n"
		                                      "in international context this format is ambiguous and should not be used.)");
		row = m_lvtPrefsClockHelp->append("%e");
		m_lvtPrefsClockHelp->set_text(row, 1, "Like %d, the day of the month as a decimal number, but a leading zero is\nreplaced by a space.");
		row = m_lvtPrefsClockHelp->append("%E");
		m_lvtPrefsClockHelp->set_text(row, 1, "Modifier: use alternative format, see below.");
		row = m_lvtPrefsClockHelp->append("%F");
		m_lvtPrefsClockHelp->set_text(row, 1, "Equivalent to %Y-%m-%d (the ISO 8601 date format).");
		row = m_lvtPrefsClockHelp->append("%G");
		m_lvtPrefsClockHelp->set_text(row, 1, "The ISO 8601 week-based year (see NOTES) with century as a decimal number.\n"
		                                      "The 4-digit year corresponding to the ISO week number (see  %V).   This  has\n"
		                                      "the same format and value as %Y, except that if the ISO week number belongs to\n"
		                                      "the previous or next year, that year is used instead.");
		row = m_lvtPrefsClockHelp->append("%g");
		m_lvtPrefsClockHelp->set_text(row, 1, "Like %G, but without century, that is, with a 2-digit year (00-99).");
		row = m_lvtPrefsClockHelp->append("%h");
		m_lvtPrefsClockHelp->set_text(row, 1, "Equivalent to %b.");
		row = m_lvtPrefsClockHelp->append("%H");
		m_lvtPrefsClockHelp->set_text(row, 1, "The hour as a decimal number using a 24-hour clock (range 00 to 23).");
		row = m_lvtPrefsClockHelp->append("%I");
		m_lvtPrefsClockHelp->set_text(row, 1, "The hour as a decimal number using a 12-hour clock (range 01 to 12).");
		row = m_lvtPrefsClockHelp->append("%j");
		m_lvtPrefsClockHelp->set_text(row, 1, "The day of the year as a decimal number (range 001 to 366).");
		row = m_lvtPrefsClockHelp->append("%k");
		m_lvtPrefsClockHelp->set_text(row, 1, "The hour (24-hour clock) as a decimal number (range 0 to 23); single digits\nare preceded by a blank.  (See also %H.)");
		row = m_lvtPrefsClockHelp->append("%l");
		m_lvtPrefsClockHelp->set_text(row, 1, "The hour (12-hour clock) as a decimal number (range 1 to 12); single digits\nare preceded by a blank.  (See also %I.)");
		row = m_lvtPrefsClockHelp->append("%m");
		m_lvtPrefsClockHelp->set_text(row, 1, "The month as a decimal number (range 01 to 12).");
		row = m_lvtPrefsClockHelp->append("%M");
		m_lvtPrefsClockHelp->set_text(row, 1, "The minute as a decimal number (range 00 to 59).");
		row = m_lvtPrefsClockHelp->append("%n");
		m_lvtPrefsClockHelp->set_text(row, 1, "A newline character.");
		row = m_lvtPrefsClockHelp->append("%O");
		m_lvtPrefsClockHelp->set_text(row, 1, "Modifier: use alternative format, see below.");
		row = m_lvtPrefsClockHelp->append("%p");
		m_lvtPrefsClockHelp->set_text(row, 1, "Either \"AM\" or \"PM\" according to the given time value, or the corresponding\n"
		                                      "strings for the current locale.  Noon is treated as \"PM\" and midnight as \"AM\".");
		row = m_lvtPrefsClockHelp->append("%P");
		m_lvtPrefsClockHelp->set_text(row, 1, "Like %p but in lowercase: \"am\" or \"pm\" or a corresponding string for the current\nlocale.");
		row = m_lvtPrefsClockHelp->append("%r");
		m_lvtPrefsClockHelp->set_text(row, 1, "The time in a.m. or p.m. notation.  In the POSIX locale this is equivalent to\n%I:%M:%S %p.");
		row = m_lvtPrefsClockHelp->append("%R");
		m_lvtPrefsClockHelp->set_text(row, 1, "The time in 24-hour notation (%H:%M). (SU) For a version including the seconds,\nsee %T below.");
		row = m_lvtPrefsClockHelp->append("%s");
		m_lvtPrefsClockHelp->set_text(row, 1, "The number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).");
		row = m_lvtPrefsClockHelp->append("%S");
		m_lvtPrefsClockHelp->set_text(row, 1, "The second as a decimal number (range 00 to 60).  (The range is up to 60 to allow\nfor occasional leap seconds.)");
		row = m_lvtPrefsClockHelp->append("%t");
		m_lvtPrefsClockHelp->set_text(row, 1, "A tab character.");
		row = m_lvtPrefsClockHelp->append("%T");
		m_lvtPrefsClockHelp->set_text(row, 1, "The time in 24-hour notation (%H:%M:%S).");
		row = m_lvtPrefsClockHelp->append("%u");
		m_lvtPrefsClockHelp->set_text(row, 1, "The day of the week as a decimal, range 1 to 7, Monday being 1.  See also %w.");
		row = m_lvtPrefsClockHelp->append("%U");
		m_lvtPrefsClockHelp->set_text(row, 1, "The  week  number  of  the current year as a decimal number, range 00 to 53, starting\n"
		                                      "with the first Sunday as the first day of week 01.  See also %V and %W.");
		row = m_lvtPrefsClockHelp->append("%V");
		m_lvtPrefsClockHelp->set_text(row, 1, "The ISO 8601 week number (see NOTES) of the current year as a decimal number, range 01\n"
		                                      "to 53, where week 1 is  the  first  week that has at least 4 days in the new year. \nSee also %U and %W");
		row = m_lvtPrefsClockHelp->append("%w");
		m_lvtPrefsClockHelp->set_text(row, 1, "The day of the week as a decimal, range 0 to 6, Sunday being 0.  See also %u");
		row = m_lvtPrefsClockHelp->append("%W");
		m_lvtPrefsClockHelp->set_text(row, 1, "The  week  number  of  the current year as a decimal number, range 00 to 53, starting\nwith the first Monday as the first day of week 01.");
		row = m_lvtPrefsClockHelp->append("%x");
		m_lvtPrefsClockHelp->set_text(row, 1, "The preferred date representation for the current locale without the time.");
		row = m_lvtPrefsClockHelp->append("%X");
		m_lvtPrefsClockHelp->set_text(row, 1, "The preferred time representation for the current locale without the date.");
		row = m_lvtPrefsClockHelp->append("%y");
		m_lvtPrefsClockHelp->set_text(row, 1, "The year as a decimal number without a century (range 00 to 99).");
		row = m_lvtPrefsClockHelp->append("%Y");
		m_lvtPrefsClockHelp->set_text(row, 1, "The year as a decimal number including the century.");
		row = m_lvtPrefsClockHelp->append("%z");
		m_lvtPrefsClockHelp->set_text(row, 1, "The +hhmm or -hhmm numeric timezone (that is, the hour and minute offset from UTC).");
		row = m_lvtPrefsClockHelp->append("%Z");
		m_lvtPrefsClockHelp->set_text(row, 1, "The timezone or name or abbreviation.");
		row = m_lvtPrefsClockHelp->append("%+");
		m_lvtPrefsClockHelp->set_text(row, 1, "The date and time in date(1) format.");
		row = m_lvtPrefsClockHelp->append("%%");
		m_lvtPrefsClockHelp->set_text(row, 1, "A literal '%' character.");
	}
	// m_fontbuttonClock //
	m_builder->get_widget("fontbuttonClock", m_fontbuttonClock);
	if(m_fontbuttonClock){
		//m_fontbuttonClock->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_comboboxtextClockFontWeight //
	m_builder->get_widget("comboboxtextClockFontWeight", m_comboboxtextClockFontWeight);
	if(m_comboboxtextClockFontWeight){
		//m_comboboxtextClockFontWeight->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_colorbuttonClockFontColour //
	m_builder->get_widget("colorbuttonClockFontColour", m_colorbuttonClockFontColour);
	if(m_colorbuttonClockFontColour){
		//m_colorbuttonClockFontColour->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	set_keep_above(true);
}

Prefs::~Prefs()
{
	delete m_lvtPrefsClockHelp;
}

Glib::ustring Prefs::get_font_name() const
{
	return m_fontbuttonPrefesGlobal->get_font_name();
}

void Prefs::set_font_name(Glib::ustring font)
{
	m_fontbuttonPrefesGlobal->set_font_name(font);
}

int Prefs::get_min_button_size() const
{
	return m_adjustmentMinTaskWidth->get_value();
}

void Prefs::set_min_button_size(int sz)
{
	m_adjustmentMinTaskWidth->set_value(sz);
}

Glib::ustring Prefs::get_entryTimeFormatTopln() const
{
	return m_entryTimeFormatTopln->get_text();
}

void Prefs::set_entryTimeFormatTopln(Glib::ustring format)
{
	m_entryTimeFormatTopln->set_text(format);
}

Glib::ustring Prefs::get_entryTimeFormatBottomln() const
{
	return m_entryTimeFormatBottomln->get_text();
}

void Prefs::set_entryTimeFormatBottomln(Glib::ustring format)
{
	m_entryTimeFormatBottomln->set_text(format);
}

Pango::Weight Prefs::get_font_weight() const
{
	Glib::ustring weight = m_comboboxtextFontWeight->get_active_text();
	if(weight == "ultralight"){
		return Pango::WEIGHT_ULTRALIGHT;
	}else if(weight == "light"){
		return Pango::WEIGHT_LIGHT;
	}else if(weight == "normal"){
		return Pango::WEIGHT_NORMAL;	
	}else if(weight == "semibold"){
		return Pango::WEIGHT_SEMIBOLD; 	
	}else if(weight == "bold"){
		return Pango::WEIGHT_BOLD; 	
	}else if(weight == "ultrabold"){
		return Pango::WEIGHT_ULTRABOLD; 	
	}else if(weight == "heavey"){
		return Pango::WEIGHT_HEAVY; 	
	}else{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: weight == " << weight << std::endl;
		return static_cast<Pango::Weight>(0);
	}
}

void Prefs::set_font_weight(Pango::Weight weight)
{
	switch(weight){
		case(0):
		{
			m_comboboxtextFontWeight->set_active_id("None");
			break;
		}
		case(Pango::WEIGHT_ULTRALIGHT):
		{
			m_comboboxtextFontWeight->set_active_id("ultralight");
			break;
		}
		case(Pango::WEIGHT_LIGHT):
		{
			m_comboboxtextFontWeight->set_active_id("light");
			break;
		}
		case(Pango::WEIGHT_NORMAL):
		{
			m_comboboxtextFontWeight->set_active_id("normal");
			break;
		}
		case(Pango::WEIGHT_SEMIBOLD):
		{
			m_comboboxtextFontWeight->set_active_id("semibold");
			break;
		}
		case(Pango::WEIGHT_BOLD):
		{
			m_comboboxtextFontWeight->set_active_id("bold");
			break;
		}
		case(Pango::WEIGHT_ULTRABOLD):
		{
			m_comboboxtextFontWeight->set_active_id("ultrabold");
			break;
		}
		case(Pango::WEIGHT_HEAVY):
		{
			m_comboboxtextFontWeight->set_active_id("heavy");
			break;
		}
	} // switch(weight) //
} //  void Prefs::set_font_weight(Pango::Weight weight) //

Gdk::RGBA Prefs::get_global_colour() const
{
	return m_colorbuttonPrefsFontColour->get_rgba();
}

void Prefs::set_global_colour(Gdk::RGBA colour)
{
	m_colorbuttonPrefsFontColour->set_rgba(colour);
}

Glib::ustring Prefs::get_clock_font_name() const
{
	return m_fontbuttonClock->get_font_name();
}

void Prefs::set_clock_font_name(Glib::ustring font)
{
	m_fontbuttonClock->set_font_name(font);
}

Pango::Weight Prefs::get_clock_font_weight() const
{
	Glib::ustring weight = m_comboboxtextClockFontWeight->get_active_text();
	if(weight == "ultralight"){
		return Pango::WEIGHT_ULTRALIGHT;
	}else if(weight == "light"){
		return Pango::WEIGHT_LIGHT;
	}else if(weight == "normal"){
		return Pango::WEIGHT_NORMAL;	
	}else if(weight == "semibold"){
		return Pango::WEIGHT_SEMIBOLD; 	
	}else if(weight == "bold"){
		return Pango::WEIGHT_BOLD; 	
	}else if(weight == "ultrabold"){
		return Pango::WEIGHT_ULTRABOLD; 	
	}else if(weight == "heavey"){
		return Pango::WEIGHT_HEAVY; 	
	}else{
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: weight == " << weight << std::endl;
		return static_cast<Pango::Weight>(0);
	}
}

void Prefs::set_clock_font_weight(Pango::Weight weight)
{
	switch(weight){
		case(0):
		{
			m_comboboxtextClockFontWeight->set_active_id("None");
			break;
		}
		case(Pango::WEIGHT_ULTRALIGHT):
		{
			m_comboboxtextClockFontWeight->set_active_id("ultralight");
			break;
		}
		case(Pango::WEIGHT_LIGHT):
		{
			m_comboboxtextClockFontWeight->set_active_id("light");
			break;
		}
		case(Pango::WEIGHT_NORMAL):
		{
			m_comboboxtextClockFontWeight->set_active_id("normal");
			break;
		}
		case(Pango::WEIGHT_SEMIBOLD):
		{
			m_comboboxtextClockFontWeight->set_active_id("semibold");
			break;
		}
		case(Pango::WEIGHT_BOLD):
		{
			m_comboboxtextClockFontWeight->set_active_id("bold");
			break;
		}
		case(Pango::WEIGHT_ULTRABOLD):
		{
			m_comboboxtextClockFontWeight->set_active_id("ultrabold");
			break;
		}
		case(Pango::WEIGHT_HEAVY):
		{
			m_comboboxtextClockFontWeight->set_active_id("heavy");
			break;
		}
		default:
		{
			m_comboboxtextClockFontWeight->set_active_id("None");
		}
	} // switch(weight) //
} //  void Prefs::set_clock_font_weight(Pango::Weight weight) //

Gdk::RGBA Prefs::get_clock_colour() const
{
	return m_colorbuttonClockFontColour->get_rgba();
}

void Prefs::set_clock_colour(Gdk::RGBA colour)
{
	m_colorbuttonClockFontColour->set_rgba(colour);
}











