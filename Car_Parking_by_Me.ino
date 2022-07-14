#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //Change the HEX address
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
void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
pinMode(IR1, INPUT);
pinMode(IR2, INPUT);
myservo1.attach(3);
myservo1.write(31);
lcd.setCursor (4,0);
lcd.print("SMART CAR ");
lcd.setCursor (1,1);
lcd.print("PARKING SYSTEM ");
delay (5000);
lcd.clear();  
slot_status();
}
void up(){
  for(int i=30;i<135;i++)
    myservo1.write(i);
}
void down(){
  for(int i=myservo1.read();i>=30;i--)
    myservo1.write(i);
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
}
void loop(){ 
   r1=!digitalRead (IR1);
   r2=!digitalRead (IR2);
  Serial.print(r1);
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
}
