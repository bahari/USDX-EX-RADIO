#include <Wire.h>
#include <EEPROM.h>

volatile byte buffer[40];
volatile int rxHowMany;
volatile int rxInterrupts = 0;
volatile boolean flagRequest;

#define DEBUG_SERIAL

// Serial LPF pin definition
#define SLPFEIGHTY     12	// 80m serial LPF selection
#define SLPFSIXTY      11  	// 60m serial LPF selection
#define SLPFFORTY      10  	// 40m serial LPF selection
#define SLPFTHIRTY     9   	// 30m serial LPF selection
#define SLPFTWENTY     8   	// 20m serial LPF selection
#define SLPFSEVENTEEN  7   	// 17m serial LPF selection

// RF PA pin definition
#define RFPAOUT        6	// RF PA output to the final LPF 
#define RFPAIN	       5	// RF PA input

// Final LPF selection
#define LPFEIGHTY	   A0	// 80m final LPF selection
#define LPFFORTY	   A1   // 40m final LPF selection 
#define LPFSEVENT	   A2   // 40m final LPF selection       
#define LPFTEN   	   A3   // 40m final LPF selection

int lpfSel = 0;
int rfPATx = 0;
int prevLpfSel = 0;

/****************************************************************
 *Function Name: receiveEvent
 *Description:   Interrupt handler to receive I2C data 
 *Return:        NO
 *
 ***************************************************************/
void receiveEvent(int howMany)
{
	for( int i=0; i<howMany; i++)
		buffer[i] = Wire.read();
  
	rxHowMany = howMany;
	rxInterrupts++;
}

/****************************************************************
 *Function Name: requestEvent
 *Description:   Interrupt handler for data request by I2C
 *Return:        NO
 *
 ***************************************************************/
void requestEvent()
{
	flagRequest = true;
}

/****************************************************************
 *Function Name: read_Lpf_Eeprom
 *Description:   Read last LPF setting from EEPROM memory 
 *Return:        NO
 *
 ***************************************************************/
void read_Lpf_Eeprom()
{
	int lpfVal = 0;
	int lpfExist = 0;
	
	lpfVal = EEPROM.read(1);
	// Fresh controller start, put a default at 40m band
	if (lpfVal == 0)
	{
		// Default 40m band
		EEPROM.write(0, 2);
		delay(100);
		EEPROM.write(1, 1);
		delay(100);
		
		// OFF other selection - Serial LPF
		digitalWrite(SLPFEIGHTY, LOW);
		digitalWrite(SLPFSIXTY, LOW);
		digitalWrite(SLPFTHIRTY, LOW);
		digitalWrite(SLPFTWENTY, LOW);
		digitalWrite(SLPFSEVENTEEN, LOW);
		
		// OFF other selection - Final LPF
		digitalWrite(LPFEIGHTY, LOW);
		digitalWrite(LPFSEVENT, LOW);
	
		// Serial LPF
		digitalWrite(SLPFFORTY, HIGH);
		// Final LPF
		digitalWrite(LPFFORTY, HIGH);
	}
	else 
	{
		// Read last serial LPF selection from EEPROM 
		lpfVal = EEPROM.read(0);
		
		// Selection of the LPF
		// 80 meters -> 3.5000MHz - 3.800MHz
		// 60 meters -> 5.000MHz -
		// 40 meters -> 7.000  - 7.200MHz
		// 30 metres -> 10.100 - 10.150MHz
		// 20 metres -> 14.000 - 14.350MHz
		// 17 metres -> 18.068 - 18.168MHz
		switch(lpfVal)
		{
			// 80m serial LPF, final LPF - 80m
			case 0:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFSIXTY, LOW);
				digitalWrite(SLPFFORTY, LOW);
				digitalWrite(SLPFTHIRTY, LOW);
				digitalWrite(SLPFTWENTY, LOW);
				digitalWrite(SLPFSEVENTEEN, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFFORTY, LOW);
				digitalWrite(LPFSEVENT, LOW);
								
				// Serial LPF
				digitalWrite(SLPFEIGHTY, HIGH);
				// Final LPF
				digitalWrite(LPFEIGHTY, HIGH);
			break;
			// 60m serial LPF, final LPF - 40m
			case 1:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFEIGHTY, LOW);
				digitalWrite(SLPFFORTY, LOW);
				digitalWrite(SLPFTHIRTY, LOW);
				digitalWrite(SLPFTWENTY, LOW);
				digitalWrite(SLPFSEVENTEEN, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFEIGHTY, LOW);
				digitalWrite(LPFSEVENT, LOW);
			
				// Serial LPF
				digitalWrite(SLPFSIXTY, HIGH);
				// Final LPF
				digitalWrite(LPFFORTY, HIGH);
			break;
			// 40m serial LPF, final LPF - 40m
			case 2:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFEIGHTY, LOW);
				digitalWrite(SLPFSIXTY, LOW);
				digitalWrite(SLPFTHIRTY, LOW);
				digitalWrite(SLPFTWENTY, LOW);
				digitalWrite(SLPFSEVENTEEN, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFEIGHTY, LOW);
				digitalWrite(LPFSEVENT, LOW);
			
				// Serial LPF
				digitalWrite(SLPFFORTY, HIGH);
				// Final LPF
				digitalWrite(LPFFORTY, HIGH);
			break;
			// 30m serial LPF, final LPF - 20m -> 17m
			case 3:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFEIGHTY, LOW);
				digitalWrite(SLPFSIXTY, LOW);
				digitalWrite(SLPFFORTY, LOW);
				digitalWrite(SLPFTWENTY, LOW);
				digitalWrite(SLPFSEVENTEEN, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFEIGHTY, LOW);
				digitalWrite(LPFFORTY, LOW);
				
				// Serial LPF
				digitalWrite(SLPFTHIRTY, HIGH);
				// Final LPF
				digitalWrite(LPFSEVENT, HIGH);
			break;
			// 20m serial LPF, final LPF - 20m -> 17m
			case 4:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFEIGHTY, LOW);
				digitalWrite(SLPFSIXTY, LOW);
				digitalWrite(SLPFFORTY, LOW);
				digitalWrite(SLPFTHIRTY, LOW);
				digitalWrite(SLPFSEVENTEEN, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFEIGHTY, LOW);
				digitalWrite(LPFFORTY, LOW);
				
				// Serial LPF
				digitalWrite(SLPFTWENTY, HIGH);
				// Final LPF
				digitalWrite(LPFSEVENT, HIGH);
			break;
			// 17m serial LPF, final LPF - 20m -> 17m
			case 5:
				// OFF other selection - Serial LPF
				digitalWrite(SLPFEIGHTY, LOW);
				digitalWrite(SLPFSIXTY, LOW);
				digitalWrite(SLPFFORTY, LOW);
				digitalWrite(SLPFTHIRTY, LOW);
				digitalWrite(SLPFTWENTY, LOW);
				
				// OFF other selection - Final LPF
				digitalWrite(LPFEIGHTY, LOW);
				digitalWrite(LPFFORTY, LOW);
				
				// Serial LPF
				digitalWrite(SLPFSEVENTEEN, HIGH);
				// Final LPF
				digitalWrite(LPFSEVENT, HIGH);
			break;
		}
	}
}

/****************************************************************
 *Function Name: setup
 *Description:   Setup and initialize all necessary parameter
 *Return:        NO
 *
 ***************************************************************/
void setup()
{
#ifdef DEBUG_SERIAL
	Serial.begin(9600);           // start serial for output
	Serial.println("\nSlave");
#endif

	Wire.begin(0x08);                // join i2c bus as slave with address #4
	Wire.onReceive(receiveEvent); // interrupt handler for receiving i2c data
	Wire.onRequest(requestEvent); // interrupt handler for when data is requested by i2c
	
	// Output pin initialization - Serial LPF selection 
	pinMode(SLPFEIGHTY, OUTPUT);
	pinMode(SLPFSIXTY, OUTPUT);
	pinMode(SLPFFORTY, OUTPUT);
	pinMode(SLPFTHIRTY, OUTPUT);
	pinMode(SLPFTWENTY, OUTPUT);
	pinMode(SLPFSEVENTEEN, OUTPUT);
	
	// Output pin initialization - RF PA 
	pinMode(RFPAOUT, OUTPUT);
	pinMode(RFPAIN, OUTPUT);
	
	// Output pin initialization - Final LPF selection 
	pinMode(LPFEIGHTY, OUTPUT);
	pinMode(LPFFORTY, OUTPUT);
	pinMode(LPFSEVENT, OUTPUT);
	pinMode(LPFTEN, OUTPUT);
	
	// Define default state - Serial LPF selection 
	digitalWrite(SLPFEIGHTY, LOW);
	digitalWrite(SLPFSIXTY, LOW);
	digitalWrite(SLPFFORTY, LOW);
	digitalWrite(SLPFTHIRTY, LOW);
	digitalWrite(SLPFTWENTY, LOW);
	digitalWrite(SLPFSEVENTEEN, LOW);
	
	// Define default state - RF PA
	digitalWrite(RFPAOUT, LOW);
	digitalWrite(RFPAIN, LOW);
	
	// Define default state - Final LPF selection
	digitalWrite(LPFEIGHTY, LOW);
	digitalWrite(LPFFORTY, LOW);
	digitalWrite(LPFSEVENT, LOW);
	digitalWrite(LPFTEN, LOW);
	
	// Read last serial LPF selection from EEPROM and switch it 
	read_Lpf_Eeprom();
	//EEPROM.write(0, 0);
	//delay(100);
	//EEPROM.write(1, 0);
	//delay(100);
}

/****************************************************************
 *Function Name: loop
 *Description:   Program entry point
 *Return:        NO
 *
 ***************************************************************/
void loop()
{
	noInterrupts();
	int rxInterruptsCopy = rxInterrupts;
	rxInterrupts = 0;
	interrupts();
  
	// Using all the text output to the Serial port is part of the stress test.
	// That causes delays and interrupts.
	if( rxInterruptsCopy > 0)
	{
#ifdef DEBUG_SERIAL
		Serial.print("Receive: ");
#endif
		// I2C data missed, for the time being just display for debugging
		if( rxInterruptsCopy > 1)
		{
			// Printing to the serial port at 9600 is slow.
			// Therefor it is normal that this sketch misses received data,
			// if too much data was received.
			// As long as the i2c data is correct, everything is okay. It is a stress test.
			// Display the missed data
#ifdef DEBUG_SERIAL
			Serial.print("Missed:");
			Serial.print( rxInterruptsCopy);
			Serial.print(" ");
#endif
		}
#ifdef DEBUG_SERIAL
		Serial.print("howMany:");
		Serial.print( rxHowMany);
    
		Serial.print(", data:");
#endif
		for(int i=0; i<rxHowMany; i++)
		{
			if( i == 0)
#ifdef DEBUG_SERIAL
				Serial.print(F("*"));      // indicate the first number (sometimes used for a counter value).
#endif
#ifdef DEBUG_SERIAL
			Serial.print((unsigned int) buffer[i], DEC);
			lpfSel = buffer[i];
			Serial.print(" ");
#endif
		}
#ifdef DEBUG_SERIAL
		Serial.println();// Receive: howMany:1, data:*1
#endif
		// Process the LPF selection and 
		if (rxHowMany == 1)
		{
			// PTT ON function - link to activate RFPA IN and RFPA OUT relay 
			// Sequence of operation:
			// 01 - Activate first RF PA output relay to ensure the antenna ae connected first to the RF PA
			// 02 - Delay for about 25ms
			// 03 - Activate RF PA input relay 
			if (lpfSel == 6)
			{
				digitalWrite(RFPAOUT, HIGH);
				delay (25);
				digitalWrite(RFPAIN, HIGH);
			}
			// PTT OF function - link to activate RFPA IN and RFPA OUT relay 
			// Sequence of operation:
			// 01 - Deactivate RF PA input relay.
			// 02 - Delay for about 25ms
			// 03 - Finally deactivate RF PA output relay 
			else if (lpfSel == 7)
			{
				digitalWrite(RFPAIN, LOW);
				delay (25);
				digitalWrite(RFPAOUT, LOW);
			}
			// LPF selection process 
			else
			{
				// Write current serial LPF state to EEPROM - Page 0
				EEPROM.write(0, lpfSel);
				delay(100);
				
				// Selection logic from usdx radio board 
				//uint8_t lpf_io = (f > 17) ? 0x05 : (f > 12) ? 0x04 : (f > 8) ? 0x03 : (f > 6) ? 0x02 : (f > 4) ? 0x01 : /*(f <= 4)*/ 0x00; // cut-off freq in MHz to IO port of LPF relay
				
				// Selection of the LPF
				// 80 meters -> 3.5000MHz - 3.800MHz
				// 60 meters -> 5.000MHz - 6.000MHz
				// 40 meters -> 7.000  - 7.200MHz
				// 30 metres -> 10.100 - 10.150MHz
				// 20 metres -> 14.000 - 14.350MHz
				// 17 metres -> 18.068 - 18.168MHz
				switch(lpfSel)
				{
					// 80m serial LPF, final LPF - 80m
					case 0:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFSIXTY, LOW);
						digitalWrite(SLPFFORTY, LOW);
						digitalWrite(SLPFTHIRTY, LOW);
						digitalWrite(SLPFTWENTY, LOW);
						digitalWrite(SLPFSEVENTEEN, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFFORTY, LOW);
						digitalWrite(LPFSEVENT, LOW);
										
						// Serial LPF
						digitalWrite(SLPFEIGHTY, HIGH);
						// Final LPF
						digitalWrite(LPFEIGHTY, HIGH);
					break;
					// 60m serial LPF, final LPF - 40m
					case 1:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFEIGHTY, LOW);
						digitalWrite(SLPFFORTY, LOW);
						digitalWrite(SLPFTHIRTY, LOW);
						digitalWrite(SLPFTWENTY, LOW);
						digitalWrite(SLPFSEVENTEEN, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFEIGHTY, LOW);
						digitalWrite(LPFSEVENT, LOW);
					
						// Serial LPF
						digitalWrite(SLPFSIXTY, HIGH);
						// Final LPF
						digitalWrite(LPFFORTY, HIGH);
					break;
					// 40m serial LPF, final LPF - 40m
					case 2:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFEIGHTY, LOW);
						digitalWrite(SLPFSIXTY, LOW);
						digitalWrite(SLPFTHIRTY, LOW);
						digitalWrite(SLPFTWENTY, LOW);
						digitalWrite(SLPFSEVENTEEN, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFEIGHTY, LOW);
						digitalWrite(LPFSEVENT, LOW);
					
						// Serial LPF
						digitalWrite(SLPFFORTY, HIGH);
						// Final LPF
						digitalWrite(LPFFORTY, HIGH);
					break;
					// 30m serial LPF, final LPF - 20m -> 17m
					case 3:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFEIGHTY, LOW);
						digitalWrite(SLPFSIXTY, LOW);
						digitalWrite(SLPFFORTY, LOW);
						digitalWrite(SLPFTWENTY, LOW);
						digitalWrite(SLPFSEVENTEEN, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFEIGHTY, LOW);
						digitalWrite(LPFFORTY, LOW);
						
						// Serial LPF
						digitalWrite(SLPFTHIRTY, HIGH);
						// Final LPF
						digitalWrite(LPFSEVENT, HIGH);
					break;
					// 20m serial LPF, final LPF - 20m -> 17m
					case 4:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFEIGHTY, LOW);
						digitalWrite(SLPFSIXTY, LOW);
						digitalWrite(SLPFFORTY, LOW);
						digitalWrite(SLPFTHIRTY, LOW);
						digitalWrite(SLPFSEVENTEEN, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFEIGHTY, LOW);
						digitalWrite(LPFFORTY, LOW);
						
						// Serial LPF
						digitalWrite(SLPFTWENTY, HIGH);
						// Final LPF
						digitalWrite(LPFSEVENT, HIGH);
					break;
					// 17m serial LPF, final LPF - 20m -> 17m
					case 5:
						// OFF other selection - Serial LPF
						digitalWrite(SLPFEIGHTY, LOW);
						digitalWrite(SLPFSIXTY, LOW);
						digitalWrite(SLPFFORTY, LOW);
						digitalWrite(SLPFTHIRTY, LOW);
						digitalWrite(SLPFTWENTY, LOW);
						
						// OFF other selection - Final LPF
						digitalWrite(LPFEIGHTY, LOW);
						digitalWrite(LPFFORTY, LOW);
						
						// Serial LPF
						digitalWrite(SLPFSEVENTEEN, HIGH);
						// Final LPF
						digitalWrite(LPFSEVENT, HIGH);
					break;
				}
			}
		}
	}
}
