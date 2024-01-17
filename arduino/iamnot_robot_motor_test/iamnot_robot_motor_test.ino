#define WAIT 1
#define ROTATE 2
#define REVERSE 3
#define STOP 9

#define SWITCH_RIGHT 4
#define SWITCH_LEFT 5
#define MOTOR_1 11
#define MOTOR_2 12
#define MOTOR_PWM_PORT 1
#define MOTOR_PWM_VAL 200

int switch_r = 0, switch_l = 0;
int pre_switch_r = 0, pre_switch_l = 0;

int status = ROTATE;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH_RIGHT, INPUT_PULLUP);
  pinMode(SWITCH_LEFT, INPUT_PULLUP);
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  Serial.begin(9600);

  delay(5000);

  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, LOW);
  analogWrite(MOTOR_PWM_PORT, MOTOR_PWM_VAL);
  status = ROTATE;
}

// モーターが行ったり来たりするコード
void loop() {
  Serial.println(status);
  // put your main code here, to run repeatedly:
  switch_r = digitalRead(SWITCH_RIGHT);
  switch_l = digitalRead(SWITCH_LEFT);

  if (pre_switch_l == 1 && switch_l == 0) {
    Serial.println("LEFT SWITCH IS PUSHED.");
    digitalWrite(MOTOR_1, HIGH);
    digitalWrite(MOTOR_2, LOW);
    analogWrite(MOTOR_PWM_PORT, MOTOR_PWM_VAL);
    status = ROTATE;
  }
  if (pre_switch_r == 1 && switch_r == 0) {
    Serial.println("RIGHT SWITCH IS PUSHED.");
    digitalWrite(MOTOR_1, LOW);
    digitalWrite(MOTOR_2, HIGH);
    analogWrite(MOTOR_PWM_PORT, MOTOR_PWM_VAL);
    status = REVERSE;
  }

  pre_switch_r = switch_r;
  pre_switch_l = switch_l;

  delay(100);
}
