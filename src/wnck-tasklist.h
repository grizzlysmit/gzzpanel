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

#ifndef _WNCK_TASKLIST_H_
#define _WNCK_TASKLIST_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>

namespace Wnck {

	class Tasklist_Class;

	class Tasklist: public Gtk::Container 
	{
		public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
			typedef Tasklist CppObjectType;
			typedef Tasklist_Class CppClassType;
			typedef WnckTasklist BaseObjectType;
			typedef WnckTasklistClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
			
			enum GroupingType { 
				NEVER_GROUP = WNCK_TASKLIST_NEVER_GROUP,
				AUTO_GROUP = WNCK_TASKLIST_AUTO_GROUP,
				ALWAYS_GROUP = WNCK_TASKLIST_ALWAYS_GROUP
			};

			//                      return,      icon_name         size    flags              //
			typedef sigc::signal<GdkPixbuf*, const Glib::ustring&, int, unsigned> type_signal_load_icon;

			//                      return,      icon_name         size    flags              //
			typedef sigc::signal<void, Gtk::Allocation&> type_signal_allocation;
			
			Tasklist();
			~Tasklist();

			///Provides access to the underlying C GtkObject.
			Tasklist* gobj() { return reinterpret_cast<Tasklist*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const Tasklist* gobj() const { return reinterpret_cast<Tasklist*>(gobject_); };

			// The Task bar stuff //
			void set_grouping(GroupingType grouping);
			void set_grouping_limit(gint limit);
			void set_include_all_workspaces(bool include_all_workspaces);
			void set_switch_workspace_on_unminimize(bool switch_workspace_on_unminimize);
			void set_button_relief(Gtk::ReliefStyle relief);
			const std::vector<int> get_size_hint_list();

			///Do not use this for internal use only 
			GdkPixbuf* signal_load_icon_emit(const Glib::ustring icon_name, int size, unsigned flags);
			
			// signal for the load icon fun call back //
			type_signal_load_icon signal_load_icon();
			type_signal_allocation signal_allocation();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
			static GType get_type()      G_GNUC_CONST;


			static GType get_base_type() G_GNUC_CONST;
#endif
			
		protected:
			type_signal_load_icon m_signal_load_icon;
			type_signal_allocation m_signal_allocation;

			explicit Tasklist(const Glib::ConstructParams& construct_params);
			explicit Tasklist(WnckTasklist* castitem);
			
			//Overrides:
/*			virtual Gtk::SizeRequestMode get_request_mode_vfunc() const;
			virtual void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const;
			virtual void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const;
			virtual void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const;
			virtual void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const;*/
			virtual void on_size_allocate(Gtk::Allocation& allocation);
			virtual void on_map();
			virtual void on_unmap();
			virtual void on_realize();
			virtual void on_unrealize();
			virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		private:
			friend class Tasklist_Class;
			static CppClassType tasklist_class_;

			// noncopyable
			Tasklist(const Tasklist&);
			Tasklist& operator=(const Tasklist&);
			

	};
	
}; // namespace Wnck //


namespace Glib
{
	/** A Glib::wrap() method for this object.
		* 
	 * @param object The C instance.
	 * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
	 * @result A C++ instance that wraps this C instance.
	 *
	 * @relates Gtk::Toolbar
	 */
	Wnck::Tasklist* wrap(WnckTasklist* object, bool take_copy = false);
} //namespace Glib





#endif // _WNCK_TASKLIST_H_

