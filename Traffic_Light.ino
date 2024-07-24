#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define COUNT_LED 3
#define PIXEL_PIN 13
#define COLOR_RED 

#define WIFI_SSID "trafficlighttest"
#define WIFI_PASS "qweasdzxc"

WiFiUDP Udp;
unsigned int localPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
Adafruit_NeoPixel TrafficLight(COUNT_LED, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

enum COLOR {GREEN, YELLOW, RED, CLEAR};

void set_color(COLOR color)
{
    TrafficLight.clear();
    switch (color)
    {
        case RED:
            Serial.println("RED");
            TrafficLight.setPixelColor(RED, TrafficLight.Color(255, 0, 0));
            break;
        case YELLOW:
            Serial.println("YELLOW");
            TrafficLight.setPixelColor(YELLOW, TrafficLight.Color(255, 180, 0));
            break;
        case GREEN:  
            Serial.println("GREEN");
            TrafficLight.setPixelColor(GREEN, TrafficLight.Color(0, 255, 0));
            break;
        default:
        {
            Serial.println("CLEAR");
            break;
        }
    }
    TrafficLight.show();
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
        set_color(RED);
        delay(100);
        set_color(CLEAR);
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
        Serial.println(packetBuffer);
        if (packetBuffer[0] == 49)
        {
            //green_on();
        }
    }
}






















