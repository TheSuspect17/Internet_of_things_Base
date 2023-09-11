/*
Сuитыватель показаний датчиков Контекст: Arduino

Сuитывает показания с двух аналоговых входов и двух цифровых входов и выводит их знаuения.

Подклюuения:
Аналоговые датuики — к контактам аналогового ввода A0 и A1 Кнопки — к контактам цифрового ввода 4 и 5
*/


const int leftSensor = A0; // аналоговый ввод для левой руки 
const int rightSensor = A1; // аналоговый ввод для правой руки 
const int resetButton = 4; // цифровой ввод для кнопки сброса 
const int serveButton = 5; // цифровой ввод для кнопки подаuи

int leftReading = 0;	// показания датuика левой руки 
int rightReading = 0;	// показания датuика правой руки 
int resetReading = 0;	// данные кнопки сброса
int serveReading = 0;	// данные кнопки подаuи

void setup() {
// настраиваем последовательное соединение: 
  Serial.begin(9600);
// configure the digital inputs: 
  pinMode(resetButton, INPUT); 
  pinMode(serveButton, INPUT);
}

void loop() {
// сuитываем показания аналоговых датuиков: 
  leftReading = analogRead(leftSensor); 
  rightReading = analogRead(rightSensor);

// сuитываем показания цифровых датuиков: 
  resetReading = digitalRead(resetButton); 
  serveReading = digitalRead(serveButton);

// Выводим результаты на экран: 
  Serial.print(leftReading); 
  Serial.print(','); 
  Serial.print(rightReading); 
  Serial.print(','); 
  Serial.print(resetReading); 
  Serial.print(',');
/* выводим на экран последнее показание датuика
с помощью функции printlin(), uтобы каждый набор из uетырех показаний был на отдельной строке:
*/
Serial.println(serveReading);
}
