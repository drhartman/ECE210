/* Initialization Functions */

void	LEDBARInit(void);
void 	DIPSWInit(void);
void	PBSwInit(void);	
void 	RGB_LEDInit(void);
void 	sysTickInit(void);
/* Inputs, outputs, and wait timers */			
int 	read_PBSwitchNum(int SwitchNumber);
int		read_Switches(void);
void    LEDBAROutput(int value);
void 	turnOn(char color);
void 	turnOff(char color);
void    sysTickWait1mS(int waitTime);
/* Xbee Functions */
void 	Xbee_ConfigureAddresses(int destination, int ownAddr);
void 	Xbee_Send(int message);
int		Xbee_Receive(void);
void Display(int numWin);
void    RIT128x96x4StringDraw(const char* letter, int xx, int yy, int intensity);
char* 	convertForWin(int baudotCode);
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
	int	currTurn;
	int p1Add = 1;
	int p2Add = 2;
	int p3Add = 3;
	int p4Add = 4;
	int p1Dead = 0;
	int p2Dead = 0;
	int p3Dead = 0;
	int p4Dead = 0;
	int currAdd;
	int nxtAdd;
	int hasWinner;
	int countDead = 0;
	int p1Active = 1;
	int p2Active = 0;
	int p3Active = 0;
	int p4Active = 0;
	int messageToSend = 0x0;	//Variables for containing the messages sent 
	int receivedMessage;		//and recieved

	//Initializing the LEDBAR, RGB LED, DIPSwitches and Pushbuttons, and a wait timer
	LEDBARInit();
	DIPSWInit();
	PBSwInit();
	RGB_LEDInit();
	sysTickInit();
	
	countDead = p1Dead + p2Dead + p3Dead + p4Dead;
	
	//Wait to configure address
	turnOn('R');
	sysTickWait1mS(150);
	turnOff('R');
	sysTickWait1mS(150);
	turnOn('R');
	sysTickWait1mS(150);
	turnOff('R');
	sysTickWait1mS(150);

	Xbee_ConfigureAddresses(p2Add, p1Add);
	
	//LED Sequence lets us know we have configured the Xbee 
	turnOn('B');
	sysTickWait1mS(150);
	turnOff('B');
	sysTickWait1mS(150);
	turnOn('B');
	sysTickWait1mS(150);
	turnOff('B');
	sysTickWait1mS(150);
	
	Xbee_Send(turn);	
	Xbee_Send(countDead);
	Xbee_Send(p1Dead);
	Xbee_Send(p2Dead);
	Xbee_Send(p3Dead);
	Xbee_Send(p4Dead);
		
	/* Main Part of the Program starts here */
	while (1){
		turn = Xbee_Receive();
		countDead = Xbee_Receive();
		p1Dead = Xbee_Receive();
		p2Dead = Xbee_Receive();
		p3Dead = Xbee_Receive();
		p4Dead = Xbee_Receive();
		
				
		if(turn == 1 && countDead < 3){
	
			turnOn('G');
			sysTickWait1mS(150);
			turnOff('G');
			sysTickWait1mS(150);
			turnOn('G');
			sysTickWait1mS(150);
			turnOff('G');
			sysTickWait1mS(150);
			//Play Game
		
			countDead = p1Dead + p2Dead + p3Dead + p4Dead;
	
			//Send turn
			Xbee_Send(turn);
	
			//Send num dead
			Xbee_Send(countDead);
	
		}
		else if (countDead >= 3) {
				if (!p1Dead){
						//Display "P1 Wins!"
							Display(13);
							break;
						}
				else if (!p2Dead){
							//Display "P2 Wins!"
							Display(14);
							break;
						}
				else if (!p3Dead){
							//Display "P3 Wins!"
							Display(15);
							break;
						}
				else if (!p4Dead){
							//Display "P4 Wins!"
							Display(16);
							break;
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
		case(31): return "V";
				
	}
	return " ";
}
