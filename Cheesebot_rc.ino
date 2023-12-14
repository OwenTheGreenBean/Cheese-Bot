
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define motor1_left 2
#define motor1_right 3
#define motor1_speed 4


#define motor2_left 5
#define motor2_right 6
#define motor2_speed 7

RF24 radio(8, 9); // CE, CSN

const byte address[6] = "00001";



void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //radio stuff

  pinMode(motor1_left, OUTPUT);
  pinMode(motor1_right, OUTPUT);
  pinMode(motor1_speed, OUTPUT);
  pinMode(motor2_left, OUTPUT);
  pinMode(motor2_right, OUTPUT);
  pinMode(motor2_speed, OUTPUT);
  
  Serial.println("Starting");
  

}

struct Data{
  int x;
  int y;
};

typedef struct Data Data;

Data data;

void loop() {
    if (radio.available()) {  
       radio.read(&data, sizeof(data));
       Serial.println(data.x);
       Serial.println(data.y);

       digitalWrite(motor1_left, LOW);
       digitalWrite(motor1_right, LOW);
       digitalWrite(motor2_left, LOW);
       digitalWrite(motor2_right, LOW);
  
       if (data.x > 3) {
          // Turn left
          digitalWrite(motor1_left, LOW);
          digitalWrite(motor1_right, HIGH);
          digitalWrite(motor2_left, LOW);
          digitalWrite(motor2_right, HIGH);
       }
       
       if (data.x < -3) {
          // Turn right
          digitalWrite(motor1_left, HIGH);
          digitalWrite(motor1_right, LOW);
          digitalWrite(motor2_left, HIGH);
          digitalWrite(motor2_right, LOW);
       }

       if (data.y > 3) {
          // Move forward
          digitalWrite(motor1_left, HIGH);
          digitalWrite(motor1_right, LOW);
          digitalWrite(motor2_left, LOW);
          digitalWrite(motor2_right, HIGH);
       }
       
       if (data.y < -3) {
          // Move backward
          digitalWrite(motor1_left, LOW);
          digitalWrite(motor1_right, HIGH);
          digitalWrite(motor2_left, HIGH);
          digitalWrite(motor2_right, LOW);
       }    
    }
    delay(10);
}
