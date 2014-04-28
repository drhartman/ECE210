#include <stdlib.h> /* required for randomize() and random() */
#include <time.h>

//*****************************************************************************
// TITLE:			LAB 8
// 
// NAME:		    <Your Name Here>
// LAB SECTION:		<301, 302, 303, 304, 305, or 306>
// LAB DAY:			<Lab Day>
//
// CLASS:			ECE 210
// DATE: 			FALL 2014
// 
// DESCRIPTION:		<Insert a short description of what you are working on in 
//                   in this lab>
//*****************************************************************************
/* Initialization Functions */
void	LEDBARInit(void);
void 	DIPSWInit(void);
void	PBSwInit(void);	
void 	RGB_LEDInit(void);
void 	sysTickInit(void);
int rand(void);
/* Inputs, outputs, and wait timers */			
int 	read_PBSwitchNum(int SwitchNumber);
int		read_Switches(void);
void    LEDBAROutput(int value);
void 	turnOn(char color);
void 	turnOff(char color);
void  potentiometersInit(void);
int   readPotentiometer0(void);
int   readPotentiometer1(void);
int   readPotentiometer2(void);
void    LEDBAROutput(int number);
void    LEDBAR_TurnOn(int number);
void    LEDBAR_TurnOff(int number);
int   read_SwitchNum(int SwitchNum);
int   read_Switches();
void    sysTickWait1mS(int waitTime);
void	RIT128x96x4Init(int freq);
void    RIT128x96x4Clear(void); 
void    RIT128x96x4StringDraw(const char* letter, int xx, int yy, int intensity);
char* 	convert(int baudotCode);
//int randomize(void);
time_t time(time_t *);
//*****************************************************************************
//
// Main Program:
//
//*****************************************************************************
int
main(void)
{
	//Initializing the variables used in the lab.
	int turnItCodes[10];
	int correctcode[10];
	int pushItCodes[10];
	int switchItCodes[10];
	int loserCodes[10];

	int ii;   					//for counter variable
	int xx;							//x axis string position
	int yy;							//y axis string position

	int turnIt;		//holds 'Turn It' message
	int correct;	// holds 'Correct' message
	int pushIt;	//  holds 'Push it" message
	int switchIt; // holds 'Switch it' message
	int loserMsg; //holds "you lose' message
	
	int dead;
	int SEED;

	// used to read current values
	int potenValue0 = 0;
	int pushButton1 = 1;
	int switchButton1 = 0;

	int isInput = 0;
	int inputRequested = 0;
	int inputSelected = 0;
	int ATWCCW = 1; // 0 = false, 1 = true
	int switchON = 0; // 0 = false, 1= true
  int number = 0;
  int SwitchNum = 4;
	
	// timer variables
	int waitTimer = 0;
	int waitCounter = 0;
	int waitLimit;


	//Initializing the LEDBAR, RGB LED, DIPSwitches and Pushbuttons, and a wait timer
	LEDBARInit();
	DIPSWInit();
	PBSwInit();
	RGB_LEDInit();
	sysTickInit();
	potentiometersInit();
	RIT128x96x4Init(1000000);

	/* Main Part of the Program starts here */

	// code for 'Turn It'
  turnItCodes[0] = 16;	// T
	turnItCodes[1] = 7;	// U
	turnItCodes[2] = 10;	// R
	turnItCodes[3] = 12;	// N
	turnItCodes[4] = 4;	// 
	turnItCodes[5] = 6;	// I
	turnItCodes[6] = 16;	// T

	// code for 'Correct'
	correctcode[0] = 14;	// C
	correctcode[1] = 24;	// O
	correctcode[2] = 10;	// R
	correctcode[3] = 10;	// R
	correctcode[4] = 1;	// E
	correctcode[5] = 14;	// C
	correctcode[6] = 16;	// T 

	// code for 'Push It'
	pushItCodes[0] = 22;	// P
	pushItCodes[1] = 7;	// U
	pushItCodes[2] = 5;	// S
	pushItCodes[3] = 20;	// H
	pushItCodes[4] = 4;	// 
	pushItCodes[5] = 6;	// I
	pushItCodes[6] = 16;	// T 

	// code for 'Switch It'
	switchItCodes[0] = 5;	// S
	switchItCodes[1] = 19;     // W
	switchItCodes[2] = 6;     // I
	switchItCodes[3] = 16;	// T
	switchItCodes[4] = 14;     // C
	switchItCodes[5] = 20;     // H
	switchItCodes[6] = 4;	//
  switchItCodes[7] = 6;	// I
  switchItCodes[8] = 16;	// T
	
	// code for 'You Lose'
	loserCodes[0] = 21;	//Y
	loserCodes[1] = 24;	//O
	loserCodes[2] = 7;	//U
	loserCodes[3] = 4;	//
	loserCodes[4] = 18; //L
	loserCodes[5] = 24;	//O
	loserCodes[6] = 5;	//S
	loserCodes[7] = 1;	//E

	//Flash twice to say we are getting ready to go!
	turnOn('B');
	sysTickWait1mS(250);
	turnOff('B');
	turnOn('B');
	sysTickWait1mS(250);
	turnOff('B');

	//Clear messages on the screen
	RIT128x96x4Clear();

	//Start at the upper left hand corner of the screen!
	xx = 0;
	yy = 0;

	//(unsigned int) srand(time(NULL)); // set new seed?
	SEED = 42;//time(NULL);
	
	srand(SEED);
	//srand(time(NULL));
	
	sysTickWait1mS(1000);
	
  while(1){

		// Assign inputRequest - 1: button,  2: switch, 3: knob 
		int randomNum = rand() % 3;	// generates a number between 0-3

		/*
		if (randomNum <= 1)
		{
			inputRequested = 1;	// button
		}
    else if (1 < randomNum <= 2)
    {
			inputRequested = 2;	// switch
    }
		else if (2 < randomNum <= 3)
		{
			inputRequested = 3;	// knob
		}
*/
		
		switch(randomNum)
{
   case 0:
      inputRequested = 1;	// button
      break;

   case 1:
      inputRequested = 2;	// switch
      break;

   case 2:
      inputRequested = 3;	// knob
      break;

}
		
		if (inputRequested == 1)
		{
			//Display 'Push it'
			for(ii = 0; ii < 7;ii++)
			{
				pushIt = pushItCodes[ii];
				RIT128x96x4StringDraw(convert(pushIt), xx + 6*ii,yy,15);
			}
		} else if (inputRequested == 2)
		{
			//Display 'Switch it'
            		for(ii = 0; ii < 9;ii++)
			{
				switchIt = switchItCodes[ii];
				RIT128x96x4StringDraw(convert(switchIt), xx + 6*ii,yy,15);
			}	
		} else if (inputRequested == 3)
		{
			//Display 'Turn it'
			for(ii = 0; ii < 7;ii++)
			{
				turnIt = turnItCodes[ii];
				RIT128x96x4StringDraw(convert(turnIt), xx + 6*ii,yy,15);
			}
		}

    // Set timeout
		waitLimit = 50;
		LEDBAROutput(31);
		
			while (isInput == 0)	// loop until an input is detected
			{

				// record values of inputs here
				potenValue0 = readPotentiometer0();				  // knob value
				pushButton1 = read_PBSwitchNum(1);					// push button
				switchButton1 = read_SwitchNum(SwitchNum);  // switch number
				// Did the knob change?
				if (ATWCCW == 1 && (potenValue0 >= 500))
				{
						inputSelected = 3;
						ATWCCW = 0;
						isInput = 1;
				}
				else if (ATWCCW == 0 && (potenValue0 <= 500)) //ATWCW
				{
					isInput = 1;
					inputSelected = 3;
					ATWCCW = 1;
				}
				

				//Did a switch change?
				if (switchON == 0 && switchButton1 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON = 1;
						isInput = 1;
        } else if (switchON == 1 && switchButton1 == 0) 	//switchON
          {
             switchON = 0;
             isInput = 1;
             inputSelected = 2;
          }
        		 	
				//Was a button pushed?
				if (pushButton1 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}
				
				//Are we over the time limit?
				if(waitTimer > waitLimit){
					//p1Dead = 1;    //Board Specific!!
					isInput = 1;
					inputSelected = 0;
				}

				waitTimer = waitTimer + 1;
				sysTickWait1mS(100);
				//LEDBAROutput();
				
				
				// display time on LEDBAR
				/* //not sure if case statement would work for this. 
				//Need to figure out how to adjust time display as time speeds up
				switch(randomNum)
				{
					case 0:
						LEDBAR_TurnOn(number);
						break;

					case 1:
						LEDBAR_TurnOn(number);
						break;

					case 2:
						LEDBAR_TurnOn(number);
						break;
}
				*/
				
			  if ((10 < waitTimer) && (waitTimer <= 20))
				{
					LEDBAR_TurnOff(4);
				} else if ((20 < waitTimer) && (waitTimer <= 30))
				{
					LEDBAR_TurnOff(3);
				} else if ((30 < waitTimer) && (waitTimer <= 40))
				{
					LEDBAR_TurnOff(2);
				} else if ((40 < waitTimer) && (waitTimer <= 50))
				{
					LEDBAR_TurnOff(1);
				}

			}//end while(no input)
			waitTimer = 0;
			LEDBAR_TurnOff(0);
			LEDBAR_TurnOff(1);
			LEDBAR_TurnOff(2);
			LEDBAR_TurnOff(3);
			LEDBAR_TurnOff(4);


			// Was the input correct?
			if (inputSelected == inputRequested)
			{
					//Flash to confirm correct input!
					turnOn('G');
					sysTickWait1mS(250);
					turnOff('G');
					turnOn('G');
					sysTickWait1mS(250);
					turnOff('G');

					//Clear messages on the screen
					RIT128x96x4Clear();
				
					// Display 'correct'
					//Letters are displayed left to right
					for(ii = 0; ii < 7;ii++)
					{
						correct = correctcode[ii];
						RIT128x96x4StringDraw(convert(correct), xx + 6*ii,yy,15);
					}
				sysTickWait1mS(1000);
					
				//Clear messages on the screen
				RIT128x96x4Clear();
			}
			else
			{
					//Flash to confirm incorrect input!
					turnOn('R');
					sysTickWait1mS(250);
					turnOff('R');
					turnOn('R');
					sysTickWait1mS(250);
					turnOff('R');
				
				  //Clear messages on the screen
					RIT128x96x4Clear();
				
					dead = 1; ////THIS VALUE IS BOARD SPECIFIC
					for(ii = 0 ; ii < 8 ; ii++)
					{
						loserMsg =  loserCodes[ii];
						RIT128x96x4StringDraw(convert(loserMsg), xx + 6*ii,yy,15);
					}
					sysTickWait1mS(1000);
					//Clear messages on the screen
					RIT128x96x4Clear();
			}

			//RESET VALUES
			isInput = 0;
			inputSelected = 0;

			}//end while(1)

	}


/* The convert() function maps 5 bit Baudot codes to the output needed for 
   for the LCD Display */

char* convert(int baudotCode)
{
	switch(baudotCode)
	{
		case(1): return "E";
		case(3): return "A";
		case(4): return " ";
		case(5): return "S";
		case(6): return "I";
		case(7): return "U";
		case(9): return "D";
		case(10): return "R";
		case(11): return "J";
		case(12): return "N";		 
		case(13): return "F";					 	
		case(14): return "C";
		case(15): return "K";
		case(16): return "T";
		case(17): return "Z";
		case(18): return "L";
		case(19): return "W";
		case(20): return "H";			 					 
		case(21): return "Y";
		case(22): return "P";
		case(23): return "Q";
		case(24): return "O";
		case(25): return "B";
		case(26): return "G";
		case(28): return "M";
		case(29): return "X";
		case(31): return "V";
	}
	return " ";
}
