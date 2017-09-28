/*
 * main.c
 *
 *  Created on: 2017 Feb 24 23:36:35
 *  Author: Brendan Jackman
 *
 *  Example of using XMC CCU4 in counter and capture modes.
 *
 *  One CCU4 timer slice is used to count transitions on a digital input pin.  Another slice is used to capture the freerunning timer 
 *  value when an digital input transition occurs.
 *
 *  A global variable switchInput is used to alter the digital I/O pins using the uc/Probe app.  The pins are updated in the main
 *  event loop.  Some interrupts are enabled to observe the counter and capture operation.
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

// some GUI globals for uc/Probe access

int32_t switchInput;
uint32_t counterValue;

void CounterMatchIRQHandler( void )
{
      XMC_DEBUG("Counter match detected\n");
}

void CounterEdgeIRQHandler( void )
{
	    XMC_DEBUG("Counter edge detected\n");
}

void CaptureIRQHandler( void )
{
	    XMC_DEBUG("Capture edge detected\n");
	
			// get the captured time for display purposes.
	
			CAPTURE_GetCapturedTime( &CAPTURE_0, &counterValue );
	  
}


/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
		
		// update the digital outputs with GUI switch value.  This will trigger the connected hardware counter and capture units.
		
		if ( switchInput == 1 )
		{
			DIGITAL_IO_SetOutputHigh( &DIGITAL_IO_0 );
			DIGITAL_IO_SetOutputHigh( &DIGITAL_IO_1 );
		}
		else 
		{
			DIGITAL_IO_SetOutputLow( &DIGITAL_IO_0 );
			DIGITAL_IO_SetOutputLow( &DIGITAL_IO_1 );
		}
  }
}
