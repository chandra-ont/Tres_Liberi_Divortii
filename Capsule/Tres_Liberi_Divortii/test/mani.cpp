#include <WiFi.h>
#include <iostream>
using namespace std;

const char* ssid = "";
const char* pass = "YOUR_WIFI_PASSWORD";

const char* serverIP = "192.168.10.159"; // your PC
const uint16_t serverPort = 5000;

WiFiClient client;

void connectWiFi() {
  WiFi.mode(WIFI_STA);        // station mode (client)
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection failed");
    return;
  }

  Serial.println("Connected to server");

  client.println("READY");   // send message

}

void Setup() {
    Serial.begin(115200);
    connectWiFi();
}

void loop() {
     if (client.available()) {
    String response = client.readStringUntil('\n');
    response.trim();

    Serial.print("Server says: ");
    Serial.println(response);

    if (response == "200") {
      Serial.println("Continue execution");
    } else if (response == "404") {
      Serial.println("Await / hold");
    }
  }

  delay(1000);
    
}