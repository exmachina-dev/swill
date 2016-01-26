#include <Arduino.h>
#include <protocol.h>

using namespace std ;

// CLASS METHODS
// ----------------------------------------------------------------------------

// Constructors:
// ---------------------------------------------------------------------------
Device::Device() {

  _Protocol = "ExmEisla";
	_SerialNumber = "0116VARM0001";
	_End= "\r\n";
	_delimitator = ':';
}

void Device::sendData(String data1, String command) {

    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_End);
}

void Device::sendData(String data1, String command, bool value) {
  
    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _delimitator.length() + 8 + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    binaryRepr value_send;
    value_send.toBool.bool0 = value;

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_delimitator);

    Serial.write(value_send.toBytes[0]);

    Serial.print(_End);
}

void Device::sendData(String data1, String command, unsigned int value) {
  
    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _delimitator.length() + 16 + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    binaryRepr value_send;
    value_send.toInt.int0 = value;

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_delimitator);

    Serial.write(value_send.toBytes[0]);
    Serial.write(value_send.toBytes[1]);

    Serial.print(_End);
}


void Device::sendData(String data1, String command, float value) {
  
    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _delimitator.length() + 32 + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    binaryRepr value_send;
    value_send.toFloat = value;

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_delimitator);

    Serial.write(value_send.toBytes[0]);
    Serial.write(value_send.toBytes[1]);    
    Serial.write(value_send.toBytes[2]);
    Serial.write(value_send.toBytes[3]);

    Serial.print(_End);
}


void Device::sendData(String data1, String command, String value= "") {
  
    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _delimitator.length() + value.length() + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_delimitator);
    Serial.print(value);
    Serial.print(_End);
}

/*
void serial_analyse(Packet packet, String *pro, String *serial_num, String *data1, String *data2, String *data3) {
  char chara;
  String temp = "";
  *pro = "";
  //temp += (char(packet.data[0]));
  for (int i = 0; i < 8; i++){
    *pro += char(packet.data[i]);
   }

  *serial_num  = "";

  for (int i = 10; i < 22; i++){
    *serial_num += char(packet.data[i]);
  }

  *data1 = "";
  *data2 = "";
  *data3 = "";
  int i = 22;
  chara = packet.data[i];

  while (!(chara == ':' || i == packet.length)) {
    temp += chara;
    i += 1;
    chara = packet.data[i];
  }
  
  if (i != packet.length) {
    *data1 = temp;
    temp = "";
    i += 1;
    chara = packet.data[i];
    while (!(chara == ':' || i == packet.length) ) {
      temp += chara;
      i += 1;
      chara = packet.data[i];
    }
    
    if (i != packet.length) {
      *data2 = temp;
      temp = "";
      i += 1;

      chara = packet.data[i];
      while (!(chara == ':' || i == packet.length) ) {
        temp += chara;
        i += 1;
        chara = packet.data[i];

      }
      *data3 = temp.substring(0, temp.length() - 2);
      temp = "";
    }
    else {
      *data2 = temp.substring(0, temp.length() - 2);
      *data3 = "";
    }
  }
  else {
    *data1 = temp.substring(0, temp.length() - 2);
    *data2 = "";
    *data3 = "";
  }
}
*/
String get_confirm_key(String *str, String *key) {
  int i = 0;

  char chara;
  String temp = *str;

  String temp_key;

  temp_key = "";

  chara = temp[i];

  while (chara != '.' ) {
    i += 1;
    chara = temp[i];
  }
  i += 1;
  chara = temp[i];
  while (chara != '.' ) {
    i += 1;
    chara = temp[i];
  }
  i += 1;
  chara = temp[i];
  while (!(chara == '.' || i == temp.length())) {

    temp_key += chara;
    i += 1;
    chara = temp[i];
  }
  *key = temp_key;
}