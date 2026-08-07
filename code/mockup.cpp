#include <WiFi.h>
#include <esp_now.h>

const int MOTOR1 = 12;
const int MOTOR2 = 13;
const int MOTOR3 = 14;

struct Message {
  bool motorsOn;
};

Message incomingData;

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len != sizeof(Message)) {
    return;
  }

  memcpy(&incomingData, data, sizeof(incomingData));

  digitalWrite(MOTOR1, incomingData.motorsOn ? HIGH : LOW);
  digitalWrite(MOTOR2, incomingData.motorsOn ? HIGH : LOW);
  digitalWrite(MOTOR3, incomingData.motorsOn ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);

  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  digitalWrite(MOTOR3, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Init failed");
    while (true);
  }

  esp_now_register_recv_cb(onDataRecv);

  Serial.println("Receiver ready");
}

void loop() {
}
