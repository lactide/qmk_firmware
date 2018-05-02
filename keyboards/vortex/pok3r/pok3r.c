#include "vortex.h"
#include "proto.h"
#include "quantum.h"
#include "raw_hid.h"
#include "debug.h"

#define SP 0x80
#define ER 0x40
#define LK(k,s) ((k & 0xFF) | ((s & 0xFF) << 8))

const uint16_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_60_ansi(
        LK(1,4),  LK(2,4),  LK(3,4),  LK(4,4),  LK(5,4),  LK(6,4),  LK(7,4),  LK(8,4),  LK(9,4),  LK(10,4), LK(11,4), LK(12,4), LK(13,4), LK(14,(8|ER)),
        LK(15,6), LK(16,4), LK(17,4), LK(18,4), LK(19,4), LK(20,4), LK(21,4), LK(22,4), LK(23,4), LK(24,4), LK(25,4), LK(26,4), LK(27,4), LK(28,(6|ER)),
        LK(29,7), LK(30,4), LK(31,4), LK(32,4), LK(33,4), LK(34,4), LK(35,4), LK(36,4), LK(37,4), LK(38,4), LK(39,4), LK(40,4), LK(41,(9|ER)),
        LK(42,9), LK(43,4), LK(44,4), LK(45,4), LK(46,4), LK(47,4), LK(48,4), LK(49,4), LK(50,4), LK(51,4), LK(52,4), LK(53,(11|ER)),
        LK(54,5), LK(55,5), LK(56,5), LK(57,25),LK(58,5), LK(59,5), LK(60,5), LK(61,5)
    ),
    LAYOUT_60_ansi_split_lshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
        55, 56, 57, 58, 59, 60, 61, 62
    ),
    LAYOUT_60_ansi_split_rshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
        55, 56, 57, 58, 59, 60, 61, 62
    ),
    LAYOUT_60_ansi_split_lshift_rshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 62, 63
    ),
};

const char *layout_names[NUM_LAYOUTS] = {
    "ansi60",
    "ansi60_spls",      // split left shift
    "ansi60_sprs",      // split right shift
    "ansi60_splsrs",    // split left and right shift
};
