#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //Change the HEX address
#define echoPin1 6// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 7 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 9// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 10 //attach pin D3 Arduino to pin Trig of HC-SR04

Servo myservo1;
int IR1 = 2;
int IR2 = 4;
int r1=0,r2=0;
int slot = 4;           //Enter Total number of parking Slots
int flag1 = 0;
int flag2 = 0;
int in=0;
int out=0;
int p=0;
int entry=0,exitt=0;
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement
void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  myservo1.attach(5);

  lcd.setCursor (4,0);
  lcd.print("SMART CAR ");
  lcd.setCursor (1,1);
  lcd.print("PARKING SYSTEM ");
  delay(3000);
  lcd.clear();  
  //Serial.print(myservo1.read());
  myservo1.write(93);
  slot_status();
//  delay(10000);
}
void up(){
  //Serial.print("up is calling");
  for(int i=93;i<180;i=i+1)
{
  //Serial.println("up");
   myservo1.write(i);
   delay(10);
}
}
void down(){
  //Serial.print("down is calling");
 for(int i=180;i>=93;i=i-1)
{
 // Serial.println("down");
   myservo1.write(i);
   delay(10);
}
}
void slot_status(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.println("OCCUPIED SLOT-");
  lcd.setCursor(15,0);
  lcd.print(4-slot);
  lcd.setCursor(0,1);
  lcd.println("AVAILABLE SLOT-");
  lcd.setCursor(15,1);
 lcd.print(slot);
 // Serial.println("OCCUPIED SLOT-");
  Serial.println(4-slot);
  //Serial.println("AVAILABLE SLOT-");
 // Serial.println(slot);
}
void loop(){
  r1=0;
  r2=0;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.print("Distance1: ");
//  Serial.print(distance1);
//  Serial.println(" cm");
   //nghjhjjhjhjhjj
   //Ultra Sonic sensor-2
  // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.print("Distance2: ");
//  Serial.print(distance2);
//  Serial.println(" cm");
   if(distance1>=0&&distance1<=8)
       r1=1;
if(distance2>=0&&distance2<=8)
       r2=1;
//Serial.print(r1);
 if(r1==1&&flag1==0&&r2==0&&flag2==0){
  if(slot>0){
    flag1=1;
    lcd.clear();
    lcd.setCursor (4,0);
    lcd.print("WELCOME!");
    up();
    }
 else{
    lcd.clear();
    lcd.setCursor (4,0);
    lcd.print("SORRY NO");
    lcd.setCursor (0,1);
    lcd.print(" SLOTS AVAILABLE");
    delay(3000);
    slot_status();
    }
  //slot_status();
}
else if(r1==0&&flag1==1&&r2==1&&flag2==0){
  flag2=1;
  entry=1;
}
         
else if(r1==0&&flag1==1&&flag2==1&&r2==0&&entry==1){
  if(slot>0){
  slot--;
  flag1=0;
  flag2=0;
  entry=0;
  down();
  slot_status();
  }
}
else if(r2==1&&flag2==0&&r1==0&&flag1==0){
  flag2=1;
  if(slot<=3){
    lcd.clear();
    lcd.setCursor (4,0);
    lcd.print("THANK YOU !");
    up();
  }
  else{
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print("NO PARKING !");
  }
}
else if(r2==0&&flag2==1&&r1==1&&flag1==0){
  flag1=1;
  entry=0;
}
else if(r2==0&&flag2==1&&r1==0&&flag1==1&&entry==0){
  if(slot<=3){
    slot++;
    flag1=0;
    flag2=0;
    entry=0;
   down();
   slot_status();
  }
}
//delay(2000);
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
