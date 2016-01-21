#include <Arduino.h>
#include <ST7036.h>
#include <Wire.h>
#include <protocol.h>
#include "./Varmo.h"


/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

/*CONTRAST*/
int F_contrast = 0;

/*MENU*/
int MODE = 3;
int MODE_OLD = -1;

bool FLAG_MENU = 1;
bool FLAG_RESOLUTION = 0;
bool Mode_chosen = 0;
bool resolution_chosen = 0;

/*PARAMETERS*/
float SPEED_TARGET = 0;
float TORQUE_TARGET = 0;
float POSITION_TARGET = 0;
float HOME_POSITION_TARGET = 0;
float ACCELERATION_TARGET = 0;
float DECELERATION_TARGET = 0;

int CONTRAST = 5;

signed int CONTRAST_OLD = 5;

float SPEED_GET = 10;
float TORQUE_GET = 20;
float  POSITION_GET = 30;
float HOME_POSITION_GET = 40;
float ACCELERATION_GET = 50;
float DECELERATION_GET = 60;

/*RESOLUTION*/
float RESOLUTION = 1;
float RESOLUTION_old = 1;

/*CUSTOM CHARACTER*/
const uint8_t charBitmap[][8] = {
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

/*TIMER*/
unsigned long time_push = 0;
unsigned long refresh = 100;
unsigned long last_refresh = 0;

/*SEND*/
bool send_button_push_old = HIGH;
bool send_state = LOW;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool SEND = LOW;

/*GET*/
String inputString = "";
bool stringComplete = false;
String data1 = "";
String data2 = "";
String data3 = "";
String confirm_key = "";
String SerialNumber_receipt;
String protocol_receipt;
float actual_speed;

/*LED STATUS*/
bool LED_1_STATUS;
bool LED_2_STATUS;

/*TIME OUT*/
bool Serial_OK = 1;
long time_out = 200;
long time_ping;

bool flag = false;

char inChar_old;

bool MOTOR_OFF;
unsigned long timer_motor_off;
bool SENS = 1;


void setup() {

  pinMode(13, OUTPUT);
  //ENCODER INITIALISATION
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  pinMode(SEND_BUTTON, INPUT);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  pinMode(DIRECTION_1, INPUT);
  pinMode(DIRECTION_2, INPUT);

  analogWrite(CONTRAST_PWM, 0);
  //LCD INITIALISATION
  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachina");
  lcd.setCursor(1, 0);
  lcd.print(VARMO_VERSION);
  delay(3000);

  // Load Custom Character
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  // Load custom character set into CGRAM
  for (int i = 0; i < charBitmapSize; i++ )  {
    lcd.load_custom_character ( i, (uint8_t *)charBitmap[i] );
  }

  //SERIAL INITIALISATION
  Serial.begin(115200);

  lcd.clear ();
  lcd.print("Connexion...");
  time_ping = millis();
  Varmo.sendData(Get, Device_serial_num);/*
  while (flag == false) {
    if (millis() - time_ping > time_out) {
      Varmo.sendData(Get, Device_serial_num);
      time_ping = millis();
    }
    if (stringComplete == true) {
      lcd.setCursor(0,0);
      lcd.print(inputString);
      serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
      get_confirm_key(&data1, &confirm_key);

      if (SerialNumber_receipt == data3 && confirm_key == "ok") {
        flag = true;
      }
      else if (confirm_key = "error") {
        lcd.print(data3);
      }
      inputString = "";
      stringComplete = false;
    }
  }
  flag = false;*/
}

void loop()
{

/*
  if (Serial_OK == false) {
  	lcd.print("Com Error");
  	lcd.setCursor(1,0);
  	lcd.print("Reconnecting...");
    Varmo.sendData(Get, Device_serial_num);
    time_ping = millis();
    flag = false;
    while (flag == false) {
      if (millis() - time_ping > time_out) {
        Varmo.sendData(Get, Device_serial_num);
        time_ping = millis();
      }
     if (stringComplete == true) {
        serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
        get_confirm_key(&data1, &confirm_key);
        if (SerialNumber_receipt == data3 && confirm_key == "ok") {
          flag = true;
        }
        else if (confirm_key = "error") {
          lcd.print(data3);
        }
        inputString = "";
        stringComplete = false;
      }
    }
    flag = false;
    Serial_OK = true;
  }*/


  while (Serial_OK) {
    delay(100);
    encoder0Pos_old = encoder0Pos;

    /*###############################MENU###############################*/
    int encoder_push = digitalRead(encoderE);
    if (encoder_push == LOW)  {

      encoder_push = digitalRead(encoderE);
      time_push = millis();
      while (encoder_push != HIGH)  {
        encoder_push = digitalRead(encoderE);
      }

      if (((millis() - time_push)  > 250 ) || (MODE == 0) || (MODE == 1) )   {
        Mode_chosen = 0;
        while (Mode_chosen == 0) {
          MODE = menu_set(MODE);
          encoder_push = digitalRead(encoderE);
          if (encoder_push == LOW)  {
            encoder_push = digitalRead(encoderE);
            while (encoder_push != HIGH)  {
              encoder_push = digitalRead(encoderE);
            }
            FLAG_MENU = 1;
            Mode_chosen = 1;
          }
        }
      }
      else  {
        resolution_chosen = 0;
        RESOLUTION_old = RESOLUTION;
        while (resolution_chosen == 0)  {
          RESOLUTION = resolution_set(RESOLUTION);
          encoder_push = digitalRead(encoderE);
          if (encoder_push == LOW)  {
            encoder_push = digitalRead(encoderE);
            while (encoder_push != HIGH)  {
              encoder_push = digitalRead(encoderE);
            }
            FLAG_RESOLUTION = 1;
            resolution_chosen = 1;
          }
        }
      }
    }


    /*###########################GET VALUE###########################*/

    if ( (millis() - last_refresh) > refresh ) {
      last_refresh = millis();

      switch (MODE)  {
        case 1 :
          Varmo.sendData(Get, Position);
          flag = false;
          break;
        case 2 :
          Varmo.sendData(Get, Torque);
          flag = false;
          break;
        case 3 :
          Varmo.sendData(Get, Speed);
          flag = false;
          break;
        case 4 :
          Varmo.sendData(Get, Pos_Home);
          flag = false;
          break;
        case 5 :
          Varmo.sendData(Get, Acceleration);
          flag = false;
          break;
        case 6 :
          Varmo.sendData(Get, Deceleration);
          flag = false;
          break;
      }
      /*
      time_ping = millis();
      while (flag == false) {
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }
        if (stringComplete == true) {
          serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
          get_confirm_key(&data1, &confirm_key);
          if (confirm_key = "ok") {
            POSITION_GET = data3.toInt();
            flag = true;
          }
          else if (confirm_key = "error") {
            lcd.print(data3);
          }
          inputString = "";
          stringComplete = false;
        }
      }
      Varmo.sendData(Get, Drive_Enable);
      time_ping = millis();
      while (flag == false) {
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }
        if (stringComplete == true) {
          serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
          get_confirm_key(&data1, &confirm_key);
          if (confirm_key = "ok") {
            if (data3 == "HIGH") {
              LED_1_STATUS = HIGH;
            }
            else if (data3 == "LOW") {
              LED_1_STATUS = LOW;
            }
            flag = true;
          }
          else if (confirm_key = "error") {
            lcd.print(data3);
          }
          inputString = "";
          stringComplete = false;
        }
      }
      flag = false;


      Varmo.sendData(Get, Torque);
      time_ping = millis();
      while (flag == false) {
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }
        if (stringComplete == true) {
          serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
          get_confirm_key(&data1, &confirm_key);
          if (confirm_key = "ok") {
            if (data2.toFloat() > 0) {
              LED_2_STATUS = HIGH;
            }
            else {
              LED_2_STATUS = LOW;
            }
            flag = true;
          }
          else if (confirm_key = "error") {
            lcd.print(data3);
          }
          inputString = "";
          stringComplete = false;
        }
      }
      flag = false;*/
    }

    /*###########################GET DIRECTION###########################*/
    bool sens1 = digitalRead(DIRECTION_1);
    bool sens2 = digitalRead(DIRECTION_2);

    if (!(sens1 == HIGH) && (sens2 == HIGH))  {
      timer_motor_off = millis();
    }

    if ((sens1 == HIGH) && (sens2 == LOW)) {
      SENS = HIGH;
      MOTOR_OFF = LOW;
    }
    else if ((sens1 == LOW) && (sens2 == HIGH)) {
      SENS = LOW;
      MOTOR_OFF = LOW;
    }
    else if (millis() - timer_motor_off > 50) {
      MOTOR_OFF = HIGH;
    }

    /*###########################SET TARGET###########################*/
    bool send_button_push = digitalRead(SEND_BUTTON);
    if (send_button_push != send_button_push_old) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (send_button_push != send_state) {
        send_state = send_button_push;

        if (send_button_push == LOW)  {
          SEND = HIGH;
        }
      }
    }
    send_button_push_old = send_button_push;

    if (SEND == HIGH || MOTOR_OFF == 1) {
      SEND = LOW;
      switch (MODE)  {
        case 1 :
          Varmo.sendData(Set, Position_ref, String(POSITION_TARGET));/*
          while (flag == false) {
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }
            if (stringComplete == true) {
              serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
              get_confirm_key(&data1, &confirm_key);
              if (confirm_key = "ok") {
                flag = true;
              }
              else if (confirm_key = "error") {
                lcd.print(data3);
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;*/
          Varmo.sendData(Set, Pos_go, String(HIGH));
          break;
        case 2 :
          Varmo.sendData(Set, Torque_ref, String(TORQUE_TARGET));
          break;
        case 3 :
          Varmo.sendData(Set, Speed_ref, String(SPEED_TARGET));
          break;
        case 4 :
          Varmo.sendData(Set, Pos_Home, String(HOME_POSITION_TARGET));
          break;
        case 5 :
          Varmo.sendData(Set, Acceleration, String(ACCELERATION_TARGET));
          break;
        case 6 :
          Varmo.sendData(Set, Deceleration, String(DECELERATION_TARGET));
          break;

      }
      /*
      while (flag == false) {
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }
        if (stringComplete == true) {
          serial_analyse(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
          get_confirm_key(&data1, &confirm_key);
          if (confirm_key = "ok") {
            flag = true;
          }
          else if (confirm_key = "error") {
            lcd.print(data3);
          }
          inputString = "";
          stringComplete = false;
        }
      }
      flag = false;*/
    }

    /*###############################REFRESH MENU###############################*/
    if (FLAG_MENU == 1)  {
      lcd_print_menu(MODE, CONTRAST, POSITION_TARGET, TORQUE_TARGET, SPEED_TARGET, HOME_POSITION_TARGET, ACCELERATION_TARGET, DECELERATION_TARGET, 
                     TORQUE_GET, SPEED_GET, POSITION_GET, HOME_POSITION_GET, ACCELERATION_GET, DECELERATION_GET,encoder0Pos);
      if (MODE_OLD != MODE)    {
        menu_init(MODE, &CONTRAST, &POSITION_TARGET, &TORQUE_TARGET, &SPEED_TARGET, &HOME_POSITION_TARGET, &ACCELERATION_TARGET, &DECELERATION_TARGET, &encoder0Pos, RESOLUTION);
        MODE_OLD = MODE;
      }
      else    {
        encoder0Pos = encoder0Pos_old;
      }
      FLAG_MENU = 0;
    }

    if (FLAG_RESOLUTION == 1) {
      encoder0Pos = encoder0Pos_old * (RESOLUTION_old / RESOLUTION);
      FLAG_RESOLUTION = 0;
      lcd.cursor_off();
    }

    switch (MODE)  {
      case 0 :
        contrast_convert(&CONTRAST, &F_contrast, &encoder0Pos);
        if (CONTRAST != CONTRAST_OLD) {
          CONTRAST_OLD = CONTRAST;
          lcd_print_contrast_value(CONTRAST);
          analogWrite(CONTRAST_PWM, F_contrast);
        }
        break;
      case 1 :
        POSITION_TARGET = encoder0Pos;
        lcd_print_float_value(POSITION_GET, POSITION_TARGET);
        break;
      case 2 :
        converter(&TORQUE_TARGET, &encoder0Pos, RESOLUTION, SENS, 500);
        lcd_print_float_value(TORQUE_GET, TORQUE_TARGET);
        break;
      case 3 :
        converter(&SPEED_TARGET, &encoder0Pos, RESOLUTION, SENS,4400);
        lcd_print_float_value(SPEED_GET, SPEED_TARGET);
        break;
      case 4 :
        converter(&HOME_POSITION_TARGET, &encoder0Pos, RESOLUTION, SENS, 5000);
        lcd_print_float_value(HOME_POSITION_GET, HOME_POSITION_TARGET);
        break;
      case 5 :
        converter_abs(&ACCELERATION_TARGET, &encoder0Pos, RESOLUTION, 5000);
        lcd_print_float_value(ACCELERATION_GET, ACCELERATION_TARGET);
        break;
      case 6 :
        converter_abs(&DECELERATION_TARGET, &encoder0Pos, RESOLUTION, 5000);
        lcd_print_float_value(DECELERATION_GET, DECELERATION_TARGET);
        break;
    }

    /*###########################REFRESH LEDS###########################*/

    if (LED_1_STATUS == 1) {
      digitalWrite(LED_1, HIGH);
    }
    else {
      digitalWrite(LED_1, LOW);
    }
    if (LED_2_STATUS == 1) {
      digitalWrite(13, HIGH);
    }
    else {
      digitalWrite(13, LOW);
    }
  }

}

/*##################SERIAL##################*/
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if ((inChar_old == '\r') && (inChar == '\n')) {
      stringComplete = true;
    }
    inChar_old = inChar;
  }
}

/*
  ExmEisla080116VARM0001machine.get.ok:machine.serialnumber
  ExmEisla0H0116ARCP0001machine.get.ok:machine.serialnumber:0116ARCP0001
  ExmEisla\x00L00116ARCP0001machine.get.ok:machine.serialnumber:0116ARCP0001
  ExmEisla560116ARCP0001machine.get.ok:machine.speed:595
  ExmEisla600116ARCP0001machine.set.ok:machine.speed_ref:595
*/


/*##################ENCODER##################*/
void doEncoderA() {

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB() {

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

/*##################MENU##################*/
int menu_set(int MENU)  {
  int RESOLUTION = 21;
  int MENU_SELECTOR = abs(int(encoder0Pos) % RESOLUTION);
  lcd.setCursor(0, 0);
  lcd.print("Menu            ");
  lcd.setCursor(1, 0);
  if (MENU_SELECTOR <=  3)  {
    lcd.print("Contrast        ");
    MENU = 0;
  }
  else if (MENU_SELECTOR <= 6)  {
    lcd.print("Position        ");
    MENU = 1;
  }
  else if (MENU_SELECTOR <= 9)  {
    lcd.print("Torque          ");
    MENU = 2;
  }
  else if (MENU_SELECTOR <= 12)  {
    lcd.print("Speed           ");
    MENU = 3;
  }
  else if (MENU_SELECTOR <= 15) { 
    lcd.print("Set Home        ");
    MENU = 4;
  }
  else if (MENU_SELECTOR <= 18) { 
    lcd.print("Acceleration    ");
    MENU = 5;
  }
  else if (MENU_SELECTOR <= 21) {
    lcd.print("Deceleration    ");
    MENU = 6;
  }
  return MENU;
}

float resolution_set(float RESOLUTION)  {

  int RESOLUTION_SELECTOR = abs(int(encoder0Pos) % 25);
  if (RESOLUTION_SELECTOR <=  5)  {
    lcd.setCursor(1, 10);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  else if (RESOLUTION_SELECTOR <= 10)  {
    lcd.setCursor(1, 8);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR <= 15)  {
    lcd.setCursor(1, 7);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR <= 20)  {
    lcd.setCursor(1, 6);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  else if (RESOLUTION_SELECTOR <= 25)  {
    lcd.setCursor(1, 5);
    lcd.cursor_on();
    RESOLUTION = 1000;
  }
  return RESOLUTION;
}

void menu_init(int MODE, int *CONTRAST, float *POSITION, float * TORQUE, float * SPEED, float *HOME_POSITION, float *ACCELERATION, float *DECELERATION, float * encoder0Pos, float resolution)  {
  switch (MODE) {
    case 0:
      *encoder0Pos = *CONTRAST * 4;
      break;
    case 1:
      *encoder0Pos = *POSITION;
      break;
    case 2:
      *encoder0Pos = *TORQUE / resolution;
      break;
    case 3:
      *encoder0Pos = *SPEED / resolution;
      break;
    case 4:
      *encoder0Pos = *HOME_POSITION / resolution;
      break;
    case 5:
      *encoder0Pos = *ACCELERATION / resolution;
      break;
    case 6:
      *encoder0Pos = *DECELERATION / resolution;
      break;
  }
}

/*##################LCD PRINT##################*/

void lcd_print_menu(int MODE, int CONTRAST, float POSITION, float TORQUE, float SPEED, float HOME_POSITION, float ACCELERATION, float DECELERATION,
                    float torque_get, float speed_get, float position_get, float home_position_get, float acceleration_get, float decelaration_get, float encoder0Pos)  {
  lcd.clear();
  lcd.setCursor(0,0);
  switch (MODE) {
    case 0:
      lcd.print("CONTRAST");
      lcd_print_contrast_value(CONTRAST);
      break;
    case 1:
      lcd.print("Pos:");
      lcd_print_float_value(position_get, POSITION);
      break;
    case 2:
      lcd.print("Trq:");
      lcd_print_float_value(torque_get, TORQUE);
      break;
    case 3:
      lcd.print("Spd:");
      lcd_print_float_value(speed_get, SPEED);
      break;
    case 4:
      lcd.print("Hom:");
      lcd_print_float_value(home_position_get, HOME_POSITION);
      break;
    case 5:
      lcd.print("Acc:");
      lcd_print_float_value(acceleration_get, ACCELERATION);
      break;
    case 6:
      lcd.print("Dec:");
      lcd_print_float_value(decelaration_get, DECELERATION);
      break;
  }
}

void lcd_print_contrast_value(int CONTRAST) {
  lcd.setCursor(1, 3);
  lcd.print("          ");
  lcd.setCursor(1, 2);
  lcd.print ("-");
  for (int i = 1; i <= CONTRAST ; i++) {
    lcd.print(char(0));
  }
  lcd.setCursor(1, 13);
  lcd.print ("+");
}

void lcd_print_sign(float value)  {
  if (value >= 0)  {
    lcd.print("+");
  }
  else  {
    lcd.print("-");
  } 
}
/*
void lcd_print_int_align_right(int value)  {
  if (value == 0) {
    lcd.print("000");
  }
  else if (abs(value) < 10) {
    lcd.print("000");
  }
  else if (abs(value) < 100) {
    lcd.print("00");
  }
  else if (abs(value) < 1000) {
    lcd.print("0");
  }
  lcd.print(abs(value));
}
*/
void lcd_print_float_align_right(float value)  {
  if (value == 0) {
    lcd.print("000");
  }
  else if (abs(value) < 1) {
    lcd.print("000");
  }
  else if (abs(value) < 10) {
    lcd.print("000");
  }
  else if (abs(value) < 100) {
    lcd.print("00");
  }
  else if (abs(value) < 1000) {
    lcd.print("0");
  }
  lcd.print(abs(value));
}

void lcd_print_float_value(float value1, float value2) {
  lcd.setCursor(0, 4);
  lcd_print_sign(value1);
  lcd_print_float_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  lcd_print_sign(value2);

  lcd_print_float_align_right(value2);
}
/*
void lcd_print_int_value(int value1, int value2) {
  lcd.setCursor(0, 4);
  lcd_print_sign(value1);
  lcd_print_int_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Tgt: ");
  lcd_print_sign(value2);
  lcd_print_int_align_right(value2);
  lcd.print(value2);
}
*/
/*##################CONVERTER##################*/
void contrast_convert(int *CONTRAST, int *F_contrast, float * encoder0Pos) {
  int resolution = 10;
  int sensibility = 4;
  int  value = *CONTRAST;
  value = int(*encoder0Pos / sensibility );
  if (value >= 0 && value <= 10)  {
    *CONTRAST = value;
    *F_contrast = int( 25.5 * value);
  }
  else if (value > 10)  {
    *encoder0Pos = resolution * sensibility;
  }
  else if (value < 0)  {
    *encoder0Pos = 0;
  }
}


void converter(float *value, float *encoder0Pos, float resolution, bool sens, float max){
  float temp = *encoder0Pos * resolution;
  if (temp > 0 && temp < max) {
    if (sens == HIGH)  {
      *value = temp;
    }
    else if (sens == LOW)  {
      *value = (-1) * temp;
    }
  }
  else if (temp >= max)  {
    if (sens == HIGH)  {
      *value = max;
    }
    else if (sens == LOW)  {
      *value = (-1) * max;
    }
    *encoder0Pos = max / resolution;
  }
  else if (temp <= 0) {
    *value = 0;
    *encoder0Pos = 0;
  }
}

void converter_abs(float *value, float *encoder0Pos, float resolution, float max){
  float temp = *encoder0Pos * resolution;
  if (temp > 0 && temp < max) {
    *value = temp;
  }
  else if (temp >= max)  {
    *value = max;
    *encoder0Pos = max / resolution;
  }
  else if (temp <= 0) {
    *value = 0;
    *encoder0Pos = 0;
  }
}

/*
void speed_convert(float * SPEED, float * encoder0Pos, float resolution, bool SENS)  {
  float value = *encoder0Pos * resolution;

  if (value > 0 && value < 4400) {
    if (SENS == HIGH)  {
      *SPEED = value;
    }
    else if (SENS == LOW)  {
      *SPEED = (-1) * value;
    }
  }
  else if (value >= 4400)  {
  	if (SENS == HIGH)  {
      *SPEED = 4400;
    }
    else if (SENS == LOW)  {
      *SPEED = -4400;
    }
  	*encoder0Pos = 4400 / resolution;
  }
  else if (value <= 0) {
  	*SPEED = 0;
    *encoder0Pos = 0;
  }
}

void torque_convert(float * TORQUE, float * encoder0Pos, float resolution, bool SENS)  {
  float value = *encoder0Pos * resolution;
  if (value > 0 && value < 500) {
        if (SENS == HIGH)  {
      *TORQUE = value;
    }
    else if (SENS == LOW)  {
      *TORQUE = (-1) *value;
    }

  }
  else if (value >= 500)  {
    if (SENS == HIGH)  {
      *TORQUE = 500;
    }
    else if (SENS == LOW)  {
      *TORQUE = -500;
    }

    *encoder0Pos = 500 / resolution;
  }
  else if (value <= 0) {
    *TORQUE = 0;
    *encoder0Pos = 0;
  }

}
*/
