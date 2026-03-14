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

### Option A – Controller is factory-new or has been reset (easiest)

A brand-new DualShock 3 controller ships with `00:00:00:00:00:00` as its stored
master Bluetooth address, which is exactly what the firmware defaults to.  
Just flash the firmware and press the **PS** button – the controller will connect
automatically.

### Option B – Controller was previously paired to a PS3 console

The controller will already store the PS3 console's MAC address.  Choose one of
the following:

* **Reset the controller pairing** – Connect the controller to your PC via USB,
  open SixaxisPairTool / sixaxispairer, and write `00:00:00:00:00:00` as the
  *Master Bluetooth Address*.  This reverts it to factory default so Option A
  applies again.

* **Match the firmware to the controller** – In SixaxisPairTool note the
  *Master Bluetooth Address* currently stored (e.g. `aa:bb:cc:dd:ee:ff`), then
  edit `src/main.cpp`:
  ```cpp
  #define CONTROLLER_MAC "aa:bb:cc:dd:ee:ff"
  ```
  Flash the firmware and press **PS** to connect.

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
ESP32 Bluetooth MAC address: 00:00:00:00:00:00
PS3 Controller Connected!
Cross (X) pressed
Cross (X) released
Triangle pressed
...
```