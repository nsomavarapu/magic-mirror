#include "calendar.h"

int get_num_events() {
  int numEvents = 0;

  ifstream in(".events");
  std::string line;

  if(in.is_open()) {
    while(getline(in, line)) {
      numEvents++;
    }
  }
  return numEvents;
}
void populate_event_strings(const gchar **event_strings, int numEvents) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(".events", "r");
    if (fp != NULL) {
      for(int i = 0; i < numEvents; i++) {
        read = getline(&line, &len, fp);
        char *pos;
        if((pos = strchr(line, '\n')) != NULL)
        	*pos = '\0';
        event_strings[i] = g_locale_to_utf8(line, -1, NULL, NULL, NULL);
      }
    }
    fclose(fp);
    if (line)
        free(line);
}