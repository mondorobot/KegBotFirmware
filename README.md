# KegBotFirmware
The firmware for controlling and communicating with Arduino and between the KegBot Rest interface (TBD)

## Development/Installation and Contributing
1. We are using Atom as our IDE
2. [Install the platformIO package](http://platformio.org/get-started) in order to upload firmware and monitor over the serial port

### Serial port monitoring
1. Ensure the baudrate is set to 9600
2. Select the correct port, it may default to bluetooth and you want a USB port
3. Under Advanced settings, set printable to true
4. turn on local echo

### Project Structure

You may put external libraries in the /lib folder

|--lib
|  |--Bar
|  |  |--docs
|  |  |--examples
|  |  |--src
|  |     |- Bar.c
|  |     |- Bar.h
|  |--Foo
|  |  |- Foo.c
|  |  |- Foo.h
