#ifndef SUPABASEC_H
#define SUPABASEC_H

#include "SupabaseC.h"
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


    time_t getLocalDate();

    time_t convertToTimestamp(const String& dateStr);

    bool checkDate(const String& dt1,const String& dt2);
    

  public:
    SupabaseC();

    bool checkCodeInDatabase(const String& code);
   
};
#endif