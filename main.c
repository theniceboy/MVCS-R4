//
//  main.c
//  Robot Code
//
//  Created by Tristan Taylor on 11/6/17.
//  Copyright © 2017 Tristan Taylor. All rights reserved.
//

#include <stdio.h>
#include <math.h>
const int threshhold = 10;
int mult = 1;

task speedToggl{
    while (true){
        if(vexRT[btn7D]){
            if(mult == 2){
                    mult = 1;
            } else {
                mult = 2;
            }
            if(vexRT[btn7D]){
                wait1MSec(1);
            }
        }
        endTimeSlice();
    }
}


task main {
    while (true){
        int rmtrs = 0;
        int lmtrs = 0;
        int x = vexRT[Ch3];
        int y = vexRT[Ch4];
        if(x < 0){
            rmtrs += abs(x);
        } else {
            lmtrs += x;
        }
        rmtrs += abs(y)
        lmtrs += abs(y)
        if(y < 0-threshhold){
            rmtrs *= -1;
            lmtrs *= -1;
        }
        motor[mL1] = motor[mL2] = lmtrs / mult;
        motor[mR1] = motor[mR2] = lmtrs / mult;
        endTimeSlice();
    }
}
