#define BUF_SIZE 100

#define hexStop 0x80
#define hexStraight 0x81
#define hexLeft 0x84
#define hexRight 0x82
#define hexReverse 0x88
#define hexStraightStation 0xC1 /* Mooi C1! */
#define hexLeftStation 0xC4
#define hexRightStation 0xC2
#define hexReverseStation 0xC8
#define hexRequestCommand 0x31
#define hexMineDetected 0x30 

unsigned char inBuf[BUF_SIZE];
int serialPort, serialNotConnected = 1, robotDriving = 1, routeStep, waypointStep, removeWaypointNextStep = 0, lastStep = 0;
extern int robotDone;
extern char challengeType;

struct timeval stop, start;


void emptyBuf () {

    int i;

    for (i = 0; i < BUF_SIZE; i++)
        inBuf[i] = '\0';
}



void setupSerial () {

    char meuk;

    printf("(For windows systems, enter (comport number - 1)\n");
    printf("(For *NIX systems, use 16 for ttyUSB0 and 0 for ttyS0\n");
    printf("Please enter serial port number: ");
    scanf("%d", &serialPort);
    scanf("%c", &meuk);
    printf("\n");

    serialNotConnected = RS232_OpenComport(serialPort, 9600, "8N1");
    RS232_flushRXTX(serialPort);

    if (!serialNotConnected)
        printf("Serial port succesfully connected!\n");

    emptyBuf();

}

void getSerial () {
    
    usleep(100000);
    emptyBuf();
    RS232_PollComport(serialPort, inBuf, BUF_SIZE);
}

void stopSerial () {
	RS232_CloseComport(serialPort);
}


double get_time_ms()
{
struct timeval t;
gettimeofday(&t, NULL);
return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}


void sendRoute () {

    int minePos[2], i = 0;


    if (inBuf[0] != 0) { 


        fprintf(stdout, "%lu\n", (unsigned long)time(NULL)); 

        printf("Current routeStep: %d = %d-%d", routeStep, route[routeStep][0], route[routeStep][1]);


    	if (inBuf[0] == hexMineDetected && challengeType == 'B') {

            removeWaypointNextStep = 0;
            lastStep = 0;

            while (route[routeStep - 1][3] == 0) {
                routeStep--;
            }

            minePos[0] = (route[routeStep - 1 - i][0] + route[routeStep][0]) / 2.0;
            minePos[1] = (route[routeStep - 1 - i][1] + route[routeStep][1]) / 2.0;


            printf("\nMine detected! On position: \t %d-%d\n", minePos[0], minePos[1]);

            markMine(minePos);



            setCurrentWaypoint(route[routeStep - 1 - i]);
            flipNextWaypointDir(route[routeStep]);

            robotDriving = 0;            

    	} else if (inBuf[0] == hexRequestCommand) {    		

    		do {
    			routeStep++;
    		} while (route[routeStep][3] == 0);

            if (removeWaypointNextStep) {
                printf("Removing waypoint: %d\n", waypointStep);
                removeWaypoint(waypointStep++);
                removeWaypointNextStep = 0;
            }
            if (lastStep) {
                robotDriving = 0;
                robotDone = 1;
            } 

    		switch (route[routeStep][3]) {
    			case 1 :
    				RS232_SendByte(serialPort, hexStraight);
    				printf("\nSend robot command: \thexStraight \t(%X)\n", hexStraight);
    				break;
    			case 2 :
    				RS232_SendByte(serialPort, hexLeft);
    				printf("\nSend robot command: \thexLeft \t(%X)\n", hexLeft);
    				break;
    			case 3 :
    				RS232_SendByte(serialPort, hexRight);
    				printf("\nSend robot command: \thexRight \t(%X)\n", hexRight);
    				break;
    			case 11 :
    				RS232_SendByte(serialPort, hexStraightStation);
    				printf("\nSend robot command: \thexStraightStation (%X)\n", hexStraightStation);
    				removeWaypointNextStep = 1;
    				break;
    			case 12 :
    				RS232_SendByte(serialPort, hexLeftStation);
    				printf("\nSend robot command: \thexLeftStation (%X)\n", hexLeftStation);
                    removeWaypointNextStep = 1;
    				break;
    			case 13 :
    				RS232_SendByte(serialPort, hexRightStation);
    				printf("\nSend robot command: \thexRightStation (%X)\n", hexRightStation);
                    removeWaypointNextStep = 1;
    				break;
    		}

            printf("removeWaypointNextStep: %d\n", removeWaypointNextStep);


    		printf("Robot is driving from: \t%d -%d \tto: %d - %d\n", route[routeStep][0], route[routeStep][1], route[routeStep + 1][0], route[routeStep + 1][1]);

    		setCurrentWaypoint(route[routeStep]);

    		if (route[routeStep + 1][0] == -1 && route[routeStep + 1][1] == -1) {
    			lastStep = 1;
            }

    	} else {
    		printf("Received serial garbage: %X\n", inBuf[0]);
    	}
    }
}


void driveRoute () {

    if (serialNotConnected) {
        printf("No serial connection, program exiting now!\n");
        exit(0);
    } else {
        
    	robotDriving = 1;
    	routeStep = -1;
    	waypointStep = 1;
    	inBuf[0] = hexRequestCommand;

        while(robotDriving) {
            sendRoute();
            getSerial();
        }
    }
}

