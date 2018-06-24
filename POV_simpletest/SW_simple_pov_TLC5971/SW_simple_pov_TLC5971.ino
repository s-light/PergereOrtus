/******************************************************************************

    SW_simple_pov_TLC5971
        simple pov test with LEDBoard_4x4_16bit
        debugout on usbserial interface: 115200baud

    hardware:
        Board:
            Arduino compatible (with serial port)
            LED on pin 13
        Connections:
            D4 --> push button to GND
            SCK --> Clock input of TLC5791
            MOSI --> Data input of TLC5791
            only if TLC5791 is used with 5V@ VCC and VREG
            see www.ti.com/lit/ds/symlink/tlc5971.pdf
            page31 9.3 System Examples - Figure 38
            (eventually use a 74HC4050 as Levelshifter 5V-->3.8V
            if you use different VCC/VREG for Chips.)


    libraries used:
        ~ slight_DebugMenu
        ~ slight_Button
        ~ slight_FaderLin
            License: MIT
            written by stefan krueger (s-light),
                github@s-light.eu, http://s-light.eu, https://github.com/s-light/
        ~ Tlc59711.h
            License: MIT
            Copyright (c) 2016 Ulrich Stern
            https://github.com/ulrichstern/Tlc59711

    written by stefan krueger (s-light),
        github@s-light.eu, http://s-light.eu, https://github.com/s-light/

    changelog / history
        check git commit messages

    TO DO:
        ~ xx


******************************************************************************/
/******************************************************************************
    The MIT License (MIT)

    Copyright (c) 2018 Stefan Krüger

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

#include <slight_DebugMenu.h>
#include <slight_FaderLin.h>
#include <slight_ButtonInput.h>

#include <Tlc59711.h>

#include "./pattern_struckt.h"
#include "./patterns.h"


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
    out.println(F("| SW_simple_pov_TLC5971.ino"));
    out.println(F("|   simple pov test with LEDBoard_4x4_16bit"));
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
const byte infoled_pin = 13;

unsigned long debugOut_LiveSign_TimeStamp_LastAction = 0;
const uint16_t debugOut_LiveSign_UpdateInterval = 1000; //ms

boolean debugOut_LiveSign_Serial_Enabled = 0;
boolean debugOut_LiveSign_LED_Enabled = 1;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu

// slight_DebugMenu(Stream &in_ref, Print &out_ref, uint8_t input_length_new);
slight_DebugMenu myDebugMenu(Serial, Serial, 15);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Position detector

const uint8_t pos1_pin = A4;
const uint8_t pos2_pin = A5;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LEDBoard

const uint16_t board_interval = 50;
uint32_t board_timestamp_last = 0;


const uint8_t boards_count = 2;

const uint8_t chips_per_board = 4;

const uint8_t colors_per_led = 3;
const uint8_t leds_per_chip = 4;

const uint8_t colorchannels_per_board = (
    colors_per_led * leds_per_chip * chips_per_board
);

const uint8_t leds_per_row = 4;
const uint8_t leds_per_column = 4;
const uint8_t row_count = leds_per_column;
const uint8_t column_count = leds_per_row;
const uint8_t leds_per_board = leds_per_row*leds_per_column;
const uint8_t leds_total = leds_per_board*boards_count;


const uint8_t BOARD0 = 0;
const uint8_t BOARD1 = 1;


// const uint8_t channel_position_map[leds_per_column][leds_per_row] = {
//     { 0,  1,  4,  5},
//     { 2,  3,  6,  7},
//     { 8,  9, 12, 13},
//     {10, 11, 14, 15},
// };
const uint8_t channel_position_map[row_count*2][column_count] = {
    { 0,  1,  4,  5},
    { 2,  3,  6,  7},
    { 8,  9, 12, 13},
    {10, 11, 14, 15},
    {16, 17, 20, 21},
    {18, 19, 22, 23},
    {24, 25, 28, 29},
    {26, 27, 30, 31},
};

// const uint8_t pixel_line_count = 8;
const uint8_t pixel_line_list[pixel_line_count] = {
     8,
    24,
     9,
    25,
    12,
    28,
    13,
    29,
};

// const uint8_t pattern_map[pixel_line_count][pattern_count] = {
// };
// this is now in patterns.h

// tlc info
const uint8_t tlc_channels = colors_per_led * leds_per_chip;
const uint8_t tlc_channels_per_board = tlc_channels * chips_per_board;
const uint8_t tlc_chips = boards_count * chips_per_board;
const uint8_t tlc_channels_total = (uint8_t)(tlc_chips * tlc_channels);

Tlc59711 tlc(tlc_chips);

bool output_enabled = true;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mode

enum class mode_t : uint8_t {      // c++ typesafe; arduino > 1.6.
    STANDBY,
    standby,
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FaderLin

const uint8_t myFaderRGB__channel_count = colors_per_led;
slight_FaderLin myFaderRGB(
    0, // byte cbID_New
    myFaderRGB__channel_count, // byte cbChannelCount_New
    myFaderRGB_callback_OutputChanged, // tCbfuncValuesChanged cbfuncValuesChanged_New
    myCallback_onEvent // tCbfuncStateChanged cbfuncStateChanged_New
);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button

const uint8_t button_pin = 4;

slight_ButtonInput button(
    0,  // byte cbID_New
    button_pin,  // byte cbPin_New,
    button_getInput,  // tCbfuncGetInput cbfuncGetInput_New,
    button_onEvent,  // tcbfOnEvent cbfCallbackOnEvent_New,
      30,  // const uint16_t cwDuration_Debounce_New = 30,
     500,  // const uint16_t cwDuration_HoldingDown_New = 1000,
      50,  // const uint16_t cwDuration_ClickSingle_New =   50,
     500,  // const uint16_t cwDuration_ClickLong_New =   3000,
     500   // const uint16_t cwDuration_ClickDouble_New = 1000
);


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
            // out.println(F("\t 'A': Show 'HelloWorld' "));
            // out.println(F("\t 'a': toggle sequencer"));
            // out.println(F("\t 'a': toggle SPIRAL"));
            // out.println(F("\t 'b': toggle SPIRAL2"));
            // out.println(F("\t 'B': toggle SPIRALSUN"));
            // out.println(F("\t 'c': toggle HPLINE"));
            // out.println(F("\t 'I': set sequencer interval 'i65535'"));
            // out.println(F("\t 'v': set effect value_low 'v65535'"));
            // out.println(F("\t 'V': set effect value_high 'V65535'"));
            out.println();
            out.println(F("\t 's': set channel 's1:65535'"));
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

            // out.println(F("nothing to do."));
            //
            // // uint16_t wTest = 65535;
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
            //
            // out.println();

            speedtest_TLC5971(out);

            out.println(F("__________"));
        } break;
        //---------------------------------------------------------------------
        // case 'A': {
        //     out.println(F("\t Hello World! :-)"));
        // } break;
        // case 'a': {
        //     out.println(F("\t toggle sequencer:"));
        //     if (sequencer_mode == sequencer_OFF) {
        //         sequencer_mode = sequencer_CHANNELCHECK;
        //         out.print(F("\t sequencer_mode: CHANNELCHECK\n"));
        //     }
        //     else {
        //         sequencer_mode = sequencer_OFF;
        //         out.print(F("\t sequencer_mode: OFF\n"));
        //     }
        // } break;
        // case 'A': {
        //     out.println(F("\t toggle SPIRAL:"));
        //     if (sequencer_mode == sequencer_OFF) {
        //         sequencer_mode = sequencer_SPIRAL;
        //         out.print(F("\t sequencer_mode: SPIRAL\n"));
        //     }
        //     else {
        //         sequencer_mode = sequencer_OFF;
        //         out.print(F("\t sequencer_mode: OFF\n"));
        //     }
        // } break;
        // case 'b': {
        //     out.println(F("\t toggle SPIRAL2:"));
        //     if (sequencer_mode == sequencer_OFF) {
        //         sequencer_mode = sequencer_SPIRAL2;
        //         out.print(F("\t sequencer_mode: SPIRAL2\n"));
        //         sequencer_interval = 100;
        //     }
        //     else {
        //         sequencer_mode = sequencer_OFF;
        //         out.print(F("\t sequencer_mode: OFF\n"));
        //     }
        // } break;
        // case 'B': {
        //     out.println(F("\t toggle SPIRALSUN:"));
        //     if (sequencer_mode == sequencer_OFF) {
        //         sequencer_mode = sequencer_SPIRALSUN;
        //         out.print(F("\t sequencer_mode: SPIRALSUN\n"));
        //         sequencer_interval = 100;
        //     }
        //     else {
        //         sequencer_mode = sequencer_OFF;
        //         out.print(F("\t sequencer_mode: OFF\n"));
        //     }
        // } break;
        // case 'c': {
        //     out.println(F("\t toggle HPLINE:"));
        //     if (sequencer_mode == sequencer_OFF) {
        //         sequencer_mode = sequencer_HPLINE;
        //         out.print(F("\t sequencer_mode: HPLINE\n"));
        //         sequencer_interval = 150;
        //     }
        //     else {
        //         sequencer_mode = sequencer_OFF;
        //         out.print(F("\t sequencer_mode: OFF\n"));
        //     }
        // } break;
        // case 'I': {
        //     out.print(F("\t set sequencer interval "));
        //     // convert part of string to int
        //     // (up to first char that is not a number)
        //     uint8_t command_offset = 1;
        //     uint16_t value = atoi(&command[command_offset]);
        //     out.print(value);
        //     out.println();
        //     sequencer_interval = value;
        // } break;
        // case 'v': {
        //     out.print(F("\t set effect value_low"));
        //     // convert part of string to int
        //     // (up to first char that is not a number)
        //     uint8_t command_offset = 1;
        //     uint16_t value = atoi(&command[command_offset]);
        //     out.print(value);
        //     out.println();
        //     value_low = value;
        // } break;
        // case 'V': {
        //     out.print(F("\t set effect value_high"));
        //     // convert part of string to int
        //     // (up to first char that is not a number)
        //     uint8_t command_offset = 1;
        //     uint16_t value = atoi(&command[command_offset]);
        //     out.print(value);
        //     out.println();
        //     value_high = value;
        // } break;
        // ------------------------------------------
        case 's': {
            out.print(F("\t set channel "));
            // convert part of string to int
            // (up to first char that is not a number)
            uint8_t command_offset = 1;
            uint8_t ch = atoi(&command[command_offset]);
            // convert single character to int representation
            // uint8_t id = &command[1] - '0';
            command_offset = 3;
            if (ch > 9) {
                command_offset = command_offset +1;
            }
            out.print(ch);
            out.print(F(" : "));
            uint16_t value = atoi(&command[command_offset]);
            out.print(value);
            out.println();

            if (output_enabled) {
                tlc.setChannel(ch, value);
                tlc.write();
            }
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
// LEDBoard


void setup_Boards(Print &out) {
    out.println(F("setup LEDBoards:"));

    out.println(F("\t init tlc lib"));
    tlc.beginFast();
    out.println(F("\t start with leds off"));
    tlc.setRGB();
    tlc.write();
    // out.println(F("\t set leds to 0, 0, 1"));
    // tlc.setRGB(0, 0, 1);
    // tlc.write();
    // delay(2000);

    out.println(F("\t set two blue lines"));

    set_line(BOARD0, 0, 0, 1);
    set_line(BOARD1, 0, 0, 1);

    out.println(F("\t switch infoled off"));
    debugOut_LiveSign_LED_Enabled = 0;
    digitalWrite(infoled_pin, LOW);

    out.println(F("\t finished."));
}

void set_line_old(uint16_t r, uint16_t g, uint16_t b) {
    // all black
    // tlc.setRGB(0, 0, 0);
    // define pattern
    // const uint8_t pattern_map[pixel_count] {
    //     4, 6, 12, 14, 20, 22, 28, 30
    // };
    const uint8_t pattern_map[row_count*2][column_count] {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    };
    // set pattern
    for (size_t row = 0; row < row_count*2; row++) {
        for (size_t column = 0; column < column_count; column++) {
            uint8_t pixel = channel_position_map[row][column];
            if (pattern_map[row][column] == 1) {
                tlc.setRGB(pixel, r, g, b);
            } else {
                tlc.setRGB(pixel, 0, 0, 0);
            }
        }
    }
    tlc.write();
}

void set_line(uint8_t board_index, uint16_t r, uint16_t g, uint16_t b) {
    // for board_index 0: 0,2,4,6
    // for board_index 1: 1,3,5,7
    for (
        size_t line_index = board_index;
        line_index < pixel_line_count;
        line_index = line_index + 2
    ) {
        tlc.setRGB(pixel_line_list[line_index], r, g, b);
    }
    tlc.write();
}

void set_line_pattern(
    uint8_t board_index,
    const tPattern *pattern,
    uint8_t pattern_column,
    uint16_t r,
    uint16_t g,
    uint16_t b
) {
    // set pattern
    // for board_index 0: 0,2,4,6
    // for board_index 1: 1,3,5,7
    for (
        size_t line_index = board_index;
        line_index < pixel_line_count;
        line_index = line_index + 2
    ) {
        // switch (pattern_map[line_index][pattern_column]) {
        //     case 1 : {
        //         tlc.setRGB(pixel_line_list[line_index], r, g, b);
        //     } break;
        //     default: {
        //         tlc.setRGB(pixel_line_list[line_index], 0, 0, 0);
        //     };
        // } //end switch
        if (pattern->data[line_index][pattern_column] == 1) {
            tlc.setRGB(pixel_line_list[line_index], r, g, b);
        } else {
            tlc.setRGB(pixel_line_list[line_index], 0, 0, 0);
        }
    }
    tlc.write();
}


void update_Boards() {
    if(
        analogRead(pos1_pin) > 210
    ) {
        board_timestamp_last =  millis();
        // set_line(0, 65535, 0);
        // set_line(0, 0, 10000);
        // set_line(0, 65535, 0);
        // set_line(0, 0, 10000);
        // set_line(0, 65535, 0);
        // set_line(0, 0, 10000);
        // set_line(0, 65535, 0);
        // set_line(65535, 65535, 0);
        for (
            size_t pattern_index = 0;
            pattern_index < pattern_memory[(uint8_t)pattern_name].count;
            pattern_index++
        ) {
            set_line_pattern(
                BOARD0,
                &pattern_memory[(uint8_t)pattern_name],
                pattern_index,
                30000, 0, 65535);
        }
        set_line(BOARD0,  0, 0, 0);
    }
    if(
        analogRead(pos2_pin) > 210
    ) {
        // board_timestamp_last =  millis();
        for (
            size_t pattern_index = 0;
            pattern_index < pattern_memory[(uint8_t)pattern_name].count;
            pattern_index++
        ) {
            set_line_pattern(
                BOARD1,
                &pattern_memory[(uint8_t)pattern_name],
                pattern_index,
                30000, 0, 65535);
        }
        set_line(BOARD1,  0, 0, 0);
    }
}

void map_to_allBoards() {
    if (output_enabled) {
        // set all channels (mapping)
        for (
            size_t channel_index = 0;
            channel_index < colorchannels_per_board;
            channel_index++
        ) {
            // uint8_t mapped_channel = mapping_single_board[i];
            // Serial.print("mapping: ");
            // Serial.print(i);
            // Serial.print("-->");
            // Serial.print(mapped_channel);
            // Serial.println();
            for (size_t board_index = 0; board_index < boards_count; board_index++) {
                tlc.setChannel(
                    channel_index + (tlc_channels_per_board * board_index),
                    tlc.getChannel(channel_index)
                );
            }
        }
    }
}

void speedtest_TLC5971(Print &out) {
    uint32_t loop_count = 1;
    uint32_t start = micros();
    uint32_t end = micros();
    uint32_t duration = end - start;

    out.println(F("Speedtest for set_Line"));
    loop_count = 10;
    start = micros();
        set_line(BOARD0, 0, 65535, 0);
        set_line(BOARD0, 0, 0, 0);
        set_line(BOARD0, 0, 65535, 0);
        set_line(BOARD0, 0, 0, 0);
        set_line(BOARD0, 0, 65535, 0);
        set_line(BOARD0, 0, 0, 0);
        set_line(BOARD0, 0, 65535, 0);
        set_line(BOARD0, 0, 0, 0);
        set_line(BOARD0, 0, 65535, 0);
        set_line(BOARD0, 0, 0, 0);
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us for "));
    out.print(loop_count);
    out.print(F("calls."));
    out.println();
    out.print(F("\t--> "));
    out.print(float(duration)/(loop_count));
    out.print(F("us per calls."));
    out.println();
    out.print(F("\t--> "));
    out.print((float(duration)/(loop_count))/1000);
    out.print(F("ms per calls."));
    out.println();


    out.println(F("Speedtest for set_Line(0,xxx,0)"));
    loop_count = 1;
    start = micros();
        set_line(BOARD0, 0, 65535, 0);
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us per call."));
    out.println();

    out.println(F("Speedtest for setRGB(0,0,0)"));
    loop_count = 1;
    start = micros();
        tlc.setRGB(0, 0, 0);
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us per call."));
    out.println();

    out.println(F("Speedtest for tlc.write"));
    loop_count = 1;
    start = micros();
        tlc.write();
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us per call."));
    out.println();

    out.println(F(" * * * * * "));
    out.println(F("Speedtest for set_line_pattern"));
    loop_count = 1;
    start = micros();
        set_line_pattern(
            BOARD0,
            &pattern_memory[(uint8_t)pattern_name],
            0,
            30000, 0, 65535);
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us per call."));
    out.println();

    out.println(F("Speedtest for full 1board pattern write"));
    loop_count = 1;
    start = micros();
        for (
            size_t pattern_index = 0;
            pattern_index < pattern_memory[(uint8_t)pattern_name].count;
            pattern_index++
        ) {
            set_line_pattern(
                BOARD0,
                &pattern_memory[(uint8_t)pattern_name],
                pattern_index,
                30000, 0, 65535);
        }
    end = micros();
    duration = end - start;
    out.println(F("\tresults: "));
    out.print(F("\t"));
    out.print(duration);
    out.print(F("us per call."));
    out.println();




    out.println(F("---- finished."));
    // reset to blue
    set_line(BOARD0, 0, 0, 65535);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mode

void update_Handler() {
    if (sequencer_mode != sequencer_OFF) {
        if(
            (millis() - sequencer_timestamp_last) > sequencer_interval
        ) {
            sequencer_timestamp_last =  millis();
            calculate_step();
        }
    }
    switch (/* expression */) {
        case /* value */:
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FaderLin

void setup_myFaderRGB(Print &out) {
    out.println(F("setup myFaderRGB:"));

    out.println(F("\t myFaderRGB.begin();"));
    myFaderRGB.begin();

    out.println(F("\t myFaderRGB welcome fade"));
    // myFaderRGB.startFadeTo( 1000, memList_A[memList_A__Full]);
    myFaderRGB_fadeTo(1000, 60000, 60000, 0);
    // run fading
    // while ( myFaderRGB.getLastEvent() == slight_FaderLin::event_fading_Finished) {
    //     myFaderRGB.update();
    // }
    while ( myFaderRGB.update() == slight_FaderLin::state_Fading) {
        // nothing to do.
    }
    myFaderRGB.update();

    // myFaderRGB.startFadeTo( 1000, memList_A[memList_A__Off]);
    myFaderRGB_fadeTo(1000, 1000, 500, 1);
    // run fading
    // while ( myFaderRGB.getLastEvent() != slight_FaderLin::event_fading_Finished) {
    //     myFaderRGB.update();
    // }
    while ( myFaderRGB.update() == slight_FaderLin::state_Fading) {
        // nothing to do.
    }
    myFaderRGB.update();

    // myFaderRGB.startFadeTo( 1000, memList_A[memList_A__Off]);
    myFaderRGB_fadeTo(1000, 0, 0, 1);
    // run fading
    // while ( myFaderRGB.getLastEvent() != slight_FaderLin::event_fading_Finished) {
    //     myFaderRGB.update();
    // }
    while ( myFaderRGB.update() == slight_FaderLin::state_Fading) {
        // nothing to do.
    }
    myFaderRGB.update();

    out.println(F("\t finished."));
}

void myFaderRGB_callback_OutputChanged(uint8_t id, uint16_t *values, uint8_t count) {

    // if (bDebugOut_myFaderRGB_Output_Enable) {
    //     Serial.print(F("OutputValue: "));
    //     printArray_uint16(Serial, wValues, bCount);
    //     Serial.println();
    // }

    // for (size_t channel_index = 0; channel_index < count; channel_index++) {
    //     tlc.setChannel(channel_index, values[channel_index]);
    // }

    if (output_enabled) {
        tlc.setRGB(values[0], values[1], values[2]);
        tlc.write();
    }

}

void myFaderRGB_fadeTo(uint16_t duration, uint16_t r, uint16_t g, uint16_t b) {
    uint16_t values[myFaderRGB__channel_count];
    // init array with 0
    values[0] = r;
    values[1] = g;
    values[2] = b;
    myFaderRGB.startFadeTo(duration, values);
}

void myCallback_onEvent(slight_FaderLin *pInstance, byte event) {


    // Serial.print(F("Instance ID:"));
    // Serial.println((*pInstance).getID());
    //
    // Serial.print(F("Event: "));
    // (*pInstance).printEvent(Serial, event);
    // Serial.println();


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
        } break;
    } //end switch

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button callbacks

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

    // uint8_t button_id = (*pInstance).getID();

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
            Serial.println(F("duration active: "));
            Serial.println(duration);
            if (duration <= 2000) {
                myFaderRGB_fadeTo(500, 10000, 0, 0);
            }
            else if (duration <= 3000) {
                myFaderRGB_fadeTo(500, 0, 10000, 0);
            }
            else if (duration <= 4000) {
                myFaderRGB_fadeTo(500, 0, 0, 10000);
            }
            else if (duration <= 6000) {
                myFaderRGB_fadeTo(500, 0, 65000, 65000);
            }
            else if (duration <= 7000) {
                myFaderRGB_fadeTo(500, 65000, 0, 65000);
            }
            else if (duration <= 8000) {
                myFaderRGB_fadeTo(500, 65535, 65535, 0);
            }
            else if (duration <= 9000) {
                myFaderRGB_fadeTo(1000, 65535, 65535, 65535);
            }
            else {
                myFaderRGB_fadeTo(1000, 65535, 65535, 65535);
            }

        } break;
        case slight_ButtonInput::event_Up : {
            Serial.println(F("up"));
            myFaderRGB_fadeTo(1000, 0, 0, 1);
        } break;
        case slight_ButtonInput::event_Click : {
            // Serial.println(F("FRL click"));
        } break;
        case slight_ButtonInput::event_ClickLong : {
            // Serial.println(F("click long"));
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
        //     switch ((*pInstance).getClickCount()) {
        //         case 4 : {
        //             //
        //         } break;
        //         case 5 : {
        //             //
        //         } break;
        //         case 6 : {
        //             //
        //         } break;
        //     }
        // } break;
    }  // end switch
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

        // pinMode(lowbat_warning_pin, OUTPUT);
        // digitalWrite(lowbat_warning_pin, HIGH);

        // as of arduino 1.0.1 you can use INPUT_PULLUP

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // initialise serial

        // for ATmega32U4 devices:
        #if defined (__AVR_ATmega32U4__)
            // wait for arduino IDE to release all serial ports after upload.
            delay(2000);
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
    // setup LEDBoard
        setup_Boards(out);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setup Fader

    out.print(F("# Free RAM = "));
    out.println(freeRam());

    // setup_myFaderRGB(out);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setup button

    out.print(F("# Free RAM = "));
    out.println(freeRam());

    out.println(F("setup button:")); {
        out.println(F("\t set button pin"));
        pinMode(button_pin, INPUT_PULLUP);
        out.println(F("\t button begin"));
        button.begin();
    }
    out.println(F("\t finished."));

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setup position sensors

    out.println(F("setup position sensor:")); {
        out.println(F("\t set pos1_pin"));
        pinMode(pos1_pin, INPUT);
        out.println(F("\t set pos2_pin"));
        pinMode(pos2_pin, INPUT);
    }
    out.println(F("\t finished."));

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

        myFaderRGB.update();
        button.update();

        // update_Boards();
        update_Handler();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // timed things

        // if (sequencer_mode != sequencer_OFF) {
        //     if(
        //         (millis() - sequencer_timestamp_last) > sequencer_interval
        //     ) {
        //         sequencer_timestamp_last =  millis();
        //         calculate_step();
        //     }
        // }



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
                // Serial.println();
                Serial.print(F("; pos1 voltage: "));
                // 1024 = 5V
                // analogRead = x
                // x = 5.0*analogRead/1024
                uint16_t raw1 = analogRead(pos1_pin);
                Serial.print(5.0 *  raw1 / 1024);
                Serial.print(F("V (="));
                Serial.print(raw1);
                Serial.print(F(")"));
                // Serial.println();
                Serial.print(F("; pos2 voltage: "));
                uint16_t raw2 = analogRead(pos2_pin);
                Serial.print(5.0 *  raw2 / 1024);
                Serial.print(F("V (="));
                Serial.print(raw2);
                Serial.print(F(")"));
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
