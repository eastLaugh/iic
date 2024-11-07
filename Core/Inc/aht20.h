#ifndef AHT20_H
#define AHT20_H

#include "i2c.h"
void AHT20_Init();
void AHT20_Read(float *Temperature, float *humidity);
#endif