/*MAZE ROUTER V5COM1
  Hetzelfde als de Maze Router v4, maar nu is het mogelijk om DRIE bestemmingen in te voeren en de robot zal ze allemaal afgaan in een zo kort mogelijke tijd
  Deze versie verstuurt ook de signalen via de COM-poort, maar wil nog steeds feedback van het toetsenbord van de computer
*/


#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define COMPORT "COM3"
#define BAUDRATE CBR_9600


/*Specificeer hieronder de verhouding in tijd die het kost om rechtdoor te rijden tegen het nemen van een bocht*/
#define BOCHTWEGING 2
#define WEGENWEGING 1


int plattegrond[13][13] =
{
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1}
};

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
    /*Antwoord interpreteren*/
    if (buffRead[0] == '1')
    {
        /*Geen mijn*/
        return(1);
    }
    if (buffRead[0] == '0')
    {
        return(0);
    }
    return(2);
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


int loop(int startpunt, int eindpunt)
{
    int i = 0, j = 0, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int punt[2]; /*Array met de coordinaten van het pad om terug te komen*/
    int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/
    int bochten = 0, rechten = 0;

    /*In de array alle nummertjes groter dan 0 veranderen in een 0*/
    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (plattegrond[i][j] > 0)
            {
                plattegrond[i][j] = 0;
            }
        }
    }


    k = 1;

    /*Coordinaten toewijzen*/
    switch(startpunt)
    {
    case 1 :
        startc[0] = 12;
        startc[1] = 4;
        vorigerichting = 2;
        break;
    case 2 :
        startc[0] = 12;
        startc[1] = 6;
        vorigerichting = 2;
        break;
    case 3 :
        startc[0] = 12;
        startc[1] = 8;
        vorigerichting = 2;
        break;
    case 4 :
        startc[0] = 8;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 5 :
        startc[0] = 6;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 6 :
        startc[0] = 4;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 7 :
        startc[0] = 0;
        startc[1] = 8;
        vorigerichting = 1;
        break;
    case 8 :
        startc[0] = 0;
        startc[1] = 6;
        vorigerichting = 1;
        break;
    case 9 :
        startc[0] = 0;
        startc[1] = 4;
        vorigerichting = 1;
        break;
    case 10 :
        startc[0] = 4;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    case 11 :
        startc[0] = 6;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    case 12 :
        startc[0] = 8;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    default :
        /*Foutmelding door onbekend startpunt*/
        printf("\nFATALE FOUT!\n");
        printf("\tOnbekend startpunt\n");
        /*Voorkom dat de handel vastloopt*/
        k = 100;
    }

    /*Coordinaten toewijzen*/
    switch(eindpunt)
    {
    case 1 :
        eindc[0] = 12;
        eindc[1] = 4;
        break;
    case 2 :
        eindc[0] = 12;
        eindc[1] = 6;
        break;
    case 3 :
        eindc[0] = 12;
        eindc[1] = 8;
        break;
    case 4 :
        eindc[0] = 8;
        eindc[1] = 12;
        break;
    case 5 :
        eindc[0] = 6;
        eindc[1] = 12;
        break;
    case 6 :
        eindc[0] = 4;
        eindc[1] = 12;
        break;
    case 7 :
        eindc[0] = 0;
        eindc[1] = 8;
        break;
    case 8 :
        eindc[0] = 0;
        eindc[1] = 6;
        break;
    case 9 :
        eindc[0] = 0;
        eindc[1] = 4;
        break;
    case 10 :
        eindc[0] = 4;
        eindc[1] = 0;
        break;
    case 11 :
        eindc[0] = 6;
        eindc[1] = 0;
        break;
    case 12 :
        eindc[0] = 8;
        eindc[1] = 0;
        break;
    default :
        /*Foutmelding door onbekend eindpunt*/
        printf("\nFATALE FOUT!\n");
        printf("\tOnbekend eindpunt\n");
        /*Voorkom dat de handel vastloopt*/
        k = 100;
    }
    /*De bestemming krijgt waarde i, ofwel 1*/
    plattegrond[eindc[0]][eindc[1]] = k;

    /*Zolang de startpositie nog niet bereikt is*/
    while((plattegrond[startc[0]][startc[1]] == 0) && (k < 90))
    {
        /*Zoek naar waarde k*/
        for (i=0; i<13; i++)
        {
            for (j=0; j<13; j++)
            {
                if(plattegrond[i][j] == k)
                {
                    /*Buren zoeken*/
                    /*Buur 1*/
                    if (i <12)
                    {
                        if (plattegrond[i+1][j] == 0)
                        {
                            plattegrond[i+1][j] = k + 1;
                        }
                    }
                    /*Buur 2*/
                    if (i > 0)
                    {
                        if (plattegrond[i-1][j] == 0)
                        {
                            plattegrond[i-1][j] = k + 1;
                        }
                    }
                    /*Buur 3*/
                    if (j<12)
                    {
                        if (plattegrond[i][j+1] == 0)
                        {
                            plattegrond[i][j+1] = k + 1;
                        }
                    }
                    /*Buur 4*/
                    if (j > 0)
                    {
                        if (plattegrond[i][j-1] == 0)
                        {
                            plattegrond[i][j-1] = k + 1;
                        }
                    }
                }
            }
        }

        k = k + 1;
    }

    if (k < 90)
    {
        /*Spring naar het eindpunt met de punt*/
        punt[0] = startc[0];
        punt[1] = startc[1];
        while(k > 3)
        {
            /*Voorkeursburen*/
            /*Voorkeursbuur 1*/
            if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] + 2;
            }
            /*Voorkeursbuur 2*/
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] - 2;
            }
            /*Voorkeursbuur 3*/
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[1] = punt[1] + 2;
            }
            /*Voorkeursbuur 4*/
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[1] = punt[1] - 2;
            }

            /*Standaardlijstje buren*/
            /*Buur 1*/
            else if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 1;
                /*Punt doorschuiven*/
                punt[0] = punt[0] + 2;
            }
            /*Buur 2*/
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] - 2;
            }
            /*Buur 3*/
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 3;
                /*Punt doorschuiven*/
                punt[1] = punt[1] + 2;
            }
            /*Buur 4*/
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 4;
                /*Punt doorschuiven*/
                punt[1] = punt[1] - 2;
            }
        }
    }
    /*Lengte terugsturen*/
    return (BOCHTWEGING*bochten + WEGENWEGING*rechten);
}


void route(int startpunt, int eindpunt)
{
    /****************
    /   OPSTARTEN   *
    ****************/

    HANDLE hSerial;

    int klaar = 0, opnieuw = 0; /*Om meerdere wegen te proberen tot het eindpunt is bereikt*/
    int i = 0, j = 0, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int x1, x2, y1, y2; /*Integers om coordinaten x en y tijdelijk op te slaan*/
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int punt[2]; /*Array met de coordinaten van het pad om terug te komen*/
    int skip = 0; /*Om de controle op buren over te slaan*/
    int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/
    int eindrichting = 0; /*Voor de laatste richting naar het eindstation*/
    int antwoord = 0; /*Reactie van de robot*/

    char vooruitchar=-127;
    char byteBuffer[BUFSIZ+1];

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




    /*In de array alle nummertjes groter dan 0 veranderen in een 0*/
    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (plattegrond[i][j] > 0)
            {
                plattegrond[i][j] = 0;
            }
        }
    }


    /****************
    /   Stations    *
    ****************/
    /*Coordinaten toewijzen*/
    switch(startpunt)
    {
    case 1 :
        startc[0] = 12;
        startc[1] = 4;
        vorigerichting = 2;
        break;
    case 2 :
        startc[0] = 12;
        startc[1] = 6;
        vorigerichting = 2;
        break;
    case 3 :
        startc[0] = 12;
        startc[1] = 8;
        vorigerichting = 2;
        break;
    case 4 :
        startc[0] = 8;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 5 :
        startc[0] = 6;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 6 :
        startc[0] = 4;
        startc[1] = 12;
        vorigerichting = 4;
        break;
    case 7 :
        startc[0] = 0;
        startc[1] = 8;
        vorigerichting = 1;
        break;
    case 8 :
        startc[0] = 0;
        startc[1] = 6;
        vorigerichting = 1;
        break;
    case 9 :
        startc[0] = 0;
        startc[1] = 4;
        vorigerichting = 1;
        break;
    case 10 :
        startc[0] = 4;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    case 11 :
        startc[0] = 6;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    case 12 :
        startc[0] = 8;
        startc[1] = 0;
        vorigerichting = 3;
        break;
    default :
        /*Foutmelding door onbekend startpunt*/
        printf("\nFATALE FOUT!\n");
        printf("\tOnbekend startpunt\n");
        /*Voorkom dat de handel vastloopt*/
        k = 100;
    }


    /*Coordinaten toewijzen*/
    switch(eindpunt)
    {
    case 1 :
        eindc[0] = 12;
        eindc[1] = 4;
        eindrichting = 1;
        break;
    case 2 :
        eindc[0] = 12;
        eindc[1] = 6;
        eindrichting = 1;
        break;
    case 3 :
        eindc[0] = 12;
        eindc[1] = 8;
        eindrichting = 1;
        break;
    case 4 :
        eindc[0] = 8;
        eindc[1] = 12;
        eindrichting = 3;
        break;
    case 5 :
        eindc[0] = 6;
        eindc[1] = 12;
        eindrichting = 3;
        break;
    case 6 :
        eindc[0] = 4;
        eindc[1] = 12;
        eindrichting = 3;
        break;
    case 7 :
        eindc[0] = 0;
        eindc[1] = 8;
        eindrichting = 2;
        break;
    case 8 :
        eindc[0] = 0;
        eindc[1] = 6;
        eindrichting = 2;
        break;
    case 9 :
        eindc[0] = 0;
        eindc[1] = 4;
        eindrichting = 2;
        break;
    case 10 :
        eindc[0] = 4;
        eindc[1] = 0;
        eindrichting = 4;
        break;
    case 11 :
        eindc[0] = 6;
        eindc[1] = 0;
        eindrichting = 4;
        break;
    case 12 :
        eindc[0] = 8;
        eindc[1] = 0;
        eindrichting = 4;
        break;
    default :
        /*Foutmelding door onbekend eindpunt*/
        printf("\nFATALE FOUT!\n");
        printf("\tOnbekend eindpunt\n");
        /*Voorkom dat de handel vastloopt*/
        k = 100;
    }






    /*******************
    / Rijden tot einde *
    *******************/

    /*Spring naar het eindpunt met de punt*/
    punt[0] = startc[0];
    punt[1] = startc[1];

    /*Startpunt afdrukken*/
    printf("Start vanaf station %d, richting het speelveld (%d)\n", startpunt, vorigerichting);




    while (klaar == 0)

    {

        /**********************
        / Nummertjes optellen *
        **********************/

        /*Beginnen aan een nieuwe ronde*/
        opnieuw = 0;
        k = 1;

        /*De bestemming krijgt waarde k, ofwel 1*/
        plattegrond[eindc[0]][eindc[1]] = k;

        /*Zolang de startpositie nog niet bereikt is*/
        while((plattegrond[startc[0]][startc[1]] == 0) && (k < 90))
        {
            /*Zoek naar waarde k*/
            for (i=0; i<13; i++)
            {
                for (j=0; j<13; j++)
                {
                    if(plattegrond[i][j] == k)
                    {
                        /*Buren zoeken*/
                        /*Buur 1*/
                        if (i <12)
                        {
                            if (plattegrond[i+1][j] == 0)
                            {
                                plattegrond[i+1][j] = k + 1;
                            }
                        }
                        /*Buur 2*/
                        if (i > 0)
                        {
                            if (plattegrond[i-1][j] == 0)
                            {
                                plattegrond[i-1][j] = k + 1;
                            }
                        }
                        /*Buur 3*/
                        if (j<12)
                        {
                            if (plattegrond[i][j+1] == 0)
                            {
                                plattegrond[i][j+1] = k + 1;
                            }
                        }
                        /*Buur 4*/
                        if (j > 0)
                        {
                            if (plattegrond[i][j-1] == 0)
                            {
                                plattegrond[i][j-1] = k + 1;
                            }
                        }
                    }
                }
            }


            /*De buur van de buur invullen*/
            k = k + 1;

            /*Als er geen route wordt gevonden*/
            if (k == 90)
            {
                printf("\nOPMERKING!\n");
                printf("\tEr is geen weg gevonden tussen station %d en %d\n", startpunt, eindpunt);
                klaar = 2;
            }
        }




        /*******************
        / Terugweg printen *
        *******************/
        if ((k < 90) && (opnieuw == 0))
        {

            /*Punt laten zoeken naar buur op een kruising*/


            while((k > 3) && (opnieuw == 0))
            {
                /*Voorkeursburen*/
                /*Voorkeursbuur 1*/
                if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]+2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (1) naar c%d%d\n\n", x2, y2);
                    writeByte(hSerial, &vooruitchar);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Voorkeursbuur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]-2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (2) naar c%d%d\n\n", x2, y2);
                    writeByte(hSerial, &vooruitchar);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Voorkeursbuur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]+2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (3) naar c%d%d\n\n", x2, y2);
                    writeByte(hSerial, &vooruitchar);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Voorkeursbuur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]-2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (4) naar c%d%d\n\n", x2, y2);
                    writeByte(hSerial, &vooruitchar);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] - 2;
                }





                /*Standaardlijstje buren*/
                /*Buur 1*/
                if ((skip == 0) && (punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]+2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    if (vorigerichting == 3)
                    {
                        /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                        printf("\nDraai rechtsom naar   (1) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "‚");
                    }
                    if (vorigerichting == 4)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (1) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "„");
                    }
                    k = k - 2;
                    vorigerichting = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Buur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]-2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    if (vorigerichting == 4)
                    {
                        /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                        printf("\nDraai rechtsom naar   (2) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "‚");
                    }
                    if (vorigerichting == 3)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (2) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "„");
                    }
                    k = k - 2;
                    vorigerichting = 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Buur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]+2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    if (vorigerichting == 2)
                    {
                        /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                        printf("\nDraai rechtsom naar   (3) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "‚");
                    }
                    if (vorigerichting == 1)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (3) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "„");
                    }
                    k = k - 2;
                    vorigerichting = 3;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Buur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]-2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    if (vorigerichting == 1)
                    {
                        /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                        printf("\nDraai rechtsom naar   (4) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "‚");
                    }
                    if (vorigerichting == 2)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (4) en ga naar c%d%d\n\n", x2, y2);
                        writeByte(hSerial, "„");
                    }
                    k = k - 2;
                    vorigerichting = 4;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] - 2;
                }


                if (skip == 0)
                {
                    printf("\nFATALE FOUT!\n");
                    printf("\tGeen buur kunnen vinden\n");
                    k = 0;
                }
                else
                {
                    skip = 0;
                }



                /***********************
                / Reactie van de robot *
                ***********************/

                /*Wachten op antwoord van de robot, voor nu scanf*/
                printf("Wachten op antwoord\n");
                while (antwoord != 2)
                {
                    antwoord=readByte(hSerial, byteBuffer);
                }
                if (antwoord == 1)
                {
                    printf("Robot goed aangekomen, weg vervolgen\n");
                }
                if (antwoord == 0)
                {
                    /*Bepaal het punt van de mijn*/
                    x1 = punt[1];
                    y1 = punt[0];
                    switch(vorigerichting)
                    {
                    case 1 :
                        punt[0] = punt[0] - 2;
                        y1 = y1 - 1;
                        vorigerichting = 2;
                        break;
                    case 2 :
                        punt[0] = punt[0] + 2;
                        y1 = y1 + 1;
                        vorigerichting = 1;
                        break;
                    case 3 :
                        punt[1] = punt[1] - 2;
                        x1 = x1 - 1;
                        vorigerichting = 4;
                        break;
                    case 4 :
                        punt[1] = punt[1] + 2;
                        x1 = x1 + 1;
                        vorigerichting = 3;
                        break;
                    }

                    /*Vertel waar de mijn ligt*/
                    printf("!!\tMijn gevonden op [%d;%d] in de array\n", x1, y1);

                    /*Omdraaien en geef het kruispunt wat de robot tegenkomt*/
                    x2 = (punt[1])/2 - 1;
                    y2 = 5 - (punt[0])/2;
                    printf("\nDraai volledig om (%d) naar c%d%d\n\n", vorigerichting, x2, y2);

                    /*Startpunt zetten naar het huidige punt*/
                    startc[0] = punt[0];
                    startc[1] = punt[1];

                    /*Geblokkeerde weg op -1 zetten*/
                    plattegrond[y1][x1] = -1;

                    /*In de array alle nummertjes groter dan 0 veranderen in een 0*/
                    for (i=0; i<13; i++)
                    {
                        for (j=0; j<13; j++)
                        {
                            if (plattegrond[i][j] > 0)
                            {
                                plattegrond[i][j] = 0;
                            }
                        }
                    }

                    /*Opnieuw de nummertjes invullen om daarna weer opnieuw een route te berekenen*/
                    opnieuw = 1;
                }

            }



            /*Laatste stap weergeven*/

            /*Dezelfde richting*/
            if (opnieuw == 0)
            {

                if (vorigerichting == eindrichting)
                {
                    printf("\nGa naar het eindpunt, rechtdoor (%d) naar station %d\n\n", eindrichting, eindpunt);
                    writeByte(hSerial, "Á");
                }

                /*Eerst draaien*/
                if (vorigerichting != eindrichting)
                {
                    if (eindrichting == 1)
                    {
                        if (vorigerichting == 3)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Â");
                        }
                        if (vorigerichting == 4)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Ä");
                        }
                    }

                    if (eindrichting == 2)
                    {
                        if (vorigerichting == 4)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Â");
                        }
                        if (vorigerichting == 3)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Ä");
                        }
                    }

                    if (eindrichting == 3)
                    {
                        if (vorigerichting == 2)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Â");
                        }
                        if (vorigerichting == 1)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Ä");
                        }
                    }

                    if (eindrichting == 4)
                    {
                        if (vorigerichting == 1)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Â");
                        }
                        if (vorigerichting == 2)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            writeByte(hSerial, "Ä");
                        }
                    }
                }

                klaar = 1;

            }

        }

    }

    if (klaar == 1)
    {
        printf("Bestemming bereikt\n");
        printf("Typ even een 1 om aan te geven dat je klaar bent om verder te gaan\n");
        scanf("%d", &antwoord);
        if (antwoord == 1)
        {
            writeByte(hSerial, "€");
            CloseHandle(hSerial);
        }
    }
}


int main()
{
    /*Eventjes geen communicatie*/
    int input[4]; /*Opslag input*/
    int perm[6]; /*Opslag weging routes*/
    int kortste = 0; /*Lengte kortste route*/
    int volgorde = 0; /*Volgorde stations bezoeken*/
    int i;

    printf("MAZE ROUTER V5\n\nVoer een station in waarbij de robot start, gevolgd door drie stations die\nbezocht moeten worden. Scheid alle stations met een spatie of enter tijdens\nhet invoerproces.\n\n");
    for(i = 0; i < 4; i++) /*Input opvragen*/
    {
        scanf("%d", &input[i]);
    }
    /*Alle routes tussen de stations berekenen en opslaan in de array perm*/
    perm[0] = loop(input[0],input[1]);
    perm[1] = loop(input[0],input[2]);
    perm[2] = loop(input[0],input[3]);
    perm[3] = loop(input[1],input[2]);
    perm[4] = loop(input[1],input[3]);
    perm[5] = loop(input[2],input[3]);

    /*Dit is voor debug doeleinden*/
    for(i = 0; i < 6; i++)
        printf("perm[%d] = %d\n", i, perm[i]);

    /*De korste route bepalen*/
    kortste = perm[0] + perm[3] + perm[5];
    if(perm[0] + perm[4] + perm[5] < kortste)
    {
        kortste = perm[0] + perm[4] + perm[5];
        volgorde = 1;
    }
    if(perm[1] + perm[3] + perm[4] < kortste)
    {
        kortste = perm[1] + perm[3] + perm[4];
        volgorde = 2;
    }
    if(perm[1] + perm[5] + perm[4] < kortste)
    {
        kortste = perm[1] + perm[5] + perm[4];
        volgorde = 3;
    }
    if(perm[2] + perm[4] + perm[3] < kortste)
    {
        kortste = perm[2] + perm[4] + perm[3];
        volgorde = 4;
    }
    if(perm[2] + perm[5] + perm[3] < kortste)
    {
        kortste = perm[2] + perm[5] + perm[3];
        volgorde = 5;
    }


    /*De kortste volgorde*/
    switch(volgorde)
    {
    case 0 :
        /*Volgorde 0 1 2 3*/
        route(input[0], input[1]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[1], input[2]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[2], input[3]);
        printf("\nAlle stations bezocht\n");
        break;
    case 1 :
        /*Volgorde 0 1 3 2*/
        route(input[0], input[1]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[1], input[3]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[3], input[2]);
        printf("\nAlle stations bezocht\n");
        break;
    case 2 :
        /*Volgorde 0 2 1 3*/
        route(input[0], input[2]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[2], input[1]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[1], input[3]);
        printf("\nAlle stations bezocht\n");
        break;
    case 3 :
        /*Volgorde 0 2 3 1*/
        route(input[0], input[2]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[2], input[3]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[3], input[1]);
        printf("\nAlle stations bezocht\n");
        break;
    case 4 :
        /*Volgorde 0 3 1 2*/
        route(input[0], input[3]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[3], input[1]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[1], input[2]);
        printf("\nAlle stations bezocht\n");
        break;
    case 5 :
        /*Volgorde 0 3 2 1*/
        route(input[0], input[3]);
        printf("\nDraai volledig om richting het speelveld en\n");
        route(input[3], input[2]);
        printf("\nDraai volledig om richting het speelveld\n");
        route(input[2], input[1]);
        printf("\nAlle stations bezocht\n");
        break;
    }
    return 0;

}
