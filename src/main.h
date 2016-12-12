#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include "weather/weather.h"
#include "calendar/calendar.h"

typedef struct weather {
  const char *icon_paths[4];
  const char *time_info[4];
  const char *temp[4];
} weather;

typedef struct weather_view {
	GtkWidget *w_images[4];
	GtkWidget *w_titles[4];
	GtkWidget *w_temps[4];
} weather_view;

static void set_textview_styling(GtkWidget *widget, const char *font_descriptor, GdkRGBA *rgba_bg, GdkRGBA *rgba_fg);
void clock_handler(GtkTextBuffer *text);
void weather_handler(weather_view *wv);
GtkWidget* generate_main_window(GtkApplication *app, const gchar *title, gint w, gint h, gint padding, GdkRGBA *rgba);
GtkWidget* generate_clock_view(const char *font_descriptor, GdkRGBA *rgba_bg, GdkRGBA *rgba_fg);
static void activate(GtkApplication *app, gpointer user_data);
void generate_weather_struct(json *weather_json);

#endif