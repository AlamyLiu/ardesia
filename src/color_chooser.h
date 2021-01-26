/*
 * Copyright (C) 2009 Pilolli Pietro <pilolli.pietro@gmail.com>
 * Copyright (C) 2021 Alamy Liu <Alamy.Liu@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <gtk/gtk.h>

/*
 * Start the dialog that ask to the user where save the image
 * containing the screenshot; it return the selected colour.
 */
void start_color_chooser_dialog(
    GtkToolButton * toolbutton,
    GtkWindow * parent,
    GdkRGBA * color);
