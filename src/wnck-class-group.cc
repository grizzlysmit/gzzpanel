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

#include "wnck-class-group.h"

namespace Wnck {

	ClassGroup::ClassGroup(WnckClassGroup *cg)
		: Glib::Object(reinterpret_cast<GObject*>(cg))
	{
	}

	ClassGroup::ClassGroup(const Glib::ustring &id)
		: Glib::Object(reinterpret_cast<GObject*>(wnck_class_group_get(id.c_str())))
	{
	}

	ClassGroup::~ClassGroup()
	{
	}

	bool ClassGroup::class_group_id_valid(const Glib::ustring &id) const
	{
		return wnck_class_group_get(id.c_str());
	}

	const Glib::ustring ClassGroup::get_id() const
	{
		return Glib::ustring(wnck_class_group_get_id(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	const Glib::ustring ClassGroup::get_name() const
	{
		return Glib::ustring(wnck_class_group_get_name(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	Glib::RefPtr<Gdk::Pixbuf> ClassGroup::get_icon() const
	{
		return Glib::wrap(wnck_class_group_get_icon(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	Glib::RefPtr<Gdk::Pixbuf> ClassGroup::get_mini_icon() const
	{
		return Glib::wrap(wnck_class_group_get_mini_icon(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj()))));
	}

	std::vector<Window*> ClassGroup::get_windows()
	{
		std::vector<Window*> result;
		GList *lst = wnck_class_group_get_windows(const_cast<WnckClassGroup*>(reinterpret_cast<const WnckClassGroup*>(gobj())));
		for(GList *i = lst; i; i = i->next){
			result.insert(result.end(), Glib::wrap(reinterpret_cast<WnckWindow*>(i->data)));
		}
		return result;
	}

}; // namespace Wnck //

namespace {

	static const Glib::SignalProxyInfo ClassGroup_signal_icon_changed_info =
	{
		"icon_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};

	static const Glib::SignalProxyInfo ClassGroup_signal_name_changed_info =
	{
		"name_changed",
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
		(GCallback) &Glib::SignalProxyNormal::slot0_void_callback
	};


}; // anonymous namespace  //

namespace Wnck {

	Glib::SignalProxy0<void> ClassGroup::signal_icon_changed()
	{
		return Glib::SignalProxy0<void>(this, &ClassGroup_signal_icon_changed_info);
	}

	Glib::SignalProxy0<void> ClassGroup::signal_name_changed()
	{
		return Glib::SignalProxy0<void>(this, &ClassGroup_signal_name_changed_info);
	}
	
}; // namespace Wnck //


namespace Glib
{

	Wnck::ClassGroup* wrap(WnckClassGroup* object/*, bool take_copy*/)
	{
		return dynamic_cast<Wnck::ClassGroup*>(Glib::wrap_auto(reinterpret_cast<GObject*>(object), false));
	}
	
} // namespace Glib //


