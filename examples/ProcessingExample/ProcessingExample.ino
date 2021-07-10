/*

  BeyondByte demo program by Bryce Cherry

  Usage:
  READ/WRITE WORD/DWORD/QWORD/CHAR_ARRAY/BINARY_ARRAY byte_count - byte count is only required for anything other than an array
  BYTE_ORDER (LSBFIRST/MSBFIRST) - set byte order for above command

*/

#include <BeyondByte.h>

const byte ArraySize = 5;
char CharArray[ArraySize] = {'H', 'E', 'L', 'L', 'O'};
uint8_t BinaryArray[ArraySize] = {'F', 'I', 'R', 'S', 'T'};
word WordStorage = 0x4849; // HI
unsigned long DwordStorage = 0x4C4F4E47; // LONG
uint64_t QwordStorage = 0; // will be QUEENTWO after initialization
uint8_t ByteOrder = MSBFIRST;

const int CommandSize = 30;
char Command[CommandSize];

// ensures that the serial port is flushed fully on request
const unsigned long SerialPortRate = 9600;
const byte SerialPortRateTolerance = 5; // percent - increase to 50 for rates above 115200 up to 4000000
const byte SerialPortBits = 10; // start (1), data (8), stop (1)
const unsigned long TimePerByte = ((((1000000ULL * SerialPortBits) / SerialPortRate) * (100 + SerialPortRateTolerance)) / 100); // calculated on serial port rate + tolerance and rounded down to the nearest uS, long caters for even the slowest serial port of 75 bps

void FlushSerialBuffer() {
  while (true) {
    if (Serial.available() > 0) {
      byte dummy = Serial.read();
      while (Serial.available() > 0) { // flush additional bytes from serial buffer if present
        dummy = Serial.read();
      }
      if (TimePerByte <= 16383) {
        delayMicroseconds(TimePerByte); // delay in case another byte may be received via the serial port
      }
      else { // deal with delayMicroseconds limitation
        unsigned long DelayTime = TimePerByte;
        DelayTime /= 1000;
        if (DelayTime > 0) {
          delay(DelayTime);
        }
        DelayTime = TimePerByte;
        DelayTime %= 1000;
        if (DelayTime > 0) {
          delayMicroseconds(DelayTime);
        }
      }
    }
    else {
      break;
    }
  }
}

void getField (char* buffer, int index) {
  int CommandPos = 0;
  int FieldPos = 0;
  int SpaceCount = 0;
  while (CommandPos < CommandSize) {
    if (Command[CommandPos] == 0x20) {
      SpaceCount++;
      CommandPos++;
    }
    if (Command[CommandPos] == 0x0D || Command[CommandPos] == 0x0A) {
      break;
    }
    if (SpaceCount == index) {
      buffer[FieldPos] = Command[CommandPos];
      FieldPos++;
    }
    CommandPos++;
  }
  for (int ch = 0; ch < strlen(buffer); ch++) { // correct case of command
    buffer[ch] = toupper(buffer[ch]);
  }
  buffer[FieldPos] = '\0';
}

void setup() {
  QwordStorage = 0x51554545; // QUEE
  QwordStorage <<= 32; // now QUEE____
  QwordStorage += 0x4E54574F; // now QUEENTWO
  Serial.begin(SerialPortRate);
}

void loop() {
  static int ByteCount = 0;
  if (Serial.available() > 0) {
    char value = Serial.read();
    if (value != '\n' && ByteCount < CommandSize) {
      Command[ByteCount] = value;
      ByteCount++;
    }
    else {
      ByteCount = 0;
      bool ValidField = true;
      char field[20];
      bool Read_nWrite = true;
      byte ByteCount;
      byte DataType;
      getField(field, 0);
      if (strcmp(field, "BYTE_ORDER") == 0) {
        getField(field, 1);
        if (strcmp(field, "LSBFIRST") == 0) {
          ByteOrder = LSBFIRST;
        }
        else if (strcmp(field, "MSBFIRST") == 0) {
          ByteOrder = MSBFIRST;
        }
        else {
          ValidField = false;
        }
      }
      else if (strcmp(field, "READ") == 0 || strcmp(field, "WRITE") == 0) {
        if (strcmp(field, "WRITE") == 0) {
          Read_nWrite = false;
        }
        if (ValidField == true) {
          getField(field, 1);
          if (strcmp(field, "WORD") == 0) {
            DataType = 0;
          }
          else if (strcmp(field, "DWORD") == 0) {
            DataType = 1;
          }
          else if (strcmp(field, "QWORD") == 0) {
            DataType = 2;
          }
          else if (strcmp(field, "CHAR_ARRAY") == 0) {
            DataType = 3;
          }
          else if (strcmp(field, "BINARY_ARRAY") == 0) {
            DataType = 4;
          }
          else {
            ValidField = false;
          }
          if (ValidField == true) {
            getField(field, 2);
            ByteCount = atoi(field);
          }
        }
        FlushSerialBuffer();
        if (ValidField == true) {
          if ((DataType == 3 || DataType == 4) && ByteCount > ArraySize) { // do not go beyond the bounds of the array
            ByteCount = ArraySize;
          }
          if (Read_nWrite == true) {
            Serial.print(F("Enter "));
            Serial.print(ByteCount);
            Serial.println(F(" characters"));
            switch (DataType) {
              case 0:
                WordStorage = BeyondByte.readWord(0, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 1:
                DwordStorage = BeyondByte.readDword(0, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 2:
                QwordStorage = BeyondByte.readQword(0, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 3:
                BeyondByte.readToCharArray(0, CharArray, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 4:
                BeyondByte.readToBinaryArray(0, BinaryArray, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
            }
            FlushSerialBuffer();
          }
          else {
            switch (DataType) {
              case 0:
                BeyondByte.writeWord(0, WordStorage, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 1:
                BeyondByte.writeDword(0, DwordStorage, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 2:
                BeyondByte.writeDword(0, QwordStorage, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 3:
                BeyondByte.writeFromCharArray(0, CharArray, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
              case 4:
                BeyondByte.writeFromBinaryArray(0, BinaryArray, ByteCount, BeyondByte_Serial, ByteOrder);
                break;
            }
            Serial.println(F(""));
          }
        }
      }
      else {
        ValidField = false;
      }
      if (ValidField == true) {
        Serial.println(F("OK"));
      }
      else {
        Serial.println(F("ERROR"));
      }
    }
  }
}