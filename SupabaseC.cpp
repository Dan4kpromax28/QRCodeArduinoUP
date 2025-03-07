#include "SupabaseC.h"

SupabaseC::SupabaseC() : timeClient(ntpUDP) {  
  db.begin(SUPABASE_URL, SUPABASE_KEY);
  timeClient.begin();
  timeClient.setTimeOffset(3600 * 2); // Latvija GMT +2
  Serial.println("Ir savienojums ar datubazei");  
}

time_t SupabaseC::getLocalDate() {
  timeClient.forceUpdate();
  time_t timestamp = timeClient.getEpochTime();
  return timestamp;
}

time_t SupabaseC::convertToTimestamp(const String& dateStr) {
  int year, month, day;
  sscanf(dateStr.c_str(), "%4d-%2d-%2d", &year, &month, &day);

  struct tm t;
  memset(&t, 0, sizeof(struct tm));
  t.tm_year = year - 1900;  
  t.tm_mon = month - 1;     
  t.tm_mday = day;
  t.tm_hour = 0;
  t.tm_min = 0;
  t.tm_sec = 0;

  return mktime(&t);  
}

bool SupabaseC::checkDate(const String& dt1,const String& dt2){
  return ((convertToTimestamp(dt1) <= getLocalDate()) && (convertToTimestamp(dt2) >= getLocalDate()));
}

bool SupabaseC::checkCodeInDatabase(const String& code) {
  db.begin(SUPABASE_URL, SUPABASE_KEY);
  String result = db.from("ticket").select("*").eq("user_string", code).doSelect();
  db.urlQuery_reset();

  DynamicJsonDocument doc(1024);  
  DeserializationError error = deserializeJson(doc, result);
  if (error) {
    Serial.print("JSON kluda: ");
    Serial.println(error.c_str());
    return false;  
  }
  if (doc.is<JsonArray>() && doc.size() > 0) {
    JsonObject obj = doc[0];
    valid_until = obj["valid_until"].as<const char*>();
    start_at = obj["start_at"].as<const char*>();

    return checkDate(start_at, valid_until);
  }
  else {
    return false;
  }

}

