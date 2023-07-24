/* Exercise 1.3: Modify the temp conversion program to print a heading above the table */

#include <stdio.h>

/* print Fahrenheit to Celsius table for fahr = 0, 20, ..., 300 */
int main() {
    float fahr, celsius;
    int lower, upper, step;
    
    lower = 0; /* lower limit of temp table */
    upper = 300; /* duh... */
    step = 20; /* step size for fahr */
    
    fahr = lower;
    printf("Fahrenheit\tCelsius\n");
    while ( fahr <= upper ) {
        celsius = (5.0/9.0) * ( fahr-32.0 );
        printf("%.0f\t\t\t%.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
   return 0;
}
