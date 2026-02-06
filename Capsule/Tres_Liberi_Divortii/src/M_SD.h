#pragma once
#include <stdint.h>


int SD_log(int64_t time, int32_t voc, uint16_t sraw, float temp, float pressure);
int SD_setup(const char* h1,
              const char* h2,
              const char* h3,
              const char* h4,
              const char* h5,
              const char* h6,
              const char* h7,
              const char* h8,
              const char* h9);
void printCSVFile(const char* filename);