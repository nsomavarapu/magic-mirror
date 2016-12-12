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

void weather_handler(app_data *wv) {
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
    gtk_image_set_from_file(GTK_IMAGE(wv->w_images[i]), path.c_str());
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(wv->w_temps[i])), temp.c_str(), -1);
  }
}

// void calendar_handler() {
//   system("python src/calendar/quickstart.py");
// }

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
  int numEvents = get_num_events();
  
  GtkWidget  *window;
  GtkWidget  *grid;
  GtkWidget  *clock_view;
  GdkRGBA    rgba_bg, rgba_fg;
  GdkRGBA    color_pallette[10];
  GtkWidget  *calendar;
  GtkWidget  *events[numEvents];
  
  GtkWidget  *weather_images[4];
  GtkWidget  *weather_titles[4];
  GtkWidget  *weather_temps[4];

  gdk_rgba_parse(&rgba_bg, "black");
  gdk_rgba_parse(&rgba_fg, "white");
  gdk_rgba_parse(&color_pallette[0], "#F49AC2");
  gdk_rgba_parse(&color_pallette[1], "#CB99C9");
  gdk_rgba_parse(&color_pallette[2], "#77DD77");
  gdk_rgba_parse(&color_pallette[3], "#FFB347");
  gdk_rgba_parse(&color_pallette[4], "#779ECB");
  gdk_rgba_parse(&color_pallette[5], "#C23B22");
  gdk_rgba_parse(&color_pallette[6], "#AEC6CF");
  gdk_rgba_parse(&color_pallette[7], "#03C03C");
  gdk_rgba_parse(&color_pallette[8], "#966FD6");
  gdk_rgba_parse(&color_pallette[8], "#DEA5A4");

  window = generate_main_window(app, "Magic Mirror", 1390, 768, 10, &rgba_bg);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER (window), grid);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);

  clock_view = generate_clock_view("40", &rgba_bg, &rgba_fg);
  gtk_grid_attach(GTK_GRID(grid), clock_view, 0, 0, 4, 1);
  clock_handler(gtk_text_view_get_buffer(GTK_TEXT_VIEW(clock_view)));
  // g_timeout_add(60000, (GSourceFunc) clock_handler, gtk_text_view_get_buffer(GTK_TEXT_VIEW(clock_view)));

  for (int i = 0; i < 4; i++) {
    weather_images[i] = gtk_image_new_from_file("");
    weather_titles[i] = gtk_text_view_new();
    weather_temps[i] = gtk_text_view_new();
    set_textview_styling(weather_titles[i], "15", &rgba_bg, &rgba_fg);
    set_textview_styling(weather_temps[i], "10", &rgba_bg, &rgba_fg);

    gtk_grid_attach(GTK_GRID(grid), weather_titles[i], i, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), weather_images[i], i, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), weather_temps[i], i, 3, 1, 1);

    ((app_data *)user_data)->w_images[i] = weather_images[i];
    ((app_data *)user_data)->w_titles[i] = weather_titles[i];
    ((app_data *)user_data)->w_temps[i] = weather_temps[i];
  }
  weather_handler((app_data *) user_data);
  g_timeout_add(900000, (GSourceFunc) weather_handler, (app_data *) user_data);

  calendar = gtk_calendar_new ();
  gtk_grid_attach(GTK_GRID(grid), calendar, 0, 4, 4, 1);
  // calendar_handler();
  // g_timeout_add(5000, (GSourceFunc) calendar_handler, NULL);
  
  const gchar *events_strings[numEvents];

  populate_event_strings(events_strings, numEvents);
  
  for (int i = 0; i < numEvents; i++) {
    events[i] = gtk_text_view_new();
    set_textview_styling(events[i], "10", &color_pallette[i], &rgba_fg);
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(events[i])), events_strings[i], -1);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(events[i]), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(events[i]), 10);
    gtk_grid_attach(GTK_GRID(grid), events[i], 0, (5+i), 4, 1);
  }

  gtk_widget_show_all(window);
}

int main (int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app_data *wv = (app_data *) malloc(sizeof(app_data));
  app = gtk_application_new ("org.gtk.mm", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), wv);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  free(wv);
  return status;
} 