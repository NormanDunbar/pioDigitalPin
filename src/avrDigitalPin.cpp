#include "avrDigitalPin.h"
#include <avr/io.h>

// Constructor
avrDigitalPin::avrDigitalPin(pinName_t pinNumber,
                             pinMode_t Mode)
    : _isOutput(false)
{
    // Calculate the PORT, PIN and DDR from the pin.
    // D0 through D7 = PORTD,
    // D8 through D13 = PORTB,
    // D14 (A0) through D19 (A5) = PORTC.
    if (pinNumber <= pinD7) {
        // We are in D registers.
        _port = &PORTD;
        _pin = &PIND;
        _ddr = &DDRD;

        // PinBit is the same as the pin.
        _bitMask = pinNumber;
    } else if (pinNumber <= pinD13) {
        // We are in B registers.
        _port = &PORTB;
        _pin = &PINB;
        _ddr = &DDRB;

        // PinBit is the pin - 8
        _bitMask = pinNumber - 8;
    } else {
        // We are in C registers.
        _port = &PORTC;
        _pin = &PINC;
        _ddr = &DDRC;

        // PinBit is the pin - 14
        _bitMask = pinNumber - 14;
    }

    // Now we have the registers, configure the pin.
    if (Mode == pinOUTPUT) {
        // OUTPUT_pin: set bit in DDRx register.
        *_ddr |= (1 << _bitMask);
        _isOutput = true;
    } else {
        // INPUT [+/-PULLUP].
        // Clear bit in DDRx register.
        *_ddr &= ~(1 << _bitMask);

        if (Mode == pinINPUT) {
            // INPUT: Clear bit in PORTx register.
            *_port &= ~(1 << _bitMask);
        } else {
            // INPUT_PULLUP: Set bit in PORTx Register.
            *_port |= (1 << _bitMask);
        }
    }
}                     


// For Output digitalPins:

// Set the pin state to high or low.
void avrDigitalPin::setState(pinState_t pinState)
{
    if (!_isOutput)
        return;

    if (pinState)
        *_port |= (1 << _bitMask);
    else
        *_port &= ~(1 << _bitMask);
}


// Toggle the current pin state.
void avrDigitalPin::toggleState()
{
    if (!_isOutput)
        return;
        
    *_pin |= (1 << _bitMask);
}


// For Input and Output Pins.

// Read the pin state.
pinState_t avrDigitalPin::getState()
{
    return (pinState_t)(!!(*_pin & (1 << _bitMask)));
}
