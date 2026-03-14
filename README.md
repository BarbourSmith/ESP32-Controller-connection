# ESP32-Controller-connection

Interface a DualShock 3 (PS3) controller to an ESP32 over Bluetooth.  
When a button is pressed or released the event is printed over the serial port.

## How it works

A PS3 controller stores the Bluetooth MAC address of the console it should
connect to.  The ESP32 uses its own native Bluetooth MAC address — nothing is
overwritten.  You read that MAC from the serial monitor after flashing and write
it into the controller once with a pairing tool.

The firmware uses the [esp32-ps3](https://github.com/jvpernis/esp32-ps3)
library (PS3 Controller Host) which handles the low-level Bluetooth HID
protocol.

## Prerequisites

* [PlatformIO](https://platformio.org/) (CLI or the VS Code extension)
* An ESP32 development board
* A DualShock 3 controller
* [SixaxisPairTool](https://dancingpixelstudios.com/sixaxis-controller/sixaxispairtool/)
  (Windows/macOS) **or** [sixaxispairer](https://github.com/user-none/sixaxispairer)
  (Linux) to write the ESP32's MAC address into the controller

## Setup & Pairing

1. Flash the firmware (see *Build & Flash* below).
2. Open the serial monitor – the ESP32 will print its Bluetooth MAC address,
   for example `14:33:5C:38:26:B8`.
3. Connect the controller to your PC via USB and open SixaxisPairTool /
   sixaxispairer.
4. Set the *Master Bluetooth Address* to the MAC shown in step 2 and click
   *Update*.
5. Disconnect the USB cable, press the **PS** button – the controller will
   connect to the ESP32.

## Build & Flash

```bash
# Install dependencies and build
pio run

# Build and upload to the connected ESP32
pio run --target upload

# Open the serial monitor (115200 baud)
pio device monitor
```

## Serial output

Once connected you will see messages like:

```
Ready – waiting for PS3 controller...
ESP32 Bluetooth MAC address: 14:33:5C:38:26:B8
→ Write the above MAC into the controller via SixaxisPairTool.
PS3 Controller Connected!
Cross (X) pressed
Cross (X) released
Triangle pressed
...
```