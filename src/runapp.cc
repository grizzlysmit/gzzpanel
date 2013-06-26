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

#include "runapp.h"

RunApp::RunApp(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Dialog(cobject), m_builder(builder), 
    m_comboboxtextRunApplication(nullptr), m_comboboxtextentry(nullptr), 
    m_checkbuttonRunInTerm(nullptr)
{
	// m_comboboxtextRunApplication //
	m_builder->get_widget("comboboxtextRunApplication", m_comboboxtextRunApplication);
	if(m_comboboxtextRunApplication){
		//m_comboboxtextRunApplication->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
		m_comboboxtextentry = m_comboboxtextRunApplication->get_entry();
	}
	// m_checkbuttonRunInTerm //
	m_builder->get_widget("checkbuttonRunInTerm", m_checkbuttonRunInTerm);
	if(m_checkbuttonRunInTerm){
		//m_checkbuttonRunInTerm->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
}

RunApp::~RunApp()
{
}

Glib::ustring RunApp::get_entry_text() const
{
	return m_comboboxtextRunApplication->get_entry_text();
}

void RunApp::set_entry_text(Glib::ustring text)
{
	m_comboboxtextentry->set_text(text);
}

bool RunApp::get_use_term()
{
	return m_checkbuttonRunInTerm->get_active();
}

void RunApp::set_text_items(const std::vector<RunApp::CmdHist>& items)
{
	m_comboboxtextRunApplication->remove_all();
	for(auto item : items){
		m_comboboxtextRunApplication->append(item.cmd);
	}
}

std::ostream& operator<<(std::ostream& out, const RunApp::CmdHist& cmd_hist)
{
	out << cmd_hist.datetime_str << ',' << cmd_hist.used_term << ',' << cmd_hist.cmd << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, RunApp::CmdHist& cmd_hist)
{
	std::string line;
	if(getline(in, line)){
		auto pos = line.find(',');
		if(pos == std::string::npos){
			in.setstate(std::ios_base::failbit);
			return in;
		}
		cmd_hist.datetime_str = line.substr(0, pos);
		line = line.substr(pos + 1);
		pos = line.find(',');
		if(pos == std::string::npos){
			in.setstate(std::ios_base::failbit);
			return in;
		}
		std::string used_str = line.substr(0, pos);
		cmd_hist.used_term = (used_str == "true");
		cmd_hist.cmd = line.substr(pos + 1);
	}
	return in;
}





