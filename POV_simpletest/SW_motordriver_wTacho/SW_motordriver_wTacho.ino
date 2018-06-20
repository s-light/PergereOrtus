/******************************************************************************

    SW_motordriver_wTacho.ino
        basis for multiple quick test things
        debugout on usbserial interface: 115200baud

    hardware:
        Board:
            Arduino compatible (with serial port)
            Arduino MICRO
            LED on pin 13
        Connections:
            D4 --> push button to GND
            D5 --> push button to GND
            D6 --> push button to GND
            D7 --> push button to GND
            D8 / A8 --> poti 5V-GND
            D9 --> LED green
            D10 --> LED blue
            D11 --> LED white

            SCK --> Clock input of ?
            MOSI --> Data input of ?

            D2 I2C SDA --> Data for ?
            D3 I2C SCL --> Clock for ?

            D0 RX --> ?
            D1 TX --> ?
            D12 --> ?

            D3 --> PWM out

    libraries used:
        ~ slight_DebugMenu
        ~ slight_Button
        ~ slight_FaderLin
            MIT, cc by sa, s-light - stefan krueger,
            http://s-light.eu
        ~ Adafruit_NeoPixel
			Written by Phil Burgess / Paint Your Dragon for Adafruit Industries,
			Adafruit Industries GNU LGPL,
			https://github.com/adafruit/Adafruit_NeoPixel
			https://learn.adafruit.com/adafruit-neopixel-uberguide
		~ Adafruit_DotStar
			Written by Limor Fried and Phil Burgess for Adafruit Industries,
			Adafruit Industries GNU LGPL,
			https://github.com/adafruit/Adafruit_DotStar
			https://learn.adafruit.com/adafruit-dotstar-leds
        ~ FastLED
            MIT, FastLED-Team
            https://github.com/FastLED/FastLED
        ~ DMXSerial
			Copyright (c) 2005-2012 by Matthias Hertel,
			http://www.mathertel.de
        ~ FreqMeasure
			Copyright (c) 2011 PJRC.COM, LLC - Paul Stoffregen <paul@pjrc.com>
			https://www.pjrc.com/teensy/td_libs_FreqMeasure.html
        ~ Servo
            Arduino Built in Servo Library

    written by stefan krueger (s-light),
        github@s-light.eu, http://s-light.eu, https://github.com/s-light/

    changelog / history
        check git commit messages

    TO DO:
        ~ xx


******************************************************************************/
/******************************************************************************
    The MIT License (MIT)

    Copyright (c) 2017 Stefan Krüger

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
******************************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// use "file.h" for files in same directory as .ino
// #include "file.h"
// use <file.h> for files in library directory
// #include <file.h>

#include <SPI.h>

#include <LiquidCrystal.h>

// #include <Servo.h>

#include <slight_DebugMenu.h>
#include <slight_FaderLin.h>
#include <slight_ButtonInput.h>

// #include <Tlc59711.h>

// #include <Adafruit_NeoPixel.h>
// #include <Adafruit_DotStar.h>

// #include "FastLED.h"

// #include <DMXSerial.h>

#include <FreqMeasure.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Info
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sketchinfo_print(Print &out) {
    out.println();
    //             "|~~~~~~~~~|~~~~~~~~~|~~~..~~~|~~~~~~~~~|~~~~~~~~~|"
    out.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    out.println(F("|                       ^ ^                      |"));
    out.println(F("|                      (0,0)                     |"));
    out.println(F("|                      ( _ )                     |"));
    out.println(F("|                       \" \"                      |"));
    out.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    out.println(F("| SW_motordriver_wTacho.ino"));
    out.println(F("|   branch: 'DMXServo' - receive DMX and control one Servo"));
    out.println(F("|"));
    out.println(F("| This Sketch has a debug-menu:"));
    out.println(F("| send '?'+Return for help"));
    out.println(F("|"));
    out.println(F("| dream on & have fun :-)"));
    out.println(F("|"));
    out.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    out.println(F("|"));
    //out.println(F("| Version: Nov 11 2013  20:35:04"));
    out.print(F("| version: "));
    out.print(F(__DATE__));
    out.print(F("  "));
    out.print(F(__TIME__));
    out.println();
    out.println(F("|"));
    out.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    out.println();

    //out.println(__DATE__); Nov 11 2013
    //out.println(__TIME__); 20:35:04
}


// Serial.print to Flash: Notepad++ Replace RegEx
//     Find what:        Serial.print(.*)\("(.*)"\);
//     Replace with:    Serial.print\1\(F\("\2"\)\);



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// definitions (global)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Debug Output

boolean infoled_state = 0;
const byte infoled_pin = 9;

unsigned long debugOut_LiveSign_TimeStamp_LastAction = 0;
const uint16_t debugOut_LiveSign_UpdateInterval = 1000; //ms

boolean debugOut_LiveSign_Serial_Enabled = 0;
boolean debugOut_LiveSign_LED_Enabled = 1;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu

// slight_DebugMenu(Stream &in_ref, Print &out_ref, uint8_t input_length_new);
slight_DebugMenu myDebugMenu(Serial, Serial, 15);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LCD

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);

uint32_t lcd_update_timestamp_last = 0;
const uint16_t lcd_update_interval = 500; //ms

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FaderLin

const uint8_t myFaderSpeed__channel_count = 1;
slight_FaderLin myFaderSpeed(
    0, // byte cbID_New
    myFaderSpeed__channel_count, // byte cbChannelCount_New
    myFaderSpeed_callback_OutputChanged, // tCbfuncValuesChanged cbfuncValuesChanged_New
    myFaderSpeed_onEvent // tCbfuncStateChanged cbfuncStateChanged_New
);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// analog in

const uint8_t analog_pin = 8;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button

// enum button_names {
//     button
// };

const uint16_t button_duration_Debounce      =   10;
const uint16_t button_duration_HoldingDown   = 1000;
const uint16_t button_duration_ClickSingle   =   40;
const uint16_t button_duration_ClickLong     = 1000;
const uint16_t button_duration_ClickDouble   =  200;

const uint8_t button_1 = 0;
const uint8_t button_2 = 1;
const uint8_t button_3 = 2;
const uint8_t button_4 = 3;


const uint8_t buttons_COUNT = 4;
slight_ButtonInput buttons[buttons_COUNT] = {
    slight_ButtonInput(
        button_1,
        4,
        button_getInput,
        button_onEvent,
        button_duration_Debounce,
        button_duration_HoldingDown,
        button_duration_ClickSingle,
        button_duration_ClickLong,
        button_duration_ClickDouble
    ),
    slight_ButtonInput(
        button_2,
        5,
        button_getInput,
        button_onEvent,
        button_duration_Debounce,
        button_duration_HoldingDown,
        button_duration_ClickSingle,
        button_duration_ClickLong,
        button_duration_ClickDouble
    ),
    slight_ButtonInput(
        button_3,
        6,
        button_getInput,
        button_onEvent,
        button_duration_Debounce,
        button_duration_HoldingDown,
        button_duration_ClickSingle,
        button_duration_ClickLong,
        button_duration_ClickDouble
    ),
    slight_ButtonInput(
        button_4,
        7,
        button_getInput,
        button_onEvent,
        button_duration_Debounce,
        button_duration_HoldingDown,
        button_duration_ClickSingle,
        button_duration_ClickLong,
        button_duration_ClickDouble
    )
};








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Motor

// enum class motorstate_t : uint8_t {      // c++ typesafe; arduino > 1.6.
enum motorstate_t {  // c
    STATE_notvalid,
    // STATE_error,
    STATE_coast,
    STATE_run,
    STATE_fadeup,
    STATE_fadedown,
};
motorstate_t motor_state = STATE_coast;

const uint8_t motor_pin = 3;

const uint16_t motor_fade_duration = 2000;
// uint8_t motor_speed = 0;

const uint8_t motor_min_value = 20;
const uint8_t motor_max_value = 50;

uint8_t motor_target_value = 20;
uint8_t motor_current_value = 0;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Tacho

uint8_t tacho_pin = 13;

float tacho_frequency = 0;
// float tacho_duration = 0;
uint32_t tacho_raw = 0;

// double tacho_sum = 0;
// int16_t tacho_count = 0;
// const uint8_t tacho_average_count = 30;

uint32_t tacho_lastread_timestamp = 0;
const uint16_t tacho_timeout = 2000; //ms

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// other things..












//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// debug things

// freeRam found at
// http://forum.arduino.cc/index.php?topic=183790.msg1362282#msg1362282
// posted by mrburnette
int freeRam () {
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu System

// Main Menu
void handleMenu_Main(slight_DebugMenu *pInstance) {
    Print &out = pInstance->get_stream_out_ref();
    char *command = pInstance->get_command_current_pointer();
    // out.print("command: '");
    // out.print(command);
    // out.println("'");
    switch (command[0]) {
        case 'h':
        case 'H':
        case '?': {
            // help
            out.println(F("____________________________________________________________"));
            out.println();
            out.println(F("Help for Commands:"));
            out.println();
            out.println(F("\t '?': this help"));
            out.println(F("\t 'i': sketch info"));
            out.println(F("\t 'y': toggle DebugOut livesign print"));
            out.println(F("\t 'Y': toggle DebugOut livesign LED"));
            out.println(F("\t 'x': tests"));
            out.println();
            out.println(F("\t 'A': Show 'HelloWorld' "));
            // out.println(F("\t 'a': toggle sequencer"));
            // out.println(F("\t 's': set channel 's1:65535'"));
            // out.println(F("\t 'f': DemoFadeTo(ID, value) 'f1:65535'"));
            out.println();
            out.println(F("____________________________________________________________"));
        } break;
        case 'i': {
            sketchinfo_print(out);
        } break;
        case 'y': {
            out.println(F("\t toggle DebugOut livesign Serial:"));
            debugOut_LiveSign_Serial_Enabled = !debugOut_LiveSign_Serial_Enabled;
            out.print(F("\t debugOut_LiveSign_Serial_Enabled:"));
            out.println(debugOut_LiveSign_Serial_Enabled);
        } break;
        case 'Y': {
            out.println(F("\t toggle DebugOut livesign LED:"));
            debugOut_LiveSign_LED_Enabled = !debugOut_LiveSign_LED_Enabled;
            out.print(F("\t debugOut_LiveSign_LED_Enabled:"));
            out.println(debugOut_LiveSign_LED_Enabled);
        } break;
        case 'x': {
            // get state
            out.println(F("__________"));
            out.println(F("Tests:"));

            out.println(F("nothing to do."));

            // uint16_t wTest = 65535;
            // uint16_t wTest = atoi(&command[1]);
            // out.print(F("wTest: "));
            // out.print(wTest);
            // out.println();
            //
            // out.print(F("1: "));
            // out.print((byte)wTest);
            // out.println();
            //
            // out.print(F("2: "));
            // out.print((byte)(wTest>>8));
            // out.println();

            // char buffer[] = "--------.---\0";
            // snprintf(
            //     buffer, sizeof(buffer),
            //     "%*.*f",
            //     10,
            //     2,
            //     12345.789);
            // out.print(F("sprintf: "));
            // out.print(buffer);
            // out.println();
            //
            // memset(buffer, '\0', sizeof(buffer));
            // dtostrf(12345.789, 0, 2, buffer);
            // out.print(F("dtostrf: '"));
            // out.print(buffer);
            // out.print(F("'"));
            // out.println();
            //
            // memset(buffer, '\0', sizeof(buffer));
            // dtostrf(12345.789, 1, 3, buffer);
            // out.print(F("dtostrf: '"));
            // out.print(buffer);
            // out.print(F("'"));
            // out.println();
            //
            // memset(buffer, '\0', sizeof(buffer));
            // dtostrf(12.789, 8, 2, buffer);
            // out.print(F("dtostrf: '"));
            // out.print(buffer);
            // out.print(F("'"));
            // out.println();
            //
            // memset(buffer, '\0', sizeof(buffer));
            // dtostrf(12.789, -8, 2, buffer);
            // out.print(F("dtostrf: '"));
            // out.print(buffer);
            // out.print(F("'"));
            // out.println();
            //
            // char buffer2[] = "--.--\0";
            // memset(buffer2, '\0', sizeof(buffer2));
            // dtostrf(123.78, 5, 2, buffer2);
            // out.print(F("dtostrf: '"));
            // out.print(buffer2);
            // out.print(F("'"));
            // out.println();

            out.print(F("FLT_MAX: '"));
            out.print(FLT_MAX);
            out.print(F("'"));
            out.println();

            out.print(F("print_float_align_right: '"));
            slight_DebugMenu::print_float_align_right(
                out, 123.78, 6, 2, true);
            out.print(F("'"));
            out.println();


            out.println();

            out.println(F("__________"));
        } break;
        //---------------------------------------------------------------------
        case 'A': {
            out.println(F("\t Hello World! :-)"));
        } break;
        case 'a': {
            out.println(F("\t toggle sequencer:"));
            // if (sequencer_mode == sequencer_OFF) {
            //     /* code */
            //     sequencer_mode = sequencer_CHANNELCHECK;
            //     out.print(F("\t sequencer_mode: CHANNELCHECK\n"));
            // }
            // else {
            //     sequencer_mode = sequencer_OFF;
            //     out.print(F("\t sequencer_mode: OFF\n"));
            // }
        } break;
        case 's': {
            out.print(F("\t set channel "));
            // convert part of string to int
            // (up to first char that is not a number)
            // uint8_t command_offset = 1;
            // uint8_t ch = atoi(&command[command_offset]);
            // // convert single character to int representation
            // // uint8_t id = &command[1] - '0';
            // command_offset = 3;
            // if (ch > 9) {
            //     command_offset = command_offset +1;
            // }
            // out.print(ch);
            // out.print(F(" : "));
            // uint16_t value = atoi(&command[command_offset]);
            // out.print(value);
            // out.println();
            //
            // if (output_enabled) {
            //     tlc.setChannel(ch, value);
            //     tlc.write();
            // }
        } break;
        // case 'f': {
        //     out.print(F("\t DemoFadeTo "));
        //     // convert part of string to int
        //     // (up to first char that is not a number)
        //     uint8_t id = atoi(&command[1]);
        //     // convert single character to int representation
        //     // uint8_t id = &command[1] - '0';
        //     out.print(id);
        //     out.print(F(" : "));
        //     uint16_t value = atoi(&command[3]);
        //     out.print(value);
        //     out.println();
        //     //demo_fadeTo(id, value);
        //     tlc.setChannel()
        //     out.println(F("\t demo for parsing values --> finished."));
        // } break;
        //---------------------------------------------------------------------
        default: {
            if(strlen(command) > 0) {
                out.print(F("command '"));
                out.print(command);
                out.println(F("' not recognized. try again."));
            }
            pInstance->get_command_input_pointer()[0] = '?';
            pInstance->set_flag_EOC(true);
        }
    } // end switch

    // end Command Parser
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LCD

void setup_LCD(Print &out) {
    out.println(F("setup button:")); {
        out.println(F("\t set 16x2"));
        // setup LCD's number of columns & rows
        lcd.begin(16, 2);

        out.println(F("\t print welcome text"));
        // set cursor (first char, first line)
        lcd.setCursor(0, 0);
        lcd.print("32U4wLCD_proto");
        lcd.setCursor(0, 1);
        lcd.print("MotorDri. wTacho");

        // delay(500);
        // lcd.clear();
    }
    out.println(F("\t finished."));
}


// Display Layout:
//     0000000000111111
//     0123456789012345
//  0  running    t:255
//  1  1800.00rps c:255
//  -- old --
//  0  status: running
//  0  running  1800.00
//  1  t: 255    c: 255

void print_Status(LiquidCrystal &lcd) {
    lcd.setCursor(0, 0);
    // lcd.print("status: ");
    switch (motor_state) {
        case STATE_notvalid: {
            lcd.print("--------");
        } break;
        case STATE_coast: {
            lcd.print("coast   ");
        } break;
        case STATE_run: {
            lcd.print("running ");
        } break;
        case STATE_fadeup: {
            lcd.print("fadeup  ");
        } break;
        case STATE_fadedown: {
            lcd.print("fadedown");
        } break;
    }
}

void print_TargetValue(LiquidCrystal &lcd) {
    lcd.setCursor(13, 0);
    slight_DebugMenu::print_uint8_align_right(lcd, motor_target_value);
}

void print_CurrentValue(LiquidCrystal &lcd) {
    lcd.setCursor(13, 1);
    slight_DebugMenu::print_uint8_align_right(lcd, motor_current_value);
}

void print_CurrentRPS(LiquidCrystal &lcd) {
    lcd.setCursor(0, 1);
    // 123.12
    // slight_DebugMenu::print_float_align_right(
    //     lcd, tacho_frequency, 6, 2, true);

    char buffer1[] = "---.--___;";
    char buffer2[] = "---.--___;";
    // sprintf(buffer1, "%6.2f", tacho_frequency);
    // Serial.println(buffer1);

    // Serial.println();
    // Serial.print("buffer1: ");
    // Serial.println(buffer1);
    // Serial.print("buffer2: ");
    // Serial.println(buffer2);

    // based on https://stackoverflow.com/a/27652012/574981
    dtostrf(tacho_frequency, 1, 2, buffer1);

    // Serial.print("buffer1: ");
    // Serial.println(buffer1);
    // Serial.print("buffer2: ");
    // Serial.println(buffer2);

    sprintf(buffer2,"%6srps", buffer1);
    // sprintf(buffer2,"%2s", "World");

    // Serial.print("buffer1: ");
    // Serial.println(buffer1);
    // Serial.print("buffer2: ");
    // Serial.println(buffer2);

    lcd.print(buffer2);
    // lcd.print("rps");
    // lcd.print(tacho_raw);
}

void print_CurrentRPM(LiquidCrystal &lcd) {
    lcd.setCursor(0, 1);
    // 1234.1
    slight_DebugMenu::print_float_align_right(
        lcd, tacho_frequency, 6, 1, true);
    lcd.print("rpm");
}

void update_LCD(LiquidCrystal &lcd) {
    lcd.clear();
    print_Status(lcd);

    print_CurrentRPS(lcd);

    lcd.setCursor(10, 0);
    lcd.print("t:");
    print_TargetValue(lcd);

    lcd.setCursor(10, 1);
    lcd.print("c:");
    print_CurrentValue(lcd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FaderLin

void setup_myFaderSpeed(Print &out) {
    out.println(F("setup myFaderSpeed:"));

    out.println(F("\t myFaderSpeed.begin();"));
    myFaderSpeed.begin();

    // out.println(F("\t myFaderSpeed welcome fade"));
    // // myFaderSpeed.startFadeTo( 1000, memList_A[memList_A__Full]);
    // myFaderSpeed_fadeTo(1000, 60000, 60000, 0);
    // // run fading
    // // while ( myFaderSpeed.getLastEvent() == slight_FaderLin::event_fading_Finished) {
    // //     myFaderSpeed.update();
    // // }
    // while ( myFaderSpeed.update() == slight_FaderLin::state_Fading) {
    //     // nothing to do.
    // }
    // myFaderSpeed.update();
    // // myFaderSpeed.startFadeTo( 1000, memList_A[memList_A__Off]);
    // myFaderSpeed_fadeTo(1000, 0, 0, 1);
    // // run fading
    // // while ( myFaderSpeed.getLastEvent() != slight_FaderLin::event_fading_Finished) {
    // //     myFaderSpeed.update();
    // // }
    // while ( myFaderSpeed.update() == slight_FaderLin::state_Fading) {
    //     // nothing to do.
    // }
    myFaderSpeed.update();

    out.println(F("\t finished."));
}

void myFaderSpeed_callback_OutputChanged(uint8_t id, uint16_t *values, uint8_t count) {

    // if (bDebugOut_myFaderSpeed_Output_Enable) {
    //     Serial.print(F("OutputValue: "));
    //     printArray_uint16(Serial, wValues, bCount);
    //     Serial.println();
    // }

    // for (size_t channel_index = 0; channel_index < count; channel_index++) {
    //     tlc.setChannel(channel_index, values[channel_index]);
    // }

    motor_set_output(values[0]);

}

void myFaderSpeed_fadeTo(uint16_t duration, uint8_t v) {
    uint16_t values[myFaderSpeed__channel_count];
    // init array with 0
    values[0] = v;
    Serial.print(F("start fade to "));
    Serial.print(v);
    Serial.print(F(" in "));
    Serial.print(duration);
    Serial.print(F(" ms."));
    myFaderSpeed.startFadeTo(duration, values);
}

void myFaderSpeed_onEvent(slight_FaderLin *pInstance, byte event) {


    Serial.print(F("Instance ID:"));
    Serial.println((*pInstance).getID());

    Serial.print(F("Event: "));
    (*pInstance).printEvent(Serial, event);
    Serial.println();


    // react on events:
    switch (event) {
        case slight_FaderLin::event_StateChanged : {
            // Serial.print(F("slight_FaderLin "));
            // Serial.print((*pInstance).getID());
            // Serial.println(F(" : "));
            // Serial.print(F("\t state: "));
            // (*pInstance).printState(Serial);
            // Serial.println();

            // switch (state) {
            //     case slight_FaderLin::state_Standby : {
            //             //
            //         } break;
            //     case slight_FaderLin::state_Fading : {
            //             //
            //         } break;
            //     case slight_FaderLin::state_Finished : {
            //             //
            //         } break;
            // } //end switch

        } break;

        case slight_FaderLin::event_fading_Finished : {
            // Serial.print(F("\t fading Finished."));
            switch (motor_state) {
                case STATE_notvalid: {
                    // nothing to do.
                } break;
                case STATE_coast: {
                    // nothing to do.
                } break;
                case STATE_run: {
                    // nothing to do.s
                } break;
                case STATE_fadeup: {
                    motor_state = STATE_run;
                } break;
                case STATE_fadedown: {
                    motor_state = STATE_coast;
                    motor_set_output(0);
                } break;
            }
            print_Status(lcd);
        } break;
    } //end switch

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button

void buttons_init(Print &out) {
    out.println(F("setup button:")); {
        // out.println(F("\t set button pin"));
        // pinMode(button.getPin(), INPUT_PULLUP);
        // out.println(F("\t button begin"));
        // button.begin();
        for (size_t index = 0; index < buttons_COUNT; index++) {
            pinMode(buttons[index].getPin(), INPUT_PULLUP);
            buttons[index].begin();
        }
    }
    out.println(F("\t finished."));
}


void buttons_update() {
    for (size_t index = 0; index < buttons_COUNT; index++) {
        buttons[index].update();
    }
}

boolean button_getInput(uint8_t id, uint8_t pin) {
    // read input invert reading - button closes to GND.
    // check HWB
    // return ! (PINE & B00000100);
    return ! digitalRead(pin);
}

void button_onEvent(slight_ButtonInput *pInstance, byte bEvent) {
    // Serial.print(F("FRL button:"));
    // Serial.println((*pInstance).getID());
    //
    // Serial.print(F("Event: "));
    // Serial.print(bEvent);
    // // (*pInstance).printEvent(Serial, bEvent);
    // Serial.println();

    uint8_t button_id = (*pInstance).getID();

    // show event additional infos:
    switch (bEvent) {
        // case slight_ButtonInput::event_StateChanged : {
        //     Serial.println(F("\t state: "));
        //     (*pInstance).printlnState(Serial);
        //     Serial.println();
        // } break;
        case slight_ButtonInput::event_Down : {
            // Serial.println(F("FRL down"));
        } break;
        case slight_ButtonInput::event_HoldingDown : {
            uint32_t duration = (*pInstance).getDurationActive();
            // Serial.println(F("duration active: "));
            // Serial.println(duration);

            uint8_t count = 1;

            if (duration <= 2000) {
                count = 5;
            }
            else if (duration <= 10000) {
                count = 10;
            }
            else if (duration <= 15000) {
                count = 20;
            }

            if (button_id == button_1) {
                motor_set_value(motor_target_value - count);
                print_TargetValue(lcd);
            }
            if (button_id == button_2) {
                motor_set_value(motor_target_value + count);
                print_TargetValue(lcd);
            }
            if (button_id == button_3) {
                // nothing to do.
            }
            if (button_id == button_4) {
                // nothing to do.
                // myFaderSpeed_fadeTo(0, 0);
            }

        } break;
        case slight_ButtonInput::event_Up : {
            Serial.println(F("up"));
            // myFaderSpeed_fadeTo(500, 0, 0, 1);
        } break;
        case slight_ButtonInput::event_Click : {
            Serial.println(F("click"));

            if (button_id == button_1) {
                Serial.print("motor_target_value: ");
                Serial.print(motor_target_value);
                Serial.print(" -> ");
                motor_set_value(motor_target_value - 1);
                Serial.print(motor_target_value);
                Serial.println();
                print_TargetValue(lcd);
            }
            if (button_id == button_2) {
                Serial.print("motor_target_value: ");
                Serial.print(motor_target_value);
                Serial.print(" -> ");
                motor_set_value(motor_target_value + 1);
                Serial.print(motor_target_value);
                Serial.println();
                print_TargetValue(lcd);
            }

            if (button_id == button_3) {
                switch (motor_state) {
                    case STATE_notvalid: {
                        // nothing to do.
                    } break;
                    case STATE_fadedown:
                    case STATE_coast: {
                        // nothing to do.
                    } break;
                    case STATE_fadeup:
                    case STATE_run: {
                        motor_state = STATE_fadeup;
                        myFaderSpeed_fadeTo(
                            motor_fade_duration,
                            motor_target_value);
                    } break;
                }
                print_Status(lcd);
            }
            if (button_id == button_4) {
                switch (motor_state) {
                    case STATE_notvalid: {
                        // nothing to do.
                    } break;
                    case STATE_fadedown:
                    case STATE_coast: {
                        motor_state = STATE_fadeup;
                        myFaderSpeed_fadeTo(
                            motor_fade_duration,
                            motor_target_value);
                    } break;
                    case STATE_fadeup:
                    case STATE_run: {
                        motor_state = STATE_fadedown;
                        myFaderSpeed_fadeTo(
                            50,
                            motor_min_value);
                    } break;
                }
                print_Status(lcd);
            }

        } break;
        case slight_ButtonInput::event_ClickLong : {
            Serial.println(F("click long"));
        } break;
        case slight_ButtonInput::event_ClickDouble : {
            // Serial.println(F("click double"));
        } break;
        case slight_ButtonInput::event_ClickTriple : {
            // Serial.println(F("click triple"));
        } break;
        // case slight_ButtonInput::event_ClickMulti : {
        //     Serial.print(F("click count: "));
        //     Serial.println((*pInstance).getClickCount());
        // } break;
    }  // end switch
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Motor

void setup_Motor(Print &out) {
    out.println(F("setup Motor:"));

    pinMode(motor_pin, OUTPUT);

    analogWrite(motor_pin, 0);

    out.println(F("\t finished."));
}

void motor_set_value(uint8_t value) {
    motor_target_value = constrain(
        value,
        motor_min_value,
        motor_max_value
    );
    // if (value < motor_min_value) {
    //     motor_target_value = motor_min_value;
    // } else {
    //     if (value > motor_max_value) {
    //         motor_target_value = motor_max_value;
    //     } else {
    //         motor_target_value = value;
    //     }
    // }
}

void motor_set_output(uint8_t value) {
    if (motor_state == STATE_coast) {
        motor_current_value = 0;
    } else {
        motor_current_value = value;
    }
    analogWrite(motor_pin, motor_current_value);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Tacho

void setup_Tacho(Print &out) {
    out.println(F("setup Tacho:"));

    pinMode(tacho_pin, INPUT);

    FreqMeasure.begin();

    out.println(F("\t finished."));
}

void tacho_update() {
    if (FreqMeasure.available()) {
        tacho_lastread_timestamp = millis();
        // Serial.println("tacho available");
        // average several reading together
        tacho_raw =  FreqMeasure.read();
        // Serial.println(tacho_raw);
        tacho_frequency = FreqMeasure.countToFrequency(tacho_raw);
        // Serial.println(tacho_frequency);
        // tacho_duration =  FreqMeasure.countToNanoseconds(tacho_raw);
        // tacho_sum = tacho_sum + FreqMeasure.read();
        // tacho_count = tacho_count + 1;
        // if (tacho_count > tacho_average_count) {
        //     tacho_frequency = FreqMeasure.countToFrequency(tacho_sum / tacho_count);
        //     tacho_sum = 0;
        //     tacho_count = 0;
        // }
    } else {
        if ((millis() - tacho_lastread_timestamp) > tacho_timeout) {
            tacho_lastread_timestamp = millis();
            tacho_frequency = 0;
            // Serial.println("reset tacho");
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// other things..




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setup
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // initialise PINs

        //LiveSign
        pinMode(infoled_pin, OUTPUT);
        digitalWrite(infoled_pin, HIGH);

        // as of arduino 1.0.1 you can use INPUT_PULLUP

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // initialise serial

        // for ATmega32U4 devices:
        #if defined (__AVR_ATmega32U4__)
            // wait for arduino IDE to release all serial ports after upload.
            delay(1000);
        #endif

        Serial.begin(115200);

        // for ATmega32U4 devices:
        #if defined (__AVR_ATmega32U4__)
            // Wait for Serial Connection to be Opend from Host or
            // timeout after 6second
            uint32_t timeStamp_Start = millis();
            while( (! Serial) && ( (millis() - timeStamp_Start) < 1000 ) ) {
                // nothing to do
            }
        #endif

        Print &out = Serial;
        out.println();

        out.print(F("# Free RAM = "));
        out.println(freeRam());

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // print welcome

        sketchinfo_print(out);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setup things

    setup_LCD(out);

    out.print(F("# Free RAM = "));
    out.println(freeRam());

    buttons_init(out);

    setup_Motor(out);

    setup_Tacho(out);

    out.print(F("# Free RAM = "));
    out.println(freeRam());

    setup_myFaderSpeed(out);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setup XXX1

        // out.print(F("# Free RAM = "));
        // out.println(freeRam());
        //
        // out.println(F("setup XXX1:")); {
        //
        //     out.println(F("\t sub action"));
        // }
        // out.println(F("\t finished."));

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // show serial commands

        // myDebugMenu.set_user_EOC_char(';');
        myDebugMenu.set_callback(handleMenu_Main);
        myDebugMenu.begin();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // update_LCD
        delay(1000);
        update_LCD(lcd);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // go

        out.println(F("Loop:"));

} /** setup **/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main loop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // menu input
        myDebugMenu.update();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // update sub parts

        myFaderSpeed.update();
        // button.update();
        buttons_update();
        tacho_update();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // timed things

        // if (sequencer_mode != sequencer_OFF) {
        //     if(
        //         (millis() - sequencer_timestamp_last) > sequencer_interval
        //     ) {
        //         sequencer_timestamp_last =  millis();
        //         // calculate_step();
        //     }
        // }


        if(
            (millis() - lcd_update_timestamp_last) > lcd_update_interval
        ) {
            lcd_update_timestamp_last =  millis();
            print_CurrentValue(lcd);
            print_CurrentRPS(lcd);
            // update_LCD(lcd);
        }


        // if(
        //     (millis() - dmx_timestamp_last) > dmx_interval
        // ) {
        //     dmx_timestamp_last =  millis();
        //     handle_DMX();
        // }

    // handle_DMX();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // debug output

        if (
            (millis() - debugOut_LiveSign_TimeStamp_LastAction) >
            debugOut_LiveSign_UpdateInterval
        ) {
            debugOut_LiveSign_TimeStamp_LastAction = millis();

            if ( debugOut_LiveSign_Serial_Enabled ) {
                Serial.print(millis());
                Serial.print(F("ms;"));
                Serial.print(F("  free RAM = "));
                Serial.print(freeRam());
                // Serial.print(F("; bat votlage: "));
                // Serial.print(bat_voltage/100.0);
                // Serial.print(F("V"));
                Serial.println();
            }

            if ( debugOut_LiveSign_LED_Enabled ) {
                infoled_state = ! infoled_state;
                if (infoled_state) {
                    //set LED to HIGH
                    digitalWrite(infoled_pin, HIGH);
                } else {
                    //set LED to LOW
                    digitalWrite(infoled_pin, LOW);
                }
            }

        }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // other things

} /** loop **/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THE END
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
