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
// Generated from:
//   Version: v3
//   Revision: 225
// Generated by:
//    Tool: google-apis-code-generator 1.5.1
//     C++: 0.1.4
#ifndef  GOOGLE_CALENDAR_API_EVENT_DATE_TIME_H_
#define  GOOGLE_CALENDAR_API_EVENT_DATE_TIME_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/client/util/date_time.h"
#include "googleapis/strings/stringpiece.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_calendar_api {
using namespace googleapis;

/**
 * No description provided.
 *
 * @ingroup DataObject
 */
class EventDateTime : public client::JsonCppData {
 public:
  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static EventDateTime* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit EventDateTime(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit EventDateTime(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~EventDateTime();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_calendar_api::EventDateTime</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_calendar_api::EventDateTime");
  }

  /**
   * Determine if the '<code>date</code>' attribute was set.
   *
   * @return true if the '<code>date</code>' attribute was set.
   */
  bool has_date() const {
    return Storage().isMember("date");
  }

  /**
   * Clears the '<code>date</code>' attribute.
   */
  void clear_date() {
    MutableStorage()->removeMember("date");
  }


  /**
   * Get the value of the '<code>date</code>' attribute.
   */
  client::Date get_date() const {
    const Json::Value& storage = Storage("date");
    return client::JsonValueToCppValueHelper<client::Date >(storage);
  }

  /**
   * Change the '<code>date</code>' attribute.
   *
   * The date, in the format "yyyy-mm-dd", if this is an all-day event.
   *
   * @param[in] value The new value.
   */
  void set_date(client::Date value) {
    client::SetJsonValueFromCppValueHelper<client::Date >(
      value, MutableStorage("date"));
  }

  /**
   * Determine if the '<code>dateTime</code>' attribute was set.
   *
   * @return true if the '<code>dateTime</code>' attribute was set.
   */
  bool has_date_time() const {
    return Storage().isMember("dateTime");
  }

  /**
   * Clears the '<code>dateTime</code>' attribute.
   */
  void clear_date_time() {
    MutableStorage()->removeMember("dateTime");
  }


  /**
   * Get the value of the '<code>dateTime</code>' attribute.
   */
  client::DateTime get_date_time() const {
    const Json::Value& storage = Storage("dateTime");
    return client::JsonValueToCppValueHelper<client::DateTime >(storage);
  }

  /**
   * Change the '<code>dateTime</code>' attribute.
   *
   * The time, as a combined date-time value (formatted according to RFC3339). A
   * time zone offset is required unless a time zone is explicitly specified in
   * timeZone.
   *
   * @param[in] value The new value.
   */
  void set_date_time(client::DateTime value) {
    client::SetJsonValueFromCppValueHelper<client::DateTime >(
      value, MutableStorage("dateTime"));
  }

  /**
   * Determine if the '<code>timeZone</code>' attribute was set.
   *
   * @return true if the '<code>timeZone</code>' attribute was set.
   */
  bool has_time_zone() const {
    return Storage().isMember("timeZone");
  }

  /**
   * Clears the '<code>timeZone</code>' attribute.
   */
  void clear_time_zone() {
    MutableStorage()->removeMember("timeZone");
  }


  /**
   * Get the value of the '<code>timeZone</code>' attribute.
   */
  const StringPiece get_time_zone() const {
    const Json::Value& v = Storage("timeZone");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>timeZone</code>' attribute.
   *
   * The time zone in which the time is specified. (Formatted as an IANA Time
   * Zone Database name, e.g. "Europe/Zurich".) For recurring events this field
   * is required and specifies the time zone in which the recurrence is
   * expanded. For single events this field is optional and indicates a custom
   * time zone for the event start/end.
   *
   * @param[in] value The new value.
   */
  void set_time_zone(const StringPiece& value) {
    *MutableStorage("timeZone") = value.data();
  }

 private:
  void operator=(const EventDateTime&);
};  // EventDateTime
}  // namespace google_calendar_api
#endif  // GOOGLE_CALENDAR_API_EVENT_DATE_TIME_H_