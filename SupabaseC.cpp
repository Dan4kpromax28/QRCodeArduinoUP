#include "SupabaseC.h"

SupabaseC::SupabaseC() : timeClient(ntpUDP) {  
  db.begin(SUPABASE_URL, SUPABASE_KEY);
  db.login_email(USER_LOGIN, USER_PASSWORD);
  configTzTime("EET-2EEST,M3.5.0/3,M10.5.0/4", "pool.ntp.org");
  Serial.println("Ir savienojums ar datubazei");  
}

String SupabaseC::getLocalDate() {
  struct tm timeinfo;
   if (!::getLocalTime(&timeinfo)) {
    return "1970-01-01"; 
  }
  char timeStr[11];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d", &timeinfo);
  return String(timeStr);
}

String SupabaseC::getLocalTime(){
  struct tm timeinfo;
  if (!::getLocalTime(&timeinfo)) {
    return "00:00:00"; 
  }
  char timeStr[9];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  return String(timeStr);
}

bool SupabaseC::checkDate(const String& dt1,const String& dt2){
  return ((dt1 <= getLocalDate()) && (getLocalDate() <= dt2));
}

bool SupabaseC::checkDate(const String& dt1){
  return (dt1 <= getLocalDate());
}

bool SupabaseC::checkTime(const String& time1, const String& time2){
  Serial.print(getLocalTime());
  return ((time2 >= getLocalTime())&& (getLocalTime() >= time1));
}


void SupabaseC::sendStatistic(int id){
  String body = "{\"client_id\": " + String(id) + "}";
  int code = db.insert("time_stamps", body, false);
  db.urlQuery_reset();
}

bool SupabaseC::checkCodeInDatabase(const String& code) {
  //db.begin(SUPABASE_URL, SUPABASE_KEY);
  String result = db.from("ticket")
    .select("*,user_subscription(client_id,start_date,end_date,start_time,end_time,invoice(status,id),subscriptions(restriction_start,restriction_end,is_date,is_time))")
    .eq("user_string", code)
    .doSelect();
  db.urlQuery_reset();
  Serial.print(result);

  JsonDocument doc;  
  DeserializationError error = deserializeJson(doc, result);
  if (error) {
    Serial.println("JSON kluda: ");
    Serial.println(error.c_str());
    return false;  
  }
  if (doc.is<JsonArray>() && doc.size() > 0) {
    int id = doc[0]["id"];
    int user_subscription = doc[0]["user_subscription_id"];
    int count = doc[0]["count"];
    int client_id = doc[0]["user_subscription"]["client_id"];
    String status = doc[0]["user_subscription"]["invoice"][0]["status"];
    String invoice_id = String(doc[0]["user_subscription"]["invoice"][0]["id"].as<int>());

    String start_rest = doc[0]["user_subscription"]["subscriptions"]["restriction_start"];
    String end_rest = doc[0]["user_subscription"]["subscriptions"]["restriction_end"];
   
    bool isDate = doc[0]["user_subscription"]["subscriptions"]["is_date"];
    bool isTime = doc[0]["user_subscription"]["subscriptions"]["is_time"];

    Serial.print(isDate);
    Serial.print(isTime);
    


    if (status != "valid"){
      Serial.println("NAv derigs status" + status);
      return false;
    }
    Serial.print("Come 1");
    if (!checkTime(start_rest, end_rest)) return false;
    Serial.print("Come 2");
    if (isDate && isTime ){
      String startDate = doc[0]["user_subscription"]["start_date"];
      String startTime = doc[0]["user_subscription"]["start_time"];
      String endTime = doc[0]["user_subscription"]["end_time"];
      if(!checkDate(startDate)){
        Serial.println("Notika kluda ar dati");
        return false;
      }
      if(!checkTime(startTime, endTime)){
        Serial.println("Notika kluda ar laiku");
        return false;
      }
    }
    Serial.print("Come 3");
    if (!isTime  && isDate ){
      String start_date = doc[0]["user_subscription"]["start_date"];
      String end_date = doc[0]["user_subscription"]["end_date"];
      Serial.println(start_date);
      Serial.println(getLocalDate());
      Serial.println(checkDate(start_date, end_date));
      if(!checkDate(start_date, end_date)){
        
        Serial.println("Notika kluda ar datumu 2");
        return false;

      }
    }
    Serial.print("Come 4");
    Serial.print(isTime);
    Serial.print(isDate);
    if (!isTime && !isDate){
      Serial.println(count);
      if (count <= 0){
        Serial.println("Datums nav derigs");
        return false;
      }
      int new_count = count - 1;
      String body = "{\"status\": " + String(new_count) + "}";
      int code = db.update("invoice").eq("id",invoice_id ).doUpdate(body);
      Serial.println("TAs ir kods" + code);
      db.urlQuery_reset();

    }
    Serial.print("Come 5");
    sendStatistic(client_id);

    return true;
  }
  else {
    return false;
  }

}

int getTotalSeconds(int hour, int minutes, int seconds){
  return (hour * 3600 + minutes * 60 + seconds);
}


bool operator<=(const String& date1, const String& date){
    int year = date.substring(0,4).toInt();
    Serial.println(year);
    int year1 = date1.substring(0,4).toInt();
    Serial.println(year1);
    int month = date.substring(5,7).toInt();
    Serial.println(month);
    int month1 = date1.substring(5,7).toInt();
    Serial.println(month1);
    int day = date.substring(8,10).toInt();
    Serial.println(day);
    int day1 = date1.substring(8,10).toInt();
    Serial.println(day1);
    if (year1 < year) return true;
    if (year1 == year && month1 < month) return true;
    if (year1 == year && month1 == month && day1 <= day) return true;
    return false;

}

bool operator>=(const String& time1, const String& time){
    int hour = time.substring(0,2).toInt();
    int hour1 = time1.substring(0,2).toInt();
    int minutes = time.substring(3,5).toInt();
    int minutes1 = time1.substring(3,5).toInt();
    int sec = time.substring(6,8).toInt();
    int sec1 = time1.substring(6,8).toInt();
    return (getTotalSeconds(hour1,minutes1,sec1) >= getTotalSeconds(hour, minutes, sec));
  }

