#include <stdio.h>
#include <math.h> 
/***********************
* Ofek Yemini
* 3
***********************/ 
#define SIZE 15 
#define LIMIT 30

/*SIZE and LIMIT are 2 const variables that will be used later */

/******************
* Function Name:IfPrimeNum
* Input:number type int
* Output: 1 if the input is a Prime number. 0 if it isn't.
* Function Operation: The function gets an integer number and it checks if the number
  is a Prime Number. If it is it will return 1, else it will return 0. 
  The function is used by the functions printPrimeNumbers() and goldbachTheory().
******************/
int ifPrimeNum(int num) { 
    if (num <= 1) {/*if it's smaller than 2 it isn't Prime*/
        return 0;
    } 
    else {
        int numOfDivisors = 0;
        
        for (int i = 1; i <= num; i++) {
            if (num % i == 0) { /*is the index a divisor of the input?*/
                numOfDivisors++;
            }
        } 

        if (numOfDivisors == 2) { /*if number has 2 divisors, it means the number is Prime.*/
            return 1;
        } 
        else { /*else it isn't a prime number*/
            return 0;
        }
    }
    
}  

/******************
* Function Name:printPrimeNumber
* Input:none
* Output:0
* Function Operation: The function Prints all the Prime numbers till the variable SIZE. 
*the function is using the function isPrimeNum().
******************/
int printPrimeNumber() {
    
    if (SIZE >= 2) {/*SIZE has to be equal or bigger than 2*/
        printf("%d", 2); /*used to avoid the space after the last Prime Number for the "Submit Output"*/
    } 

    for (int i = 3; i <= SIZE; i++){ 

        int check = ifPrimeNum(i);/*checking if the index is a Prime Number*/
        if (check==1) {
            printf(" %d", i);   /*if it does. the function prints it*/
        }
 
    }

    return 0;
} 

/******************
* Function Name:goldbachTheory
* Input:none
* Output:0
* Function Operation:The function is showing the proof to the goldbach theory. and it does that
by showing that all the even numbers till can be shown by sum of 2 Prime numbers till the variable SIZE. and it prints the proof. 
the function is using the function isPrimeNum();
******************/
int goldbachTheory() {
    /*the index go till SIZE*2 because the last one will be shown by
    the sum of the biggest prime Number till size with itself, it means 2*SIZE*/
    /*less than the number 4 can't be shown by prime numbers*/
    for (int i = 4; i <= SIZE*2; i++) { /*less than the number 4 can't be shown by prime numbers*/
        
        if (i % 2 != 0) { /*if it isn't an even number than it doesn't need to be shown*/
            continue;
        }  

        else {

            int avoidDouble = i/2;/*the program doesn't need to write 3+5 and 5+3 because it is the same thing*/
            for (int j = 2; j <= avoidDouble && j <= SIZE; j++) {
                
                int check = ifPrimeNum(j);  
                if (check == 1) {
                    
                    for (int k = 2; k <= i && k <= SIZE; k++) {
                       
                        int check2 = ifPrimeNum(k); 
                        if (check2 == 1) {
                            if (k + j == i) { 
                                /*checks if the sum of the prime numbers k and j is equal to the
                                number that we are proofing for it*/
                                printf("%d = %d + %d\n" ,i, j, k);/*if the sum is equal then it prints*/
                                break;
                            }
                        } 

                    }

                } 
                
            }

        }
    }  

    return 0;
} 

/******************
* Function Name:lychreNum
* Input:integer number
* Output:0
* Function Operation:The function is getting an integer number and it prints the process for this number that 
is sums the number and it's reversed form till the result is a Palindrome and then it stops. 
For example:  for 48 the process that the function is printing is 48:48+84=132:132+231=363 
it stops in 363 because 363 is Palindrome. 
The function used by the function printLychreNaturals().
******************/
int lychreNum(int num) { 
    printf("%d", num);
    int copyNum = num;
    int reversedNum = 0;
    int remi;
    while (copyNum != 0) {
        remi = copyNum % 10;
        int mulValue = 10 * reversedNum;
        reversedNum = mulValue + remi;
        copyNum /= 10;
    }  
    if (reversedNum == num) { 
        printf("\n");
        return 0;
    } 
    else { 
        printf(":%d+%d=", num, reversedNum);
        int sumNumbers = num + reversedNum;
        lychreNum(sumNumbers); 
        return 0;
    }

}
 
/******************
* Function Name:printLychrelNaturals
* Input:none
* Output:0
* Function Operation:The function is proofing that all the Naturals numbers till the variable LIMIT 
aren't all lychre numbers by printing all the process for every natural number till LIMIT that is showing when 
the number is reaching to a palindrome. 
The function is using the function lychreNum().
******************/
int printLychrelNaturals() {
    for (int i = 1; i < LIMIT; i++) { /*all the Naturals till LIMIT*/
        lychreNum(i); /*printing the process for every index*/
    } 
    return 0;
} 

int totalMax = 1; /*used in numOfElemnts() and in maxSet() so read in there
                  it's a global variable holding the biggest size of all the increasing sequences that has been checked 
                  by the function numOfElemnts()*/

/******************
* Function Name: numOfElements
* Input: an array of integers that is represnt the set and an integer number that represnt the size of the set
* Output: it returns an integer (Max) that is holding the size of the "biggest increasing sequance" 
of the set from the input.
* Function Operation: the function is getting a set of numbers (set[]) and the size of the set(sizeSet)
and its calculating which of all the increasing Sequences of the set is the biggest one from this set. 
the biggest one is the output of the function(Max). the function also checks if the number of the biggest 
increasing set from the previous sets that used the function(represneted the global variant "totalMax") is
bigger than the max of the current check. if the current max is bigger than the totalmax than totalmax is become 
the current max for the future checks.

******************/
int numOfElements(int set[], int sizeSet)
{
    if (sizeSet == 1) {
        return 1; /*if the set has only one number than the biggest increasing sequence has only 1 number*/
    }
        
    int retValue;
    int max = 1;/*the current max for the current input set*/
    for (int i = 1; i < sizeSet; i++) {
        /*retValue holds the number of the biggest size of all
         the other increasing sequences*/
        retValue = numOfElements(set, i); 
        
        /*if the current index number of the set (-1) is smaller than the last of the set
        and if retValue(+1) holds bigger size than the previous sizes the the current max is holding
        then, max will now and on be retValue(+1) because it is now the biggest size of all  */
        if ((set[i - 1] < set[sizeSet - 1]) && (retValue + 1 > max)) { 
            
            max = retValue + 1;
        } 

    } 

    /*if the max size of increasing sequence from all the other sets that have been
     used by this function then, totalmax will now be the current max because it is now
     the biggest size of all*/
    if (totalMax < max) { 
        totalMax = max;
    }
    
    return max; /*in any case the current set's max size is the output*/
}

/******************
* Function Name:maxSet
* Input:none
* Output:0
* Function Operation: the function is getting the size of a set, and the set itself from the user. and it's printing 
the size of the "biggest increasing sequence" of the set. 
the function is using the function numOfElements() so you also need to read NumOfElemnts() details.
******************/
int maxSet() { 

    printf("Enter the number of elements\n"); 
    int sizeSet;
    scanf("%d", &sizeSet); 

    int set[SIZE]; 
    for (int i = 0; i < sizeSet; i++) {
        scanf("%d", &set[i]); 
    }   

    numOfElements(set, sizeSet);
    /*totalMax is holding the biggest size of increasing sequence after using numOfElements()
    and so we need to print totalMax*/
    printf("%d\n", totalMax); 
    return 0;
} 

int main() 
{   
    int inputNum;
    printf("1: primes\n2: goldbach\n3: lychrel\n4: max set\n"); /*prints the menu*/
    scanf("%d", &inputNum);
    switch (inputNum)/*which option the user chose to do*/
    { 
    case 1:
        printPrimeNumber();
        break; 
    case 2:  
        goldbachTheory();
        break; 
    case 3:
        printLychrelNaturals();
        break; 
    case 4: 
        maxSet();
        break;
    default:
        printf("Wrong option!\n"); /*if it isn't one of the options, an error message will be shown*/
        break;
    }
    
}