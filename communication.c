#define SERIAL_PORT 0 /* 0 for internal, 16 for USB */

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
int serialNotConnected = 1, robotDriving = 1, routeStep, waypointStep, removeWaypointNextStep = 0, lastStep = 0;
extern int robotDone;
extern char challengeType;


void emptyBuf () {

    int i;

    for (i = 0; i < BUF_SIZE; i++)
        inBuf[i] = '\0';
}



void setupSerial () {

    serialNotConnected = RS232_OpenComport(SERIAL_PORT, 9600, "8N1");
    RS232_flushRXTX(SERIAL_PORT);

    if (!serialNotConnected)
        printf("Serial port succesfully connected!\n");

    emptyBuf();

}

void getSerial () {
    
    usleep(100000);
    emptyBuf();
    RS232_PollComport(SERIAL_PORT, inBuf, BUF_SIZE);
}

void stopSerial () {
	RS232_CloseComport(SERIAL_PORT);
}

void sendRoute () {

    int minePos[2], i = 0;


    if (inBuf[0] != 0) { 


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
                removeWaypoint(waypointStep++);
                removeWaypointNextStep = 0;
            }

            if (lastStep) {
                robotDriving = 0;
                robotDone = 1;
            } 

    		switch (route[routeStep][3]) {
    			case 1 :
    				RS232_SendByte(SERIAL_PORT, hexStraight);
    				printf("\nSend robot command: \thexStraight \t(%X)\n", hexStraight);
    				break;
    			case 2 :
    				RS232_SendByte(SERIAL_PORT, hexLeft);
    				printf("\nSend robot command: \thexLeft \t(%X)\n", hexLeft);
    				break;
    			case 3 :
    				RS232_SendByte(SERIAL_PORT, hexRight);
    				printf("\nSend robot command: \thexRight \t(%X)\n", hexRight);
    				break;
    			case 11 :
    				RS232_SendByte(SERIAL_PORT, hexStraightStation);
    				printf("\nSend robot command: \thexStraightStation (%X)\n", hexStraightStation);
    				removeWaypointNextStep = 1;
    				break;
    			case 12 :
    				RS232_SendByte(SERIAL_PORT, hexLeftStation);
    				printf("\nSend robot command: \thexLeftStation (%X)\n", hexLeftStation);
                    removeWaypointNextStep = 1;
    				break;
    			case 13 :
    				RS232_SendByte(SERIAL_PORT, hexRightStation);
    				printf("\nSend robot command: \thexRightStation (%X)\n", hexRightStation);
                    removeWaypointNextStep = 1;
    				break;
    		}

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

