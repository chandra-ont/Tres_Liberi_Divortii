#pragma once
#include <stdint.h>
#include <SPI.h>

extern SPIClass* spi_instance;

int SD_log(int64_t time,
    float tf,
    int32_t voc_index,
    uint16_t sraw,
    int temp,
    int pressure,
    int NO,
    int UV);
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