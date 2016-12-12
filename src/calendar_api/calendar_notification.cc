// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// This code was generated by google-apis-code-generator 1.5.1
//   Build date: 2016-10-17 16:43:55 UTC
//   on: 2016-11-16, 06:17:22 UTC
//   C++ generator version: 0.1.4

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   Calendar API (calendar/v3)
// Description:
//   Manipulates events and other calendar data.
// Classes:
//   CalendarNotification
// Documentation:
//   https://developers.google.com/google-apps/calendar/firstapp

#include "google/calendar_api/calendar_notification.h"
#include <string>
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"


#include <string>
#include "googleapis/strings/strcat.h"

namespace google_calendar_api {
using namespace googleapis;


// Object factory method (static).
CalendarNotification* CalendarNotification::New() {
  return new client::JsonCppCapsule<CalendarNotification>;
}

// Standard immutable constructor.
CalendarNotification::CalendarNotification(const Json::Value& storage)
  : client::JsonCppData(storage) {
}

// Standard mutable constructor.
CalendarNotification::CalendarNotification(Json::Value* storage)
  : client::JsonCppData(storage) {
}

// Standard destructor.
CalendarNotification::~CalendarNotification() {
}
}  // namespace google_calendar_api
