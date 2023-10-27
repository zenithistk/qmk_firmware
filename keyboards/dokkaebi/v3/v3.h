#pragma once

#include "dokaebi.h"

#include "quantum.h"

extern void (*pointing_device_set_button)(uint8_t btn);
extern void (*pointing_device_clear_button)(uint8_t btn);

#define LAYOUT( \
     K01, K05, K09, K13, K17, K21,                        K41, K45, K49, K53, K57, K61, \
     K02, K06, K10, K14, K18, K22,     K25, K29, K37,     K42, K46, K50, K54, K58, K62, \
     K03, K07, K11, K15, K19, K23,     K31, K30, K33,     K43, K47, K51, K55, K59, K63, \
     K04, K08, K12, K16, K20, K24,     K32, K35, K34,     K44, K48, K52, K56, K60, K64, \
                         K28, K27, K26,     K36,     K38, K39, K40 \
    ) \
    { \
        { K01, K05, K09, K13, K17, K21, K25, K29}, \
        { K02, K06, K10, K14, K18, K22, K26, K30}, \
        { K03, K07, K11, K15, K19, K23, K27, K31}, \
        { K04, K08, K12, K16, K20, K24, K28, K32}, \
        { K61, K57, K53, K49, K45, K41, K37, K33}, \
        { K62, K58, K54, K50, K46, K42, K38, K34}, \
        { K63, K59, K55, K51, K47, K43, K39, K35}, \
        { K64, K60, K56, K52, K48, K44, K40, K36}  \
    }
