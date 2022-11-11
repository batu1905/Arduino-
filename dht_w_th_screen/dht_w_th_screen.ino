#include <dht11.h>
#include <Servo.h>
#include <LiquidCrystal_I2C_AvrI2C.h> 
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);
#include <dht11.h> // dht11 kütüphanesini kodlarımıza dahil ediyoruz.
int DhtPin=6; // DhtPin olarak Dijital 2'yi belirliyoruz.
dht11 dht_sensor; // dht_sensor adında bir DHT11 nesnesi oluşturduk.
Servo myservo1;
Servo myservo2;
int buzzer=13;
int pos1 =0;
int pos2 =0;
void setup()
{
  Serial.begin(9600); // Seri iletişimi başlatıyoruz.
  lcd.begin();
  lcd.print("Batuhan");
  lcd.setCursor(8, 1);
  lcd.print("Demir");
  pinMode(buzzer,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  myservo1.attach(10);
  myservo2.attach(9);
  pos1= myservo1.read();
  pos2= myservo2.read();
   for(pos1 = myservo1.read() ; pos1 >= 1; pos1 -= 1){
     myservo1.write(pos1);
     delay(15); 
  }
  for(pos2 = myservo2.read() ; pos2 >= 1; pos2 -= 1){
     myservo2.write(pos2);
     delay(15); 
  }
}
 
void loop()
{
  // Sensör konrol ediliyor. 
 
  int chk = dht_sensor.read(DhtPin);
  int temp = dht_sensor.temperature;
  int hum = dht_sensor.humidity;
  int ldr = analogRead(A1);
  int gas = analogRead(A0);
  Serial.println(gas);
  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)dht_sensor.temperature, 2);
  lcd.begin();
  lcd.print("tempature:");
  lcd.setCursor(10, 0);
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("hum:");
  lcd.setCursor(4, 1);
  lcd.print(hum);
  lcd.setCursor(8, 1);
  lcd.print("Ldr:");
  lcd.setCursor(12, 1);
  lcd.print(ldr);
  Serial.println("int temp :");
  Serial.println(temp);
  // Sensörden okunan değerleri serial ekranda yazdırıyoruz.
  Serial.print("Nem Orani (%): ");
  Serial.println((float)dht_sensor.humidity, 2);
 
  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)dht_sensor.temperature, 2);
  if( gas > 700){
    tone(13,300);
   // digitalWrite(buzzer,HIGH); 
    digitalWrite(12,HIGH);               
  }
  else {
    noTone(13); 
    digitalWrite(12,LOW); 
  }
   if(ldr > 850){
    digitalWrite(11,HIGH);                      
  }
  else{
    digitalWrite(11,LOW); 

  }

 if(temp > 25){
   for(pos1 = 0; pos1< 120; pos1 += 1){
       myservo1.write(pos1);
       delay(15); 
      }
   if(pos1 == 120){
      for(pos1 = 120; pos1>= 1; pos1 -= 1){
      myservo1.write(pos1);
      delay(15); 
      }
      }
  } if(hum > 60){
   for(pos2 = 0; pos2< 120; pos2 += 1){
       myservo2.write(pos2);
       delay(15); 
      }
   if(pos2 == 120){
      for(pos2 = 120; pos2>= 1; pos2 -= 1){
      myservo2.write(pos2);
      delay(15); 
      }
      }
  }
 
  
 
 
}
