#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>



#include "buttons.h"

bool sys_ready_speed = false;
bool sys_ready_pos = false;
bool sys_armed = false;
double rpm = 0; // stores integer read from spin button widget
double runTime = 0;

int fd;
char PID[] = "(500,1000,10000,100,0,0,100\r";
char decel[] = "H2222,0,1000,1000,500,50,1\r";
char Q[] = "Q";
char motorParams[] = ",0,0,2800,5000,5000,5000,2000,1000,50,1\r";
char serialRpm[100];
char stop[] = "R\r";
char encoder[] = "l\r";
int i;

void  getRpm(int rpm)//conver RPM to serial data and concatenate serial string for mtoro control
{
	char rpmStr[50];
	int rpmVal;
	
	strcpy(serialRpm, Q);
	
	rpmVal = (rpm *8.333);
	sprintf(rpmStr,"%d", rpmVal);
	
	
	strcat(serialRpm,rpmStr);
	strcat(serialRpm, motorParams);

	printf("Motor:%s\n",serialRpm);


		
}


int on_start_button_clicked (GtkButton *button, app_widgets *app_widgets)
{
	

	printf("Motor Starting\n %s\n",serialRpm);
	fflush(stdout);
	delay(1000);

	serialPuts(fd, serialRpm);
	
	delay(runTime);
	fflush(stdout);
	
	serialPuts(fd,decel);
	delay (runTime/2);
	
	fflush(stdout);
	serialPuts (fd, stop);

	serialClose(fd);


	return 0;





}
int  on_set_params_clicked (GtkButton * button, app_widgets *app_wdgts)
{
	printf("Set Params\n");
	
	getRpm(rpm);
	
	printf("%s\n",serialRpm);
	
	if ((fd = serialOpen ("/dev/ttyUSB0", 57600)) <0)
	{
		fprintf(stderr, "Unable to open serial device: %s\n",strerror (errno));
		return 1;		
	}
	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno));
		return 1;
	}

	fflush(stdout);
	serialPuts (fd, PID);
	
	delay (3000);
	fflush(stdout);
	printf("PID Set\n");

	return 0;
}
void on_rpm_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts)
{
	//printf("speed button\n");
	gchar out_str[100] = {0}; // buffer for string

	rpm = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->w_rpm_spbtn));
	g_snprintf(out_str, sizeof(out_str), "%.2f", rpm);
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_rpm_label), out_str);
	
	

	//printf("speed button\n");
}

void on_time_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts)
{
	
	double runTime = 0;
	gchar out_str[100] = {0}; // buffer for string

	runTime = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->w_time_spbtn));
	g_snprintf(out_str, sizeof(out_str), "%.2f", runTime);
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_time_label), out_str);

	
	//printf("position button \n");
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

