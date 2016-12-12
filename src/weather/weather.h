#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
json getWeather(float latitude, float longitude);
#endif