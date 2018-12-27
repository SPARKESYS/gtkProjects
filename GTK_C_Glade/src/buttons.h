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
	GtkWidget *w_speed_value;//speed percentage update
	GtkWidget *w_sbtn_button;
	
	GtkWidget *w_pos_limit;//stop position update
	GtkWidget *w_pos_button;



}app_widgets;
void on_start_button_clicked();
void on_set_params_clicked();

#endif
