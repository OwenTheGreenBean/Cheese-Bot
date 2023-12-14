
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define JoyStick_x A0
#define JoyStick_y A1
#define buttonPin 3



RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


struct Data{
  int x;
  int y;
  int button;
};

typedef struct Data Data;

Data data;

void loop() {

  data.x = analogRead(JoyStick_x);
  data.y = analogRead(JoyStick_y);
  data.button = digitalRead(buttonPin);


  

  data.x = map(data.x, 0,1023,-255 ,255);
  data.y = map(data.y, 0,1023,-255 ,255);

  Serial.print("X: ");
  Serial.println(data.x);
  Serial.print("Y: ");
  Serial.println(data.y);
  Serial.println(data.button);


  radio.write(&data, sizeof(data));


}
