
#include <stdio.h>
#include <stdlib.h>

#include "support.c"

/*  Verhouding tijd bocht vs rechtdoor  */
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


int distance(int startpunt, int eindpunt)   {

    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/

    startc[0] = yPos(startpunt);
    startc[1] = xPos(startpunt);
    vorigerichting = richtingStationBegin(startpunt);

    eindc[0] = yPos(eindpunt);
    eindc[1] = xPos(eindpunt);

    return routeLength(startc, eindc, vorigerichting);
}


void route(int startpunt, int eindpunt) {
    /****************
    /   OPSTARTEN   *
    ****************/

    int klaar = 0, opnieuw = 0; /*Om meerdere wegen te proberen tot het eindpunt is bereikt*/
    int i, j, x1, y1, x2, y2, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int punt[2]; /*Array met de coordinaten van het pad om terug te komen*/
    int skip = 0; /*Om de controle op buren over te slaan*/
    int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/
    int eindrichting = 0; /*Voor de laatste richting naar het eindstation*/
    int antwoord = 0; /*Reactie van de robot*/

    startc[0] = yPos(startpunt);
    startc[1] = xPos(startpunt);
    vorigerichting = richtingStationBegin(startpunt);

    eindc[0] = yPos(eindpunt);
    eindc[1] = xPos(eindpunt);
    eindrichting = richtingStationHalverwege(eindpunt);

    punt[0] = startc[0];
    punt[1] = startc[1];

    /*Startpunt afdrukken*/
    printf("Start vanaf station %d, richting het speelveld (%d)\n", startpunt, vorigerichting);




    while (klaar == 0)

    {
 
        /*Beginnen aan een nieuwe ronde*/
        opnieuw = 0;

        vulPlattegrond(startc, eindc);

        k = plattegrond[startc[0]][startc[1]];


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
                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (1) naar c%d%d\n\n", punt[0]+2, punt[1]);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Voorkeursbuur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
                {
                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (2) naar c%d%d\n\n", punt[0]-2, punt[1]);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Voorkeursbuur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
                {
                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (3) naar c%d%d\n\n", punt[0], punt[1]+2);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Voorkeursbuur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
                {
                    /*Print dit plekje*/
                    printf("\nDraai niet, rechtdoor (4) naar c%d%d\n\n", punt[0], punt[1]-2);
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] - 2;
                }





                /*Standaardlijstje buren*/
                /*Buur 1*/
                if ((skip == 0) && (punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1))
                {
                    /*Print dit plekje*/
                    if (vorigerichting == 3)
                        printf("\nDraai rechtsom naar   (1) en ga naar c%d%d\n\n", punt[0]+2, punt[1]); /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                    if (vorigerichting == 4)
                        printf("\nDraai linksom naar    (1) en ga naar c%d%d\n\n", punt[0]+2, punt[1]); /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/ /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/

                    k = k - 2;
                    vorigerichting = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Buur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1))
                {
                    /*Print dit plekje*/
                    if (vorigerichting == 4)
                        printf("\nDraai rechtsom naar   (2) en ga naar c%d%d\n\n", punt[0]-2, punt[1]);      /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/
                    if (vorigerichting == 3)
                        printf("\nDraai linksom naar    (2) en ga naar c%d%d\n\n", punt[0]-2, punt[1]);     /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/

                    k = k - 2;
                    vorigerichting = 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Buur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1))
                {
                    /*Print dit plekje*/
                    if (vorigerichting == 2)
                        printf("\nDraai rechtsom naar   (3) en ga naar c%d%d\n\n", punt[0], punt[1]+2);
                    if (vorigerichting == 1)
                        printf("\nDraai linksom naar    (3) en ga naar c%d%d\n\n", punt[0], punt[1]+2);
                    k = k - 2;
                    vorigerichting = 3;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Buur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1))
                {
                    /*Print dit plekje*/
                    if (vorigerichting == 1)
                        printf("\nDraai rechtsom naar   (4) en ga naar c%d%d\n\n", punt[0], punt[1]-2); /*Rechtsom draaien/ rechtsaf slaan/ rechterwiel stil*/

                    if (vorigerichting == 2)
                        printf("\nDraai linksom naar    (4) en ga naar c%d%d\n\n", punt[0], punt[1]-2);      /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                    
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
                scanf("%d", &antwoord);
                /* 1  Goed aangekomen */
                /* 0  Mijn gedetecteerd */
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

                    nulPlattegrond();

                    /*Opnieuw de nummertjes invullen om daarna weer opnieuw een route te berekenen*/
                    opnieuw = 1;
                }

            }



            /*Laatste stap weergeven*/

            /*Dezelfde richting*/
            if (opnieuw == 0)
            {

                if (vorigerichting == eindrichting)
                    printf("\nGa naar het eindpunt, rechtdoor (%d) naar station %d\n\n", eindrichting, eindpunt);

                /*Eerst draaien*/
                if (vorigerichting != eindrichting)
                {
                    if (eindrichting == 1)
                    {
                        if (vorigerichting == 3)
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                        if (vorigerichting == 4)
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                    }

                    if (eindrichting == 2)
                    {
                        if (vorigerichting == 4)
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                        if (vorigerichting == 3)
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                    }

                    if (eindrichting == 3)
                    {
                        if (vorigerichting == 2)
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                        if (vorigerichting == 1)
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                    }

                    if (eindrichting == 4)
                    {
                        if (vorigerichting == 1)
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                        if (vorigerichting == 2)
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                    }
                }

                klaar = 1;

            }

        }

    }

    if (klaar == 1)
    {
        printf("Bestemming bereikt\n");
    }
}


int readInput () {

    int rawInput[4], input[4][3], i;

    for(i = 0; i < 4; i++) {

        scanf("%d", &rawInput[i]);

        if (rawInput[i] > -1 && rawInput[1] < 13) {
            input[i][0] = yPos(rawInput[i]);
            input[i][1] = xPos(rawInput[i]);
            input[i][2] = richtingStationHalverwege(rawInput[i]);
            if (i == 0)
                input[i][2] = richtingStationBegin(rawInput[i]);

        } else {
            printf("Please check your input!");
        }
    }

    return   
}

int main()
{
    int rawInput[4], input[4][3] i, volgorde; /*Opslag input*/

    printf("MAZE ROUTER V5\n\nVoer een station in waarbij de robot start, gevolgd door drie stations die \n
        bezocht moeten worden. Scheid alle stations met een spatie of enter tijdens \n
        het invoerproces.\n\n");

    volgorde = bepaalVolgorde(readInput());



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
