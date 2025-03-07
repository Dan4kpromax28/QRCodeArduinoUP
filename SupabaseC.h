#ifndef SUPABASEC_H
#define SUPABASEC_H

#include <Arduino.h>
#include <ESPSupabase.h>
#include "config.h"
#include <WiFi.h>

class SupabaseC {
  private:
    Supabase db;
  public:
    SupabaseC() {  
      
      db.begin(SUPABASE_URL, SUPABASE_KEY);
      Serial.println("Ir savienojums ar datubazei");  
    }

    String checkCodeInDatabase(String code) {
      db.begin(SUPABASE_URL, SUPABASE_KEY);
      String result = db.from("ticket").select("*").eq("user_string", code).doSelect();
      return result;
      
    }
};

#endif