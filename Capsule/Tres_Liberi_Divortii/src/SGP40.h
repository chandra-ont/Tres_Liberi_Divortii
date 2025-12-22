#pragma once
#include <stdint.h>

void SGP_setup();
int32_t SGP_loop(float t);
uint16_t Get_raw(float t);