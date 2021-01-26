/*
 * Copyright (C) 2009 Pilolli Pietro <pilolli.pietro@gmail.com>
 * Copyright (C) 2021 Alamy Liu <Alamy.Liu@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
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
