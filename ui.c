#include <gtk/gtk.h>
#include <stdlib.h>
#include "ui.h"
#include "swww.h"

static GtkWidget *entry_path;
static GtkWidget *combo_transition;
static GtkWidget *entry_duration;

static const char *transitions[] = {"any", "wipe", "fade", "none"};

static void on_apply_clicked(GtkWidget *widget, gpointer data) {
    const gchar *path = gtk_entry_get_text(GTK_ENTRY(entry_path));
    const gchar *duration = gtk_entry_get_text(GTK_ENTRY(entry_duration));
    gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_transition));
    const gchar *transition = transitions[active];

    run_swww_command(path, transition, duration);
}

void build_ui(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "swww Frontend");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *label_path = gtk_label_new("Wallpaper Path:");
    entry_path = gtk_entry_new();

    GtkWidget *label_transition = gtk_label_new("Transition Type:");
    combo_transition = gtk_combo_box_text_new();
    for (int i = 0; i < 4; ++i)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_transition), transitions[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_transition), 2);

    GtkWidget *label_duration = gtk_label_new("Duration (s):");
    entry_duration = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_duration), "1.0");

    GtkWidget *button_apply = gtk_button_new_with_label("Apply Wallpaper");
    g_signal_connect(button_apply, "clicked", G_CALLBACK(on_apply_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), label_path, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_path, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_transition, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), combo_transition, 1, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_duration, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_duration, 1, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_apply, 0, 3, 2, 1);

    gtk_widget_show_all(window);
}
