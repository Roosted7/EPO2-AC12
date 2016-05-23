
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
        if (stationsbereikt == 0)
        {
            vorigerichting = 2;
        }
        break;
    case 2 :
        startc[0] = 12;
        startc[1] = 6;
        if (stationsbereikt == 0)
        {
            vorigerichting = 2;
        }
        break;
    case 3 :
        startc[0] = 12;
        startc[1] = 8;
        if (stationsbereikt == 0)
        {
            vorigerichting = 2;
        }
        break;
    case 4 :
        startc[0] = 8;
        startc[1] = 12;
        if (stationsbereikt == 0)
        {
            vorigerichting = 4;
        }
        break;
    case 5 :
        startc[0] = 6;
        startc[1] = 12;
        if (stationsbereikt == 0)
        {
            vorigerichting = 4;
        }
        break;
    case 6 :
        startc[0] = 4;
        startc[1] = 12;
        if (stationsbereikt == 0)
        {
            vorigerichting = 4;
        }
        break;
    case 7 :
        startc[0] = 0;
        startc[1] = 8;
        if (stationsbereikt == 0)
        {
            vorigerichting = 1;
        }
        break;
    case 8 :
        startc[0] = 0;
        startc[1] = 6;
        if (stationsbereikt == 0)
        {
            vorigerichting = 1;
        }
        break;
    case 9 :
        startc[0] = 0;
        startc[1] = 4;
        if (stationsbereikt == 0)
        {
            vorigerichting = 1;
        }
        break;
    case 10 :
        startc[0] = 4;
        startc[1] = 0;
        if (stationsbereikt == 0)
        {
            vorigerichting = 3;
        }
        break;
    case 11 :
        startc[0] = 6;
        startc[1] = 0;
        if (stationsbereikt == 0)
        {
            vorigerichting = 3;
        }
        break;
    case 12 :
        startc[0] = 8;
        startc[1] = 0;
        if (stationsbereikt == 0)
        {
            vorigerichting = 3;
        }
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
