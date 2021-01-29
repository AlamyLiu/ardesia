/*
 * Copyright (C) 2009 Pilolli Pietro <pilolli.pietro@gmail.com>
 * Copyright (C) 2021 Alamy Liu <Alamy.Liu@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <utils.h>
#include <preference_dialog.h>
#include <background_window.h>

/* Update the preview image. */
G_MODULE_EXPORT void on_image_chooser_button_update_preview(
    GtkFileChooser * file_chooser,
    gpointer data)
{
    PreferenceData *preference_data = (PreferenceData *) data;
    gchar *filename;
    GdkPixbuf *pixbuf;
    gboolean have_preview;

    filename = gtk_file_chooser_get_preview_filename(file_chooser);

    if (filename) {
        pixbuf = gdk_pixbuf_new_from_file_at_size(filename, 128, 128, NULL);
        have_preview = (pixbuf != NULL);
        g_free(filename);
        filename = NULL;

        gtk_image_set_from_pixbuf(GTK_IMAGE(preference_data->preview),
                                  pixbuf);

        if (pixbuf) {
            g_object_unref(pixbuf);
            pixbuf = NULL;
        }

        gtk_file_chooser_set_preview_widget_active(file_chooser,
                                                   have_preview);
    }
}

/* Shot when the selected folder change in the file browser. */
G_MODULE_EXPORT void on_image_chooser_button_file_set(
    GtkButton * buton,
    gpointer data)
{
    PreferenceData *preference_data = (PreferenceData *) data;
    GObject *file_obj =
        gtk_builder_get_object(preference_data->preference_dialog_gtk_builder,
                               "file");
    GtkToggleButton *image_tool_button = GTK_TOGGLE_BUTTON(file_obj);
    gtk_toggle_button_set_active(image_tool_button, TRUE);
}

/* Shot when is pushed the background colour button. */
G_MODULE_EXPORT void on_background_color_button_color_set(
    GtkButton * buton,
    gpointer data)
{
    PreferenceData *preference_data = (PreferenceData *) data;
    GObject *color_obj =
        gtk_builder_get_object(preference_data->preference_dialog_gtk_builder,
                               "color");
    GtkToggleButton *color_tool_button = GTK_TOGGLE_BUTTON(color_obj);
    gtk_toggle_button_set_active(color_tool_button, TRUE);
}

/* Shot when the ok button in preference dialog is pushed. */
G_MODULE_EXPORT void on_preference_ok_button_clicked(
    GtkButton * buton,
    gpointer data)
{
    PreferenceData *preference_data = (PreferenceData *) data;
    gchar *a = NULL;
    GObject *color_tool_obj =
        gtk_builder_get_object(preference_data->preference_dialog_gtk_builder,
                               "color");
    GtkToggleButton *color_tool_button = GTK_TOGGLE_BUTTON(color_tool_obj);

    if (gtk_toggle_button_get_active(color_tool_button)) {
        /* background colour */
        GObject *bg_color_obj =
            gtk_builder_get_object
            (preference_data->preference_dialog_gtk_builder,
             "backgroundColorButton");

        GtkColorButton *background_color_button =
            GTK_COLOR_BUTTON(bg_color_obj);
        GdkColor *gdkcolor = g_malloc((gsize) sizeof(GdkColor));
        gtk_color_button_get_color(background_color_button, gdkcolor);
        GdkRGBA gdkrgba = {
            .red   = CLAMP ((double) gdkcolor->red   / 65535.0, 0.0, 1.0),
            .green = CLAMP ((double) gdkcolor->green / 65535.0, 0.0, 1.0),
            .blue  = CLAMP ((double) gdkcolor->blue  / 65535.0, 0.0, 1.0),
            .alpha = 1.0,
        };
        update_background_color( &gdkrgba );

        g_free(a);
        g_free(gdkcolor);
        set_background_type(1);
    } else {
        GObject *file_obj =
            gtk_builder_get_object
            (preference_data->preference_dialog_gtk_builder, "file");
        GtkToggleButton *image_tool_button = GTK_TOGGLE_BUTTON(file_obj);
        if (gtk_toggle_button_get_active(image_tool_button)) {
            /* background png from file */
            GObject *image_obj =
                gtk_builder_get_object
                (preference_data->preference_dialog_gtk_builder,
                 "imageChooserButton");
            GtkFileChooserButton *image_chooser_button =
                GTK_FILE_CHOOSER_BUTTON(image_obj);
            gchar *filename =
                gtk_file_chooser_get_filename(GTK_FILE_CHOOSER
                                              (image_chooser_button));
            if (filename) {
                FILE *stream = g_fopen(filename, "r");
                if (stream == NULL) {
                    GObject *preference_obj = (GObject *) NULL;
                    GtkWindow *preference_window = (GtkWindow *) NULL;
                    preference_obj =
                        gtk_builder_get_object
                        (preference_data->preference_dialog_gtk_builder,
                         "preferences");
                    preference_window = GTK_WINDOW(preference_obj);
                    show_permission_denied_dialog(preference_window);
                } else {
                    update_background_image(filename);
                    set_background_type(2);
                    fclose(stream);
                }
            } else {
                /* The file is not set; same cae that no background */
                clear_background_window();
                set_background_type(0);
            }
        } else {
            /* none */
            clear_background_window();
            set_background_type(0);
        }
    }
}

/* Shot when is pushed the cancel button. */
G_MODULE_EXPORT void on_preference_cancel_button_clicked(
    GtkButton * buton,
    gpointer data)
{
    /* do nothing */
}
