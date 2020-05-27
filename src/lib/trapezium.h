#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double integration(double x){
    //This function is responsible for calculating the function for a certain x value
    double y = 0;
    y = sqrt((100*100) - x*x);
    return y;
};

double trapeziumCalc(double j, double xi, double xf){
    /* j = discretization interval
     * xi = initial x
     * xf = final x
     */
    int i;
    double h, n;
    double x, sum = 0, result1 = 0, result2 = 0;
    
    //n = number of subdivisions between xf and xi
    n = (xf-xi)/j; 
    // h = trapezium height
    h = (xf - xi)/n;
    //The calculum is initialized with the first value for x, or xi.
    x = xi;
    while(x <= (xf-j)){
        result1 = integration(x);
        x = x + j;
        result2 = integration(x);
        sum = sum + (h/2)*(result1 + result2);
    }
    
    return sum;
}



    

  