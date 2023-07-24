/* Exercise 1.4: Write a program to print the corresponding Celsius to Fahrenheit table */

#include <stdio.h>

/*  TIP: °F = (°C × 9/5) + 32 and  °C = (5/9) * (°F - 32) */
/*  print Celius to Fahr table for celsius = 0, 20, ..., 300 */

int main() {
    float fahr, celsius;
    int lower, upper, step;
    
    lower = 0;    /* lower limit of temp table */
    upper = 300;  /* duh... */
    step = 20;    /* step size for celsius */
    
    celsius = lower;
    printf("Celsius\tFahrenheit\n");
    while ( celsius <= upper ) {
        fahr = (celsius * (9.0/5.0) + 32.0 );
        printf("%.0f\t\t\t%.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
 return 0;   
}
