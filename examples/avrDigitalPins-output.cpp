/*
 * Example sketch using the "avrDigitalPins" library.
 *
 * Norman Dunbar
 * 26 August 2021.
 */

// Include the library header.
#include "avrDigitalPin.h"

// Header for _delay_ms() also required.
#include <util/delay.h>

// Create an avrDigitalPin connected to the built in LED
// and configure it as output.
avrDigitalPin ledPin(pinD13, pinOUTPUT);

int main() {
    // SETUP:


    // No further setup required, but quick
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


    while (1) {

        // Flash the pin every second.
        ledPin.toggleState();
        _delay_ms(1000);
    }
}

