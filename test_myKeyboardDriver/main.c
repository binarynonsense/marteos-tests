/*---------------------------------------------------------------------------
-- My Keyboard Driver                                                      --
-----------------------------------------------------------------------------
--                                                                         --
-- A test for MaRTE OS.                                                    --
--                                                                         --
-- author: Alvaro Garcia Cuesta                                            --
-- email: alvaro@binarynonsense.com                                        --
-- website: www.binarynonsense.com                                         --
--                                                                         --
-- file: main.c                                                            --
--                                                                         --
-- this file contains the main logic of the test                           --
-----------------------------------------------------------------------------
-- License                                                                 --
-----------------------------------------------------------------------------
--                                                                         --
-- This is free software; you can redistribute it and/or modify it         --
-- under the terms of the GNU General Public License version 2 as          --
-- published by the Free Software Foundation.                              --
-- See COPYING file for more info about the license                        --
--                                                                         --
-----------------------------------------------------------------------------
-- last update: 29 Aug 2014                                                --
---------------------------------------------------------------------------*/

#include <intr.h>  // may need to add CPP_BEGIN_DECLS & CPP_END_DECLS in intr.h when using with mg++
#include <stdio.h>
#include <sys/pio.h>
#include <time.h>   // timespec, nanosleep
#include <misc/timespec_operations.h>  // double_to_timespec

unsigned char pressedKeys[128] = {0};

double deltaTime;
struct timespec timeLastFrame, timeCurrentFrame;
double TimespecDiff(struct timespec start, struct timespec end);

static int gamingKBD_irq_handler (void *area, intr_t irq)
{
    unsigned char scancode = inb(0x60);
    
    if (scancode & 0x80)
    {//key released
        //printf("%d",scancode);
        pressedKeys[scancode - 128] = 0;
    }
    else
    {//key pressed
        //printf("%d",scancode);
        pressedKeys[scancode] = 1;
    }
    //printf("algo\n");
    //return POSIX_INTR_HANDLED_NOTIFY;
    //return POSIX_INTR_HANDLED_DO_NOT_NOTIFY;
    return 0;
}

void Test1();
void Test2();

int main()
{
    posix_intr_associate(KEYBOARD_HWINTERRUPT, gamingKBD_irq_handler, ((void *)0), 0); //((void *)0)==NULL
    //posix_intr_unlock (KEYBOARD_HWINTERRUPT);
    
    clock_gettime(CLOCK_REALTIME, &timeLastFrame);
    
    printf("start test:\n");
    Test2();
    //Test1();
    
    return 0;
}

void Test2()
{
    float timeSinceLast = 0;
    //unsigned char lastKeyPressed = 129;
    
    while(1)
    {        
        clock_gettime(CLOCK_REALTIME, &timeCurrentFrame);
        deltaTime = TimespecDiff(timeLastFrame, timeCurrentFrame);
        // UPDATE FRAME /////////////////////////////////////////////
        
        timeSinceLast += deltaTime;
        
        if(timeSinceLast > 1)
        {
            timeSinceLast = 0;
            int i;
            int pressed = 129;
            for(i = 0; i < 128; i++)
            {
                if(pressedKeys[i])
                {
                    pressed = i;
                    break;
                }
            }
            
            if(pressed != 129)
            {
                printf("Key number %d is pressed\n", pressed);
            }
        }

        // END UPDATE FRAME /////////////////////////////////////////    
        timeLastFrame = timeCurrentFrame; 
    }   
    
    // Note: same strange behabiour with the arrows like in Test1
}

void Test1()
{
    /* Strange: the arrows print a number on screen even if I don't make a print */
    
    while(1)
    {        
        clock_gettime(CLOCK_REALTIME, &timeCurrentFrame);
        deltaTime = TimespecDiff(timeLastFrame, timeCurrentFrame);
        // UPDATE FRAME /////////////////////////////////////////////

        if(pressedKeys[72])
        {            
            printf("UP\n");
        }
        if(pressedKeys[75])
        {            
            printf("LEFT\n");
        }

        // END UPDATE FRAME /////////////////////////////////////////    
        timeLastFrame = timeCurrentFrame; 
    }
}

double TimespecDiff(struct timespec start, struct timespec end)
{
  double startSecs = start.tv_sec + start.tv_nsec / 1000000000.0;
  double endSecs = end.tv_sec + end.tv_nsec / 1000000000.0;
  return endSecs - startSecs;
}
