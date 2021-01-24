/*
 * Ardesia -- a program for painting on the screen
 * with this program you can play, draw, learn and teach
 * This program has been written such as a freedom sonet
 * We believe in the freedom and in the freedom of education
 *
 * Copyright (C) 2009 Pilolli Pietro <pilolli.pietro@gmail.com>
 *
 * Ardesia is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ardesia is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif

#include <color_chooser.h>
#include <utils.h>
#include <keyboard.h>

/* old picked color in RGBA format */
//static GdkRGBA *picked_color = NULL;

/*
 * Start the color selector dialog
 * it return the selected color.
 */
void start_color_chooser_dialog(
    GtkToolButton * toolbutton,
    GtkWindow * parent,
    GdkRGBA *color)
{
    GtkToggleToolButton *button = GTK_TOGGLE_TOOL_BUTTON(toolbutton);
    GtkWidget *color_dialog;

    /* No need to continued if there is no space to store color */
    if (!color) {
        return;
    }

    if (!gtk_toggle_tool_button_get_active(button)) {
        return;
    }

    start_virtual_keyboard();

    /* Create a color chooser dialog */
    color_dialog = gtk_color_chooser_dialog_new ("Choose color",
                                                 GTK_WINDOW (parent));

    /* Pre-choose current color */
    gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (color_dialog), color);
    gint response_id = gtk_dialog_run (GTK_DIALOG (color_dialog));

    /* Wait for user to select OK or Cancel. */
    if (response_id == GTK_RESPONSE_OK) {
        gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (color_dialog), color);
    }

    gtk_widget_destroy(color_dialog);

    stop_virtual_keyboard();

    return;
}
