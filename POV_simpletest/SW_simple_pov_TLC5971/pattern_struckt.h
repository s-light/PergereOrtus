#ifndef POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_
#define POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_

#include <Arduino.h>

const uint8_t pixel_line_count = 8;
const uint8_t pixel_column_count = 80;

struct tPattern {
    const uint8_t count;
    const uint8_t data[pixel_line_count][pixel_column_count];

    uint8_t operator () (uint8_t pixel_line, uint8_t pixel_column) const {
        // return pgm_read_byte(
        //     &data[0] + (pixel_line * pixel_column_count) + pixel_column);
        // // bound check
        if (pixel_line < pixel_line_count && pixel_column < pixel_column_count) {
            return pgm_read_byte_far(
                uint32_t(&data[0]) +
                (pixel_line * pixel_column_count) +
                pixel_column);
        } else {
            return 0;
        }
    }
};


// // based on
// // http://www.cplusplus.com/articles/G8hv0pDG/
// class tPattern {
//  public:
//     // constructor
//     tPattern(unsigned wd, unsigned ht): nWd(wd), nHt(ht), pAr(0) {
//         if (wd > 0 && ht > 0) {
//             pAr = new uint8_t[wd * ht];
//         }
//     }
//
//     // destructor
//     ~tPattern() {
//         delete[] pAr;
//     }
//
//     // indexing (parenthesis operator)
//     //  two of them (for const correctness)
//     const uint8_t& operator () (unsigned x, unsigned y) const {
//         // return pAr[ y*nWd + x ];
//         return pgm_read_byte(pAr + (y * nWd) + x );
//     }
//
//     // get dims
//     unsigned GetWd() const {
//         return nWd;
//     }
//     unsigned GetHt() const {
//         return nHt;
//     }
//
//  private:
//     const unsigned nWd;
//     const unsigned nHt;
//     const uint8_t* pAr;
//
//     // to prevent unwanted copying:
//     // tPattern(const tPattern<uint8_t>&);
//     // tPattern& operator = (const tPattern<uint8_t>&);
// };


    #endif  // POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_
