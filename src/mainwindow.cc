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
#include <gdk/gdkx.h>

Main_window::Main_window(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
  : Gtk::Window(cobject), m_builder(builder), m_buttonMenu(nullptr), m_menuPanel(nullptr), 
    m_imagemenuitemExit(nullptr), m_labelClock(nullptr), m_labelDate(nullptr), m_boxDeskTop(nullptr), 
    m_pagerDeskTop(nullptr), m_boxTaskBar(nullptr), m_taskbar(nullptr), m_imagemenuitemUnity(nullptr), 
    m_imagemenuitemCompiz(nullptr), m_imagemenuitemPreferences(nullptr), 
    m_imagemenuitemRun(nullptr), m_dialogPreferences(nullptr), 
    m_dialogRunApplication(nullptr), m_icontheme(Gtk::IconTheme::get_default()), 
    m_clockformat("%Y-%m-%d %H:%M:%S"), m_dateformat("%A %d %B"), m_refscreen(get_screen()), 
    m_wnck_screen(new Wnck::Screen), 
    m_counter(0)
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
	// m_imagemenuitemUnity //
	m_builder->get_widget("imagemenuitemUnity", m_imagemenuitemUnity);
	if(m_imagemenuitemUnity){
		m_imagemenuitemUnity->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Unity) );
	}
	// m_imagemenuitemCompiz //
	m_builder->get_widget("imagemenuitemCompiz", m_imagemenuitemCompiz);
	if(m_imagemenuitemCompiz){
		m_imagemenuitemCompiz->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Compiz) );
	}
	// m_imagemenuitemPreferences //
	m_builder->get_widget("imagemenuitemPreferences", m_imagemenuitemPreferences);
	if(m_imagemenuitemPreferences){
		m_imagemenuitemPreferences->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Prefrences) );
	}
	// m_imagemenuitemRun //
	m_builder->get_widget("imagemenuitemRun", m_imagemenuitemRun);
	if(m_imagemenuitemRun){
		m_imagemenuitemRun->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_RunApp) );
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

	//Glib::RefPtr<Gdk::Screen> m_refscreen = get_screen();
	// m_boxTaskBar //
	m_builder->get_widget("boxTaskBar", m_boxTaskBar);
	if(m_boxTaskBar){
		//m_boxTaskBar->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
		m_wnck_screen->force_update();
		m_taskbar = Gtk::manage(new gzz::Taskbar(*m_wnck_screen));
		/*m_taskbar->signal_load_icon().connect( sigc::mem_fun(*this, &Main_window::on_load_icon) );
		m_taskbar->signal_allocation().connect( sigc::mem_fun(*this, &Main_window::on_allocate) );
		m_taskbar->set_include_all_workspaces(false);
		m_taskbar->set_grouping(Wnck::Tasklist::AUTO_GROUP);*/
		//m_taskbar->set_grouping_limit(4);
		//m_taskbar->set_button_relief(Gtk::RELIEF_NORMAL);
		//Glib::ustring data = "WnckTasklist {color: #ff0000;font: Lucida Grande 6}";
		Glib::ustring data = "GtkWindow {color: #000000;font: Lucida Grande 8}";
		auto css = Gtk::CssProvider::create();
		if(not css->load_from_data(data)) {
			std::cerr << "Failed to load css" << std::endl;
			std::exit(1);
		}
		//auto screen = Gdk::Screen::get_default();
		//auto ctx = m_taskbar->get_style_context();
		auto ctx = get_style_context();
		ctx->add_provider_for_screen(m_refscreen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		m_boxTaskBar->override_font(Pango::FontDescription("[Lucida Grande][bold Black][8]"));
		m_boxTaskBar->pack_start(*m_taskbar, true, true, 0);
		std::cout << __FILE__ << '[' << __LINE__ << "] m_refscreen->get_width() == " << m_refscreen->get_width() << std::endl;
		std::cout << __FILE__ << '[' << __LINE__ << "] m_refscreen->get_width() - 2024 == " << m_refscreen->get_width() - 2024 << std::endl;
		m_boxTaskBar->set_size_request(m_refscreen->get_width() - 2024, 36); // try and force it //
		m_taskbar->set_size_request(m_refscreen->get_width() - 2028, 36);     // try and force it //
		Gdk::Geometry geom;
		geom.max_width = m_refscreen->get_width() - 512;
		geom.min_width = m_refscreen->get_width() - 512;
		geom.base_width = -1;
		geom.max_height = 38;
		geom.min_height = 38;
		geom.base_height = -1;
		geom.height_inc = 1;
		geom.width_inc = 1;
		geom.win_gravity = GDK_GRAVITY_NORTH_WEST;
		set_geometry_hints(*m_boxTaskBar, geom, Gdk::HINT_MAX_SIZE /*| Gdk::HINT_MIN_SIZE*/);
		m_taskbar->show();
		/*std::vector<int> vec = m_taskbar->get_size_hint_list();
		int total = 0;
		std::cout << "{ " << std::flush;
		for(auto e : vec){
			std::cout << e << ", " << std::flush;
			total += e;
		}
		std::cout << '}' << std::endl << "total == " << total << std::endl;*/
	}

	// m_dialogPreferences //
	m_builder->get_widget_derived("dialogPreferences", m_dialogPreferences);
	if(m_dialogPreferences){
		//m_dialogPreferences->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
	}
	// m_dialogRunApplication //
	m_builder->get_widget_derived("dialogRunApplication", m_dialogRunApplication);
	if(m_dialogRunApplication){
		//m_dialogRunApplication->signal_activate().connect( sigc::mem_fun(*this, &Main_window::on_menuitem_Exit) );
	}

	//set_type_hint(Gdk::WINDOW_TYPE_HINT_DOCK);
	set_default_size(m_refscreen->get_width() - 49, 38);
	resize(m_refscreen->get_width() - 49, 38);
	set_size_request(m_refscreen->get_width() - 49, 38); // try and force it //
	move(49, m_refscreen->get_height() - 40);
	set_opacity(0.90);
	set_keep_above(true);
	m_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Main_window::on_timeout), 100);
	stick(); // make it sticky //
	signal_map().connect ( sigc::mem_fun(*this, &Main_window::on_window_mapped) );
	signal_show().connect ( sigc::mem_fun(*this, &Main_window::on_window_mapped) );
	signal_realize().connect ( sigc::mem_fun(*this, &Main_window::on_window_mapped) );
	//hide();
	//show_all();
	Gdk::Geometry geom;
	geom.max_width = m_refscreen->get_width() - 512;
	geom.min_width = m_refscreen->get_width() - 512;
	geom.base_width = -1;
	geom.max_height = 38;
	geom.min_height = 38;
	geom.base_height = -1;
	geom.height_inc = 1;
	geom.width_inc = 1;
	geom.win_gravity = GDK_GRAVITY_NORTH_WEST;
	set_geometry_hints(*m_taskbar, geom, Gdk::HINT_MAX_SIZE | Gdk::HINT_MIN_SIZE);
	resize(m_refscreen->get_width() - 49, 38);
	move(49, m_refscreen->get_height() - 50);
	gint32 data[4] = {0, 0, 0, std::max(get_height(), get_allocated_height()) + 5};
	wnck_set_client_type(WNCK_CLIENT_TYPE_PAGER);
	gdk_property_change(get_window()->gobj(), gdk_x11_xatom_to_atom(gdk_x11_get_xatom_by_name("_NET_WM_STRUT")), gdk_x11_xatom_to_atom(gdk_x11_get_xatom_by_name("CARDINAL")), 32, GDK_PROP_MODE_REPLACE, reinterpret_cast<guchar*>(data), sizeof(gint32)*4);
	gint32 data2[12] = {0, 0, 0, std::max(get_height(), get_allocated_height()) + 5, 0, 0, 0, 0, 0, 0, 49, m_refscreen->get_width()};
	gdk_property_change(get_window()->gobj(), gdk_x11_xatom_to_atom(gdk_x11_get_xatom_by_name("_NET_WM_STRUT_PARTIAL")), gdk_x11_xatom_to_atom(gdk_x11_get_xatom_by_name("CARDINAL")), 32, GDK_PROP_MODE_REPLACE, reinterpret_cast<guchar*>(data2), sizeof(gint32)*12);
}

Main_window::~Main_window()
{
}

void Main_window::on_window_mapped()
{
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<" m_refscreen->get_width() == " << m_refscreen->get_width() << std::endl;
	std::cout << __FILE__ << '[' << __LINE__ << "] m_counter++ == " << m_counter++ << std::endl;
	set_default_size(m_refscreen->get_width() - 49, 38);
	resize(m_refscreen->get_width() - 49, 38);
	set_size_request(m_refscreen->get_width() - 49, 38); // try and force it //
	move(49, m_refscreen->get_height() - 38);
	set_opacity(0.85);
}

void Main_window::on_allocate(Gtk::Allocation& allocation)
{
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<" allocation.get_width() == " << allocation.get_width() << std::endl;
	if(allocation.get_width() > m_refscreen->get_width() - 512){
		allocation.set_width(m_refscreen->get_width() - 512);
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<" allocation.get_width() == " << allocation.get_width() << std::endl;
	}
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
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, m_clockformat.c_str(), timeinfo);
	m_labelClock->set_text(buffer);
	strftime(buffer, 80, m_dateformat.c_str(), timeinfo);
	m_labelDate->set_text(buffer);
	m_taskbar->refreshbar();
	return true;
}

void Main_window::setup_desktops()
{
	//m_refscreen = get_screen();
	Glib::RefPtr<Gdk::Display> refDisplay = m_refscreen->get_display();
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

void Main_window::on_menuitem_Unity()
{
	system("/usr/bin/unity&");
}

void Main_window::on_menuitem_Compiz()
{
	system("/usr/bin/compiz --replace&");
}

void Main_window::on_menuitem_Prefrences()
{
	//m_dialogPreferences->set_use_font(true);
	Glib::RefPtr<Pango::Context> pc = get_pango_context();
	Pango::FontDescription oldfd = pc->get_font_description();
	//Glib::ustring fname = pango_font_description_to_string(oldfd.gobj());
	Glib::ustring fname = oldfd.to_string();
	m_dialogPreferences->set_font_name(fname);
	m_dialogPreferences->set_min_button_size(m_taskbar->get_min_button_size());
	m_dialogPreferences->set_entryTimeFormatTopln(m_clockformat);
	m_dialogPreferences->set_entryTimeFormatBottomln(m_dateformat);
	int res = m_dialogPreferences->run();
	m_dialogPreferences->hide();
	if(res){
		Glib::ustring fontname = m_dialogPreferences->get_font_name();
		std::cout << "Ok clicked. fontname == " << fontname << std::endl;
		Pango::FontDescription fd(pango_font_description_from_string(fontname.c_str()));
		std::cout << "Ok clicked. fontname == " << fontname << std::endl;
		std::cout << "Ok clicked. fd.get_family() == " << fd.get_family() << std::endl;
		std::cout << "Ok clicked. fd.get_style() == " << fd.get_style() << std::endl;
		std::cout << "Ok clicked. fd.to_string() == " << fd.to_string() << std::endl;
		std::cout << "Ok clicked. fd.get_size() == " << fd.get_size()/1000 << std::endl;
		m_taskbar->override_font(fd);
		override_font(fd);
		m_taskbar->set_min_button_size(m_dialogPreferences->get_min_button_size());
		m_clockformat = m_dialogPreferences->get_entryTimeFormatTopln();
		m_dateformat = m_dialogPreferences->get_entryTimeFormatBottomln();
	}else{
		std::cout << "Cancel clicked." << std::endl;
	}
}

void Main_window::on_menuitem_RunApp()
{
	int res = m_dialogRunApplication->run();
	m_dialogRunApplication->hide();
	if(res){
		std::cout << "Execute clicked." << std::endl;
	}else{
		std::cout << "Cancel clicked." << std::endl;
	}
}





