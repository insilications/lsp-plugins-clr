/*
 * Gtk2Led.cpp
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: sadko
 */

#include <ui/gtk2/ui.h>
#include <core/debug.h>

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

namespace lsp
{
    Gtk2Led::Gtk2Led(plugin_ui *ui): Gtk2CustomWidget(ui, W_LED)
    {
        sBgColor.set(pUI->theme(), C_BACKGROUND);

        nSize       = 8;
        fValue      = 0;
        pPort       = NULL;
        fKey        = 1;

        sColor.init(this, C_GREEN, A_COLOR, -1, -1, -1, A_HUE_ID, A_SAT_ID, A_LIGHT_ID);
    }

    Gtk2Led::~Gtk2Led()
    {
    }

    bool Gtk2Led::key_matched()
    {
        return abs(fValue - fKey) <= CMP_TOLERANCE;
    }

    void Gtk2Led::draw(cairo_t *cr)
    {
        cairo_pattern_t *cp;

        // Draw background
        cairo_set_source_rgba(cr, sBgColor.red(), sBgColor.green(), sBgColor.blue(), 1.0);
        cairo_rectangle(cr, 0, 0, nWidth, nHeight);
        cairo_fill(cr);

        // Move to center of the led
        cairo_translate(cr, ssize_t(nWidth >> 1), ssize_t(nHeight >> 1));

        // Draw hole
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_arc(cr, 0, 0, (nSize >> 1) + 1, 0, 2.0 * M_PI);
        cairo_fill(cr);

        Color col(sColor);

        if (key_matched())
        {
            // Draw light
            cp = cairo_pattern_create_radial (0, 0, 0, 0, 0, nSize);
            cairo_pattern_add_color_stop_rgba(cp, 0.0, col.red(), col.green(), col.blue(), 0.5);
            cairo_pattern_add_color_stop_rgba(cp, 1.0, col.red(), col.green(), col.blue(), 0.0);
            cairo_set_source (cr, cp);
            cairo_arc(cr, 0, 0, nSize, 0, 2.0 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(cp);

            // Draw led spot
            Color c_light(col);
            c_light.lightness(c_light.lightness() * 1.5);

            cp = cairo_pattern_create_radial (0, 0, nSize >> 3, 0, 0, nSize >> 1);
            cairo_pattern_add_color_stop_rgb (cp, 0, c_light.red(), c_light.green(), c_light.blue());
            cairo_pattern_add_color_stop_rgb (cp, 1.0, col.red(), col.green(), col.blue());
            cairo_set_source (cr, cp);
            cairo_arc(cr, 0, 0, nSize >> 1, 0, 2.0 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(cp);

            // Add blink
            cp = cairo_pattern_create_radial (nSize >> 3, -ssize_t(nSize >> 3), 0, 0, 0, nSize >> 1);
            cairo_pattern_add_color_stop_rgba(cp, 0.0, 1.0, 1.0, 1.0, 1.0);
            cairo_pattern_add_color_stop_rgba(cp, 1.0, 1.0, 1.0, 1.0, 0.0);
            cairo_set_source (cr, cp);
            cairo_arc(cr, 0, 0, (nSize >> 1) - 1, 0, 2.0 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(cp);
        }
        else
        {
            ColorHolder c;
            c.set(pUI->theme(), C_GLASS);

            float r=c.red() + (col.red() - c.red()) * 0.4;
            float g=c.green() + (col.green() - c.green()) * 0.4;
            float b=c.blue() + (col.blue() - c.blue()) * 0.4;

            // Draw led glass
            cp = cairo_pattern_create_radial (0, 0, nSize >> 3, 0, 0, nSize >> 1);
            cairo_pattern_add_color_stop_rgb(cp, 0, r, g, b);
            cairo_pattern_add_color_stop_rgb(cp, 1.0, c.red(), c.green(), c.blue());
            cairo_set_source (cr, cp);
            cairo_arc(cr, 0, 0, (nSize >> 1)+1, 0, 2.0 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(cp);

            // Add blink
            cp = cairo_pattern_create_radial (nSize >> 3, -ssize_t(nSize >> 3), 0, 0, 0, nSize >> 1);
            cairo_pattern_add_color_stop_rgba(cp, 0.0, 1.0, 1.0, 1.0, 0.2);
            cairo_pattern_add_color_stop_rgba(cp, 1.0, 1.0, 1.0, 1.0, 0.0);
            cairo_set_source (cr, cp);
            cairo_arc(cr, 0, 0, (nSize >> 1) - 1, 0, 2.0 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(cp);
        }
    }

    void Gtk2Led::resize(size_t &w, size_t &h)
    {
        w = (nSize << 1);
        h = (nSize << 1);
    }

    void Gtk2Led::set(widget_attribute_t att, const char *value)
    {
        switch (att)
        {
            case A_ID:
                BIND_PORT(pUI, pPort, value);
                break;
            case A_KEY:
                PARSE_FLOAT(value, fKey = __);
                break;
            case A_SIZE:
                PARSE_INT(value, nSize = size_t(__));
                break;
            case A_BG_COLOR:
                sBgColor.set(pUI->theme(), value);
                break;
            default:
                if (sColor.set(att, value))
                    break;
                Gtk2CustomWidget::set(att, value);
                break;
        }
    }

    void Gtk2Led::notify(IUIPort *port)
    {
        Gtk2CustomWidget::notify(port);

        bool redraw = false;
        if (sColor.notify(port))
            redraw = true;
        else if (port == pPort)
        {
            const port_t *mdata = pPort->metadata();
            fValue = 0;
            if (mdata != NULL)
                fValue      = pPort->getValue();

            redraw = true;
        }

        // Request for redraw
        if (redraw)
            markRedraw();
    }

} /* namespace lsp */