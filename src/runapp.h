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

#ifndef _RUNAPP_H_
#define _RUNAPP_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>

class RunApp : public Gtk::Dialog 
{
	public:
		struct CmdHist {
			Glib::ustring datetime_str;
			bool used_term;
			Glib::ustring cmd;
			friend std::ostream& operator<<(std::ostream& out, const CmdHist& cmd_hist);
			friend std::istream& operator>>(std::istream& in, CmdHist& cmd_hist);
		};
		
		RunApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
		~RunApp();

		Glib::ustring get_entry_text() const;
		void set_entry_text(Glib::ustring text);
		bool get_use_term();
		void set_text_items(const std::vector<CmdHist>& items);
	protected:
		const Glib::RefPtr<Gtk::Builder>& m_builder;

		// gui stuff //
		Gtk::ComboBoxText* m_comboboxtextRunApplication;
		Gtk::Entry* m_comboboxtextentry;
		Gtk::CheckButton* m_checkbuttonRunInTerm;
	private:

};

#endif // _RUNAPP_H_

