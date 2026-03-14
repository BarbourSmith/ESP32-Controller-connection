# ESP32-Controller-connection

Interface a DualShock 3 (PS3) controller to an ESP32 over Bluetooth.  
When a button is pressed or released the event is printed over the serial port.

## How it works

A PS3 controller stores the Bluetooth MAC address of the console it should
connect to.  Instead of reprogramming the controller we set the ESP32's
Bluetooth MAC address to match what the controller already expects.

The firmware uses the [esp32-ps3](https://github.com/jvpernis/esp32-ps3)
library (PS3 Controller Host) which handles the low-level Bluetooth HID
protocol.

## Prerequisites

* [PlatformIO](https://platformio.org/) (CLI or the VS Code extension)
* An ESP32 development board
* A DualShock 3 controller
* [SixaxisPairTool](https://dancingpixelstudios.com/sixaxis-controller/sixaxispairtool/)
  (Windows/macOS) **or** [sixaxispairer](https://github.com/user-none/sixaxispairer)
  (Linux) to read/write the MAC address stored in the controller

## Setup & Pairing

There are two equivalent approaches – choose whichever is easier:

### Option A – Write the firmware MAC address into the controller

1. Flash the firmware (see *Build & Flash* below).  
   The default MAC address is `01:02:03:04:05:06`.
2. Connect the controller to your PC via USB and open SixaxisPairTool.
3. Change the *Master Bluetooth Address* in the tool to `01:02:03:04:05:06`
   and click *Update*.
4. Disconnect the USB cable, press the **PS** button on the controller –
   it should now connect to the ESP32.

### Option B – Set the firmware to match your controller's stored MAC

1. Connect the controller to your PC via USB and open SixaxisPairTool.
2. Note the *Master Bluetooth Address* shown (e.g. `aa:bb:cc:dd:ee:ff`).
3. Edit `src/main.cpp` and change `CONTROLLER_MAC` to that address:
   ```cpp
   #define CONTROLLER_MAC "aa:bb:cc:dd:ee:ff"
   ```
4. Flash the firmware.  The ESP32 will now advertise that MAC address and
   the controller will connect automatically when you press **PS**.

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
ESP32 Bluetooth MAC address: 01:02:03:04:05:06
PS3 Controller Connected!
Cross (X) pressed
Cross (X) released
Triangle pressed
...
```