#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define COUNT_LED 3
#define PIXEL_PIN 13

#define WIFI_SSID "traffic_light"
#define WIFI_PASS "12345678"

WiFiUDP Udp;
unsigned int localPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
Adafruit_NeoPixel TrafficLight(COUNT_LED, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void red_on()
{
    TrafficLight.setPixelColor(2, TrafficLight.Color(255, 0, 0));
    TrafficLight.show();
}

void yellow_on()
{
    TrafficLight.setPixelColor(1, TrafficLight.Color(255, 180, 0));
    TrafficLight.show();
}

void green_on()
{
    TrafficLight.setPixelColor(0, TrafficLight.Color(0, 255, 0));
    TrafficLight.show();
}

void red_off()
{
    TrafficLight.setPixelColor(2, TrafficLight.Color(0, 0, 0));
}

void yellow_off()
{
    TrafficLight.setPixelColor(1, TrafficLight.Color(0, 0, 0));
}

void green_off()
{
    TrafficLight.setPixelColor(0, TrafficLight.Color(0, 0, 0));
}

void setup()
{
    Serial.begin(9600);
    TrafficLight.begin();
    TrafficLight.clear();
    TrafficLight.show();

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    Serial.println(WiFi.localIP());
    TrafficLight.fill(TrafficLight.Color(0, 255, 0), 0, 3);
    TrafficLight.show();
    delay(5000);
    TrafficLight.clear();
    TrafficLight.show();

    Udp.begin(localPort);
}

void loop()
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        int n =  Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        packetBuffer[n] = 0;
        Serial.println(int(packetBuffer[0]));
        if (packetBuffer[0] == 49)
        {
            green_on();
        }
    }
}






















