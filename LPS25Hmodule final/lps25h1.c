/**
 ******************************************************************************
 * @file    LPS25H.c
 * @author  AST Robotics Team
 * @version V0.0.1
 * @date    03-April-2014
 * @brief   This file provides a set of functions needed to manage the lps25h.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "lps25h.h"
 
/** @addtogroup BSP
 * @{
 */
 
/** @addtogroup STM32F439_SENSITRON
 * @{
 */
 
/** @addtogroup LPS25H
 * @{
 */
 
 
/** @defgroup LPS25H_Private_TypesDefinitions
 * @{
 */
 
/**
 * @}
 */
 
/** @defgroup LPS25H_Private_Defines
 * @{
 */
 
/**
 * @}
 */
 
/** @defgroup LPS25H_Private_Macros
 * @{
 */
 
/**
 * @}
 */
 
/** @defgroup LPS25H_Private_Variables
 * @{
 */
 
PRESSURE_DrvTypeDef LPS25HDrv =
{
 LPS25H_Init,
 LPS25H_PowerOff,
 LPS25H_ReadID,
 LPS25H_RebootCmd,
 0,//LPS25H_INT1InterruptConfig,
 0,//LPS25H_EnableIT,
 0,//LPS25H_DisableIT,
 0,
 0,
 LPS25H_GetPressure,
 LPS25H_GetTemperature,
 LPS25H_SlaveAddrRemap
};
 
uint8_t LPS25H_SlaveAddress = LPS25H_ADDRESS_LOW;
 
/**
 * @}
 */
 
/** @defgroup LPS25H_Private_FunctionPrototypes
 * @{
 */
 
/**
 * @brief  Exit the shutdown mode for LPS25H.
 * @param  None
 * @retval None
 */
void LPS25H_PowerOn(void);
 
void LPS25H_I2C_ReadRawPressure(uint32_t *raw_press);
 
void LPS25H_I2C_ReadRawTemperature(int16_t *raw_data);
 
 
/**
 * @}
 */
 
/** @defgroup LPS25H_Private_Functions
 * @{
 */
 
 
/**
 * @brief  Set LPS25H Initialization.
 * @param  InitStruct: it contains the configuration setting for the LPS25H.
 * @retval Error Code (PressureError_Enum)
 */
void LPS25H_Init(PRESSURE_InitTypeDef *LPS25H_Init)
{  
    uint8_t tmp1 = 0x00;
 
    /* Configure the low level interface ---------------------------------------*/
    PRESSURE_IO_Init();
 
    LPS25H_PowerOn();
 
    PRESSURE_IO_Read(&tmp1, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
 
    /* Output Data Rate selection */
    tmp1 &= ~(LPS25H_ODR_MASK);
    tmp1 |= LPS25H_Init->OutputDataRate;
 
    /* Interrupt circuit selection */
    tmp1 &= ~(LPS25H_DIFF_EN_MASK);
    tmp1 |= LPS25H_Init->DiffEnable;
 
    /* Block Data Update selection */
    tmp1 &= ~(LPS25H_BDU_MASK);
    tmp1 |= LPS25H_Init->BlockDataUpdate;
 
    /* Serial Interface Mode selection */
    tmp1 &= ~(LPS25H_SPI_SIM_MASK);
    tmp1 |= LPS25H_Init->SPIMode;
 
    PRESSURE_IO_Write(&tmp1, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
 
    PRESSURE_IO_Read(&tmp1, LPS25H_SlaveAddress, LPS25H_RES_CONF_ADDR, 1);
 
    /* Serial Interface Mode selection */
    tmp1 &= ~(LPS25H_P_RES_MASK);
    tmp1 |= LPS25H_Init->PressureResolution;
 
    /* Serial Interface Mode selection */
    tmp1 &= ~(LPS25H_T_RES_MASK);
    tmp1 |= LPS25H_Init->TemperatureResolution;
 
    PRESSURE_IO_Write(&tmp1, LPS25H_SlaveAddress, LPS25H_RES_CONF_ADDR, 1);
}
 
/**
 * @brief  Read ID address of LPS25H
 * @param  Device ID address
 * @retval ID name
 */
uint8_t LPS25H_ReadID(void)
{
    uint8_t tmp;
 
    /* Read WHO I AM register */
    PRESSURE_IO_Read(&tmp, LPS25H_SlaveAddress, LPS25H_WHO_AM_I_ADDR, 1);
 
    /* Return the ID */
    return (uint8_t)tmp;
}
 
/**
 * @brief  Reboot memory content of LPS25H
 * @param  None
 * @retval None
 */
void LPS25H_RebootCmd(void)
{
    uint8_t tmpreg;
 
    /* Read CTRL_REG5 register */
    PRESSURE_IO_Read(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG2_ADDR, 1);
 
    /* Enable or Disable the reboot memory */
    tmpreg |= LPS25H_RESET_MEMORY;
 
    /* Write value to MEMS CTRL_REG5 regsister */
    PRESSURE_IO_Write(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG2_ADDR, 1);
}
 
/**
 * @brief Set LPS25H Interrupt INT1 configuration
 * @param  LPS25H_InterruptConfig_TypeDef: pointer to a LPS25H_InterruptConfig_TypeDef
 *         structure that contains the configuration setting for the LPS25H Interrupt.
 * @retval None
 */
void LPS25H_INT1InterruptConfig(uint16_t Int1Config)
{
 
}
 
/**
 * @brief  Enable INT1
 * @retval None
 */
void LPS25H_EnableIT()
{  
 
}
 
/**
 * @brief  Disable  INT1
 * @retval None
 */
void LPS25H_DisableIT()
{  
 
}
 
 
/**
 * @brief Read LPS25H output register, and calculate the raw  pressure.
 * @param uint32_t: raw_press. Pressure raw value.
 * @retval LPS25H_ERROR or LPS25H_OK.
 */
void LPS25H_I2C_ReadRawPressure(uint32_t *raw_press)
{
    uint8_t buffer[3], i;
    uint32_t tempVal=0;
 
    /* Read the register content */
 
    PRESSURE_IO_Read(buffer, LPS25H_SlaveAddress, LPS25H_PRESS_POUT_XL_ADDR+0x80, 3);
//    LPS25H_I2C_Read(LPS25H_PRESS_POUT_XL_ADDR+0x80, 3, buffer);
 
    /* Build the raw data */
    for (i = 0 ; i < 3 ; i++)
        tempVal |= (((uint32_t) buffer[i]) << (8 * i));
 
    /* convert the 2's complement 24 bit to 2's complement 32 bit */
    if (tempVal & 0x00800000)
        tempVal |= 0xFF000000;
 
    /* return the built value */
    *raw_press = ((uint32_t) tempVal);
}
 
/**
 * @brief Read LPS25H output register, and calculate the pressure in mbar.
 * @param float *pressure. Pressure value in mbar.
 * @retval LPS25H_ERROR or LPS25H_OK.
 */
void LPS25H_GetPressure(float* pfData)
{
    uint32_t raw_press = 0;
 
    LPS25H_I2C_ReadRawPressure(&raw_press);
 
    /* return the built value */
    //tempInt = raw_press / 4096;
 
    *pfData = (float)raw_press /4096.0f;
}
 
/**
 * @brief Read LPS25H output register, and calculate the raw temperature.
 * @param int16_t *raw_data: temperature raw value.
 * @retval LPS25H_ERROR or LPS25H_OK.
 */
void LPS25H_I2C_ReadRawTemperature(int16_t *raw_data)
{
    uint8_t buffer[2];
    uint16_t tempVal=0;
 
    /* Read the register content */
    PRESSURE_IO_Read(buffer, LPS25H_SlaveAddress, LPS25H_TEMP_OUT_L_ADDR+0x80, 2);
//    LPS25H_I2C_Read(LPS25H_TEMP_OUT_L_ADDR+0x80, 2, buffer);
 
    /* Build the raw value */
    tempVal = (((uint16_t)buffer[1]) << 8)+(uint16_t)buffer[0];
 
    /* Return it */
    *raw_data = ((int16_t)tempVal);
}
 
/**
 * @brief Read LPS25H output register, and calculate the  temperature.
 * @param float *temperature : temperature  value..
 * @retval LPS25H_ERROR or LPS25H_OK.
 */
void LPS25H_GetTemperature(float* pfData)
{
    int16_t raw_data;
 
    LPS25H_I2C_ReadRawTemperature(&raw_data);
 
    //*data_out = (int16_t)((((float)raw_data/480.0) + 42.5)*100);
    *pfData = (int16_t)((((float)raw_data/480.0) + 42.5));
}
/**
 * @brief  Exit the shutdown mode for LPS25H.
 * @param  None
 * @retval LPS25H_ERROR or LPS25H_OK
 */
void LPS25H_PowerOn(void)
{
    uint8_t tmpreg;
 
    /* Read the register content */
//        LPS25H_I2C_Read(LPS25H_CTRL_REG1_ADDR,1,&tmpReg);
    PRESSURE_IO_Read(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
 
    /* Set the power down bit */
    tmpreg |= LPS25H_MODE_ACTIVE;
 
    /* Write register */
//    PRESSURE_IO_Write(LPS25H_CTRL_REG1_ADDR,1,&tmpReg);
    PRESSURE_IO_Write(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
 
}
 
 
/**
 * @brief  Enter the shutdown mode for LPS25H.
 * @param  None
 * @retval LPS25H_ERROR or LPS25H_OK
 */
void LPS25H_PowerOff(void)
{
    uint8_t tmpreg;
 
    /* Read the register content */
//    PRESSURE_IO_Read( LPS25H_CTRL_REG1_ADDR,1,&tmpReg);
    PRESSURE_IO_Read(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
 
    /* Reset the power down bit */
    tmpreg &= ~(LPS25H_MODE_ACTIVE);
 
    /* Write register */
//    PRESSURE_IO_Write( LPS25H_CTRL_REG1_ADDR,1,&tmpReg);
    PRESSURE_IO_Write(&tmpreg, LPS25H_SlaveAddress, LPS25H_CTRL_REG1_ADDR, 1);
}
 
 
/**
 * @brief  Set the slave address according to SA0 bit.
 * @param  SA0_Bit_Status: LPS25H_SA0_LOW or LPS25H_SA0_HIGH
 * @retval None
 */
void LPS25H_SlaveAddrRemap(uint8_t SA0_Bit_Status)
{
    LPS25H_SlaveAddress = (SA0_Bit_Status==LPS25H_SA0_LOW?LPS25H_ADDRESS_LOW:LPS25H_ADDRESS_HIGH);
}
 
/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */
 
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
