/*
 * Example sketch using the "avrDigitalPins" library.
 *
 * Reads a switch on pin D2, toggles the builtin LED.
 *
 * Norman Dunbar
 * 26 August 2021.
 */

// Include the library header.
#include "avrDigitalPin.h"

// Header for _delay_ms() also required.
#include <util/delay.h>

// Create a digitalPin connected to the built in LED
// and configure it as output.
avrDigitalPin ledPin(pinD13, pinOUTPUT);

// And another attached to D2, configured as an input
// with pullup.
avrDigitalPin switchPin(pinD2, pinINPUT_PULLUP);

int main() {

    // SETUP:

    // No setup specifically required, but quick
    // flash the LED a couple of times "manually".
    for (uint8_t x = 0; x < 5; x++) {
        ledPin.setState(pinHIGH);
        _delay_ms(250);
        ledPin.setState(pinLOW);
        _delay_ms(100);
    }

    // Delay before starting the loop.
    _delay_ms(1500);


    // LOOP:

    // Read the switch and if pressed, toggle
    // the built in LED.
    // BEWARE: Without debouncing, this might be
    //         somewhat random.

    if (switchPin.getState() == pinLOW) {
        // Switch pressed, toggle the ledPin.
        ledPin.toggleState();
    }

    // A small delay. This stops the switch being
    // read again and again while held down!
    // Press and release as quick as possible!
    _delay_ms(250);
}
