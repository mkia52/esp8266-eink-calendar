#include "dtime.h"

const char* ssid = ""; // insert ssid
const char* password = ""; //insert password
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 2;
const uint16_t daylightOffset_sec = 3600 * gmtOffset_sec;

struct tm timeinfo;

int date_wifibegin()
{
    // Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(1000);
    }

    //Serial.println("Connected");
    digitalWrite(LED_BUILTIN, LOW);

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    if (!getLocalTime(&timeinfo, 10000))
    {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        //Serial.println("Failed to obtain time");
        return 1;
    }

    delay(2000);

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return 0;
}