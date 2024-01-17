#include <Servo.h>

#define FORWARD 1
#define BACKWARD 2
#define STOP 9

#define SWITCH_FRONT 4
#define SWITCH_BACK 5
#define MOTOR_1 11
#define MOTOR_2 12
#define MOTOR_PWM_PORT 1
#define MOTOR_PWM_VAL 200

Servo s1, s2;
int val1 = 25, val2 = 25;

int switch_b = 0, switch_f = 0;
int pre_switch_b = 0, pre_switch_f = 0;

int status = STOP;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);  // SerialでのString受信のタイムアウト設定（ms）

  // サーボピン初期化
  s1.attach(7, 500, 2400);  // SG90S系の場合はパルス幅を設定
  s2.attach(8, 500, 2400);  // SG90S系の場合はパルス幅を設定

  // 直動部分の設定
  pinMode(SWITCH_FRONT, INPUT_PULLUP);
  pinMode(SWITCH_BACK, INPUT_PULLUP);
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  linearStop();
}

void loop() {
  // シリアル入力が来たらサーボを動かす
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

    status = FORWARD;
    Serial.println("Start to forward.");
    delay(3000);
  }

  // Serial.print(val1);
  // Serial.print(", ");
  // Serial.println(val2);
  s1.write(val1);
  s2.write(val2);

  // これ以降は前後移動
  switch_b = digitalRead(SWITCH_BACK);
  switch_f = digitalRead(SWITCH_FRONT);

  if (status == FORWARD) {
    linearForward();
  }
  if (pre_switch_f == 1 && switch_f == 0) {
    Serial.println("FRONT SWITCH IS PUSHED.");
    linearStop();
    status = STOP;
  }
  if (pre_switch_b == 1 && switch_b == 0) {
    Serial.println("BACK SWITCH IS PUSHED.");
    linearBackward();
    status = BACKWARD;
  }

  pre_switch_b = switch_b;
  pre_switch_f = switch_f;
  delay(100);
}

void linearStop() {
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, LOW);
  analogWrite(MOTOR_PWM_PORT, 0);
}

void linearForward() {
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, HIGH);
  analogWrite(MOTOR_PWM_PORT, MOTOR_PWM_VAL);
}

void linearBackward() {
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, LOW);
  analogWrite(MOTOR_PWM_PORT, MOTOR_PWM_VAL);
}