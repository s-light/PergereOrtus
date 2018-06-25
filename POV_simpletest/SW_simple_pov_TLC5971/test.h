#ifndef POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_TEST_H_
#define POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_TEST_H_

#include <Arduino.h>



// constexpr uint16_t * Tlc59711::create_idx_lookup(const uint16_t numTlc) {
//   uint16_t result[numTlc*12];
//   for (size_t idx = 0; idx < (numTlc*12); idx++) {
//       result[idx] = (14 * (idx / 12) + idx % 12);
//   }
//   return result;
// }



// ----------------------------------------------------------------------------
// Is it possible to create and initialize an array of values using template metaprogramming?
// https://stackoverflow.com/a/2228298/574981
// https://stackoverflow.com/a/37447199/574981

template <uint16_t idx>
struct test_generator {
    test_generator<idx - 1> rest;
    static const uint16_t x = (14 * (idx / 12) + idx % 12);
    // static const uint16_t x = idx * idx;
    constexpr uint16_t operator[](uint16_t const &i) const {
        return (i == idx ?  x : rest[i]);
    }
    constexpr uint16_t size() const {
        return idx;
    }
};

template <>
struct test_generator<0> {
    static const uint16_t x = 0;
    constexpr uint16_t operator[](uint16_t const &i) const { return x; }
    constexpr uint16_t size() const { return 1; }
};


const test_generator<20> mytable;

// Just use the table so it's not optimized away
void testit() {
    for (int i = 0; i < 20; i ++) {
        Serial.print("mytable[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(mytable[i]);
        Serial.println();
    }
}




// ----------------------------------------------------------------------------
// Generating lookup table at compile time using features from C++14
// https://www.avrfreaks.net/comment/2292631#comment-2292631
//
// #include <stdint.h>
// #include <avr/io.h>
// #include <avr/pgmspace.h>
//
// #define _USE_MATH_DEFINES
// #include <math.h>
//
// // We need to return an array, which is not possible in C/C++
// // So we return a structure that contains the array.
// struct array {
//     uint8_t _[256];
//
//     // this allows reading from flash memory using array notation
//     uint8_t operator[] (int index) const {
//         return pgm_read_byte(&_[0] + index);
//     }
// };
//
// // This function returns an array structure filled with a calculated period of a sine wave (8 bit resolution).
// // Since it is defined as constexpr, the compiler knows that the result of the function can be determined at compile time.
// // No actual AVR code is generated, just data.
// constexpr array table_generator() {
//     array tmp;
//     // array tmp {};
//     for (int i = 0; i < 256; i++) {
//         tmp._[i] = (14 * (i / 12) + i % 12);
//     }
//     return tmp;
// }
//
//
// // Fill flash memory with the sine wave table
// const PROGMEM array mytable = table_generator();
//
// // Just use the table so it's not optimized away
// void testit() {
//     for (int i = 0; i < 256; i ++) {
//         Serial.print("mytable[");
//         Serial.print(i);
//         Serial.print("]: ");
//         Serial.print(mytable[i]);
//         Serial.println();
//     }
// }



// ----------------------------------------------------------------------------
// #include <array>
// #include <functional>
// #include <algorithm>
// #include <iterator>
// #include <iostream>


// // We need to return an array, which is not possible in C/C++
// // So we return a structure that contains the array.
// template <int count>
// struct array {
//   int _[count];
//
//   // // this allows reading from flash memory using array notation
//   // uint8_t operator[] (int index) const {
//   //   return pgm_read_byte(&_[0] + index);
//   // }
// };

// void testit() {
//     const size_t count = 16;
//     const auto arr = make<count>();
//
//     for (size_t i = 0; i < count; i++) {
//         Serial.print("arr[");
//         Serial.print(i);
//         Serial.print("]: ");
//         Serial.print(arr[i]);
//         Serial.println();
//     }
// }



// ----------------------------------------------------------------------------
// https://stackoverflow.com/a/2981617/574981
// is working as far as the test1 goes.
//
// template<unsigned... args> struct ArrayHolder {
//     static const unsigned data[sizeof...(args)];
// };
//
// template<unsigned... args>
// const unsigned ArrayHolder<args...>::data[sizeof...(args)] = { args... };
//
// template<size_t N, template<size_t> class F, unsigned... args>
// struct generate_array_impl {
//     typedef typename generate_array_impl<N-1, F, F<N>::value, args...>::result result;
// };
//
// template<template<size_t> class F, unsigned... args>
// struct generate_array_impl<0, F, args...> {
//     typedef ArrayHolder<F<0>::value, args...> result;
// };
//
// template<size_t N, template<size_t> class F>
// struct generate_array {
//     typedef typename generate_array_impl<N-1, F>::result result;
// };
//
//
// // usage
// template<size_t index> struct MetaFunc {
//     enum { value = (14 * (index / 12) + index % 12) };
// };
//
// void testit() {
//     const size_t count = 16;
//     typedef generate_array<count, MetaFunc>::result A;
//     for (size_t i = 0; i < count; i++) {
//         Serial.print("A::data[");
//         Serial.print(i);
//         Serial.print("]: ");
//         Serial.print(A::data[i]);
//         Serial.println();
//     }
// }





#endif  // POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_TEST_H_
