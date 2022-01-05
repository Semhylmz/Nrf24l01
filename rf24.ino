#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <MQ2.h>

int pin = A0;
MQ2 mq2(pin);

RF24 radio(9, 10);
const uint64_t address[] = {0xF4F4F4F4LL};

void setup() {
  mq2.begin();
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  float co = mq2.readCO();

  String t = String(co);
  int str_len = sizeof(t) + 1;
  char text[str_len];
  t.toCharArray(text, str_len);
  
  Serial.println(text);
 
  radio.write(&text, sizeof(text));
  delay(1000);
}
