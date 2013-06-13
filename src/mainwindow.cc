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

#include "mainwindow.h"
#include <ctime>       /* time_t, struct tm, time, localtime, strftime */
#include <boost/filesystem.hpp>

Main_window::Main_window(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Window(cobject), m_builder(builder), m_buttonMenu(0), m_menuPanel(0), 
    m_imagemenuitemExit(0), m_labelClock(0), m_labelDate(0), m_boxDeskTop(0), 
    m_pagerDeskTop(0), m_buttonboxTaskBar(0), /*m_taskbar(0),*/ m_icontheme(Gtk::IconTheme::get_default()), 
    m_clockformat("%Y-%m-%d %H:%M:%S"), m_dateformat("%A %d %B")
{
	// m_buttonMenu //
	m_builder->get_widget("buttonMenu", m_buttonMenu);
	if(m_buttonMenu){
		m_buttonMenu->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_menuPanel //
	m_builder->get_widget("menuPanel", m_menuPanel);
	if(m_menuPanel){
		//m_menuPanel->signal_clicked().connect( sigc::mem_fun(*this, &Main_window::on_button_Menu) );
	}
	// m_imagemenuitemExit //
	m_builder->get_widget("imagemenuitemExit", m_imagemenuitemExit);
	if(m_imagemenuitemExit){
		m_imagemenuitemExit->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
	}

	// m_labelClock //
	m_builder->get_widget("labelClock", m_labelClock);
	if(m_labelClock){
		//m_labelClock->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
	}
	// m_labelDate //
	m_builder->get_widget("labelDate", m_labelDate);
	if(m_labelDate){
		//m_labelDate->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
	}

	// m_boxDeskTop //
	m_builder->get_widget("boxDeskTop", m_boxDeskTop);
	if(m_boxDeskTop){
		//m_boxDeskTop->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
		m_pagerDeskTop = Gtk::manage(new Wnck::Pager());
		setup_desktops();
		m_boxDeskTop->pack_start(*m_pagerDeskTop, false, false, 0);
		m_pagerDeskTop->show();
	}

	Glib::RefPtr<Gdk::Screen> refscreen = get_screen();
	// m_buttonboxTaskBar //
	m_builder->get_widget_derived("buttonboxTaskBar", m_buttonboxTaskBar);
	if(m_buttonboxTaskBar){
		//m_buttonboxTaskBar->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
		//m_taskbar = Gtk::manage(new Wnck::Tasklist());
		//m_taskbar->set_include_all_workspaces(false);
		//m_taskbar->set_grouping(Wnck::Tasklist::AUTO_GROUP);
		//m_taskbar->set_grouping_limit(20);
		//m_taskbar->set_button_relief(Gtk::RELIEF_NORMAL);
		//m_buttonboxTaskBar->pack_start(*m_taskbar, true, true, 0);
		//m_taskbar->signal_load_icon().connect( sigc::mem_fun(*this, &Main_window::on_load_icon) );
		std::cout << __FILE__ << '[' << __LINE__ << "] refscreen->get_width() == " << refscreen->get_width() << std::endl;
		std::cout << __FILE__ << '[' << __LINE__ << "] refscreen->get_width() - 2024 == " << refscreen->get_width() - 2024 << std::endl;
		/*std::vector<int> vec = m_taskbar->get_size_hint_list();
		int total = 0;
		std::cout << "{ " << std::flush;
		for(auto e : vec){
			std::cout << e << ", " << std::flush;
			total += e;
		}*/
		//m_taskbar->show();
		//std::cout << '}' << std::endl << "total == " << total << std::endl;
		//m_buttonboxTaskBar->set_size_request(refscreen->get_width() - 2024, 36); // try and force it //
		//m_taskbar->set_size_request(refscreen->get_width() - 2028, 36);     // try and force it //
	}

	set_type_hint(Gdk::WINDOW_TYPE_HINT_DOCK);
	set_default_size(refscreen->get_width() - 49, 38);
	resize(refscreen->get_width() - 49, 38);
	set_size_request(refscreen->get_width() - 49, 38); // try and force it //
	move(49, refscreen->get_height() - 32);
	set_opacity(0.85);
	set_keep_above(true);
	m_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Main_window::on_timeout), 100);
	stick(); // make it sticky //
}

Main_window::~Main_window()
{
}

void Main_window::on_button_Menu()
{
	m_menuPanel->popup(sigc::mem_fun(*this, &Main_window::on_popup_menu_position), 0, gtk_get_current_event_time());
}

void Main_window::on_menuitem_Exit()
{
	hide();
}

void Main_window::on_popup_menu_position(int& x, int& y, bool& push_in)
{
}

bool Main_window::on_timeout()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer, 80, m_clockformat.c_str(), timeinfo);
	m_labelClock->set_text(buffer);
	strftime (buffer, 80, m_dateformat.c_str(), timeinfo);
	m_labelDate->set_text(buffer);
	return true;
}

void Main_window::setup_desktops()
{
	Glib::RefPtr<Gdk::Screen> refscreen = get_screen();
	Glib::RefPtr<Gdk::Display> refDisplay = refscreen->get_display();
	m_desktop_rows = refDisplay->get_n_screens();
	std::cout << __FILE__ << '[' << __LINE__ << "] m_desktop_rows == " << m_desktop_rows << std::endl;
	m_pagerDeskTop->set_n_rows(1);
	m_pagerDeskTop->set_show_all(true);
	m_pagerDeskTop->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	m_pagerDeskTop->set_size_request(36, 36);
	m_pagerDeskTop->set_valign(Gtk::ALIGN_CENTER);
	m_pagerDeskTop->set_margin_top(2);
}

GdkPixbuf* Main_window::on_load_icon(const Glib::ustring& icon_name, int size, unsigned flags)
{
	std::cout << __FILE__ << '[' << __LINE__ << "] icon_name == " << icon_name << std::endl;
	std::cout << __FILE__ << '[' << __LINE__ << "] size == " << size << std::endl;
	if(icon_name == "") return 0;
	boost::filesystem::path icon_path(icon_name);
	if(is_regular_file(icon_path)){
		return Gdk::Pixbuf::create_from_file(icon_name, size, size)->gobj ();
	}
	return m_icontheme->load_icon(icon_name, size, static_cast<Gtk::IconLookupFlags>(0))->gobj();
}






