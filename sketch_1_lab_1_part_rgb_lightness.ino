// Управление трехцветным светодиодом 
// Программа управляет трехцветным RGB светодиодом, чьи выходы присоеденины к коннекторам:
// R (красный) - 11
// G (зеленый) - 10
// В (синий) - 9

// Вначале обозначаем список констант 
const int redPin = 11;   // инициализируем пин под красный цвет
const int greenPin = 10; // инициализируем пин под зеленый цвет
const int bluePin = 9;   // инициализируем пин под синий цвет
int currentPin = 0;      // текущий контакт для задания яркости
int brightness = 0;      // контакт показывающий текущий уровень яркости


void setup() {
  // Инициализируем последовательную передачу данных
  Serial.begin(9600);
  // Задаем кнтакты вывода  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // если будфер содержит последовательные данные, считываем байт 
  if (Serial.available() > 0) {
    int inByte = Serial.read();
  // реагируем только на значения r, g, b и цифры от 0 до 9
  // игнорируем все другие значения 
    if (inByte == 'r') {
      currentPin = redPin;
    }
    if (inByte == 'g') {
      currentPin = greenPin;
    }
    if (inByte == 'b') {
      currentPin = bluePin;
    }
    // сопоставляем значения входящего байта диапазону команды Analog Read()
    if (inByte >= '0' && inByte <= '9') {
      brightness = map(inByte, '0', '9', 0, 255);
      // устанавливаем заданную яркость на выбранном пине  
      analogWrite (currentPin, brightness);
    }
  }
}
