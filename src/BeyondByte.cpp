#include "BeyondByte.h"

void BeyondByteClass::writeToDevice(uint16_t address, uint8_t data, uint8_t device_to_use) {
  switch (device_to_use) {
    case 0: // invalid device
      break;
    case BeyondByte_Serial:
#if defined(SERIALPORT_AVAILABLE_BeyondByte)
      Serial.write(data);
#endif
      break;
    case BeyondByte_Serial1:
#if defined(AUXSERIALPORT_1_AVAILABLE_BeyondByte)
      Serial1.write(data);
#endif
      break;
    case BeyondByte_Serial2:
#if defined(AUXSERIALPORT_2_AVAILABLE_BeyondByte)
      Serial2.write(data);
#endif
      break;
    case BeyondByte_Serial3:
#if defined(AUXSERIALPORT_3_AVAILABLE_BeyondByte)
      Serial3.write(data);
#endif
      break;
    case BeyondByte_SerialUSB:
#if defined(USBSERIALPORT_AVAILABLE_BeyondByte)
      SerialUSB.write(data);
#endif
      break;
    case BeyondByte_Wire:
#if defined(WIRE_AVAILABLE_BeyondByte)
      Wire.write(data);
#endif
      break;
    case BeyondByte_SPI:
#if defined(SPI_AVAILABLE_BeyondByte)
      SPI.transfer(data);
#endif
      break;
    case BeyondByte_EEPROM:
#if defined(EEPROM_AVAILABLE_BeyondByte)
      EEPROM.write(address, data);
#endif
      break;
  }
}

uint8_t BeyondByteClass::readFromDevice(uint16_t address, uint8_t device_to_use) {
  uint8_t data = 0;
  switch (device_to_use) {
    case 0: // invalid device
      break;
    case BeyondByte_Serial:
#if defined(SERIALPORT_AVAILABLE_BeyondByte)
      while (Serial.available() == 0 && Timeout == false) {
      }
      if (Timeout == false) {
        data = Serial.read();
      }
#endif
      break;
    case BeyondByte_Serial1:
#if defined(AUXSERIALPORT_1_AVAILABLE_BeyondByte)
      while (Serial1.available() == 0 && Timeout == false) {
      }
      data = Serial1.read();
#endif
      break;
    case BeyondByte_Serial2:
#if defined(AUXSERIALPORT_2_AVAILABLE_BeyondByte)
      while (Serial2.available() == 0 && Timeout == false) {
      }
      data = Serial2.read();
#endif
      break;
    case BeyondByte_Serial3:
#if defined(AUXSERIALPORT_3_AVAILABLE_BeyondByte)
      while (Serial3.available() == 0 && Timeout == false) {
      }
      data = Serial3.read();
#endif
      break;
    case BeyondByte_SerialUSB:
#if defined(USBSERIALPORT_AVAILABLE_BeyondByte)
      while (SerialUSB.available() == 0 && Timeout == false) {
      }
      data = SerialUSB.read();
#endif
      break;
    case BeyondByte_Wire:
#if defined(WIRE_AVAILABLE_BeyondByte)
      while (Wire.available() == 0 && Timeout == false) {
      }
      data = Wire.read();
#endif
      break;
    case BeyondByte_SPI:
#if defined(SPI_AVAILABLE_BeyondByte)
      data = SPI.transfer(0x00);
#endif
      break;
    case BeyondByte_EEPROM:
#if defined(EEPROM_AVAILABLE_BeyondByte)
      data = EEPROM.read(address);
#endif
      break;
  }
  return data;
}

void BeyondByteClass::writeWord(uint16_t address, uint16_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order) {
  if (bytes_to_write <= 2) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_write; i++) {
        uint16_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_write - 1); i >= 0; i--) {
        uint16_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
  }
}

void BeyondByteClass::writeDword(uint16_t address, uint32_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order) {
  if (bytes_to_write <= 4) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_write; i++) {
        uint32_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_write - 1); i >= 0; i--) {
        uint32_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
  }
}

void BeyondByteClass::writeQword(uint16_t address, uint64_t data, uint8_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order) {
  if (bytes_to_write <= 8) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_write; i++) {
        uint64_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_write - 1); i >= 0; i--) {
        uint64_t temp = data;
        temp >>= (8 * (bytes_to_write - 1 - i));
        temp &= 0xFF;
        writeToDevice((address + i), temp, device_to_use);
      }
    }
  }
}

void BeyondByteClass::writeFromCharArray(uint16_t address, const char *data, uint16_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (int16_t i = 0; i < bytes_to_write; i++) {
      writeToDevice((address + i), data[i], device_to_use);
    }
  }
  else if (byte_order == LSBFIRST) {
    for (int16_t i = (bytes_to_write - 1); i >= 0; i--) {
      writeToDevice((address + i), data[i], device_to_use);
    }
  }
}

void BeyondByteClass::writeFromBinaryArray(uint16_t address, const uint8_t *data, uint16_t bytes_to_write, uint8_t device_to_use, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (int16_t i = 0; i < bytes_to_write; i++) {
      writeToDevice((address + i), data[i], device_to_use);
    }
  }
  else if (byte_order == LSBFIRST) {
    for (int16_t i = (bytes_to_write - 1); i >= 0; i--) {
      writeToDevice((address + i), data[i], device_to_use);
    }
  }
}

uint16_t BeyondByteClass::readWord(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order) {
  uint16_t data = 0;
  if (bytes_to_read <= 2) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_read; i++) {
        uint16_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_read - 1); i >= 0; i--) {
        uint16_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
  }
  return data;
}

uint32_t BeyondByteClass::readDword(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order) {
  uint32_t data = 0;
  if (bytes_to_read <= 4) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_read; i++) {
        uint32_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_read - 1); i >= 0; i--) {
        uint32_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
  }
  return data;
}

uint64_t BeyondByteClass::readQword(uint16_t address, uint8_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order) {
  uint64_t data = 0;
  if (bytes_to_read <= 8) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_read; i++) {
        uint64_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_read - 1); i >= 0; i--) {
        uint64_t temp = 0;
        temp = readFromDevice((address + i), device_to_use);
        temp <<= (8 * (bytes_to_read - 1 - i));
        data |= temp;
      }
    }
  }
  return data;
}

void BeyondByteClass::readToCharArray(uint16_t address, char *data, uint16_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (uint16_t i = 0; i < bytes_to_read; i++) {
      data[i] = readFromDevice((address + i), device_to_use);
    } 
  }
  else if (byte_order == LSBFIRST) {
    for (int32_t i = (bytes_to_read - 1); i >= 0; i--) {
      data[i] = readFromDevice((address + i), device_to_use);
    } 
  }
}

void BeyondByteClass::readToBinaryArray(uint16_t address, uint8_t *data, uint16_t bytes_to_read, uint8_t device_to_use, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (uint16_t i = 0; i < bytes_to_read; i++) {
      data[i] = readFromDevice((address + i), device_to_use);
    } 
  }
  else if (byte_order == LSBFIRST) {
    for (int32_t i = (bytes_to_read - 1); i >= 0; i--) {
      data[i] = readFromDevice((address + i), device_to_use);
    } 
  }
}

uint16_t BeyondByteClass::transferWord_SPI(uint16_t dataOut, uint8_t bytes_to_transfer, uint8_t byte_order) {
  uint16_t data = 0;
  if (bytes_to_transfer <= 2) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_transfer; i++) {
        uint16_t temp = 0;
        uint16_t temp2 = data;
        temp2 >>= (8 * (bytes_to_transfer - 1 - i));
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_transfer - 1); i >= 0; i--) {
        uint16_t temp = 0;
        uint16_t temp2 = data;
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
        temp2 >>= 8;
      }
    }
  }
  return data;
}

uint32_t BeyondByteClass::transferDword_SPI(uint32_t dataOut, uint8_t bytes_to_transfer, uint8_t byte_order) {
  uint32_t data = 0;
  if (bytes_to_transfer <= 2) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_transfer; i++) {
        uint32_t temp = 0;
        uint32_t temp2 = data;
        temp2 >>= (8 * (bytes_to_transfer - 1 - i));
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_transfer - 1); i >= 0; i--) {
        uint32_t temp = 0;
        uint32_t temp2 = data;
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
        temp2 >>= 8;
      }
    }
  }
  return data;
}

uint64_t BeyondByteClass::transferQword_SPI(uint64_t dataOut, uint8_t bytes_to_transfer, uint8_t byte_order) {
  uint64_t data = 0;
  if (bytes_to_transfer <= 2) {
    if (byte_order == MSBFIRST) {
      for (int16_t i = 0; i < bytes_to_transfer; i++) {
        uint64_t temp = 0;
        uint64_t temp2 = data;
        temp2 >>= (8 * (bytes_to_transfer - 1 - i));
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
      }
    }
    else if (byte_order == LSBFIRST) {
      for (int16_t i = (bytes_to_transfer - 1); i >= 0; i--) {
        uint64_t temp = 0;
        uint64_t temp2 = data;
        temp = SPI.transfer((temp2 & 0xFF));
        temp <<= (8 * (bytes_to_transfer - 1 - i));
        data |= temp;
        temp2 >>= 8;
      }
    }
  }
  return data;
}

void BeyondByteClass::transferCharArray_SPI(char *dataIn, char *dataOut, uint16_t bytes_to_transfer, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (uint16_t i = 0; i < bytes_to_transfer; i++) {
      dataIn[i] = SPI.transfer(dataOut[i]);
    } 
  }
  else if (byte_order == LSBFIRST) {
    for (int32_t i = (bytes_to_transfer - 1); i >= 0; i--) {
      dataIn[i] = SPI.transfer(dataOut[i]);
    } 
  }
}

void BeyondByteClass::transferBinaryArray_SPI(uint8_t *dataIn, uint8_t *dataOut, uint16_t bytes_to_transfer, uint8_t byte_order) {
  if (byte_order == MSBFIRST) {
    for (uint16_t i = 0; i < bytes_to_transfer; i++) {
      dataIn[i] = SPI.transfer(dataOut[i]);
    } 
  }
  else if (byte_order == LSBFIRST) {
    for (int32_t i = (bytes_to_transfer - 1); i >= 0; i--) {
      dataIn[i] = SPI.transfer(dataOut[i]);
    } 
  }
}

BeyondByteClass BeyondByte;