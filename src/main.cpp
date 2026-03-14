#include <Arduino.h>
#include <Ps3Controller.h>
#include <esp_bt_device.h>

// The ESP32 uses its own native Bluetooth MAC address – nothing is overwritten.
// After flashing, open the serial monitor to read the MAC that is printed, then
// use SixaxisPairTool / sixaxispairer to write that MAC into the controller.

// Yield interval for the main loop (ms). All controller work is done in
// the notify() callback; the loop just needs to yield to the scheduler.
#define LOOP_DELAY_MS 10

// ---------------------------------------------------------------------------
// Called once when the PS3 controller connects
// ---------------------------------------------------------------------------
void onConnect() {
    Serial.println("PS3 Controller Connected!");
}

// ---------------------------------------------------------------------------
// Called every time new data arrives from the controller.
// Prints any button that is newly pressed or released.
// ---------------------------------------------------------------------------
void notify() {
    // --- Button-down events (newly pressed this frame) ---
    if (Ps3.event.button_down.cross)    Serial.println("Cross (X) pressed");
    if (Ps3.event.button_down.circle)   Serial.println("Circle pressed");
    if (Ps3.event.button_down.triangle) Serial.println("Triangle pressed");
    if (Ps3.event.button_down.square)   Serial.println("Square pressed");

    if (Ps3.event.button_down.up)    Serial.println("D-pad Up pressed");
    if (Ps3.event.button_down.down)  Serial.println("D-pad Down pressed");
    if (Ps3.event.button_down.left)  Serial.println("D-pad Left pressed");
    if (Ps3.event.button_down.right) Serial.println("D-pad Right pressed");

    if (Ps3.event.button_down.l1)    Serial.println("L1 pressed");
    if (Ps3.event.button_down.l2)    Serial.println("L2 pressed");
    if (Ps3.event.button_down.l3)    Serial.println("L3 (Left Stick) pressed");
    if (Ps3.event.button_down.r1)    Serial.println("R1 pressed");
    if (Ps3.event.button_down.r2)    Serial.println("R2 pressed");
    if (Ps3.event.button_down.r3)    Serial.println("R3 (Right Stick) pressed");

    if (Ps3.event.button_down.select) Serial.println("Select pressed");
    if (Ps3.event.button_down.start)  Serial.println("Start pressed");
    if (Ps3.event.button_down.ps)     Serial.println("PS button pressed");

    // --- Button-up events (just released this frame) ---
    if (Ps3.event.button_up.cross)    Serial.println("Cross (X) released");
    if (Ps3.event.button_up.circle)   Serial.println("Circle released");
    if (Ps3.event.button_up.triangle) Serial.println("Triangle released");
    if (Ps3.event.button_up.square)   Serial.println("Square released");

    if (Ps3.event.button_up.up)    Serial.println("D-pad Up released");
    if (Ps3.event.button_up.down)  Serial.println("D-pad Down released");
    if (Ps3.event.button_up.left)  Serial.println("D-pad Left released");
    if (Ps3.event.button_up.right) Serial.println("D-pad Right released");

    if (Ps3.event.button_up.l1)    Serial.println("L1 released");
    if (Ps3.event.button_up.l2)    Serial.println("L2 released");
    if (Ps3.event.button_up.l3)    Serial.println("L3 (Left Stick) released");
    if (Ps3.event.button_up.r1)    Serial.println("R1 released");
    if (Ps3.event.button_up.r2)    Serial.println("R2 released");
    if (Ps3.event.button_up.r3)    Serial.println("R3 (Right Stick) released");

    if (Ps3.event.button_up.select) Serial.println("Select released");
    if (Ps3.event.button_up.start)  Serial.println("Start released");
    if (Ps3.event.button_up.ps)     Serial.println("PS button released");

    // --- Analog sticks (dead-zone ±10 around center 128) ---
    const int DEAD_ZONE = 10;
    int lx = Ps3.data.analog.stick.lx;  // left stick X:  -128..127
    int ly = Ps3.data.analog.stick.ly;  // left stick Y:  -128..127
    int rx = Ps3.data.analog.stick.rx;  // right stick X: -128..127
    int ry = Ps3.data.analog.stick.ry;  // right stick Y: -128..127

    if (abs(lx) > DEAD_ZONE || abs(ly) > DEAD_ZONE) {
        Serial.printf("Left  stick  X: %4d  Y: %4d\n", lx, ly);
    }
    if (abs(rx) > DEAD_ZONE || abs(ry) > DEAD_ZONE) {
        Serial.printf("Right stick  X: %4d  Y: %4d\n", rx, ry);
    }
}

void setup() {
    Serial.begin(115200);

    // Register callbacks
    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);

    // Start the Ps3 library without overriding the MAC address so the ESP32
    // keeps its own native Bluetooth MAC.
    Ps3.begin();

    // Print the ESP32's actual Bluetooth MAC address.  Use SixaxisPairTool /
    // sixaxispairer to write this address into the controller so it connects.
    Serial.println("Ready – waiting for PS3 controller...");
    Serial.print("ESP32 Bluetooth MAC address: ");
    const uint8_t* mac = esp_bt_dev_get_address();
    if (mac) {
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.println(macStr);
    }
    Serial.println("→ Write the above MAC into the controller via SixaxisPairTool.");
}

void loop() {
    // Nothing to do here; all controller input is handled in notify().
    delay(LOOP_DELAY_MS);
}
