/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 15 июн. 2017 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#include <ui/ctl/ctl.h>

namespace lsp
{
    namespace ctl
    {
        // Names of widget tags, should be alphabetically sorted
        const char *widget_tags[] =
        {
            "align",
            "axis",
            "body",
            "box",
            "button",
            "capture3d",
            "cell",
            "center",
            "cgroup",
            "combo",
            "dot",
            "edit",
            "fader",
            "fbuffer",
            "file",
            "frac",
            "graph",
            "grid",
            "group",
            "hbox",
            "hgrid",
            "hlink",
            "hsbar",
            "hsbox",
            "hsep",
            "indicator",
            "knob",
            "label",
            "led",
            "listbox",
            "load",
            "marker",
            "mesh",
            "meter",
            "midinote",
            "mstud",
            "param",
            "plugin",
            "port",
            "progress",
            "sample",
            "save",
            "sbar",
            "sbox",
            "sep",
            "source3d",
            "status",
            "stream",
            "switch",
            "text",
            "threadcombo",
            "ttap",
            "value",
            "vbox",
            "vgrid",
            "viewer3d",
            "void",
            "vsbar",
            "vsbox",
            "vsep",
            "window"
        };

        // Names of widget attributes, should be alphabetically sorted
        const char *widget_attributes[] =
        {
            "activity",
            "activity2",
            "activity2_id",
            "activity_id",
            "angle",
            "angle_id",
            "aspect",
            "balance",
            "basis",
            "bg_color",
            "bind",
            "border",
            "border_color",
            "bright",
            "center",
            "color",
            "color2",
            "cols",
            "command_id",
            "coord",
            "curvature_id",
            "cycle",
            "default",
            "detailed",
            "distance_id",
            "duration_id",
            "dx",
            "dy",
            "editable",
            "embed",
            "expand",
            "fadein_id",
            "fadeout_id",
            "fill",
            "font_size",
            "format",
            "format_id",
            "fov",
            "halign",
            "head_id",
            "height",
            "height_id",
            "hfill",
            "horizontal",
            "hpos",
            "hpos_id",
            "hscale",
            "hscroll",
            "hspacing",
            "hue2_id",
            "hue_id",
            "hue_shift",
            "id",
            "id2",
            "invert",
            "key",
            "kvt_root",
            "led",
            "length",
            "length_id",
            "light2_id",
            "light_id",
            "logarithmic",
            "max",
            "max_dots",
            "max_duration_id",
            "max_height",
            "max_width",
            "mesh_id",
            "min",
            "min_height",
            "min_width",
            "mode",
            "mode_id",
            "note_id",
            "octave_id",
            "offset",
            "opacity",
            "orientation_id",
            "pad_bottom",
            "pad_left",
            "pad_right",
            "pad_top",
            "padding",
            "parallel",
            "path_id",
            "pitch_id",
            "precision",
            "progress_id",
            "proportional",
            "radius",
            "radius_id",
            "read_only",
            "resizable",
            "reversive",
            "roll_id",
            "rows",
            "s_index",
            "same_line",
            "sat2_id",
            "sat_id",
            "scale_color",
            "scale_hue",
            "scale_hue_id",
            "scale_light_id",
            "scale_sat_id",
            "scroll_id",
            "size",
            "size_id",
            "smooth",
            "spacing",
            "status_id",
            "step",
            "stereo",
            "strobe",
            "strobes",
            "tail_id",
            "text",
            "text_color",
            "tiny_step",
            "toggle",
            "transparency",
            "transpose",
            "type",
            "ui:id",
            "units",
            "url",
            "valign",
            "value",
            "vertical",
            "vfill",
            "visibility",
            "visibility_id",
            "visibility_key",
            "visible",
            "vpos",
            "vpos_id",
            "vscale",
            "vscroll",
            "vspacing",
            "width",
            "x_index",
            "xpos_id",
            "xscale_id",
            "y_index",
            "yaw_id",
            "ypos_id",
            "yscale_id",
            "zpos_id",
            "zscale_id"
        };

        widget_ctl_t widget_ctl(const char *name)
        {
            ssize_t first = 0, last = (sizeof(widget_tags)/sizeof(const char *)) - 1;

            while (first <= last)
            {
                ssize_t id = (first + last) >> 1;
                int res = strcmp(widget_tags[id], name);
                if (res == 0)
                    return widget_ctl_t(id);
                if (res < 0)
                    first   = id + 1;
                else
                    last    = id - 1;
            }

            return WC_UNKNOWN;
        }

        const char *widget_ctl(widget_ctl_t type)
        {
            return (type != WC_UNKNOWN) ? widget_tags[type] : NULL;
        }

        widget_attribute_t widget_attribute(const char *name)
        {
            ssize_t first = 0, last = (sizeof(widget_attributes)/sizeof(const char *)) - 1;

            while (first <= last)
            {
                ssize_t id = (first + last) >> 1;
                int res = strcmp(widget_attributes[id], name);
                if (res == 0)
                    return widget_attribute_t(id);
                if (res < 0)
                    first   = id + 1;
                else
                    last    = id - 1;
            }

            return A_UNKNOWN;
        }

        const char *widget_attribute(widget_attribute_t type)
        {
            return (type != A_UNKNOWN) ? widget_attributes[type] : NULL;
        }

        scrolling_t widget_scroll(const char *value)
        {
            if ((!::strcmp(value, "1")) ||
                (!::strcasecmp(value, "optional")) ||
                (!::strcasecmp(value, "o")))
                return SCROLL_OPTIONAL;
            if ((!::strcmp(value, "2")) ||
                (!::strcasecmp(value, "always")) ||
                (!::strcasecmp(value, "a")) ||
                (!::strcasecmp(value, "true")) ||
                (!::strcasecmp(value, "t")))
                return SCROLL_ALWAYS;

            return SCROLL_NONE;
        }
    }
}
