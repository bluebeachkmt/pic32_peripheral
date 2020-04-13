/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "pmod_nav.h"                   // Pmod Device function and preprosessor


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    /* Open UART1 */
    UART_SERIAL_SETUP uart_setup;
    uart_setup.baudRate = 9600;
    uart_setup.dataWidth = UART_DATA_8_BIT;
    uart_setup.parity = UART_PARITY_NONE;
    uart_setup.stopBits = UART_STOP_1_BIT;
    UART1_SerialSetup(&uart_setup, 0);
    
    /* Open SPI1 */
    SPI_TRANSFER_SETUP spi_tr_setup;
    spi_tr_setup.clockFrequency = 100000;
    spi_tr_setup.clockPhase = SPI_CLOCK_PHASE_TRAILING_EDGE;
    spi_tr_setup.clockPolarity = SPI_CLOCK_POLARITY_IDLE_HIGH;
    spi_tr_setup.dataBits = SPI_DATA_BITS_8;
    SPI1_TransferSetup(&spi_tr_setup, 0);
    
    CORETIMER_DelayMs(100);
    
    /* Initialize PmodNAV using SPI1 */
    NavInit();
    NAVDATA Acldata;
    Acldata.X = 0;
    Acldata.Y = 0;
    Acldata.Z = 0;

    /* Set UART send data */
//    char send_data[]="Hello World!";
    char send_data[10]={0};
    uint8_t i;
    
    while ( true )
    {
        CORETIMER_DelayMs(1);
        GPIO_RA0_Toggle();
        
        NavReadAccel(&Acldata);
        sprintf(send_data, "X:%d", Acldata.X);
//        sprintf(send_data, "X:%d", 10);
        UART1_Write(send_data, sizeof(send_data));
        for(i=0; i<10; i++){
            send_data[i]=0;
        }
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

