
#include<stdio.h>

#include"taylorseriesplot.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
void main(void)
{
    puts("------------------------------------");
    puts("| codedrome.com                    |");
    puts("| Taylor Series Trigonometric Plot |");
    puts("------------------------------------\n");

    taylor_sin_plot(2, 360, 8, 1440, 800, "tsp.svg");

    taylor_sin_plot(2, 360, 4, 720, 400, "1.svg");
    taylor_sin_plot(4, 720, 8, 720, 400, "2.svg");
}
