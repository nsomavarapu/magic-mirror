#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <fstream>
#include <glib.h>
using namespace std;

int get_num_events();
void populate_event_strings(const gchar **event_strings, int numEvents);
#endif