#include <Arduino.h>
#include <Ps3Controller.h>

// ---------------------------------------------------------------------------
// MAC Address Configuration
//
// A DualShock 3 controller stores the Bluetooth MAC address of its host.
// Factory-new (or reset) controllers ship with 00:00:00:00:00:00 as their
// stored master address.  Keeping this default means a brand-new controller
// will connect to the ESP32 straight away with no extra tools required.
//
// If your controller has previously been paired to a PS3 console it will
// already store that console's MAC address instead.  In that case either:
//   A) Use SixaxisPairTool / sixaxispairer to write "00:00:00:00:00:00"
//      back into the controller (factory-reset the pairing), or
//   B) Read the current master address from the controller with the same
//      tool and change CONTROLLER_MAC below to match.
// ---------------------------------------------------------------------------
#define CONTROLLER_MAC "00:00:00:00:00:00"

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
}

void setup() {
    Serial.begin(115200);

    // Register callbacks
    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);

    // Start the Ps3 library with the target MAC address.
    // This sets the ESP32's Bluetooth MAC address so the controller
    // (which stores a fixed host address) can find it.
    Ps3.begin(CONTROLLER_MAC);

    Serial.println("Ready – waiting for PS3 controller...");
    Serial.print("ESP32 Bluetooth MAC address: ");
    Serial.println(CONTROLLER_MAC);
}

void loop() {
    // Nothing to do here; all controller input is handled in notify().
    delay(LOOP_DELAY_MS);
}
