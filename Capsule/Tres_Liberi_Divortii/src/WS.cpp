#include <WiFi.h>

const char* ssid     = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

const char* server_ip   = "192.168.1.100";
const uint16_t server_port = 5001;

WiFiClient client;

// ----------------------
// Single function version
// ----------------------
void WsetupAndSend(const char* data) {
  Serial.begin(115200);
  delay(200);
  Serial.println("Starting WsetupAndSend...");

  // --- Connect Wi-Fi ---
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to Wi-Fi");
    return;
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // --- Connect to server ---
  Serial.print("Connecting to server ");
  Serial.print(server_ip);
  Serial.print(":");
  Serial.println(server_port);

  if (!client.connect(server_ip, server_port)) {
    Serial.println("Failed to connect to server");
    return;
  }

  Serial.println("Server connected");

  // --- Send handshake + data ---
  const char* handshake = "This is ESP";
  client.println(handshake);
  Serial.print("Sent: ");
  Serial.println(handshake);

  client.println(data);
  Serial.print("Sent: ");
  Serial.println(data);

  // --- Listen for server response ---
  Serial.println("Waiting for server response...");
  while (client.connected()) {
    while (client.available()) {
      String line = client.readStringUntil('\n');
      line.trim();
      Serial.print("RX: ");
      Serial.println(line);

      if (line.indexOf("200") != -1) {
        Serial.println("Received 200 → stopping");
        client.stop();
        WiFi.disconnect(true);
        return;
      }
    }
    delay(100); // small delay to avoid locking CPU
  }

  Serial.println("Server disconnected without receiving 200");
  client.stop();
  WiFi.disconnect(true);
}
