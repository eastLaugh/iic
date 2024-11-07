#ifndef AHT20_H
#define AHT20_H

#include "i2c.h"
// void AHT20_Init();
// void AHT20_Read(float *Temperature, float *humidity);

//声明
void AHT20_Measure();
void AHT20_Get();
void AHT20_Analysis(float *temperature, float *humidity);

#endif