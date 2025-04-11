#ifndef SUPABASEC_H
#define SUPABASEC_H

#include <Arduino.h>
#include <ESPSupabase.h>
#include "config.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <time.h>

class SupabaseC {
  private:
    Supabase db;
    String date;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    String valid_until;
    String start_at;


    String getLocalDate();
    String getLocalTime();
    void sendStatistic(int id);
    

    

    bool checkDate(const String& dt1,const String& dt2);
    bool checkDate(const String& dt1);
    bool checkTime(const String& time1, const String& time2);

    friend bool operator<=(const String& date1, const String& date);
    friend bool operator>=(const String& time1, const String& time);
    

  public:
    SupabaseC();

    bool checkCodeInDatabase(const String& code);
    friend int getTotalSeconds(int hour, int minutes, int seconds);
   
};
#endif