#include <Servo.h>

Servo s1, s2;
int val1 = 90, val2 = 90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);  // SerialでのString受信のタイムアウト設定（ms）

  // サーボピン初期化
  s1.attach(7, 500, 2400);  // SG90S系の場合はパルス幅を設定
  s2.attach(8, 500, 2400);  // SG90S系の場合はパルス幅を設定
}

/*
 * はじめに90度の位置になり、aとbを押すと10度ずつ正転・逆転
 */
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');
    String firstNumber = data.substring(0, commaIndex);
    String secondNumber = data.substring(commaIndex + 1);

    // 文字列を数値に変換
    int num1 = firstNumber.toInt();
    int num2 = secondNumber.toInt();

    Serial.print(num1);
    Serial.print(", ");
    Serial.println(num2);

    if (num1 >= 10 && num1 <= 170) {
      val1 = num1;
    }
    if (num2 >= 10 && num2 <= 170) {
      val2 = num2;
    }

  }

  Serial.print(val1);
  Serial.print(", ");
  Serial.println(val2);
  s1.write(val1);
  s2.write(val2);

  delay(100);
}
