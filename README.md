# BeyondByte
Discrete read/write operations for data longer than a byte

Supported Arduino boards and derivatives: Uno, Mega, Leonardo, Zero, Due

Revisions:
1.0.0	First release

## Usage

An example program is included in \ProcessingExample

Address (for EEPROM only) is uint16_t and bytes_to_(read/write) is uint8_t; binary arrays are uint8_t and byte count is uint16_t for arrays.

byte_order (Most Significant Byte - MSB/Least Significant Byte - LSB) is MSBFIRST or LSBFIRST.

device_to_use (libraries are automatically included) - attempting to use an unavailable hardware function will not affect operation within the functions (any read commands will always return 0 under these circumstances):

BeyondByte_Serial
BeyondByte_Serial1 (Mega and Due only)
BeyondByte_Serial2 (Mega and Due only)
BeyondByte_Serial3 (Mega and Due only)
BeyondByte_SerialUSB (Due only)
BeyondByte_Wire
BeyondByte_SPI
BeyondByte_EEPROM (except Due)

write(Word/Dword/Qword)(address, data, bytes_to_write, device_to_use, byte_order) - writes a word/dword/qword with specified byte count and the most significant byte starting at the specified address

writeFrom(Char/Binary)Array(address, *data, bytes_to_write, device_to_use, byte_order) - writes the contents of *data with a specified byte count and the most significant byte starting at the specified address

read(Word/Dword/Qword)(address, bytes_to_read, device_to_use, byte_order) - returns a word/dword/qword with specified byte count and the most significant byte starting at the specified address

readTo(Char/Binary)Array(address, *data, bytes_to_read, device_to_use, byte_order) - returns *data with a specified byte count and the most significant byte starting at the specified address

writeToDevice(address, data, device_to_use) - address (EEPROM only) is a uint16_t, data is uint8_t

readFromDevice(address, device_to_use) - address (EEPROM only) is a uint16_t

On a read, Serial and Wire devices will wait until data is available in the buffer or when the volatile Timeout bool is set externally via an interrupt.

Quad word (uint64_t/long long) is currently untested and requires compiler support including bitshift operations.

## Issues

Arduino HardwareSerial.h library and when included, Wire.h library consumes program memory and global registers even when flushSerial/flushWire functions are not used; until the Wire and Serial libraries are rewritten to not use any program storage and global registers if this library is included and unused, comment out the WIRE_ENABLED (already done here) and/or SERIAL_ENABLED #define lines in SerialFlush.h if not using the Wire functions to save such.