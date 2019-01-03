#include "buttons.h"



//setup GPIO pins

//GPIO.setmode(GPIO.BCM);
//GPIO.setup(17, GPIO.OUT);
//pwm = GPIO.PWM(17, 100);
//pwm.start(5);




int main(int argc, char *argv[])
{

	app_widgets	*widgets = g_slice_new(app_widgets);
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
			//gtk_builder_add_from_file (builder, "glade/window_external.glade", NULL);
	window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	
	widgets->w_rpm_spbtn = GTK_WIDGET(gtk_builder_get_object(builder,"rpm_spbtn"));
	widgets->w_time_spbtn = GTK_WIDGET(gtk_builder_get_object(builder, "time_spbtn"));
	widgets->w_rpm_label = GTK_WIDGET(gtk_builder_get_object(builder, "rpm_label"));
	widgets->w_time_label = GTK_WIDGET(gtk_builder_get_object(builder, "time_label"));
	widgets->w_rpmEncoder = GTK_WIDGET(gtk_builder_get_object(builder, "rpmEncoder"));
	gtk_builder_connect_signals(builder, widgets);
	g_object_unref(builder);
	gtk_widget_show(window_main);                
	//gtk_widget_show(window2);
		
	gtk_main();
	g_slice_free(app_widgets, widgets);

	return 0;


}



void on_window_main_destroy()
{
	gtk_main_quit();
}

