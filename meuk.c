
void route(int startpunt, int eindpunt)
{
    /**************************
    /   OPSTARTEN EINDROUTE   *
    **************************/

    int klaar = 0, opnieuw = 0; /*Om meerdere wegen te proberen tot het eindpunt is bereikt*/
    int i = 0, j = 0, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int x1, x2, y1, y2; /*Integers om coordinaten x en y tijdelijk op te slaan*/
    int startC[3]; /*Array met startpuntcoordinaten*/
    int eindC[3]; /*Array met eindpuntcoordinaten*/
    int huidigC[3]; /*Array met de coordinaten van het pad om terug te komen*/
    int skip = 0; /*Om de controle op buren over te slaan*/
    int eindRichting = 0; /*Voor de laatste richting naar het eindstation*/
    int antwoord = 0; /*Reactie van de robot*/
    int fromStation = 1;

    /* INSERT maak alles boven 0, een 0 */


    /****************
    /   Stations    *
    ****************/
    /*Coordinaten en richtingen toewijzen*/
    if (fromStation) {
        if (stationBreikt) {
            startC[3] = {xPos(punt), yPos(punt), richtingStationBegin(punt)};
        } else 
            startC[3] = {xPos(punt), yPos(punt), richtingSationHalverwege(punt)};
        }
        eindC[3]  = {xPos(punt), yPos(punt), richtingStationHalverwege(punt)};
    }

    huidigC[3] = startc[0];
    punt[1] = startc[1];

    /*Startpunt afdrukken*/
    if (stationsbereikt == 0)
        achteruit = 0;

    printf("\nStart vanaf station %d in richting (%d)\n", startpunt, vorigerichting);



    while (klaar == 0)

    {

        /*********************\
        | Nummertjes optellen |
        \*********************/

        /*Beginnen aan een nieuwe ronde*/
        opnieuw = 0;
        


       /* INSERT HERE vul de plattegrond met nummertjes */




        /*******************
        / Terugweg printen *
        *******************/

            /*Punt laten zoeken naar buur op een kruising*/


            while((k > 3) && (opnieuw == 0))
            {
                /*Voorkeursburen*/
                /*Voorkeursbuur 1*/
                if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1))
                {
                    
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Voorkeursbuur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
                {
                    /*Reken dat plekje om naar de skrale notatie*/
                  
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Voorkeursbuur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
                {
                
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Voorkeursbuur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
                {
                   
                    k = k - 2;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] - 2;
                }




                /*Achterstevoorkeursburen*/
                /*Achterstevoorkeursbuur 1*/
                if ((skip == 0) && (punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 2))
                {
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] + 2;
                }
                /*Achterstevoorkeursbuur 2*/
                if ((skip == 0) && (punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 1))
                {
                   
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[0] = punt[0] - 2;
                }
                /*Achterstevoorkeursbuur 3*/
                if ((skip == 0) && (punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 4))
                {
                    
                    k = k - 2;
                    achteruit = 1;
                    skip = 1;

                    /*Punt doorschuiven*/
                    punt[1] = punt[1] + 2;
                }
                /*Achterstevoorkeursbuur 4*/
                if ((skip == 0) && (punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 3))
                {
                    
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
                   
                    if (vorigerichting == 3)
                        printf("\nDraai rechtsom naar   (1) en ga naar c%d%d\n\n", x2, y2);
                    
                    if (vorigerichting == 4)
                        printf("\nDraai linksom naar    (1) en ga naar c%d%d\n\n", x2, y2);

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
                   
                    /*Print dit plekje*/
                    if (vorigerichting == 4)
                        printf("\nDraai rechtsom naar   (2) en ga naar c%d%d\n\n", x2, y2);

                    if (vorigerichting == 3)
                        printf("\nDraai linksom naar    (2) en ga naar c%d%d\n\n", x2, y2);

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

                    if (vorigerichting == 2)
                        printf("\nDraai rechtsom naar   (3) en ga naar c%d%d\n\n", x2, y2);
                    
                    if (vorigerichting == 1)
                        printf("\nDraai linksom naar    (3) en ga naar c%d%d\n\n", x2, y2);

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
                   
                    if (vorigerichting == 1)
                        printf("\nDraai rechtsom naar   (4) en ga naar c%d%d\n\n", x2, y2);
                    
                    if (vorigerichting == 2)
                        printf("\nDraai linksom naar    (4) en ga naar c%d%d\n\n", x2, y2);
                    
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


    if (klaar == 1)
    {
        printf("\n\tBestemming bereikt\n\n");
    }
}
