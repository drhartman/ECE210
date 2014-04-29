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
	
	int dead=0;
	int turn = 0;
	int SEED;

	// used to read current values
	int potenValue0 = 0;
	int potenValue1 = 0;
	int potenValue2 = 0;
	int pushButton1 = 1;
	int pushButton2 = 1;
	int pushButton3 = 1;
	int switchButton0 = 0;
	int switchButton1 = 0;
	int switchButton2 = 0;
	int switchButton3 = 0;
	int switchButton4 = 0;

	int isInput = 0;
	int inputRequested = 0;
	int inputSelected = 0;
	int ATWCCW0 = 1; // 0 = false, 1 = true
	int ATWCCW1 = 1; // 0 = false, 1 = true
	int ATWCCW2 = 1; // 0 = false, 1 = true
	int switchON0 = 0; // 0 = false, 1= true
	int switchON1 = 0; // 0 = false, 1= true
	int switchON2 = 0; // 0 = false, 1= true
	int switchON3 = 0; // 0 = false, 1= true
	int switchON4 = 0; // 0 = false, 1= true
  int number = 0;
	
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
	SEED = rand()%4242;//time(NULL);
	
	srand(SEED);
	waitLimit = 30;
	sysTickWait1mS(1000);
	
	
	
	
	
	
	

	while(dead == 0 && turn < 5){

		// Assign inputRequest - 1: button,  2: switch, 3: knob 
		int randomNum = rand() % 3;	// generates a number between 0-3
		
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
		LEDBAROutput(31);
		
			while (isInput == 0)	// loop until an input is detected
			{

				// record values of inputs here
				// knob values
				potenValue0 = readPotentiometer0();				 
				potenValue1 = readPotentiometer1();				  
				potenValue2 = readPotentiometer2();	
				// switches
				switchButton0 = read_SwitchNum(0);  
				switchButton1 = read_SwitchNum(1);  
				switchButton2 = read_SwitchNum(2);  
				switchButton3 = read_SwitchNum(3);  
				switchButton4 = read_SwitchNum(4);
	      // push buttons			  
				pushButton1 = read_PBSwitchNum(1);
        pushButton2 = read_PBSwitchNum(2);
				pushButton3 = read_PBSwitchNum(3);				
			    
				
				// Did the knob change?
				// knob0
				if (ATWCCW0 == 1 && (potenValue0 >= 500))
				{
						inputSelected = 3;
						ATWCCW0 = 0;
						isInput = 1;
				}
				else if (ATWCCW0 == 0 && (potenValue0 <= 500)) //ATWCW
				{
					isInput = 1;
					inputSelected = 3;
					ATWCCW0 = 1;
				}
				// knob1
				if (ATWCCW1 == 1 && (potenValue1 >= 500))
				{
						inputSelected = 3;
						ATWCCW1 = 0;
						isInput = 1;
				}
				else if (ATWCCW1 == 0 && (potenValue1 <= 500)) //ATWCW
				{
					isInput = 1;
					inputSelected = 3;
					ATWCCW1 = 1;
				}
				// knob2
				if (ATWCCW2 == 1 && (potenValue2 >= 500))
				{
						inputSelected = 3;
						ATWCCW2 = 0;
						isInput = 1;
				}
				else if (ATWCCW2 == 0 && (potenValue2 <= 500)) //ATWCW
				{
					isInput = 1;
					inputSelected = 3;
					ATWCCW2 = 1;
				}
				

				//Did a switch change?
				// switch0
				if (switchON0 == 0 && switchButton0 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON0 = 1;
						isInput = 1;
        } else if (switchON0 == 1 && switchButton0 == 0) 	//switchON
          {
             switchON0 = 0;
             isInput = 1;
             inputSelected = 2;
          }
				// switch1
				if (switchON1 == 0 && switchButton1 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON1 = 1;
						isInput = 1;
        } else if (switchON1 == 1 && switchButton1 == 0) 	//switchON
          {
             switchON1 = 0;
             isInput = 1;
             inputSelected = 2;
          }
				// switch2
				if (switchON2 == 0 && switchButton2 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON2 = 1;
						isInput = 1;
        } else if (switchON2 == 1 && switchButton2 == 0) 	//switchON
          {
             switchON2 = 0;
             isInput = 1;
             inputSelected = 2;
          }
				// switch3
				if (switchON3 == 0 && switchButton3 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON3 = 1;
						isInput = 1;
        } else if (switchON3 == 1 && switchButton3 == 0) 	//switchON
          {
             switchON3 = 0;
             isInput = 1;
             inputSelected = 2;
          }
				// switch4
				if (switchON4 == 0 && switchButton4 == 1) // switchOn holds last switch value 
        {
						inputSelected = 2;
						switchON4 = 1;
						isInput = 1;
        } else if (switchON4 == 1 && switchButton4 == 0) 	//switchON
          {
             switchON4 = 0;
             isInput = 1;
             inputSelected = 2;
          }
        		 	
					
				//Was a button pushed?
			  // push button1
				if (pushButton1 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}
				// push button2
				if (pushButton2 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}
				// push button3
				if (pushButton3 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}
				
				//Are we over the time limit?
				if(waitTimer > waitLimit){
					dead = 1;    //Board Specific!!
					isInput = 1;
					inputSelected = 0;
				}

				waitTimer = waitTimer + 1;
				sysTickWait1mS(100);
				
			  if (((.2*waitLimit) < waitTimer) && (waitTimer <= (.4*waitLimit)))
				{
					LEDBAR_TurnOff(4);
				} else if (((.4*waitLimit) < waitTimer) && (waitTimer <= (.6*waitLimit)))
				{
					LEDBAR_TurnOff(3);
				} else if (((.6*waitLimit) < waitTimer) && (waitTimer <= (.8*waitLimit)))
				{
					LEDBAR_TurnOff(2);
				} else if (((.8*waitLimit) < waitTimer) && (waitTimer <= waitLimit))
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
			turn = turn +1;
			}//end while(not dead && less than 5 turns)
		turnOn('B');
		waitLimit = waitLimit*.9;
		turn = 0;
			
			
			
			
			
			
			
			
			
			
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
