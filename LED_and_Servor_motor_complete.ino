
//동작사항 설명
// 차 모양 감지가 Size_1 이상이이 되면 LED의 불 밝기를 점멸으로 한다. Size_1 미만이면 불을 그냥 쭉 켠다.
// 오토바이 모양 감지가 Size_2 이상이 되면 LED의 불 밝기를 점멸으로 한다. Size_2 미만이면 불을 그냥 쭉 켠다.
// 차나 오토바이가 감지되면 로봇은 차면 오른팔을 팔을 흔들고, 오토바이면 왼팔을 흔든다.

//문제
// 카메라의 위치에 따라서 로봇 팔을 왼쪽이나 오른쪽으로 제어해줄 수 있어야하는데 일단 이걸 하기 위해서는 시리얼모니터에 어떻게
//정보가 출력되는지 먼저 봐야

#include <Pixy2.h>
#include<Servo.h>

//Sig_1 is a car
#define Sig_1 2
//Sig_2 is a motocycle
#define Sig_2 1

#define Size_1 80
#define Size_2 30

#define delayTime_0 2
#define delayTime_1 10
#define delayTime_2 20



Pixy2 pixy;

Servo myservo1;
Servo myservo2;

int servoPinRight = 12;
int servoPinLeft = 13;
int pos = 0;



void moveRightArm() {
  for(pos = 0; pos < 60; pos += 1) 
  { 
    myservo1.write(pos);
    delay(delayTime_0); //delay값을 조정하여 모터의 속도를 컨터롤가능
  } 
  for(pos = 60; pos>=0; pos-=1)
  { 
    myservo1.write(pos); 
    delay(delayTime_0); 
  } 
}

void moveLeftArm() {
  for(pos = 90; pos < 150; pos += 1) 
  { 
    myservo2.write(pos);
    delay(delayTime_0); //delay값을 조정하여 모터의 속도를 컨터롤가능
  } 
  for(pos = 150; pos>=90; pos-=1)
  { 
    myservo2.write(pos); 
    delay(delayTime_0); 
  } 
}


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.print("Starting...\n");

  //pixy cam initiate
  pixy.init();

  //pin mode of Car
  pinMode(16, OUTPUT); 
  pinMode(17, OUTPUT); 
  pinMode(18, OUTPUT); 
  pinMode(19, OUTPUT); 
  pinMode(20, OUTPUT); 
  pinMode(21, OUTPUT);  

  //pin mode of Motocycle
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  
  //pin mode of right arm
  myservo1.attach(servoPinRight);
  //pin mode of left arm
  myservo2.attach(servoPinLeft);
}

void loop() {

  //int value used in for loop
  int i, j;

  //pixt start object detection
  pixy.ccc.getBlocks();

  //if pixy cam get the recognized block
  if(pixy.ccc.numBlocks) {
    Serial.print("Object detected ");
    Serial.print(pixy.ccc.numBlocks);
    Serial.print("\n");

    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
    
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      if ( pixy.ccc.blocks[i].m_signature == Sig_1) {
        // The object_1's width value is greater than Size_1, LED_G blink faster
       if( pixy.ccc.blocks[i].m_width > Size_1) {
        moveLeftArm();
        digitalWrite(16, HIGH);
        digitalWrite(17, HIGH);
        digitalWrite(18, HIGH);
        digitalWrite(19, HIGH);
        digitalWrite(20, HIGH);
        digitalWrite(21, HIGH);
        delay(delayTime_2);
        moveRightArm();
        digitalWrite(16, LOW);
        digitalWrite(17, LOW);
        digitalWrite(18, LOW);
        digitalWrite(19, LOW);
        digitalWrite(20, LOW);
        digitalWrite(21, LOW);
        delay(delayTime_2);
       } else {
          moveLeftArm();
          digitalWrite(16, HIGH);
          digitalWrite(17, HIGH);
          digitalWrite(18, HIGH);
          digitalWrite(19, HIGH);
          digitalWrite(20, HIGH);
          digitalWrite(21, HIGH);
          moveRightArm();
       }
      }
     else if ( pixy.ccc.blocks[i].m_signature == Sig_2) {
      //if the object_2's width value is greater than Size_2, LED_R blink faster
       if( pixy.ccc.blocks[i].m_width > Size_2) {
        moveLeftArm();
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        delay(delayTime_1);

        moveRightArm();
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        delay(delayTime_1);
       } else {
        moveLeftArm();
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        moveRightArm();
       }
     }
   }
 }
  else {
    //if the object is not detected turn off the all LEDs
    
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(20, LOW);
    digitalWrite(21, LOW);
  }
}
