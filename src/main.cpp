#include "Arduino.h"
#include "E_ink.h"

#define RTC_MAGIC 0x8266ABCD
#define MAX_SLEEP_US (3 * 3600 * 1000000ULL)

struct
{
    uint32_t magic;
    int today_mday;
    uint32_t drawn;
} rtcData;

const int CS_PIN = 15; // change these variables according to your requirements.
const int DC_PIN = 12;
const int RST_PIN = 5;
const int BUSY_PIN = 4;

GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(CS_PIN, DC_PIN, RST_PIN, BUSY_PIN));

void setup()
{
    // Serial.begin(115200);

    if (date_wifibegin() == 1)
    {
        // Serial.print("Failed to get date");
        ESP.deepSleep(300 * 1000000ULL);
        return;
    };

    ESP.rtcUserMemoryRead(0, (uint32_t *)&rtcData, sizeof(rtcData));

    if (rtcData.magic != RTC_MAGIC || rtcData.today_mday != timeinfo.tm_mday)
    {
        rtcData.drawn = 0;
        rtcData.today_mday = timeinfo.tm_mday;
    }

    if (rtcData.drawn == 0)
    {
        drawCalender();
        rtcData.drawn = 1;
        ESP.rtcUserMemoryWrite(0, (uint32_t *)&rtcData, sizeof(rtcData));
        // Serial.printf("total boot = %d, today mday = %d\n", rtcData.total_bootCounter, rtcData.today_mday);
    }

    uint32_t seconds_to_midnight = (86400UL - (60 * (60 * timeinfo.tm_hour + timeinfo.tm_min) + timeinfo.tm_sec));
    uint64_t time_to_tomorrow = (uint64_t)seconds_to_midnight * 1000000ULL;
    uint64_t sleep_time = time_to_tomorrow > MAX_SLEEP_US ? MAX_SLEEP_US : time_to_tomorrow;
    ESP.deepSleep(sleep_time); 
}

void loop()
{
}
