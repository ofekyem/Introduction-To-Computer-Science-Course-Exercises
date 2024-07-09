#include <stdio.h>
#include <math.h> 

/* Name: Ofek Yemini 
   1 */ 


/* the function hello() is printing the string:
   " hello\/\/orld %d/n " */
void hello() {

    printf("\"hello \\/\\/orld %%d\\n\"\n");

}

/* the function distance() is getting 2 values (x,y) of 2 points from the user,
   and it's calculating and printing the distance between them */
void distance() { 

    int x1, y1, x2, y2; 

    printf("Enter x1:\n"); 
    scanf("%d", &x1); /* input value of x1 */
    printf("Enter y1:\n");
    scanf("%d", &y1); /* input value of y1 */
    printf("Enter x2:\n");
    scanf("%d", &x2); /* input value of x2 */
    printf("Enter y2:\n");
    scanf("%d", &y2); /* input value of y2 */

    int diff_x = x1 - x2; /* difference between x1 and x2 */
    diff_x *= diff_x; /* by the power of 2 */
    int diff_y = y1 - y2; /* difference between y1 and y2 */
    diff_y *= diff_y; /* by the power of 2 */

    int sum = diff_x + diff_y; /* the sum of the two */
    double distance = sqrt((double)sum); /* square root on the sum */
    printf("The distance between the points is: %.04f\n", distance); /* printing distance */
    
} 

/* the function "conversions()" is getting nm number from the user, 
   and it's calculating and printing the number in some other kinds of unit measurement */
void conversions() { 

    long long int nm; /* nm is long long int because it can be a 10 digits number at max */
    double const CONVERT_TO_KM = 1.0e-12; 
    double const CONVERT_TO_M = 1.0e-9;
    double const CONVERT_TO_DM = 1.0e-8;
    double const CONVERT_TO_CM = 1.0e-7;
    double const CONVERT_TO_MM = 1.0e-6; 
    /* those are scientific notations which will help us to convert nm to the right unit of measurement */

    printf("Please enter nm:\n");  
    scanf("%lld", &nm); /* input nm number */

    double  km = CONVERT_TO_KM * (double)nm; /* convert to km */
    double  m = CONVERT_TO_M * (double)nm; /* convert to m */
    double  dm = CONVERT_TO_DM * (double)nm; /* convert to dm */
    double  cm = CONVERT_TO_CM * (double)nm; /* convert to cm */
    double  mm = CONVERT_TO_MM * (double)nm; /* convert to mm */

    printf("%010.04f km\n", km); 
    printf("%010.04f m\n", m);
    printf("%010.04f dm\n", dm);
    printf("%010.04f cm\n", cm); 
    printf("%010.04f mm\n", mm);
    printf("%010lld nm\n", nm);
    /* 010.04 means that the number will bre represnted by 10 digits and 4 of them are after the point */
} 

/* the fuction "baking()" is getting baking time for a cake from the user, and it's getting the 
   current time. and it's calculating and printing in what time the cake will be ready */
void baking() { 

    int bakingHours, bakingMinutes, bakingSeconds, clockHours, clockMinutes, clockSeconds;
    
    printf("Please enter the baking time: [hh:mm:ss]\n"); 
    scanf("%d:%d:%d", &bakingHours, &bakingMinutes, &bakingSeconds);/* the baking time */
    printf("When did you put the cake into the oven? [hh:mm:ss]\n");
    scanf("%d:%d:%d", &clockHours, &clockMinutes, &clockSeconds);  /* the current clock time */

    int sumSeconds = bakingSeconds + clockSeconds; /* sum of the seconds */
    int relicSeconds = sumSeconds / 60; /* the relic will be added to the minutes (if it's zero it won't change it) */
    int finalSeconds = sumSeconds % 60; /* because there are 60 seconds in one minute */

    int sumMinutes = bakingMinutes + clockMinutes + relicSeconds; /*sum of minutes (and the relic of seconds)*/
    int relicMinutes = sumMinutes / 60; /* the relic will be added to the hours (if it's zero it won't change it) */
    int finalMinutes = sumMinutes % 60; /* because there are 60 minutes in one hour */

    int sumHours = bakingHours + clockHours + relicMinutes; /*sum of hours (and the relic of minutes)*/
    int finalHours = sumHours % 24; /* because there are 24 hours in one day */

    printf("The cake will be ready at %02d:%02d:%02d o'clock.\n", finalHours,finalMinutes,finalSeconds); /* final time */
    /* 02 means that the number will be represented by 2 digits */
}

void main() {
    hello();
    distance();
    conversions();
    baking();
}
