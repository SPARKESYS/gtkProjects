#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <glib.h>
#include <pthread.h>
#include <unistd.h>

#include "buttons.h"


pthread_t tid[3]; 
pthread_mutex_t lock; 

int fd;
char PID[] = "(500,1000,10000,100,0,0,100\r";
char decel[] = "H2222,0,1000,1000,500,50,1\r";
char motor[] = "Q8333,0,0,3000,5000,5000,5000,2000,1000,50,1\r";
char Q[] = "Q";
char motorParams[] = ",0,0,3200,5000,5000,5000,2000,1000,50,1\r";
char serialRpm[100];
char stop[] = "R\r";
char encoder[] = "l\r";

bool sys_ready_speed = false;
bool sys_ready_pos = false;
bool sys_armed = false;
double rpm = 0; // stores integer read from spin button widget
double runTime = 0;
	


int i;
////////////////////////
void * setPid(void *arg) 
{  
	getRpm(rpm);
	pthread_mutex_lock(&lock);
	
 	if ((fd = serialOpen ("/dev/ttyUSB0", 57600)) < 0)
  	{
    	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    	return NULL ;
  	}

  	if (wiringPiSetup () == -1)
  	{
    	fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    	return NULL ;
  	}
  
  	printf ("\nOut: %s: ", PID);
  	fflush (stdout);
  	serialPuts (fd, PID);
  	delay (500);
 	printf ("\n") ;
	return NULL;		
}
/////////////////

void getRpm(int rpm)//conver RPM to serial data and concatenate serial string for mtoro control
{
	char rpmStr[50];
	int rpmVal;
	
	pthread_mutex_lock(&lock);

	strcpy(serialRpm, Q);
	
	rpmVal = (rpm *8.333);
	sprintf(rpmStr,"%d", rpmVal);
	
	
	strcat(serialRpm,rpmStr);
	strcat(serialRpm, motorParams);

	printf("Motor:%s\n",serialRpm);
	
	pthread_mutex_unlock(&lock);


}

void * encoderVal (void * arg)
{
	//gchar out_str[100] = {0}; // buffer for string

	double rpmRead;
	rpmRead= serialGetchar(fd);
	fflush(stdout);
	
	
	while (serialDataAvail (fd))
	{
      		serialPuts(fd,encoder);
      		//g_snprintf(out_str, sizeof(out_str), "%.2f",rpmRead );
		//gtk_label_set_text(GTK_LABEL(app_wdgts->w_rpmEncoder), out_str);
		printf (" -> %3d\n", serialGetchar (fd)) ;
      		fflush (stdout) ;
	}

	return NULL;
}
void * setMotor(void * arg)
{
	
	int error;
	
	if (pthread_mutex_init(&lock, NULL)!=0)
	{
		printf("Mutex could not start\n");
		return NULL;

	}

	
	error = pthread_create(&(tid[2]),NULL, &encoderVal, NULL);
	if (error != 0)
	{	
		printf("\n Thread cannot be created: [%s]", strerror(error));
	}
	

	printf ("\nOut: %s: ", serialRpm);
  	fflush (stdout);
  	serialPuts (fd, serialRpm);
 	 	
	printf("\nRun Time %0.f\n",runTime);
  	delay(runTime);
	printf ("\nOut: %s: ", decel) ;
	fflush (stdout) ;
	serialPuts (fd, decel) ;
     
	delay(5000);
    
  
	printf ("\nOut: %s: ", stop) ;
	fflush (stdout) ;
	serialPuts (fd, stop) ;
	delay(1000);
   	pthread_join(tid[2],NULL);
	pthread_mutex_destroy(&lock);

	serialClose(fd);
	return 0;

}

int on_start_button_clicked (GtkButton *button, app_widgets *app_widgets)
{
	int error;

		
	if (pthread_mutex_init(&lock, NULL)!=0)
	{
		printf("Mutex could not start\n");
		return 1;

	}


	error = pthread_create(&(tid[0]),NULL, &setMotor, NULL);
	if (error != 0)
	{	
		printf("\n Thread cannot be created: [%s]", strerror(error));
	}
	
	pthread_join(tid[0],NULL);
	pthread_mutex_destroy(&lock);
	return 0;

}

int  on_set_params_clicked (GtkButton * button, app_widgets *app_wdgts)
{
	
	int error;

		
	if (pthread_mutex_init(&lock, NULL)!=0)
	{
		printf("Mutex could not start\n");
		return 1;

	}


	error = pthread_create(&(tid[1]),NULL, &setPid, NULL);
	if (error != 0)
	{	
		printf("\n Thread cannot be created: [%s]", strerror(error));
	}
	
	
	
	pthread_join(tid[1],NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}




void on_rpm_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts)
{
	gchar out_str[100] = {0}; // buffer for string

	rpm = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->w_rpm_spbtn));
	g_snprintf(out_str, sizeof(out_str), "%.2f", rpm);
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_rpm_label), out_str);
}

void on_time_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts)
{
	gchar out_str[100] = {0}; // buffer for string

	runTime = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->w_time_spbtn));
	g_snprintf(out_str, sizeof(out_str), "%.2f", runTime);
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_time_label), out_str);
	runTime *=1000;
	
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

