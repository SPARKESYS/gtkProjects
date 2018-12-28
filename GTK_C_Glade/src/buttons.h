#ifndef BUTTONS
#define BUTTONS



#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>    // read/write usleep
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions
#include <wiringPi.h>



GtkBuilder      *builder; 
GtkWidget       *window_main;
GtkWidget	*window_debug;
typedef struct
{
	GtkWidget *w_rpm_label;//speed rpm update
	GtkWidget *w_rpm_spbtn;
	GtkWidget *w_rpmEncoder;	
	GtkWidget *w_time_label;//run time update
	GtkWidget *w_time_spbtn;



}app_widgets;
void * setPid(void *arg); 
void getRpm(int rpm);
int on_start_button_clicked (GtkButton *button, app_widgets *app_widgets);
int  on_set_params_clicked (GtkButton * button, app_widgets *app_wdgts);
void on_rpm_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts);
void on_time_spbtn_value_changed (GtkButton *button, app_widgets *app_wdgts);
void on_debug_btn_clicked (GtkButton *button, app_widgets *app_wdgts);
void on_debug_back_clicked (GtkButton *button, app_widgets *app_wdgts);


#endif
