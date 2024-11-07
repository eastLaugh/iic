#include "aht20.h"

#define AHT20_ADDRESS 0x70 // 本质是0x38 iic协议中规定7位的0x38要左移1位=0x70        （0x70+1表示iic从从机读取数据 but这点hall库会帮我们解决）

void AHT20_Init()
{
    uint8_t readBuffer;
    HAL_Delay(40);
    HAL_I2C_Master_Receive(&hi2c1, 0x38 << 1, &readBuffer, 1, HAL_MAX_DELAY);
    if ((readBuffer & 0x08))
    {
        uint8_t sendBuffer[3] = {0xBE, 0x08, 0x00};
        HAL_I2C_Master_Transmit(&hi2c1, 0x38 << 1, sendBuffer, 3, HAL_MAX_DELAY);
    }
}

void AHT20_Read(float *temperature, float *humidity)
{
    uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
    uint8_t readBuffer[6];
    HAL_I2C_Master_Transmit(&hi2c1, 0x38 << 1, sendBuffer, 3, HAL_MAX_DELAY);
    HAL_Delay(75);
    HAL_I2C_Master_Receive(&hi2c1, 0x38 << 1, readBuffer, 6, HAL_MAX_DELAY);

    if ((readBuffer[0] & 0x80) == 0)
    {
        uint32_t data = 0;
        data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
        *humidity = (float)data * 100.0f / (1 << 20);

        data = (((uint32_t)readBuffer[3] & 0x0f) << 16) + ((uint32_t)readBuffer[4] << 8) + (uint32_t)readBuffer[5];
        *temperature = (float)data * 200.0f / (1 << 20) - 50;
    }
}