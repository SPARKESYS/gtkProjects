#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "buttons.h"

bool sys_ready_speed = false;
bool sys_ready_pos = false;
bool sys_armed = false;
double quantity = 0; // stores integer read from spin button widget

void on_start_button_clicked (GtkButton *button, app_widgets *app_widgets)
{
	printf("Start Button\n");

}
void on_set_params_clicked (GtkButton * button, app_widgets *app_wdgts)
{
	printf("Set Params\n");
}

void on_speed_update_clicked (GtkButton *button, app_widgets *app_wdgts)
{
	printf("speed button\n");
}

void on_pos_update_clicked (GtkButton *button, app_widgets *app_wdgts)
{
	printf("position button \n");
}

void on_debug_btn_clicked (GtkButton *button, app_widgets *app_wdgts)
{
	
	printf("Debug Button");
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
	
	window_debug = GTK_WIDGET(gtk_builder_get_object(builder, "window_debug"));	
	window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	
	gtk_builder_connect_signals(builder,NULL);
	printf("open external control window\n");
	//gtk_widget_set_opacity(window,0);
	gtk_widget_show(window_debug);
	gtk_widget_grab_focus(window_debug);
	gtk_grab_add(window_debug);
	gtk_widget_hide(window_main);



}

void on_debug_back_clicked (GtkButton *button, app_widgets *app_wdgts)
{
	printf("Destroy debug window\n");
	gtk_widget_destroy(window_debug);
}

