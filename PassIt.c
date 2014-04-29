/* Initialization Functions */

void	LEDBARInit(void);
void 	DIPSWInit(void);
void	PBSwInit(void);	
void 	RGB_LEDInit(void);
void 	sysTickInit(void);

/*Initializing Potentiometers*/
void	potentiometersInit();
int   readPotentiometer0(void);
int   readPotentiometer1(void);
int   readPotentiometer2(void);

void	RIT128x96x4Init(int freq);
void  RIT128x96x4Clear(void); 
void  RIT128x96x4StringDraw(const char* letter, int xx, int yy, int intensity);

/* Inputs, outputs, and wait timers */			
int 	read_PBSwitchNum(int SwitchNumber);
int		read_SwitchNum(int SwitchNum);
int		read_Switches(void);
void  LEDBAROutput(int value);
void 	turnOn(char color);
void 	turnOff(char color);
void  sysTickWait1mS(int waitTime);

/* Xbee Functions */
void 	Xbee_ConfigureAddresses(int destination, int ownAddr);
void Xbee_SendArray(char * s, int messageLength);
int Xbee_ReceiveArray(char * t, int messageLength);

/*Display Configurations*/
void 	Display(int numWin);

/*Conversion functions*/
char* convertForWin(int baudotCode);
char* convert(int baudotCode);

int rand(void); //random number generator

//*****************************************************************************
//
// Main Program:
//
//*****************************************************************************
int
main(void)
{
	//Initializing the variables used in the lab.
	int turn = 1;			//Pushbutton variables				
	int p1Add = 1;		//Address P1	
	int p2Add = 2;		//Address P2
	int p3Add = 3;		//Address P3
	int p4Add = 4;		//Address P4
	int p1Dead = 0;		
	int p2Dead = 0;
	int p3Dead = 0;
	int p4Dead = 0;
	int p1DeadPrev;		//Contains the previous value of p1Dead
	int p2DeadPrev;		//Contains prev value of p2Dead
	int p3DeadPrev;		//Contains prev value of p3Dead
	int p4DeadPrev;		//Contains prev value of p4Dead
	int currAdd;
	int nxtAdd;
	char messageReceived[5];
	char sendMessage[5];
	int errorCode;
	int countDead = 0;
	int turnItCodes[10];
	int correctcode[10];
	int pushItCodes[10];
	int switchItCodes[10];
	int loserCodes[10];
		
	int waitTimer = 0;
	int waitCounter = 0;
	int waitLimit = 100;
	
	int jj; 						// number of turns counter
	int ii;   					//for counter variable
	int xx;							//x axis string position
	int yy;							//y axis string position

	int turnItMsg;		//holds 'Turn It' message
	int correctMsg;	// holds 'Correct' message
	int pushItMsg;	//  holds 'Push it" message
	int loserMsg; //holds "you lose' message
	int switchItMsg;

	// used to read current values
	int potenValue0 = 0;
	int pushButton1 = 1;
	int switchButton1 = 0;

	int isInput = 0;
	int inputRequested = 0;
	int inputSelected = 0;
	int ATWCCW = 1; // 0 = false, 1 = true
	int switchON = 1; // 0 = false, 1= true
	int number = 0;																//??????????????????????
	int numberOfTurns = 4;
	int SwitchNum;

	//Initializing the LEDBAR, RGB LED, DIPSwitches and Pushbuttons, and a wait timer
	LEDBARInit();
	DIPSWInit();
	PBSwInit();
	RGB_LEDInit();
	sysTickInit();
	potentiometersInit();
	RIT128x96x4Init(1000000);
	
	//Initialize display arrays
	turnItCodes[0] = 16;	// T
	turnItCodes[1] = 7;		// U
	turnItCodes[2] = 10;	// R
	turnItCodes[3] = 12;	// N
	turnItCodes[4] = 4;		// 
	turnItCodes[5] = 6;		// I
	turnItCodes[6] = 16;	// T

		// code for 'Switch It'
	switchItCodes[0] = 5;		// S
	switchItCodes[1] = 19;	// W
	switchItCodes[2] = 6; 	// I
	switchItCodes[3] = 16;	// T
	switchItCodes[4] = 14;	// C
	switchItCodes[5] = 20;	// H
	switchItCodes[6] = 4;		//
	switchItCodes[7] = 6;		// I
  switchItCodes[8] = 16;	// T

	// code for 'Correct'
	correctcode[0] = 14;	// C
	correctcode[1] = 24;	// O
	correctcode[2] = 10;	// R
	correctcode[3] = 10;	// R
	correctcode[4] = 1;		// E
	correctcode[5] = 14;	// C
	correctcode[6] = 16;	// T 

	// code for 'Push It'
	pushItCodes[0] = 22;	// P
	pushItCodes[1] = 7;		// U
	pushItCodes[2] = 5;		// S
	pushItCodes[3] = 20;	// H
	pushItCodes[4] = 4;		// 
	pushItCodes[5] = 6;		// I
	pushItCodes[6] = 16;	// T 	

	// code for 'You Lose'
	loserCodes[0] = 21;	//Y
	loserCodes[1] = 24;	//O
	loserCodes[2] = 7;	//U
	loserCodes[3] = 4;	//
	loserCodes[4] = 18; //L
	loserCodes[5] = 24;	//O
	loserCodes[6] = 5;	//S
	loserCodes[7] = 1;	//E
	
	
	countDead = p1Dead + p2Dead + p3Dead + p4Dead;
	
	//Clear messages on the screen
	RIT128x96x4Clear();

	//Start at the upper left hand corner of the screen!
	xx = 0;
	yy = 0;
	
	//Wait to configure address
	turnOn('R');
	sysTickWait1mS(150);
	turnOff('R');
	sysTickWait1mS(150);
	turnOn('R');
	sysTickWait1mS(150);
	turnOff('R');
	sysTickWait1mS(150);

	Xbee_ConfigureAddresses(p2Add, p1Add);														//Board Specific
	RIT128x96x4Clear();
	
	//LED Sequence lets us know we have configured the Xbee 
	turnOn('B');
	sysTickWait1mS(150);
	turnOff('B');
	sysTickWait1mS(150);
	turnOn('B');
	sysTickWait1mS(150);
	turnOff('B');
	sysTickWait1mS(150);
	
	sendMessage[0] = (char) (p1Dead + 48);
	sendMessage[1] = (char) (p2Dead + 48);
	sendMessage[2] = (char) (p3Dead + 48);
	sendMessage[3] = (char) (p4Dead + 48);
	sendMessage[4] = (char) (turn + 48);
	
	Xbee_SendArray(sendMessage, 5);
		
	/* Main Part of the Program starts here */
	while (1){
		errorCode =  Xbee_ReceiveArray(messageReceived, 5);
		
		if (errorCode != 0x5A5){
			
			p1Dead = (int) messageReceived[0] - (int) '0';
			p2Dead = (int) messageReceived[1] - (int) '0';
			p3Dead = (int) messageReceived[2] - (int) '0';
			p4Dead = (int) messageReceived[3] - (int) '0';
			turn = (int) messageReceived[4] - (int) '0';
		}
		
		countDead = p1Dead + p2Dead + p3Dead + p4Dead;
		
		if(turn == 1 && countDead < 3){																					//turn is board specific
	
			turnOn('G');
			sysTickWait1mS(150);
			turnOff('G');
			sysTickWait1mS(150);
			turnOn('G');
			sysTickWait1mS(150);
			turnOff('G');
			sysTickWait1mS(150);
			
			/*******************************************************************/
			
			
			//Play Game
			
			
			/*******************************************************************/
			
			
			while(p1Dead == 0){ 																										//Board specific

		for(jj = 0 ; jj<numberOfTurns ; jj++)
		{

			// Assign inputRequest - 1: button,  2: switch, 3: knob 
		int randomNum = rand() % 3;	// generates a number between 0-3

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

		if (inputRequested == 1)
		{
			//Display 'Push it'
			for(ii = 0; ii < 7;ii++)
			{
				pushItMsg = pushItCodes[ii];
				RIT128x96x4StringDraw(convert(pushItMsg), xx + 6*ii,yy,15);
			}
		} else if (inputRequested == 2)
		{
				//Display 'Switch it'
			for(ii = 0; ii < 9;ii++)
			{
				switchItMsg = switchItCodes[ii];
				RIT128x96x4StringDraw(convert(switchItMsg), xx + 6*ii,yy,15);
			}	
		} else if (inputRequested == 3)
		{
			//Display 'Turn it'
			for(ii = 0; ii < 7;ii++)
			{
				turnItMsg = turnItCodes[ii];
				RIT128x96x4StringDraw(convert(turnItMsg), xx + 6*ii,yy,15);
			}
		}

      
			while (isInput == 0)	// loop until an input is detected
			{


				// record values of inputs here
				potenValue0 = readPotentiometer0();				  // knob value
				pushButton1 = read_PBSwitchNum(1);					// push button
				switchButton1 = read_SwitchNum(SwitchNum); 	// switch


				// Did the knob change?
				if (ATWCCW == 1)
				{
					if (potenValue0 >= 500)
					{
						inputSelected = 3;
						ATWCCW = 0;
						isInput = 1;
					}
				}
				else	//ATWCW
				{
					if (potenValue0 <= 500)
					{
						isInput = 1;
						inputSelected = 3;
						ATWCCW = 1;
					}
				}

				//Did a switch change?
					if (switchON == 0)
             {
                 if (switchButton1 == 1)
                 {
                     inputSelected = 2;
                     switchON = 1;
                     isInput = 1;
                 }
             }
             else	//switchON
             {
                 if (switchButton1 == 0)
                 {
                     switchON = 0;
                     isInput = 1;
                     inputSelected = 2;
                 }
         }

				//Was a button pushed?
				if (pushButton1 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}

				//Are we over the time limit?
				if(waitTimer > waitLimit){
					p1Dead = 1;                                     //Board Specific!!
					isInput = 1;
					inputSelected = 0;
				}

				waitTimer = waitTimer + 1;
				sysTickWait1mS(10);

			}//end while(no input)
			waitTimer = 0;
			RIT128x96x4Clear();

			// Was the input correct?
			if (inputSelected == inputRequested)
			{
					//Flash to confirm correct input!
					turnOn('G');
					sysTickWait1mS(250);
					turnOff('G');

					// Display 'correct'
					//Letters are displayed left to right
					for(ii = 0; ii < 7;ii++)
					{
						correctMsg = correctcode[ii];
						RIT128x96x4StringDraw(convert(correctMsg), xx + 6*ii,yy,15);
					}
				sysTickWait1mS(1000);
			}
			else
			{
					//Flash to confirm incorrect input!
					turnOn('R');
					sysTickWait1mS(250);
					turnOff('R');
					p1Dead = 1; 																										////THIS VALUE IS BOARD SPECIFIC
					for(ii = 0 ; ii<8 ; ii++)
					{
						loserMsg =  loserCodes[ii];
						RIT128x96x4StringDraw(convert(loserMsg), xx + 6*ii,yy,15);
					}
					break;
				}

				//RESET VALUES
				isInput = 0;
				inputSelected = 0;

			} //end for-loop number of turns

				turnOn('B'); //meaning its time to pass
		}//end while(not p1Dead)
			
			//Finish turn
			
			sendMessage[0] = (char) (p1Dead + 48);
			sendMessage[1] = (char) (p2Dead + 48);
			sendMessage[2] = (char) (p3Dead + 48);
			sendMessage[3] = (char) (p4Dead + 48);
			sendMessage[4] = (char) (2 + 48);																					//BOARD SPECIFIC!!!!
	
			Xbee_SendArray(sendMessage, 5);//Send Array to next board
				
		}
		else if (countDead >= 3) {
				if (!p1Dead){
						//Display "P1 Wins!"
							Display(13);
						}
				else if (!p2Dead){
							//Display "P2 Wins!"
							Display(14);
						}
				else if (!p3Dead){
							//Display "P3 Wins!"
							Display(15);
						}
				else if (!p4Dead){
							//Display "P4 Wins!"
							Display(16);
						}
				}
			}
		}
	
	


void Display(int numWin){
		RIT128x96x4StringDraw(convertForWin(22), 3, 15, 15);
		RIT128x96x4StringDraw(convertForWin(numWin), 9, 15, 15);
		RIT128x96x4StringDraw(convertForWin(4), 15, 15, 15);
		RIT128x96x4StringDraw(convertForWin(19), 21, 15, 15);
		RIT128x96x4StringDraw(convertForWin(6), 27, 15, 15);
		RIT128x96x4StringDraw(convertForWin(12), 33, 15, 15);
		RIT128x96x4StringDraw(convertForWin(5), 39, 15, 15);
		RIT128x96x4StringDraw(convertForWin(31), 45, 15, 15);
}

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

char* convertForWin(int baudotCode)
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
		/////////////////////////////
		case(13): return "1"; 					 	
		case(14): return "2"; 
		case(15): return "3"; 
		case(16): return "4"; 
		////////////////////////////
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
		case(31): return "!";
				
	}
	return " ";
}

