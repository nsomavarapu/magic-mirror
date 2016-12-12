#include "main.h"

static void set_textview_styling(GtkWidget *widget, const char *font_descriptor, GdkRGBA *rgba_bg, GdkRGBA *rgba_fg) {
  PangoFontDescription *font_desc;

  gtk_widget_override_background_color(widget, GTK_STATE_FLAG_NORMAL, rgba_bg);
  gtk_widget_override_color(widget, GTK_STATE_FLAG_NORMAL, rgba_fg);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(widget), false);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(widget), false);
  gtk_text_view_set_justification(GTK_TEXT_VIEW(widget), GTK_JUSTIFY_CENTER);
  font_desc = pango_font_description_from_string(font_descriptor);
  gtk_widget_override_font(widget, font_desc);
  pango_font_description_free(font_desc);
}

void clock_handler(GtkTextBuffer *text) {
  GDateTime *now = g_date_time_new_now_local(); 
  gchar *my_time = g_date_time_format(now, "%I:%M %p");
  
  gtk_text_buffer_set_text(text, my_time, -1);
  
  g_free(my_time);
  g_date_time_unref(now);
}

void weather_handler(weather_view *wv) {
  json weatherData = getWeather(33.7756, -84.3963);

  for(int i = 0; i < 4; i++) {
    json index = weatherData[std::to_string(i)];
    json iconJson = index["icon"];
    json timeJson = index["time"];
    json tempJson = index["temp"];

    string iconStringRaw = iconJson.dump();
    string iconString = iconStringRaw.substr(3, iconStringRaw.length() - 6);
    string path = "res/" + iconString + ".png";

    string timeStringRaw = timeJson.dump();
    string time = timeStringRaw.substr(1, timeStringRaw.length() - 2);

    string tempStringRaw = tempJson.dump();
    string temp = tempStringRaw.substr(1, tempStringRaw.length() - 2);

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(wv->w_titles[i])), time.c_str(), -1);
    // printf(time.c_str(), "%s");
    // printf("\n");
    gtk_image_set_from_file(GTK_IMAGE(wv->w_images[i]), path.c_str());
    // printf(path.c_str(), "%s");
    // printf("\n");
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(wv->w_temps[i])), temp.c_str(), -1);
    // printf(temp.c_str(), "%s");
    // printf("\n");
  }
}

GtkWidget* generate_main_window(GtkApplication *app, const gchar *title, gint w, gint h, gint padding, GdkRGBA *rgba) {
  GtkWidget *window;

  window = gtk_application_window_new(app);
    
  gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, rgba);
  gtk_window_set_title(GTK_WINDOW(window), title);
  gtk_window_set_default_size(GTK_WINDOW(window), w, h);
  gtk_container_set_border_width(GTK_CONTAINER(window), padding);

  return window;
} 

GtkWidget* generate_clock_view(const char *font_descriptor, GdkRGBA *rgba_bg, GdkRGBA *rgba_fg) {
  GtkWidget *clock_view;

  clock_view = gtk_text_view_new();
  set_textview_styling(clock_view, font_descriptor, rgba_bg, rgba_fg);
  return clock_view;
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget  *window;
  GtkWidget  *grid;
  GtkWidget  *clock_view;
  GdkRGBA    rgba_bg, rgba_fg;
  GdkRGBA    color_pallette[3];
  GtkWidget  *calendar;
  GtkWidget  *events[3];
  const char *events_strings[3];
  GtkWidget  *weather_images[4];
  GtkWidget  *weather_titles[4];
  GtkWidget *weather_temps[4];

  gdk_rgba_parse(&rgba_bg, "black");
  gdk_rgba_parse(&rgba_fg, "white");
  gdk_rgba_parse(&color_pallette[0], "#F49AC2");
  gdk_rgba_parse(&color_pallette[1], "#CB99C9");
  gdk_rgba_parse(&color_pallette[2], "#77DD77");

  window = generate_main_window(app, "Magic Mirror", 1390, 768, 10, &rgba_bg);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER (window), grid);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);

  clock_view = generate_clock_view("40", &rgba_bg, &rgba_fg);
  gtk_grid_attach(GTK_GRID(grid), clock_view, 0, 0, 4, 1);
  clock_handler(gtk_text_view_get_buffer(GTK_TEXT_VIEW(clock_view)));
  g_timeout_add(60000, (GSourceFunc) clock_handler, gtk_text_view_get_buffer(GTK_TEXT_VIEW(clock_view)));

  for (int i = 0; i < 4; i++) {
    weather_images[i] = gtk_image_new_from_file("");
    weather_titles[i] = gtk_text_view_new();
    weather_temps[i] = gtk_text_view_new();
    set_textview_styling(weather_titles[i], "15", &rgba_bg, &rgba_fg);
    set_textview_styling(weather_temps[i], "10", &rgba_bg, &rgba_fg);

    gtk_grid_attach(GTK_GRID(grid), weather_titles[i], i, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), weather_images[i], i, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), weather_temps[i], i, 3, 1, 1);

    ((weather_view *)user_data)->w_images[i] = weather_images[i];
    ((weather_view *)user_data)->w_titles[i] = weather_titles[i];
    ((weather_view *)user_data)->w_temps[i] = weather_temps[i];
  }
  weather_handler((weather_view *) user_data);
  g_timeout_add(900000, (GSourceFunc) weather_handler, (weather_view *) user_data);

  calendar = gtk_calendar_new ();
  gtk_grid_attach(GTK_GRID(grid), calendar, 0, 4, 4, 1);

  populate_event_strings(events_strings, 3);
  for (int i = 0; i < 3; i++) {
    events[i] = gtk_text_view_new();
    set_textview_styling(events[i], "10", &color_pallette[i], &rgba_fg);
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(events[i])), events_strings[i], -1);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(events[i]), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(events[i]), 10);
  }
  gtk_grid_attach(GTK_GRID(grid), events[0], 0, 5, 4, 1);
  gtk_grid_attach(GTK_GRID(grid), events[1], 0, 6, 4, 1);
  gtk_grid_attach(GTK_GRID(grid), events[2], 0, 7, 4, 1);

  gtk_widget_show_all(window);
}

int main (int argc, char *argv[]) {
  GtkApplication *app;
  int status;
  
  weather_view *wv = (weather_view *) malloc(sizeof(weather_view));
  app = gtk_application_new ("org.gtk.mm", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), wv);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  free(wv);
  return status;
} 