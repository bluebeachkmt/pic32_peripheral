/*******************************************************************************
  PMOD NAV 

  Company:
    Microchip Technology Inc.

  File Name:
    pmod_nav.c

  Summary:
    PMOD_NAV Source File

  Description:
    This file has driver for PmodNAV 9axis sensor

*******************************************************************************/

#include "pmod_nav.h"

/* ------------------------------------------------------------ */
/*    Nav::Init()
**
**   Parameters:
**		none				
**   Return Values:
**      void 
**
**   Errors:
**		none
**
**   Description:
**		This function initializes all the instruments by calling the specific init functions for each of them 
**		default operating mode for Accel and Gyro is Accl+Gyro						
**
*/
void NavInit()
{
//enable only acl work mode or gyro and acl work mode;
	NavInitAG(1, MODE_INST_AG);
	//init mag instrument
	NavInitMAG(1);
	//init alt instrument 
	NavInitALT(1);
}

/* ------------------------------------------------------------ */
/*	InitAG(bool fInit, uint8_t bModeSel)
**
**	Parameters:
**		fInit			- enables the instrument for initialization or disables it
**		bModeSel		- work mode for the two instruments, Accel and Gyro: Accel only or Gyro+Accel
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initializes the accelerometer only or both the accel and gyro instruments with the following settings:
**		 for Accel only: Enable all three axes in CTRL_REG5_XL register, set 10 Hz ODR in CTRL_REG6_XL register
**		 for Gyro and Accel: set 10Hz ODR in CTRL_REG1_G register and CTRL_REG6_XL, thus enabling the Gyro functionality as well;
**		 enable the output of all three axes
** 		 
**		
*/
void NavInitAG(bool fInit, uint8_t bModeSel)
{
    uint8_t send_data[2];
    if (fInit)
    {
        if (bModeSel == MODE_INST_A)
        {
            //enable all three axes
            send_data[0]=CTRL_REG5_XL;
            send_data[1]=0x38;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
            //set 10Hz odr for accelerometer
            send_data[0]=CTRL_REG6_XL;
            send_data[1]=0x20;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
        }
        else if(bModeSel==MODE_INST_AG)
        {
            //enable all three axes
            send_data[0]=CTRL_REG5_XL;
            send_data[1]=0x38;
            CS_AG_Active();
			SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
			//set 10Hz output data rate for acceleration when used together with gyro
            send_data[0]=CTRL_REG6_XL;
            send_data[1]=0x20;
            CS_AG_Active();
			SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
			//set 10Hz rate for Gyro
            send_data[0]=CTRL_REG1_G;
            send_data[1]=0x20;
            CS_AG_Active();
			SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
			//enable the axes outputs for Gyro
            send_data[0]=CTRL_REG4;
            send_data[1]=0x38;
            CS_AG_Active();
			SPI1_Write(send_data, 2);
            CS_AG_Idle();
        }
    }
    else
    {
        if (bModeSel == MODE_INST_A)
        {
            //power down acceleration
            send_data[0]=CTRL_REG5_XL;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
            send_data[0]=CTRL_REG6_XL;
            send_data[1]=0x00;
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
        }
        else if(bModeSel==MODE_INST_AG)
        {
            //power down both the accel and gyro instruments
            send_data[0]=CTRL_REG5_XL;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
            send_data[0]=CTRL_REG6_XL;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
            send_data[0]=CTRL_REG9;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();

            send_data[0]=CTRL_REG4;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
            
            send_data[0]=CTRL_REG1_G;
            send_data[1]=0x00;
            CS_AG_Active();
            SPI1_Write(send_data, 2);
            CS_AG_Idle();
        }
    }
}


/* ------------------------------------------------------------ */
/*	Nav::InitMAG(bool fInit)
**
**	Parameters:
**		fInit			- enables the instrument for initialization or disables it
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initializes the magnetometer instrument with the following settings:
**		set medium performance mode and 10H ODR for MAG, in register CTRL_REG1_M
**		disable I2C and enable SPI read and write operations, set the operating mode to continuous in CTRL_REG3_M register
** 		 
**		
*/
void NavInitMAG(bool fInit)
{
    uint8_t send_data[2];
	if (fInit)
	{
		//set medium performance mode for x and y and 10Hz ODR for MAG, 
        send_data[0]=CTRL_REG1_M;
        send_data[1]=0x30;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
		//set scale to +-4Gauss
        send_data[0]=CTRL_REG2_M;
        send_data[1]=0x00;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
		//disable I2C and enable SPI read and write operations, 
		//set the operating mode to continuous conversion
        send_data[0]=CTRL_REG3_M;
        send_data[1]=0x00;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
		//set medium performance mode for z axis
        send_data[0]=CTRL_REG4_M;
        send_data[1]=0x04;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
		//cntinuous update of output registers
        send_data[0]=CTRL_REG5_M;
        send_data[1]=0x00;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
	}
	else 
	{
		//power down the instrument
        send_data[0]=CTRL_REG3_M;
        send_data[1]=0x03;
        CS_M_Active();
        SPI1_Write(send_data, 2);
        CS_M_Idle();
	}
}

/* ------------------------------------------------------------ */
/*	NavInitALT(bool fInit)
**
**	Parameters:
**		fInit			- enables the instrument for initialization or disables it
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initializes the barometer/altimeter instrument with the following settings:
**		set active mode and 7Hz ODR rate, in register CTRL_REG1, block data update active
** 		 
**		
*/
void NavInitALT(bool fInit)
{
	uint8_t send_data[2];
	if (fInit)
	{
		//clean start
        send_data[0]=CTRL_REG1;
        send_data[1]=0x00;
        CS_ALT_Active();
        SPI1_Write(send_data, 2);
        CS_ALT_Idle();
		CORETIMER_DelayMs(1);
		//set active the device and ODR to 7Hz
        send_data[0]=CTRL_REG1;
        send_data[1]=0xA4;
        CS_ALT_Active();
        SPI1_Write(send_data, 2);
        CS_ALT_Idle();
		//increment address during multiple byte access disabled
        send_data[0]=CTRL_REG2;
        send_data[1]=0x00;
        CS_ALT_Active();
        SPI1_Write(send_data, 2);
        CS_ALT_Idle();
		//no modification to interrupt sources
        send_data[0]=CTRL_REG4;
        send_data[1]=0x00;
        CS_ALT_Active();
        SPI1_Write(send_data, 2);
        CS_ALT_Idle();
	}
	else 
	{
		//power down the instrument
        send_data[0]=CTRL_REG1;
        send_data[1]=0x00;
        CS_ALT_Active();
        SPI1_Write(send_data, 2);
        CS_ALT_Idle();
	}
}


/*   Nav::ReadAccel(int16_t &AclX, int16_t &AclY, int16_t &AclZ)
**
**  Parameters:
**		&AclX	- the output parameter that will receive acceleration on X axis - 16 bits value
**		&AclY	- the output parameter that will receive acceleration on Y axis - 16 bits value
**		&AclZ	- the output parameter that will receive acceleration on Z axis - 16 bits value
**
**  Return Values:
**      none 
**
**  Errors:
**		none	
**  Description:
**		This function provides the 3 "raw" 16-bit values read from the accelerometer. 
**			-	It reads simultaneously the acceleration on three axes in a buffer of 6 bytes using the ReadRegister function
**			-	For each of the three axes, it combines the two bytes in order to get a 16-bit value
*/
void NavReadAccel(NAVDATA *Acl)
{
	uint8_t send_data;
    uint8_t iAclX_L, iAclX_H, iAclY_L, iAclY_H, iAclZ_L, iAclZ_H;
	uint8_t rgwRegVals[6];
    
	//reads the bytes using the incremeting address functionality of the device.
    send_data = OUT_X_L_XL;
    CS_AG_Active();
    SPI1_WriteRead(&send_data, 1, rgwRegVals, 6);
    CS_AG_Idle();
    
	iAclX_L = rgwRegVals[0];
	iAclX_H = rgwRegVals[1];
	iAclY_L = rgwRegVals[2];
	iAclY_H = rgwRegVals[3];
	iAclZ_L = rgwRegVals[4];
	iAclZ_H = rgwRegVals[5];
	//combines the read values for each axis to obtain the 16-bit values
	Acl->X = ((int16_t)iAclX_H << 8) | iAclX_L;
	Acl->Y = ((int16_t)iAclY_H << 8) | iAclY_L;
	Acl->Z = ((int16_t)iAclZ_H << 8) | iAclZ_L;
}