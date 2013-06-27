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
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <fstream>
#include <algorithm>


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
		if(!css->load_from_data(data)) {
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
	//std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << "\t entering" << std::endl;
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, m_clockformat.c_str(), timeinfo);
	m_labelClock->set_text(buffer);
	strftime(buffer, 80, m_dateformat.c_str(), timeinfo);
	m_labelDate->set_text(buffer);
	//std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << "\t about to refresh taskbar" << std::endl;
	m_taskbar->refreshbar();
	//std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << "\t leaving now" << std::endl;
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
    //////////////////////////////////////////////////////////////////////////////
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
	//@@@                                                                    @@@//
	//@@@           Load prefs from config file; or use defaults             @@@//
	//@@@                                                                    @@@//
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
    //////////////////////////////////////////////////////////////////////////////
	boost::property_tree::ptree pt = get_config();
	m_dialogPreferences->set_font_name(pt.get("global.font_name", "Lucida Grande 10"));
	Gdk::RGBA rgba(pt.get("global.font_colour", "#00FF00"));
	m_dialogPreferences->set_global_colour(rgba);
	m_dialogPreferences->set_font_weight(static_cast<Pango::Weight>(pt.get("global.font_weight", 200)));
	m_dialogPreferences->set_min_button_size(pt.get("toolbar.min_button_size", m_taskbar->get_min_button_size()));
	m_dialogPreferences->set_entryTimeFormatTopln(pt.get("clock.timeformat", m_clockformat));
	m_dialogPreferences->set_entryTimeFormatBottomln(pt.get("clock.dateformat", m_dateformat));
	m_dialogPreferences->set_clock_font_name(pt.get("clock.font_name", m_clockfontname));
	m_dialogPreferences->set_clock_font_weight(static_cast<Pango::Weight>(pt.get("clock.font_weight", static_cast<int>(m_clock_font_weight))));
	Gdk::RGBA rgba_clock(pt.get("clock.font_colour", "#FF0000"));
	m_dialogPreferences->set_clock_colour(rgba_clock);

	//  run dialog   //
	int res = m_dialogPreferences->run();
	m_dialogPreferences->hide();

	// deal with results //
	if(res){
		Glib::ustring fontname = m_dialogPreferences->get_font_name();
		std::cout << "Ok clicked. fontname == " << fontname << std::endl;
		Pango::FontDescription fd(pango_font_description_from_string(fontname.c_str()));
		std::cout << "Ok clicked. fontname == " << fontname << std::endl;
		std::cout << "Ok clicked. fd.get_family() == " << fd.get_family() << std::endl;
		std::cout << "Ok clicked. fd.get_style() == " << fd.get_style() << std::endl;
		std::cout << "Ok clicked. fd.to_string() == " << fd.to_string() << std::endl;
		std::cout << "Ok clicked. fd.get_size() == " << fd.get_size()/1000 << std::endl;
		Gdk::RGBA rgba = m_dialogPreferences->get_global_colour();
		Pango::Weight global_weight = m_dialogPreferences->get_font_weight();
		int min_button_size = m_dialogPreferences->get_min_button_size();
		m_clockformat = m_dialogPreferences->get_entryTimeFormatTopln();
		m_dateformat = m_dialogPreferences->get_entryTimeFormatBottomln();
		m_clock_font_weight = m_dialogPreferences->get_clock_font_weight();
		Gdk::RGBA clock_font_colour = m_dialogPreferences->get_clock_colour();
		// put in new tree //
		boost::property_tree::ptree pt;
		pt.put("global.font_name", fontname);
		pt.put("global.font_colour", rgba.to_string());
		pt.put("global.font_weight", static_cast<int>(global_weight));
		pt.put("toolbar.min_button_size", min_button_size);
		pt.put("clock.timeformat", m_clockformat);
		pt.put("clock.dateformat", m_dateformat);
		pt.put("clock.font_name", m_clockfontname);
		pt.put("clock.font_weight", static_cast<int>(m_clock_font_weight));
		pt.put("clock.font_colour", clock_font_colour.to_string());
		// write to inifile //
		set_config(pt);

		// apply to widgits //
		m_taskbar->set_min_button_size(min_button_size);
		fd.set_weight(global_weight);
		m_taskbar->set_fontdescription(fd);
		m_taskbar->override_font(fd);
		override_font(fd);
		// font colour //
		m_taskbar->override_color(rgba);
		m_taskbar->set_colour(rgba);
		override_color(rgba);

		// clock //
		Pango::FontDescription fd_clock(pango_font_description_from_string(m_clockfontname.c_str()));
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " fd_clock.to_string() == " << fd_clock.to_string() << std::endl;
		fd_clock.set_weight(m_clock_font_weight);
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " fd_clock.to_string() == " << fd_clock.to_string() << std::endl;
		m_labelClock->override_font(fd_clock);
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " clock_font_colour.to_string() == " << clock_font_colour.to_string() << std::endl;
		m_labelClock->override_color(clock_font_colour);
		m_labelDate->override_font(fd_clock);
		m_labelDate->override_color(clock_font_colour);
	}else{
		std::cout << "Cancel clicked." << std::endl;
	}
}

void Main_window::on_menuitem_RunApp()
{
	std::vector<RunApp::CmdHist> history = load_cmd_history();
	m_dialogRunApplication->set_text_items(history);
	m_dialogRunApplication->set_entry_text("");
	int res = m_dialogRunApplication->run();
	m_dialogRunApplication->hide();
	if(res){
		Glib::ustring cmd = m_dialogRunApplication->get_entry_text();
		RunApp::CmdHist cmd_hist;
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
		cmd_hist.datetime_str = buffer;
		cmd_hist.used_term = m_dialogRunApplication->get_use_term();
		cmd_hist.cmd = cmd;
		history.insert(history.begin(), cmd_hist);
		save_cmd_history(history);
		if(cmd_hist.used_term){
			Glib::ustring command = "gnome-terminal --execute " + cmd;
			system((command + " &").c_str());
		}else{
			system((cmd + " &").c_str());
		}
		std::cout << "Execute clicked." << std::endl;
	}else{
		std::cout << "Cancel clicked." << std::endl;
	}
}

bool Main_window::insure_config_path() const
{
	std::string path = std::getenv("HOME");
	path += "/.config";
	if(!boost::filesystem::exists(path)){
		mkdir(path.c_str(), 0700);
	}else if(!boost::filesystem::is_directory(path)){
		return false;
	}
	path += "/" + m_progname;
	if(!boost::filesystem::exists(path)){
		mkdir(path.c_str(), 0775);
	}
	return boost::filesystem::exists(path) && boost::filesystem::is_directory(path);
}

std::vector<RunApp::CmdHist> Main_window::load_cmd_history()
{
	std::vector<RunApp::CmdHist> result;
	if(insure_config_path()){
		std::string path = std::getenv("HOME");
		path += "/.config/" + m_progname + "/cmd_history";
		std::ifstream in(path);
		if(in){
			RunApp::CmdHist cmd_hist;
			in >> cmd_hist;
			std::string line, datestr, used_str, cmd;
			bool used_term;
			while(in){
				result.insert(result.begin(), cmd_hist);
				in >> cmd_hist;
			}
			in.close();
		}
	}
	return result;
}

bool Main_window::save_cmd_history(std::vector<RunApp::CmdHist> history)
{
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: history.size() == " << history.size() << std::endl;
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: m_history_limit == " << m_history_limit << std::endl;
	while(history.size() > m_history_limit){
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: history.size() == " << history.size() << std::endl;
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: m_history_limit == " << m_history_limit << std::endl;
		history.erase(history.end() - 1);
	}
	std::reverse(history.begin(), history.end());
	if(insure_config_path()){
		std::string path = std::getenv("HOME");
		path += "/.config/" + m_progname + "/cmd_history";
		std::ofstream out(path);
		if(out){
			for(auto hist : history){
				out << hist << std::flush; // hist will do an std::endl anyway //
				if(!out) return false;
			}
		}
		bool result = out;
		out.close();
		return result;
	}
}

void Main_window::set_progname(std::string progname)
{
	m_progname = progname;
}

boost::property_tree::ptree Main_window::get_config() const
{
	boost::property_tree::ptree pt;
	if(insure_config_path()){
		std::string path = std::getenv("HOME");
		path += "/.config/" + m_progname + "/" + m_progname + ".ini";
		try {
			boost::property_tree::ini_parser::read_ini(path, pt);
		}
		catch(std::exception& e){
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t caught exception:msg: " << e.what() << std::endl;
		}
	}
	return pt;
}

void Main_window::set_config(boost::property_tree::ptree pt)
{
	if(insure_config_path()){
		std::string path = std::getenv("HOME");
		path += "/.config/" + m_progname + "/" + m_progname + ".ini";
		write_ini(path, pt);
	}
}

void Main_window::set_up_config_file()
{
	if(insure_config_path()){
		std::string path = std::getenv("HOME");
		path += "/.config/" + m_progname + "/" + m_progname + ".ini";
		std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here path == " << path << std::endl;
		if(!boost::filesystem::exists(path) || (boost::filesystem::is_regular_file(path) && boost::filesystem::is_empty(path))){
			boost::property_tree::ptree pt;
			pt.put("global.font_name", "Lucida Grande 10");
			pt.put("global.font_colour", "#00FF00");
			pt.put("global.font_weight", 200);
			pt.put("toolbar.min_button_size", 150);
			pt.put("clock.timeformat", m_clockformat);
			pt.put("clock.dateformat", m_dateformat);
			pt.put("clock.font_name", m_clockfontname);
			pt.put("clock.font_weight", static_cast<int>(m_clock_font_weight));
			pt.put("clock.font_colour", "#FF0000");
			
			// now write it to the ini file //
			write_ini(path, pt);
		}else if(!boost::filesystem::is_regular_file(path)){
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here path == " << path << std::endl;
			// error do something here //
		}else{
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t got here: shouldn't have path == " << path << std::endl;
		}
	}else{
			std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ <<"\t couldn't insure path: " << std::endl;
	}
}

void Main_window::apply_defaults()
{
	boost::property_tree::ptree pt = get_config();
	Glib::ustring fontname = pt.get("global.font_name", "Lucida Grande 10");
	Pango::FontDescription fd(pango_font_description_from_string(fontname.c_str()));
	Gdk::RGBA rgba(pt.get("global.font_colour", "#00FF00"));
	Pango::Weight global_weight = static_cast<Pango::Weight>(pt.get("global.font_weight", 300));
	fd.set_weight(global_weight);
	int min_button_size = pt.get("toolbar.min_button_size", 150);
	m_clockformat = pt.get("clock.timeformat", m_clockformat);
	m_dateformat = pt.get("clock.dateformat", m_dateformat);
	m_clockfontname = pt.get("clock.font_name", m_clockfontname);
	m_clock_font_weight = static_cast<Pango::Weight>(pt.get("clock.font_weight", static_cast<int>(m_clock_font_weight)));
	Gdk::RGBA clock_font_colour(pt.get("clock.font_colour", "#FF0000"));
	// apply to widgits //
	m_taskbar->set_min_button_size(min_button_size);
	fd.set_weight(global_weight);
	m_taskbar->set_fontdescription(fd);
	m_taskbar->override_font(fd);
	override_font(fd);
	// font colour //
	m_taskbar->override_color(rgba);
	m_taskbar->set_colour(rgba);
	override_color(rgba);

	// clock //
	Pango::FontDescription fd_clock(pango_font_description_from_string(m_clockfontname.c_str()));
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " fd_clock.to_string() == " << fd_clock.to_string() << std::endl;
	fd_clock.set_weight(m_clock_font_weight);
	std::cout << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " fd_clock.to_string() == " << fd_clock.to_string() << std::endl;
	m_labelClock->override_font(fd_clock);
	std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << " clock_font_colour.to_string() == " << clock_font_colour.to_string() << std::endl;
	m_labelClock->override_color(clock_font_colour);
	m_labelDate->override_font(fd_clock);
	m_labelDate->override_color(clock_font_colour);
	std::cerr << __FILE__ << '[' << __LINE__ << "] " << __PRETTY_FUNCTION__ << "\t leaving now" << std::endl;
}






