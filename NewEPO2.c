/*MAZE ROUTER V6
  Hetzelfde als de Maze Router v5, maar nu zal de robot ook achteruit gaan rijden als dat beter uitkomt
*/


#include <stdio.h>
#include <stdlib.h>

/*Specificeer hieronder de verhouding in tijd die het kost om rechtdoor te rijden tegen het nemen van een bocht*/
#define BOCHTWEGING 2
#define WEGENWEGING 1

/*Globale variabelen*/
int stationsbereikt = 0;
int achteruit = 0;
int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/
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


int xPos (int punt) {

    if (punt == 10 || punt == 11 || punt == 12)
        return 0;
    if (punt == 1 || punt == 9)
        return 4;
    if (punt == 2 || punt == 8)
        return 6;
    if (punt == 3 || punt == 7)
        return 8;
    if (punt == 4 || punt == 5 || punt == 6)
        return 12;
    return 99;
}

int yPos (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 12;
    if (punt == 4 || punt == 12)    
        return 8;
    if (punt == 5 || punt == 11)
        return 6;
    if (punt == 6 || punt == 10)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 0;
    return 99;
}

int richtingStationBegin (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 2;
    if (punt == 4 || punt == 5 || punt == 6)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 1;
    if (punt == 10 || punt == 11 || punt == 12)
        return 3;
    return 99;
}

int richtingStationHalverwege (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 1;
    if (punt == 4 || punt == 5 || punt == 6)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 2;
    if (punt == 10 || punt == 11 || punt == 12)
        return 4;
    return 99;
}

void nulPlattegrond () {
    int i, j;
    
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
}

void vulPlattegrond(int startc[], int eindc[]) {

    int i, j, k;

    nulPlattegrond();

    /*De bestemming krijgt waarde i, ofwel 1*/
    plattegrond[eindc[0]][eindc[1]] = 1;

    /*Zolang de startpositie nog niet bereikt is*/
    for (k = 1; (plattegrond[startc[0]][startc[1]] == 0) && (k < 90); k++) {
        for (i=0; i<13; i++) {
            for (j=0; j<13; j++) {
                if(plattegrond[i][j] == k)
                {
                    if (i < 12 && plattegrond[i+1][j] == 0)
                            plattegrond[i+1][j] = k + 1;

                    if (i > 0 && plattegrond[i-1][j] == 0)
                            plattegrond[i-1][j] = k + 1;

                    if (j < 12 && plattegrond[i][j+1] == 0)
                            plattegrond[i][j+1] = k + 1;

                    if (j > 0 && plattegrond[i][j-1] == 0)
                            plattegrond[i][j-1] = k + 1;
                }
            }
        }
    }
}




int routeLength (int startc[]) {

    int k, rechten = 0, bochten = 0, punt[2];

    k = plattegrond[startc[0]][startc[1]];

    if (k < 90)
    {
        /*Spring naar het eindpunt met de punt*/
        punt[0] = startc[0];
        punt[1] = startc[1];
        while(k > 3)
        {
            if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1))
            {
                rechten++;
                k = k - 2;
                punt[0] = punt[0] + 2;
            }
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
            {
                rechten++;
                k = k - 2;
                punt[0] = punt[0] - 2;
            }
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
            {
                rechten++;
                k = k - 2;
                punt[1] = punt[1] + 2;
            }
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
            {
                rechten++;
                k = k - 2;
                punt[1] = punt[1] - 2;
            }
            else if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 1;
                punt[0] = punt[0] + 2;
            }
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 2;
                punt[0] = punt[0] - 2;
            }
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 3;
                punt[1] = punt[1] + 2;
            }
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 4;
                punt[1] = punt[1] - 2;
            }
        }
    }
    return (BOCHTWEGING*bochten + WEGENWEGING*rechten);

}


void checkPoints (int startpunt, int eindpunt) {

    if (xPos(startpunt) == 99 || xPos(eindpunt) == 99) {
        printf("\tOnbekend start- of eindpunt\n");
        exit(0);
    }
}


int startFromStation(int startpunt, int eindpunt)
{
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int vorigerichting = 0, lengte; /*Om zo min mogelijk bochten te maken in de route*/
    

    checkPoints(startpunt, eindpunt);

    startc[0] = yPos(startpunt);
    startc[1] = xPos(startpunt);
    vorigerichting = richtingStationBegin(startpunt);

    eindc[0] = yPos(eindpunt);
    eindc[1] = xPos(eindpunt);


    vulPlattegrond(startc, eindc);

    /*Lengte terugsturen*/
    return routeLength(startc);;
}




void route(int startpunt, int eindpunt)
{
    /**************************
    /   OPSTARTEN EINDROUTE   *
    **************************/

    int klaar = 0, opnieuw = 0; /*Om meerdere wegen te proberen tot het eindpunt is bereikt*/
    int i = 0, j = 0, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int x1, x2, y1, y2; /*Integers om coordinaten x en y tijdelijk op te slaan*/
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int punt[2]; /*Array met de coordinaten van het pad om terug te komen*/
    int skip = 0; /*Om de controle op buren over te slaan*/
    int eindrichting = 0; /*Voor de laatste richting naar het eindstation*/
    int antwoord = 0; /*Reactie van de robot*/


    checkPoints(startpunt, eindpunt);


    startc[0] = yPos(startpunt);
    startc[1] = xPos(startpunt);

    if (!stationsbereikt)
        vorigerichting = richtingStationBegin(startpunt);

    eindc[0] = yPos(eindpunt);
    eindc[1] = xPos(eindpunt);
    eindrichting = richtingStationHalverwege (startpunt);




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


    /*******************
    / Rijden tot einde *
    *******************/

    /*Spring naar het eindpunt met de punt*/
    punt[0] = startc[0];
    punt[1] = startc[1];

    /*Startpunt afdrukken*/
    if (stationsbereikt == 0)
    {
        printf("\nStart vanaf station %d, richting het speelveld (%d)\n", startpunt, vorigerichting);
        achteruit = 0;
    }
    else
    {
        printf("\nStart vanaf station %d in richting (%d)\n", startpunt, vorigerichting);
    }



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
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] - 2;
                }




                /*Achterstevoorkeursburen*/
                /*Achterstevoorkeursbuur 1*/
                if ((skip == 0) && (punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 2))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]+2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, achteruit (1) naar c%d%d\n\n", x2, y2);
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Achterstevoorkeursbuur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 1))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1];
                    y1 = punt[0]-2;
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, achteruit (2) naar c%d%d\n\n", x2, y2);
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Achterstevoorkeursbuur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 4))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]+2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, achteruit (3) naar c%d%d\n\n", x2, y2);
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Achterstevoorkeursbuur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 3))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                    x1 = punt[1]-2;
                    y1 = punt[0];
                    x2 = (x1)/2 - 1;
                    y2 = 5 - (y1)/2;

                    /*Print dit plekje*/
                    printf("\nDraai niet, achteruit (4) naar c%d%d\n\n", x2, y2);
                    k = k - 2;
                    achteruit = 1;
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
                    }
                    if (vorigerichting == 4)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (1) en ga naar c%d%d\n\n", x2, y2);
                    }
                    k = k - 2;
                    achteruit = 0;
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
                    }
                    if (vorigerichting == 3)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (2) en ga naar c%d%d\n\n", x2, y2);
                    }
                    k = k - 2;
                    achteruit = 0;
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
                    }
                    if (vorigerichting == 1)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (3) en ga naar c%d%d\n\n", x2, y2);
                    }
                    k = k - 2;
                    achteruit = 0;
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
                    }
                    if (vorigerichting == 2)
                    {
                        /*Linksom draaien/ linksaf slaan/ linkerwiel stil*/
                        printf("\nDraai linksom naar    (4) en ga naar c%d%d\n\n", x2, y2);
                    }
                    k = k - 2;
                    achteruit = 0;
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
                    if (achteruit == 0)
                        {
                    switch(vorigerichting)
                    {
                    case 1 :
                        punt[0] = punt[0] - 2;
                        y1 = y1 - 1;
                        break;
                    case 2 :
                        punt[0] = punt[0] + 2;
                        y1 = y1 + 1;
                        break;
                    case 3 :
                        punt[1] = punt[1] - 2;
                        x1 = x1 - 1;
                        break;
                    case 4 :
                        punt[1] = punt[1] + 2;
                        x1 = x1 + 1;
                        break;
                    }

                    /*Vertel waar de mijn ligt*/
                    printf("!!\tMijn gevonden op [%d;%d] in de array\n", x1, y1);

                    /*Omdraaien en geef het kruispunt wat de robot tegenkomt*/
                    x2 = (punt[1])/2 - 1;
                    y2 = 5 - (punt[0])/2;
                    printf("\nRij achteruit (%d) naar c%d%d\n\n", vorigerichting, x2, y2);
                        }



                    else
                    {
                        switch(vorigerichting)
                    {
                    case 2 :
                        punt[0] = punt[0] - 2;
                        y1 = y1 - 1;
                        break;
                    case 1 :
                        punt[0] = punt[0] + 2;
                        y1 = y1 + 1;
                        break;
                    case 4 :
                        punt[1] = punt[1] - 2;
                        x1 = x1 - 1;
                        break;
                    case 3 :
                        punt[1] = punt[1] + 2;
                        x1 = x1 + 1;
                        break;
                    }

                    /*Vertel waar de mijn ligt*/
                    printf("!!\tMijn gevonden op [%d;%d] in de array\n", x1, y1);

                    /*Omdraaien en geef het kruispunt wat de robot tegenkomt*/
                    x2 = (punt[1])/2 - 1;
                    y2 = 5 - (punt[0])/2;
                    printf("\nRij vooruit (%d) naar c%d%d\n\n", vorigerichting, x2, y2);
                    }


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
                }

                /*Eerst draaien*/
                if (vorigerichting != eindrichting)
                {
                    if (eindrichting == 1)
                    {
                        if (vorigerichting == 3)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 4)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 2)
                        {
                            printf("\nRij achteruit naar    (%d) naar het eindpunt, station %d\n\n", vorigerichting, eindpunt);
                        }
                    }

                    if (eindrichting == 2)
                    {
                        if (vorigerichting == 4)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 3)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 1)
                        {
                            printf("\nRij achteruit naar    (%d) naar het eindpunt, station %d\n\n", vorigerichting, eindpunt);
                        }
                    }

                    if (eindrichting == 3)
                    {
                        if (vorigerichting == 2)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 1)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 4)
                        {
                            printf("\nRij achteruit naar    (%d) naar het eindpunt, station %d\n\n", vorigerichting, eindpunt);
                        }
                    }

                    if (eindrichting == 4)
                    {
                        if (vorigerichting == 1)
                        {
                            printf("\nDraai rechtsom naar   (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 2)
                        {
                            printf("\nDraai linksom naar    (%d) naar het eindpunt, station %d\n\n", eindrichting, eindpunt);
                            vorigerichting = eindrichting;
                        }
                        if (vorigerichting == 3)
                        {
                            printf("\nRij achteruit naar    (%d) naar het eindpunt, station %d\n\n", vorigerichting, eindpunt);
                        }
                    }
                }

                klaar = 1;
                stationsbereikt = stationsbereikt + 1;

            }

        }

    }

    if (klaar == 1)
    {
        printf("\n\tBestemming bereikt\n\n");
    }
}


int main()
{
    int input[4]; /*Opslag input*/
    int perm[6]; /*Opslag weging routes*/
    int kortste = 0; /*Lengte kortste route*/
    int volgorde = 0; /*Volgorde stations bezoeken*/
    int i;


    /*  Read input,
        calculate routes in array, 
        send array - while listening */

    printf("Voer een station in waarbij de robot start, gevolgd door drie stations die\nbezocht moeten worden. Scheid alle stations met een spatie of enter tijdens\nhet invoerproces.\n\n");
    
    for(i = 0; i < 4; i++) /*Input opvragen*/
        scanf("%d", &input[i]);

    /*Alle routes tussen de stations berekenen en opslaan in de array perm*/
    perm[0] = startFromStation(input[0],input[1]);
    perm[1] = startFromStation(input[0],input[2]);
    perm[2] = startFromStation(input[0],input[3]);
    perm[3] = startFromStation(input[1],input[2]);
    perm[4] = startFromStation(input[1],input[3]);
    perm[5] = startFromStation(input[2],input[3]);

    /*De korste route bepalen*/
    kortste = perm[0] + perm[3] + perm[5];

    if(perm[0] + perm[4] + perm[5] < kortste) {
        kortste = perm[0] + perm[4] + perm[5];
        volgorde = 1;
    }
    if(perm[1] + perm[3] + perm[4] < kortste) {
        kortste = perm[1] + perm[3] + perm[4];
        volgorde = 2;
    }
    if(perm[1] + perm[5] + perm[4] < kortste) {
        kortste = perm[1] + perm[5] + perm[4];
        volgorde = 3;
    }
    if(perm[2] + perm[4] + perm[3] < kortste) {
        kortste = perm[2] + perm[4] + perm[3];
        volgorde = 4;
    }
    if(perm[2] + perm[5] + perm[3] < kortste) {
        kortste = perm[2] + perm[5] + perm[3];
        volgorde = 5;
    }


    /*De kortste volgorde*/
    switch(volgorde)
    {
    case 0 :
        /*Volgorde 0 1 2 3*/
        route(input[0], input[1]);
        route(input[1], input[2]);
        route(input[2], input[3]);
        break;
    case 1 :
        /*Volgorde 0 1 3 2*/
        route(input[0], input[1]);
        route(input[1], input[3]);
        route(input[3], input[2]);
        break;
    case 2 :
        /*Volgorde 0 2 1 3*/
        route(input[0], input[2]);
        route(input[2], input[1]);
        route(input[1], input[3]);
        break;
    case 3 :
        /*Volgorde 0 2 3 1*/
        route(input[0], input[2]);
        route(input[2], input[3]);
        route(input[3], input[1]);
        break;
    case 4 :
        /*Volgorde 0 3 1 2*/
        route(input[0], input[3]);
        route(input[3], input[1]);
        route(input[1], input[2]);
        break;
    case 5 :
        /*Volgorde 0 3 2 1*/
        route(input[0], input[3]);
        route(input[3], input[2]);
        route(input[2], input[1]);
        break;
    }

    printf("\n\n\tAlle %d stations bezocht\n\n", stationsbereikt);
    return 0;

}

