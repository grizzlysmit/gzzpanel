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

#ifndef _WNCK_PAGER_H_
#define _WNCK_PAGER_H_
#include <gtkmm.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>


namespace Wnck {
	
	class Pager : public Gtk::Widget 
	{
		public:
/*#ifndef DOXYGEN_SHOULD_SKIP_THIS
			typedef Pager CppObjectType;
			typedef Pager_Class CppClassType;
			typedef GtkWidget BaseObjectType;
			typedef GtkWidgetClass BaseClassType;
#endif // DOXYGEN_SHOULD_SKIP_THIS //*/
			
			enum DisplayMode { DISPLAY_NAME = WNCK_PAGER_DISPLAY_NAME, DISPLAY_CONTENT = WNCK_PAGER_DISPLAY_CONTENT };

			Pager();
			~Pager();

			///Provides access to the underlying C GtkObject.
			WnckPager* gobj() { return reinterpret_cast<WnckPager*>(gobject_); };

			///Provides access to the underlying C GtkObject.
			const WnckPager* gobj() const { return reinterpret_cast<WnckPager*>(gobject_); };

			// the Pager specific stuff //
			bool set_orientation(Gtk::Orientation orientation);
			bool set_n_rows(int n_rows);
			void set_display_mode(DisplayMode mode);
			void set_show_all(bool show_all_workspaces = true);
			void set_shadow_type(Gtk::ShadowType shadow_type);
		protected:
			//Overrides:
			virtual Gtk::SizeRequestMode get_request_mode_vfunc() const;
			virtual void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const;
			virtual void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const;
			virtual void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const;
			virtual void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const;
			virtual void on_size_allocate(Gtk::Allocation& allocation);
			virtual void on_map();
			virtual void on_unmap();
			virtual void on_realize();
			virtual void on_unrealize();
			virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
			
		private:

	};
	
}; // namespace Wnck  //

#endif // _WNCK_PAGER_H_

