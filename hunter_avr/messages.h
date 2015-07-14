#ifndef MESSAGES_H
#define MESSAGES_H

#include <ArduinoJson.h>
#include "common.h"

class SensorStatus {
  public:

    uint32_t gps_time_ms, message_time_ms;
    Vector<int32_t> ecef_pos_cm, ecef_vel_cmps, enu_cm;
    Vector<int16_t> magnetometer;
    uint8_t gps_fix_state;

    float lat, lon, heading, vbattery, vin;

    SensorStatus();
    void toJson(JsonObject& report);
};

class DriveCommand {
  public:
    enum {
      DRIVE,        // also used to halt the hunter (set speeds = 0) 
      SET_HEADING,
      SCAN          // stop & do a scan, then await a DRIVE cmd to get moving again
    };

    uint32_t cid;
    uint8_t pid;
    uint8_t command;
    uint16_t duration;

    union {
      struct {
        uint8_t speed;
        int16_t heading;
      } drive;

      struct {
        int16_t heading;
      } heading;
      
    } payload;

    bool fromJson(JsonObject& cmd);
};

#endif


