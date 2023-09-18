#include <LiquidCrystal_I2C.h>
#include "MQ135.h"
#include "DHT.h"
#define DHTPIN 2 // Тот самый номер пина, о котором упоминалось выше
// Одна из следующих строк закоментирована. Снимите комментарий, если подключаете датчик DHT11 к arduino
DHT dht(DHTPIN, DHT11);
int sensorPin = 9;
int soilMoistureValue = 0;
int percentage=0;
#define ANALOGPIN A1 //подключение аналогового сигнального пина
#define RZERO 206.85
MQ135 gasSensor = MQ135(ANALOGPIN);
boolean noGas; //переменная для хранения значения о присутствии газа
int gasValue = 0; //переменная для хранения количества газа
LiquidCrystal_I2C LCD(0x27,16,2);
int flame; 

byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
void setup()
{
  pinMode(3,OUTPUT);
  pinMode(sensorPin, INPUT);
  float rzero = gasSensor.getRZero();
  LCD.init();
  LCD.backlight();
  Serial.begin(9600);
  LCD.begin(16, 2);
  dht.begin();
  LCD.createChar(1, degree);
  LCD.clear();
}

void loop()
{
  soilMoistureValue = analogRead(A0);
  Serial.println(percentage);
  percentage = map(soilMoistureValue, 490, 1023, 100, 0);
  if(percentage < 10)  
  {
    Serial.println(" pump on");
    digitalWrite(3,LOW);
  }
  if(percentage >75)
  {
    Serial.println("pump off");
    digitalWrite(3,HIGH);
  }
  float ppm = gasSensor.getPPM();
  Serial.println(percentage);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  delay(2000); // 2 секунды задержки
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    Serial.println("Ошибка считывания");
    return;
  }
  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C "); //Вывод показателей на экран
  LCD.setCursor(0,0);
  LCD.print("Humidity: ");
  LCD.print(h);   // отображаем значение влажности на экране ЖК дисплея
  LCD.print(" %");
  LCD.setCursor(0,1);
  LCD.print("Temperature:");
  LCD.print(t);   // отображаем значение температуры на экране ЖК дисплея
  LCD.write(1);
  LCD.print("C");

  flame = digitalRead(sensorPin);
  
  if (flame == 1)
    {
   Serial.println("Обнаружено пламя");
   delay(150);

    }
  else
    {
   Serial.println("Пламя не обнаружено");
    }
  delay(1000);
}