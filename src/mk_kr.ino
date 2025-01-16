#include <Compass.h>
#define PIN_RED 3
#define PIN_BLUE 5
Compass compass;
void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Compass begin");
    // Инициализируем компас
    compass.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
    pinMode(PIN_RED, OUTPUT);// Настройка пина для катода светодиода как выхода
    pinMode(PIN_BLUE, OUTPUT);//OUTPUT — режим, при котором пин будет использоваться для вывода сигнала.
}

void loop() {
    // число, получаемое с компаса в гауссах по оси x
    float x = abs(compass.readMagneticGaussX());

    //если использовать int то результатом последующих вычислений будет inf 
    //так как разница south - north будет равен 0 (0.45 и 0.25 будут округлены до 0)
    double north = 0.22;
    double south = 0.57;
    // число, обозначающее интенсивность красного цвета
    int color_red = 255 * abs((south - x) / (south - north)); 
    int color_blue = 255 - color_red; // число, обозначающее интенсивность синего цвета

    color_red = constrain(color_red, 0, 255);
    color_blue = constrain(color_blue, 0, 255);
    analogWrite(PIN_RED, color_red);
    analogWrite(PIN_BLUE, color_blue);
    // Serial.print("x: ");
    // Serial.print(x);
    // Serial.print("\tRed: ");
    // Serial.print(color_red);
    // Serial.print("\tBlue: ");
    // Serial.println(color_blue);

    // Задержка для стабилизации
    delay(200);
}