#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi config
const char *ssid = "TMU";              // changes with ur SSID
const char *password = "BambangDjaja"; // changes with ur Password

// MQTT config
const char *mqtt_server = "192.168.18.63"; // Ganti dengan IP Localhost
const int mqtt_port = 1883;
const char *topic_temperature = "wit/simulasi/temperature";
const char *topic_RPM = "wit/simulasi/RPM";
const char *topic_Heartbeat = "wit/simulasi/heartbeat";
void mqttCallback(char *topic, byte *payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Function setupWifi
void setupWiFi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}

// Function setupMQTT
void setupMQTT()
{
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(mqttCallback);
}

// Function to connect, reconnect, & subcribeTopic
void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect("ArduinoClient"))
        {
            Serial.println("Connected to MQTT broker!");
        }
        else
        {
            Serial.print("Failed to connect, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

// Function callbackPayloadTopic
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message received on topic: ");
    Serial.println(topic);

    // Convert payload to string
    payload[length] = '\0';
    String message = String((char *)payload);

    Serial.print("Message payload: ");
    Serial.println(message);
}

void setup()
{
    Serial.begin(9600);
    setupWiFi();
    setupMQTT();
}

void loop()
{
    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }

    mqttClient.loop(); // MQTT connection and handle incoming messages

    // Generate dummy dat
    float temperature = random(0, 100);
    float RPM = random(0, 10000);
    bool heartbeat = 1;

    // Convert float and int to string
    char temperatureStr[10];
    dtostrf(temperature, 4, 2, temperatureStr);
    char RPMStr[10];
    dtostrf(RPM, 4, 2, RPMStr);
    char HeartbeatStr[2];
    itoa(heartbeat, HeartbeatStr, 10);

    // Publish voltage and current to MQTT topics
    mqttClient.publish(topic_temperature, temperatureStr);
    mqttClient.publish(topic_RPM, RPMStr);
    mqttClient.publish(topic_Heartbeat, HeartbeatStr);

    // Print the sent data to serial monitor
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("RPM: ");
    Serial.println(RPM);
    Serial.print("Heartbeat: ");
    Serial.println(heartbeat);
    delay(5000); // Delay before checking MQTT connection and sending data
}
