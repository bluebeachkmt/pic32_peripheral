/* 
 * File:   pmod_nav.h
 * Author: BLUE
 *
 * Created on April 8, 2020, 5:39 PM
 */

#ifndef PMOD_NAV_H
#define	PMOD_NAV_H

#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config/default/peripheral/coretimer/plib_coretimer.h"
#include "config/default/peripheral/spi/plib_spi1.h"
#include "config/default/peripheral/spi/plib_spi_common.h"
#include "config/default/peripheral/gpio/plib_gpio.h"

#ifdef	__cplusplus
extern "C" {
#endif

/* CS for SPI */
#define CS_AG_Idle()                (GPIO_RA2_Set())
#define CS_AG_Active()              (GPIO_RA2_Clear())
#define CS_M_Idle()                 (GPIO_RA3_Set())
#define CS_M_Active()               (GPIO_RA3_Clear())
#define CS_ALT_Idle()               (GPIO_RB4_Set())
#define CS_ALT_Active()             (GPIO_RB4_Clear())

/* Who am I */
#define WHO_AM_I            0x0F
    
/* Address of Gyro Control Register of PmodNAV for SPI */
#define CTRL_REG1_G         0x10
#define CTRL_REG2_G         0x11
#define CTRL_REG3_G         0x12
#define ORIENT_CFG_G        0x13
#define INT_GEN_SRC_G       0x14
    
/* Address of Temperature Register of PmodNAV for SPI */
#define OUT_TEMP_L          0x15
#define OUT_TEMP_H          0x16
    
/* Status Register 0 of PmodNAV for SPI */
#define STATUS_REG0         0x17
    
/* Address of Gyro Register of PmodNAV for SPI */    
#define OUT_X_L_G           0x18
#define OUT_X_H_G           0x19
#define OUT_Y_L_G           0x1A
#define OUT_Y_H_G           0x1B
#define OUT_Z_L_G           0x1C
#define OUT_Z_H_G           0x1D
    
/* Control Register of PmodNAV for SPI */
#define CTRL_REG4           0x1E
#define CTRL_REG5_XL        0x1F
#define CTRL_REG6_XL        0x20
#define CTRL_REG7_XL        0x21
#define CTRL_REG8           0x22
#define CTRL_REG9           0x23
#define CTRL_REG10          0x24

/* Int Register of PmodNAV for SPI */
#define INT_GEN_SRC_XL      0x26
    
/* Status Register of PmodNAV for SPI */
#define STATUS_REG          0x27
    
/* Address of Acceleration Register of PmodNAV for SPI */
#define OUT_X_L_XL          0x28
#define OUT_X_H_XL          0x29
#define OUT_Y_L_XL          0x2A
#define OUT_Y_H_XL          0x2B
#define OUT_Z_L_XL          0x2C
#define OUT_Z_H_XL          0x2D
    
/*  */
#define FIFO_CTRL           0x2E
#define FIFO_SRC            0x2F
#define INT_GEN_CFG_G       0x30
#define INT_GEN_THS_XH_G    0x31
#define INT_GEN_THS_XL_G    0x32
#define INT_GEN_THS_YH_G    0x33
#define INT_GEN_THS_YL_G    0x34
#define INT_GEN_THS_ZH_G    0x35
#define INT_GEN_THS_ZL_G    0x36
#define INT_GEN_DUR_G       0x37
    
#define OFFSET_X_REG_L_M    0x05
#define OFFSET_X_REG_H_M    0x06
#define OFFSET_Y_REG_L_M    0x07
#define OFFSET_Y_REG_H_M    0x08
#define OFFSET_Z_REG_L_M    0x09
#define OFFSET_Z_REG_H_M    0x0A

#define WHO_AM_I_M          0x0F

#define CTRL_REG1_M         0x20
#define CTRL_REG2_M         0x21
#define CTRL_REG3_M         0x22
#define CTRL_REG4_M         0x23
#define CTRL_REG5_M         0x24

#define STATUS_REG_M        0x27
#define OUT_X_L_M           0x28
#define OUT_X_H_M           0x29
#define OUT_Y_L_M           0x2A
#define OUT_Y_H_M           0x2B
#define OUT_Z_L_M           0x2C
#define OUT_Z_H_M           0x2D

#define INT_CFG_M           0x30
#define INT_SRC_M           0x31
#define INT_THS_L_M         0x32
#define INT_THS_H_M         0x33

//#define REF_P_XL			0B00001000
//#define REF_P_L				0B00001001
//#define REF_P_H				0B00001010
//#define WHO_AM_I			0B00001111
//#define RES_CONF			0B00010000
//
#define CTRL_REG1			0x20
#define CTRL_REG2			0x21
//#define CTRL_REG3			0B00100010
//#define CTRL_REG4			0B00100011
//#define INTERRUPT_CFG		0B00100100
//#define INT_SOURCE			0B00100101
//
//#define STATUS_REG			0B00100111
//#define PRESS_OUT_XL		0B00101000
//#define PRESS_OUT_L			0B00101001
//#define PRESS_OUT_H			0B00101010
//#define TEMP_OUT_L			0B00101011
//#define TEMP_OUT_H			0B00101100
//
//#define FIFO_CTRL			0B00101110
//#define FIFO_STATUS			0B00101111
//#define THS_P_L				0B00110000
//#define THS_P_H				0B00110001
//
//#define RPDS_L				0B00111001
//#define RPDS_H				0B00111010
    
#define MODE_INST_A		0
#define MODE_INST_AG	1
#define MODE_INST_MAG	2
#define MODE_INST_ALT	3

#ifdef	__cplusplus
}
#endif

typedef struct{
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
}NAVDATA;

void NavInit();
void NavInitAG(bool fInit, uint8_t bModeSel);
void NavInitMAG(bool fInit);
void NavInitALT(bool fInit);
void NavReadAccel(NAVDATA *Acl);

#endif	/* PMOD_NAV_H */

