/*
 * main.c
 *
 *  Copyright (C) 2014 Marco Scholtyssek <code@scholtyssek.org>
 *
 */
#include <stdlib.h>
#include "xboxController.h"

int main(int argc, char **argv)
{
    printf("Initializing... Poop\n\n");

    int n=0;
    if (initXboxContoller(XBOX_DEVICE) >= 0)
    {
        xboxCtrl* xbox = getXboxDataStruct();
        readXboxControllerInformation(xbox);

        printf("xbox controller detected\n\naxis:\t\t%d\nbuttons:\t%d\nidentifier:\t%s\n",
               xbox->numOfAxis, xbox->numOfButtons, xbox->identifier);

        sleep(1); //Required in order to reset buttons on quit.

        printf("Ready.\n");

        while (1)
        {
            if (n==10000) // Reduce the sample rate.
            {
                n=0;
                readXboxData(xbox);
                if (xbox->btn_start >=1) //Here's the crux of it.
                {
                    printf("%d",xbox->btn_start);
                }

                if (xbox->btn_xbox ==1)
                {
                    printf("QUIT");
                    break;
                }
                //printXboxCtrlValues(xbox);}
            }

            else n+=1;
        }
        deinitXboxController(xbox);
        return 0;
    }
    else sleep(1);
}
