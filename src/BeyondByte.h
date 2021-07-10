#ifndef BeyondByte_h
#define BeyondByte_h

#include <Arduino.h>

// #define WIRE_ENABLED_BeyondByte // comment out if you do not use the Wire (I2C) library to reduce use of program storage and global registers - Wire library could be rewritten to not use any program storage and global registers if this library is included and unused - this does not affect SPI and EEPROM libraries for most platforms
#define SPI_ENABLED_BeyondByte
#define EEPROM_ENABLED_BeyondByte
#define SERIAL_ENABLED_BeyondByte // comment out if you do not use serial communication to reduce use of program storage and global registers - HardwareSerial library could be rewritten to not use any program storage and global registers if this library is included and unused - this does not affect SPI library for most platforms
#define SERIAL_1_ENABLED_BeyondByte // comment out if you do not use serial communication to reduce use of program storage and global registers - HardwareSerial library could be rewritten to not use any program storage and global registers if this library is included and unused - this does not affect SPI library for most platforms
#define SERIAL_2_ENABLED_BeyondByte // comment out if you do not use serial communication to reduce use of program storage and global registers - HardwareSerial library could be rewritten to not use any program storage and global registers if this library is included and unused - this does not affect SPI library for most platforms
#define SERIAL_3_ENABLED_BeyondByte // comment out if you do not use serial communication to reduce use of program storage and global registers - HardwareSerial library could be rewritten to not use any program storage and global registers if this library is included and unused - this does not affect SPI library for most platforms

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAM_DUE)
#if defined(SERIAL_ENABLED_BeyondByte)
#define SERIALPORT_AVAILABLE_BeyondByte
#endif
#if defined(SPI_ENABLED_BeyondByte)
#include <SPI.h> // will not consume program storage or global registers if unused
#define SPI_AVAILABLE_BeyondByte
#endif
#if defined(WIRE_ENABLED_BeyondByte)
#include <Wire.h> // consumes program storage and global registers irrespective of being used or not
#define WIRE_AVAILABLE_BeyondByte
#endif
#endif
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_ZERO)
#if defined(EEPROM_ENABLED_BeyondByte)
#include <EEPROM.h> // will not consume program storage or global registers if unused
#define EEPROM_AVAILABLE_BeyondByte
#endif
#endif

#if (defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)) // Mega and Due only
#if defined(SERIAL_1_ENABLED_BeyondByte)
#define AUXSERIALPORT_1_AVAILABLE_BeyondByte
#endif
#if defined(SERIAL_2_ENABLED_BeyondByte)
#define AUXSERIALPORT_2_AVAILABLE_BeyondByte
#endif
#if defined(SERIAL_3_ENABLED_BeyondByte)
#define AUXSERIALPORT_3_AVAILABLE_BeyondByte
#endif
#endif

#if defined(ARDUINO_SAM_DUE)
#define USBSERIALPORT_AVAILABLE_BeyondByte
#endif

#define BeyondByte_Serial 1
#define BeyondByte_Serial1 2 // Mega and Due only
#define BeyondByte_Serial2 3 // Mega and Due only
#define BeyondByte_Serial3 4 // Mega and Due only
#define BeyondByte_SerialUSB 5 // Due only
#define BeyondByte_Wire 6
#define BeyondByte_SPI 7
#define BeyondByte_EEPROM 8 // except Due

class BeyondByteClass {
  public:
    void writeWord(uint16_t address, uint16_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order);
    void writeDword(uint16_t address, uint32_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order);
    void writeQword( uint16_t address, uint64_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order);
    void writeFromCharArray(uint16_t address, const char *data, uint16_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order);
    void writeFromBinaryArray(uint16_t address, const uint8_t *data, uint16_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order);
    uint16_t readWord(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order);
    uint32_t readDword(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order);
    uint64_t readQword(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order);
    void readToCharArray(uint16_t address, char *data, uint16_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order);
    void readToBinaryArray(uint16_t address, uint8_t *data, uint16_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order);
    void writeToDevice(uint16_t address, uint8_t data, uint8_t device_to_use);
    uint8_t readFromDevice(uint16_t address, uint8_t device_to_use);
    volatile bool Timeout = false;
};

extern BeyondByteClass BeyondByte;

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega8__) // Serial/Wire/SPI/EEPROM
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // Serial/Wire/SPI/EEPROM/Aux Serial x3
#elif defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) // Serial/Wire/SPI/EEPROM
#elif defined(ARDUINO_SAMD_ZERO) // Serial/Wire/SPI/EEPROM
#elif defined(ARDUINO_SAM_DUE) // Serial/Wire/SPI/Aux Serial x3/USB Serial
#else
#error Unsupported chip, please edit BeyondByte library with corresponding supported hardware functions
#endif

#endif