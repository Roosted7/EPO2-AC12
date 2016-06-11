#define SERIAL_PORT 0 /* 0 for internal, 16 for USB */
#define BUF_SIZE 50


int serialNotConnected = 1, robotDriving = 1, currentStep;

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


void sendRoute () {

	char sendData;


    if (inBuf[0] == 49) { 

        sendData = '\0';

        if (route[currentStep][3] == 1)
            sendData = -127;
        if (route[currentStep][3] == 2)
            sendData = -124;
        if (route[currentStep][3] == 3)
            sendData = -126;
        if (route[currentStep][3] == 11) {
            sendData = -63;
            currentStep++;
        }
        if (route[currentStep][3] == 12) {
            sendData = -60;
            currentStep++;
        }
        if (route[currentStep][3] == 13) {
            sendData = -62;
            currentStep++;
        }

        RS232_SendByte(SERIAL_PORT, sendData);

        currentStep++;

    }


}

void startRoute () {

    robotDriving = 1;
    currentStep = 1;

    inBuf[0] = 49;

}


void getSerial () {

    
    emptyBuf();

    usleep(100000);

    RS232_PollComport(SERIAL_PORT, inBuf, BUF_SIZE);


}


void driveRoute () {

    if (serialNotConnected) {
        printf("No serial connection, program exiting now!\n");
        exit(0);
    } else {
        startRoute();
        while(robotDriving) {
            sendRoute();
            getSerial();
        }
    }
}
