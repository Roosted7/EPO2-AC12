/* Test Communicatie PC met Robot
 * Tim Al, C1/ A2
 * 29 Mei 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define COMPORT "COM3"
#define BAUDRATE CBR_9600

void initSio(HANDLE hSerial){

    COMMTIMEOUTS timeouts ={0};
    DCB dcbSerialParams = {0};

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("error getting state \n");
    }

    dcbSerialParams.BaudRate = BAUDRATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if(!SetCommState(hSerial, &dcbSerialParams)){
        printf("error setting state \n");
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if(!SetCommTimeouts(hSerial, &timeouts)){
        printf("error setting timeout state \n");
    }
}

int readByte(HANDLE hSerial, char *buffRead) {

    DWORD dwBytesRead = 0;

    if (!ReadFile(hSerial, buffRead, 1, &dwBytesRead, NULL))
    {
        printf("error reading byte from input buffer \n");
    }
    printf("Byte read from read buffer is: %c \n", buffRead[0]);
    return(0);
}

int writeByte(HANDLE hSerial, char *buffWrite){

    DWORD dwBytesWritten = 0;

    if (!WriteFile(hSerial, buffWrite, 1, &dwBytesWritten, NULL))
    {
        printf("error writing byte to output buffer \n");
    }
    printf("Byte written to write buffer is: %c \n", buffWrite[0]);

    return(0);
}

int main()
{
    HANDLE hSerial;


    char byteBuffer[BUFSIZ+1];
    int waarde=0;
    char vooruitchar=-127;

    hSerial = CreateFile(COMPORT,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if(hSerial == INVALID_HANDLE_VALUE){
        if(GetLastError()== ERROR_FILE_NOT_FOUND){
            printf(" serial port does not exist \n");
        }
        printf(" some other error occured. Inform user.\n");
    }

    initSio(hSerial);

    /*Instructies*/
    printf("\n\nTEST COMMUNICATIE MET DE ROBOT\n\n");
    printf("Wil je dat er ook wordt gelezen wanneer er iets wordt verzonden? (1=ja)\n");
    scanf("%d", &waarde);
    printf("Verzend telkens één karakter, waarbij:\n");
    printf("S\tStop met rijden\n");
    printf("V\tVooruit rijden\n");
    printf("R\tRechtsaf en rijden\n");
    printf("L\tLinksaf en rijden\n");
    printf("A\tAchteruit rijden\n");
    printf("B\tVooruit rijden tot aan het station\n");
    printf("C\tRechtsaf en rijden tot aan het station\n");
    printf("D\tLinksaf en rijden tot aan het station\n");
    printf("E\tAchteruit rijden tot aan het station\n");
    if (waarde != 1)
    {
        printf("I\tOntvang invoer van de robot\n");
    }
    printf("Q\tStop dit programma\n");

    while ( 1 ) {
        gets(byteBuffer);
        printf("\n");

        switch(byteBuffer[0])
        {
        case 'S' :
        case 's' :
            printf("1000 0000\tCommando stop met rijden\n");
            writeByte(hSerial, "€");
            break;
        case 'V' :
        case 'v' :
            printf("1000 0001\tCommando vooruit rijden\n");
            writeByte(hSerial, &vooruitchar);
            break;
        case 'R' :
        case 'r' :
            printf("1000 0010\tCommando rechtsaf en rijden\n");
            writeByte(hSerial, "‚");
            break;
        case 'L' :
        case 'l' :
            printf("1000 0100\tCommando linksaf en rijden\n");
            writeByte(hSerial, "„");
            break;
        case 'A' :
        case 'a' :
            printf("1000 1000\tCommando achteruit rijden\n");
            writeByte(hSerial, "ˆ");
            break;
        case 'B' :
        case 'b' :
            printf("1100 0001\tCommando vooruit rijden tot aan het station\n");
            writeByte(hSerial, "Á");
            break;
        case 'C' :
        case 'c' :
            printf("1100 0010\tCommando rechtsaf en rijden tot aan het station\n");
            writeByte(hSerial, "Â");
            break;
        case 'D' :
        case 'd' :
            printf("1100 0100\tCommando linksaf en rijden tot aan het station\n");
            writeByte(hSerial, "Ä");
            break;
        case 'E' :
        case 'e' :
            printf("1100 1000\tCommando achteruit rijden tot aan het station\n");
            writeByte(hSerial, "È");
            break;
        case 'Q' :
        case 'q' :
            break;
            break;
        case 'I' :
        case 'i' :
            readByte(hSerial, byteBuffer);
            break;
        default :
            printf("Ongeldige invoer\n");
        }

        if (byteBuffer[0] == 'q' || byteBuffer[0] == 'Q')
            break;

        if (waarde == 1)
        {
            readByte(hSerial, byteBuffer);
        }
    }

    printf("ZIGBEE IO DONE!\n");
    return 0;

    CloseHandle(hSerial);
}
