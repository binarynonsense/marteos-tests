/*---------------------------------------------------------------------------
-- Elapsed Time Loop Test                                                  --
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
-- last update: 28 Aug 2014                                                --
---------------------------------------------------------------------------*/

#include <stdio.h> // printf
#include <time.h>  // timespec

double TimespecDiff(struct timespec start, struct timespec end);

int main()
{
  
  double elapsedTime = 0;
  struct timespec timeLastFrame, timeCurrentFrame;  
  
  clock_gettime(CLOCK_REALTIME, &timeLastFrame);
  
  while(1)
  {
    clock_gettime(CLOCK_REALTIME, &timeCurrentFrame);
    elapsedTime += TimespecDiff(timeLastFrame, timeCurrentFrame);
    // UPDATE FRAME /////////////////////////////////////////////
    
    printf("time elapsed: %8.9f \n", elapsedTime);
    
    // END UPDATE FRAME /////////////////////////////////////////    
    timeLastFrame = timeCurrentFrame;
  }

  return 0;
}

double TimespecDiff(struct timespec start, struct timespec end)
{
  double startSecs = start.tv_sec + start.tv_nsec / 1000000000.0;
  double endSecs = end.tv_sec + end.tv_nsec / 1000000000.0;
  return endSecs - startSecs;
}

/*
 
timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
*/