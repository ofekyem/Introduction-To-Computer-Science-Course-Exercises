#include <stdio.h>
#include <math.h>

/***********************
* Ofek Yemini
* 2
***********************/ 

/******************
* Function Name: flushInput
* Input: none
* Output: 0
* Function Operation: The function is cleaning for a new input
******************/

void flushInput() {
    char inputc = -1;
    while (inputc != '\n')
    {
        scanf("%c", &inputc);
        if (inputc == '\n') {
            break;
        }
    }
}

/******************
* Function Name: printMenu
* Input: none
* Output: 0
* Function Operation: The function is printing the menu for the user
******************/

void printMenu() {

    printf("Choose an option:\n\t1. hexaDecimal to Decimal\n\t2. Decimal to Base\n\t3. Base to Decimal\n\t4. PLUS\n\t5. Shape\n\t6. Count bits\n\t7. Exit\n");
}
/******************
* Function Name:hexToDec
* Input: none
* Output: 0
* Function Operation: the function is getting a reversed number in base 16 by the user 
and it's printing the number in base 10
******************/

int hexToDec() {
    printf("Enter a reversed number in base 16:\n");
    int finalDecNum = 0;
    int flag = 0;
    char inputc = -1;
    int mulValue = 1;
    int powValue = 1;


    while (inputc != '\n') /*it will run while the number still has digits*/
    {
        scanf("%c", &inputc); /*getting the next digit of the input*/
        if (inputc == '\n') {
            break;
        }
        int digit = inputc - '0';
        int lower_case_letter = inputc - 'a'; /*the ascci value of a*/
        int upper_case_letter = inputc - 'A';/*the ascci value of A*/
        if (digit >= 0 && digit <= 9) /*if digit is number*/
        {
            mulValue = digit * powValue;
            finalDecNum += mulValue;
        }
        else if (lower_case_letter >= 0 && lower_case_letter <= 5) {/*if digit is lower case */
            mulValue = (lower_case_letter + 10) * powValue;
            finalDecNum += mulValue;
        }
        else if (upper_case_letter >= 0 && upper_case_letter <= 5) {
            mulValue = (upper_case_letter + 10) * powValue;
            finalDecNum += mulValue;
        }
        else
        {
            flag = 1; /*if there is a not base 16 number it will print error in the end of the loop*/

        }
        powValue *= 16; /*because we stepping forward in the number's digits*/

    }

    if (flag) { /*because the number has digit that isnt in base 16*/
        printf("Error!\n");
        return 0;
    }
    printf("%d\n", finalDecNum);
    return 0;
}

/******************
* Function Name: decToBase
* Input: none
* Output: 0
* Function Operation: The function is getting a number of certain base and a number in
base 10 from the user. and it's converting the 10 base number to the chose base and is printing
its result
******************/

int decToBase() {

    printf("Enter base and a number:\n");
    int base;
    unsigned long int num;
    int err = scanf("%d %lu", &base, &num);
    if (err == 0)
    {
        flushInput();
        printf("Error!\n");
        return 0;
    }

    unsigned long int divNum, remiNum, mulValue;
    unsigned long int powValue = 1;
    unsigned long int newBaseNum = 0;
    /*while the num has more digits it will run over all the digits of the number and convert
     everything to base that had chosen*/
    while (num != 0) { 
        divNum = num / base;
        remiNum = num % base;
        mulValue = remiNum * powValue;
        newBaseNum += mulValue;
        num = divNum;
        powValue *= 10; /*because we stepping forward in the number's digits*/
    }

    printf("%lu\n", newBaseNum);
    return 0;
}

/******************
* Function Name: baseToDec
* Input: none
* Output: 0
* Function Operation: the function is getting a number of certain base and a number in the same base,
and it's converting the number to base 10 and printing the result.
******************/

int baseToDec() {

    printf("Enter base and a number:\n");
    unsigned int base;
    unsigned long int num;
    int err = scanf("%d %lu", &base, &num);
    if (err == 0) /*is the base or num arent unsigned long int it will print error*/
    {
        flushInput();
        printf("Error!\n");
        return 0;
    }

    unsigned long int divNum, remiNum, mulValue;
    unsigned long int powValue = 1;
    unsigned long int newDegNum = 0;
    /*while the num has more digits it will run over all the digits of the number and convert
     everything to base 10*/
    while (num != 0) { 
        remiNum = num % 10;
        if (remiNum >= base) {
            printf("Error!\n"); /*the number isn't in base that the user put*/
            return 0;
        }
        else {
            divNum = num / 10; 
            mulValue = remiNum * powValue;
            newDegNum += mulValue;
            num = divNum;
            powValue *= base; /*because we stepping forward in the number's digits*/
        }
    }

    printf("%lu\n", newDegNum);
    return 0;
}

/******************
* Function Name:plusBinary
* Input:none
* Output:0
* Function Operation: The number gets 2 numbers in base 2 by the user. and its printing 
the adding process and the result.
******************/

int plusBinary() {
    printf("Enter 2 binary numbers:\n");
    unsigned long int num1, num2;
    int err = scanf("%lu %lu", &num1, &num2);
    
    /*if something is wrong and it's not an unsigned int
    it will print an error*/
    if (err == 0){
        flushInput(); /*cleaning to the next input*/
        printf("Error!\n");
        return 0;
    }
    if (num2 > num1) { /*putting the bigger number in num1*/
        unsigned long int temp = num2;
        num2 = num1;
        num1 = temp;
    }
    unsigned long int saveNum1 = num1;
    unsigned long int saveNum2 = num2;
    unsigned long int divNum1, divNum2, remiNum1, remiNum2, mulValue;
    unsigned long int powValue = 1;
    unsigned long int sum = 0;
    unsigned long int carry = 0;
    unsigned long int finalSum = 0;
    unsigned long int finalCarry = 0;
    unsigned long int counter = 1;

    /*it will run over every digit of the 2 numbers and it will caculate them and
    save the final result in finalsum and the final carry result in finalcarry*/
    while (num1 != 0) { 
        remiNum1 = num1 % 10;
        remiNum2 = num2 % 10;
        if (remiNum1 > 1 || remiNum2 > 1) { /*if the digit is beyond the base 2 it will print error*/
            flushInput();
            printf("Error!\n");
            return 0;
        }
        else {
            divNum1 = num1 / 10;
            divNum2 = num2 / 10;
            sum = carry + remiNum1 + remiNum2;
            if (sum > 1) {
                carry = 1;
            }
            else {
                carry = 0; 
            }
            sum %= 2;
            mulValue = sum * powValue;
            finalSum += mulValue;
            mulValue = carry * powValue;
            finalCarry += mulValue;
            counter++;
            num1 = divNum1; /*for the next round of the while*/
            num2 = divNum2;
            powValue *= 10;

        }

    }

    if (carry == 1) {/* if there is one more carry it will be added to the number*/
        finalSum += powValue;
    } 
    else {
        counter--;
    }

    finalCarry *= 10; /*multiplying the carry by 10 to have the last zero in the print*/
    printf("%0*lu\n", counter, finalCarry);
    printf("%0*lu\n", counter, saveNum1);
    printf("+\n");
    printf("%0*lu\n", counter, saveNum2);
    for (unsigned int i = 0; i < counter; i++) { /*printing the (-) counter times*/
        printf("-");
    }
    printf("\n%0*lu\n", counter, finalSum);
    return 0;
}  

/******************
* Function Name:shapeFly
* Input: none
* Output: 0
* Function Operation: The function is getting a number n from the user and its printing a butterfly made
of * and # in size of 2n X (2n-1).
******************/
void shapeFly()
{
    unsigned int height, stars, hash;
    int row, spaces;
    printf("Enter a number:\n");
    scanf("%u", &height);
    //printf("\n");
    
    int nb_hash = height + 1;
    if (nb_hash > 3)
        nb_hash = 3;
    /*printing the first # in the upper part of the butterfly 
    if its 0 or 1 it will print less with nb_solamit 
    in every other case it will print 3 on left and 3 on right*/
    for (hash = 0; hash < nb_hash; hash++) printf("#");
    for (spaces = 2; spaces <= 2 * (int)(height - 1) - 1; spaces++)
        printf(" ");
    for (hash = 0; hash < nb_hash; hash++) printf("#");
    printf("\n");

    /*printing the half upper body of the butterfly with * and with # around*/
    for (row = 1; row <= (int)height - 1; row++) {
        printf("#");
        for (stars = 1; stars <= row; stars++)
            printf("*");
        printf("#");
        for (spaces = 2; spaces <= 2 * (int)(height - row) - 1; spaces++)/*the space between the *** */
            printf(" ");
        printf("#");
        for (stars = row; stars >= 1; stars--)
            printf("*");
        printf("#");
        printf("\n");
    }
    /*pring the lower half body of the butterfly with * and with # around*/
    for (row = height; row >= 1; row--) {
        printf("#");
        for (stars = 1; stars <= row; stars++)
            printf("*");
        if (row != height)
            printf("#");
        for (spaces = 2; spaces <= 2 * (int)(height - row) - 1; spaces++) /*the space between the *** */
            printf(" ");
        if (row != height)
            printf("#");
        for (stars = row; stars >= 1; stars--)
            printf("*");
        printf("#");
        printf("\n");
    }
    /*printing the last # in the bottom part of the butterfly
    if its 0 or 1 it will print less with nb_hash 
    in every other case it will print 3 on left and 3 on right*/
    for (hash = 0; hash < nb_hash; hash++) printf("#");
    for (spaces = 2; spaces <= 2 * (int)(height - 1) - 1; spaces++)
        printf(" ");
    for (hash = 0; hash < nb_hash; hash++) printf("#");
    printf("\n");

}

  

/******************
* Function Name: countBits
* Input: none
* Output:0
* Function Operation: The function is getting a number in base 10 and it's printing
* how many time the bit 1 is in the number in base 2.
******************/
int countBits() {
    printf("enter a number:\n"); 
    unsigned long int num; 
    scanf("%lu", &num);
    unsigned long int counter = 0; 
    while (num!=0) { /*while the number has more digits continue .else stop*/
        int checking = num & 1; /*if number is 1 it will return 1 and if not it will be zero*/
        counter += checking;/*if the value is 1 the counter will grow*/
        num >>= 1; /*go to the next digit*/
    } 
    printf("no of bits those are 1 in its binary representation: %lu\n", counter); 
    return 0;
} 

int main() {
    int stopRun = 0;

    while (stopRun == 0) { /*loop goes on untill 7 is clicked*/
        printMenu();
        int input;
        char c;
        int err = scanf("%d", &input); //err = did the user enter something that isn't integer
        scanf("%c", &c);;
        if (err == 0) { 
            flushInput(); 
            input = 0; /*helping the switch to get to the default*/
        }
        switch (input) {
        case 1:
            hexToDec();
            break;
        case 2:
            decToBase();
            break;
        case 3:
            baseToDec();
            break;
        case 4:
            plusBinary();
            break;
        case 5: 
            shapeFly();
            break; 
        case 6: 
            countBits(); 
            break;
        case 7:
            return 0; /*ending the program*/
            break;

        default:
            printf("Wrong option!\n");
            break;

        }

    }
}
