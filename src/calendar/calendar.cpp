#include "calendar.h"

void populate_event_strings(const char **event_strings, int numEvents) {
	const char *e_strs[3];
	e_strs[0] = "Meeting with Professor Hamblen 11:30am";
  	e_strs[1] = "Dinner with Johnny 6:00pm";
  	e_strs[2] = "Party at Will's house 10:00pm";

	for(int i = 0; i < numEvents; i++) {
		event_strings[i] = e_strs[i];
	}
}