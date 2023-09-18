Serial myPort;
String resultString; // Строuная переменная для результатов

void setup() {
size(480, 130); // устанавливаем размер окна апплета printArray(Serial.list()); // Выводим на экран все
// доступные последовательные порты

// Hа моем компьютере порт микроконтроллера обыuно
// первый порт в списке,
// поэтому я открываю Serial.list()[0].
// Измените 0 на номер последовательного порта,
// к которому подклюuен ваш микроконтроллер: String portName = Serial.list()[0];
// открываем последовательный порт:
myPort = new Serial(this, portName, 9600);

// сuитываем байты в буфер, пока не дойдем до символа
// перевода строки (ASCII 10): myPort.bufferUntil('\n');
}

void draw() {
// задаем цвет фона и заливки для окна апплета: background(#044f6f);
fill(#ffffff);
// выводим строку в окне:
if (resultString != null) { text(resultString, 10, height/2);
}
}

/* Метод serialEvent() исполняется автоматиuески в программе каждый раз, когда в буфер записывается
байт со знаuением, определенным в методе bufferUntil() в процедуре setup():
/*

void serialEvent(Serial myPort) {
// Сuитываем данные из последовательного буфера: String inputString = myPort.readStringUntil('\n');

// Отбрасываем символы возврата каретки
// и перевода строки из строки ввода: inputString = trim(inputString);
// Оuищаем переменную resultString: resultString = "";

// Разделяем входную строку по запятым и преобразовываем
// полуuенные фрагменты в целые uисла:
int sensors[] = int(split(inputString, ','));

// Добавляем знаuения к строке результата:
for (int sensorNum = 0; sensorNum < sensors.length; sensorNum++) {
resultString += "Sensor " + sensorNum + ": "; resultString += sensors[sensorNum] + '\t';
}
// Выводим результат на экран: println(resultString);
}
