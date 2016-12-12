#include "weather.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

json getWeather(float latitude, float longitude) {
  CURL *curl;
  CURLcode res;
  std::string url = "https://api.darksky.net/forecast/4555e8b130586ea374ff13f2b02d0c08/";
  std::ostringstream buffLat;
  std::ostringstream buffLong;
  std::string readBuffer;

  buffLat<<latitude;
  std::string strLatitude = buffLat.str();

  buffLong<<longitude;
  std::string strLongitude = buffLong.str();
 
  url.append(strLatitude);
  url.append(",");
  url.append(strLongitude);


  curl = curl_easy_init();
  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

  }

  json total = json::parse(readBuffer);

  json currently = total["currently"];
  json currentIcon = currently["icon"];
  json currentTemp = currently["temperature"];


  json hours = total["hourly"];
  json hoursIcon = hours["icon"];
  json hoursData = hours["data"];

  int i = 0;
  int j = 0;
  char hourPtr[3];
  std::string hourAMPM;
  json output;
  while (hoursData[i].dump() != "null" && i <= 12) {
  json hoursPeriodicData = hoursData[i];
  json hoursPeriodicIcon = hoursPeriodicData["icon"];
  json hoursPeriodicTime = hoursPeriodicData["time"];
  int epochTime = atoi(hoursPeriodicTime.dump().c_str());
  time_t ts = epochTime;
  strftime(hourPtr, sizeof(hourPtr), "%H", (std::localtime(&ts)));
  int hour = atoi(hourPtr);
  std::stringstream ss;
  if (hour > 12) {
    ss << (hour % 12);
    hourAMPM = ss.str();
    hourAMPM.append("pm");
  } else if (hour == 12) {
    hourAMPM = "12pm";
  } else if (hour == 0) {
    hourAMPM = "12am";
  } else {
    ss << (hour % 12);
    hourAMPM = ss.str();
    hourAMPM.append("am");
  }
  json hoursPeriodicTemp = hoursPeriodicData["temperature"];
  if (i % 4 == 0) {
    output[std::to_string(j)] = {{"time", hourAMPM}, {"icon", hoursPeriodicIcon.dump()}, {"temp", hoursPeriodicTemp.dump()}};
    j++;
  }
  i++;
  
  }
  return output;
}