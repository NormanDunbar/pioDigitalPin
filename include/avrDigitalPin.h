#ifndef AVRDIGITALPIN_H
#define AVRDIGITALPIN_H

#include <stdint.h>

/* 
 * A library to implement a digitalPin class for the Arduino 
 * IDE. This class is designed only for the IDE, but can be
 * used unchanged by PlatformIO provided that the project
 *  using it, is using the Arduino Framework and has this
 *  defined in the platformio.ini file.
 * 
 * Norman Dunbar
 * 26 August 2021.
 */


// Typedef for the pin modes.
typedef enum pin_Mode : uint8_t {
    pinINPUT,
    pinINPUT_PULLUP,
    pinOUTPUT
} pinMode_t;


// Typedef for pin names. Covers Arduino and AVR naming.
typedef enum pin_Name : uint8_t  {
    pinD0 = 0,
    pinD1,
    pinD2,
    pinD3,
    pinD4,
    pinD5,
    pinD6,
    pinD7,
    pinD8,
    pinD9,
    pinD10,
    pinD11,
    pinD12,
    pinD13,
    pinD14,
    pinD15,
    pinD16,
    pinD17,
    pinD18,
    pinD19,
    pinA0 = pinD14,
    pinA1,
    pinA2,
    pinA3,
    pinA4,
    pinA5,
    pinPD0 = pinD0,
    pinPD1,
    pinPD2,
    pinPD3,
    pinPD4,
    pinPD5,
    pinPD6,
    pinPD7,
    pinPB0 = pinD8,
    pinPB1,
    pinPB2,
    pinPB3,
    pinPB4,
    pinPB5,
    pinPC0 = pinA0,
    pinPC1,
    pinPC2,
    pinPC3,
    pinPC4,
    pinPC5
} pinName_t;


// Typedef for the pin states.
typedef enum pin_State : uint8_t {
    pinLOW = 0,
    pinHIGH
} pinState_t;

class avrDigitalPin {

public:


    // Constructor.
    avrDigitalPin(pinName_t pinNumber,
                  pinMode_t Mode);

    // There is no destructor as a digitalPin should never
    //  go out of scope. Famous last words?


    // For Output digitalPins:
    void setState(pinState_t pinState);
    void toggleState();

    // For Input and Output Pins
    pinState_t getState();

private:
    // Data Direction Register.
    volatile uint8_t *_ddr;

    // PORT register.
    volatile uint8_t *_port;
    
    // PIN register.
    volatile uint8_t *_pin;
    
    // Which bit in the above registers for this pin?
    uint8_t _bitMask;

    // Are we an OUTPUT pin?
    bool _isOutput;
};


#endif // AVRDIGITALPIN_H