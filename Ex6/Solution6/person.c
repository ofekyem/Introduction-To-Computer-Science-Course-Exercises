#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include "person.h"
/***********************
* Ofek Yemini
* 6
***********************/ 

/******************
* Function Name: stringToDouble
* Input: string with a number in it(char *)
* Output: the number from the string (in double type)
* Function Operation: the function is getting a string with a number in it 
(the number in the string can be double or integer) 
and the functions convert the string into an actual double type 
for a string with int number it will return it with ".0" and for double it will return what needed 
depends on the number in the string.
******************/

static double stringToDouble(char* p) {
    int length = strlen(p);//number of digits of the number
    double result = 0;
    int beforePoint = 0;
    int flagOfPoint = 0;
    double afterPoint = 0;
    int powOfTen = 10;
    for (int i = 0; i < length; i++) {
        if (p[i] == '.') {
            flagOfPoint = 1; //now we calculating the number after the point
            continue;
        }
        
        if (flagOfPoint == 1) {
            //calculating the number after the point(if needed)
            double sub = p[i]-(double)'0';
            afterPoint += sub/powOfTen ;
            powOfTen *= 10;
        }
        else {
            //calculating the  number before the point
            beforePoint = (beforePoint * 10) + (p[i] - '0');
        }
        
    }  
    result = beforePoint + afterPoint;//if there are no numbers after point it will remains the same
    return result;
} 

/******************
* Function Name:load
* Input: input txt file(const char * type), the array of persons that we need to fill here(type Person[]),the number of persons that there are right now(int * type)
* Output: none
* Function Operation: the function is getting the txt file that is full of details about persons and the function is
putting the details in the array of persons that the function is getting and it organize every detail from the
txt file in every person feature. and then it updates the new number of persons with the pointer the function is getting.
******************/

void load(const char* inputFile, Person persons[], int* numOfPersonsPtr) {
    FILE* input = fopen(inputFile, "r");//open the txt file
    if (!input) {//if the file hasnt been dound
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN][MAX_STR_LEN];//make a string array for the details from the input file
    int i = 0;
    //the loop will run untill there is no more lines in the txt file
    while (fgets(buffer[i], MAX_STR_LEN, input)) {
        
        int length = strlen(buffer[i]);//length of the line i in the txt file
        buffer[i][length - 1] = '\0';//puts an end for the string
        char* pointCh;// this pointer will be used to cut the string to parts
        pointCh = strtok(buffer[i], DELIM);//cutting the first part of the string
        int j = 1;//word number
        int x = 0;
        //the loop will run untill there is no anything to cut from the string
        while (pointCh != NULL) {
            switch (j) {
                case 1://the first word from the string representing the "first name"
                    strcpy(persons[i].firstName,pointCh);
                    // updating the i place in the array of persons "first name"
                    break;  

                case 2://the second word from the string representing the "last name"
                    strcpy(persons[i].lastName, pointCh); 
                    //updating the i place in the array of persons "last name"
                    break; 

                case 3: //the third word from the string representing the "the day in the month of birthday number"
                {
                    int res = (int)stringToDouble(pointCh);//converting the string to a number
                    persons[i].dateOfBirth.day = res;
                    //updating the i place in the array of persons "the day in the month of birthday number"
                    break;
                }

                case 4: //the fourth word from the string representing the "the month of birthday number"
                {
                    int res = (int)stringToDouble(pointCh);//converting the word to a number
                    persons[i].dateOfBirth.month = res;
                    //updating the i place in the array of persons "the month of birthday number"
                    break;
                } 
                
                case 5: //the fifth word from the string representing the "the year of birthday number"
                {
                    int res = (int)stringToDouble(pointCh);//converting the word to a number
                    persons[i].dateOfBirth.year = res;
                    //updating the i place in the array of persons "the year of birthday number"
                    break;
                } 

                case 6: //the sixth word from the string representing the "the height number"
                {
                    int res = (int)stringToDouble(pointCh);//converting the word to a number
                    persons[i].height = res; 
                    //updating the i place in the array of persons "the height number"
                    break;
                }
                case 7: //the seventh word from the string representing the "the weight number"
                { 
                    double res = stringToDouble(pointCh); //converting the word to a number
                    persons[i].weight = res;
                    //updating the i place in the array of persons "the weight number"
                    break;
                }

            } 
            pointCh = strtok(NULL, ",");//the next word from the string
            j++;//next word number
        }
        i++;
    } 
    *numOfPersonsPtr = i; //updating the number of persons there are right now
    if (fclose(input)) {//closing the file, if not print error
        printf("Error with closing file: %s\n", inputFile);
        
    }
    
}  

/******************
* Function Name:strOfPerson
* Input:The array of persons, the index of the specific person(int i),a string to put the result in it(char * str)
* Output:none
* Function Operation:the function is getting array of persons,index named i and a string and it puts in the string 
all the details of the person in the place i in the array. it will be used when we want to save the details in the
new txt file. the result string will be put in "str" which we got in the input
******************/

static void strOfPerson(Person persons[], int i, char* str) {
    
    sprintf(str, "%s%s%s%s%d%s%d%s%d%s%d%s%.2f", persons[i].firstName, DELIM, persons[i].lastName, DELIM, persons[i].dateOfBirth.day, DELIM, persons[i].dateOfBirth.month, DELIM, persons[i].dateOfBirth.year, DELIM, persons[i].height, DELIM, persons[i].weight);
    //here we taking all the details from the person and we merge all the deatils into one string and "str" will be holding that string
} 


/******************
* Function Name:comparePersonByFirstName.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: a negative number or 0 or a postive number.
* Function Operation: the function is getting certain array and 2 indexes and it will check for us which
of the 2 indexes we got has a bigger first name. if the in the i place there is a bigger name it will return
postive number if in the j place there is a bigger first name then it will return a negative number. if
the names are equal it will return 0
******************/
int comparePersonByFirstName(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person struct features
    int result = strcmp(personArr[i].firstName, personArr[j].firstName);//compare first names
    return result;
}   

/******************
* Function Name:comparePersonByLastName.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: a negative number or 0 or a postive number.
* Function Operation: the function is getting certain array and 2 indexes and it will check for us which
of the 2 indexes we got has a bigger last name. if the in the i place there is a bigger name it will return
postive number if in the j place there is a bigger last name then it will return a negative number. if
the names are equal it will return 0
******************/
int comparePersonByLastName(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person struct features
    int result = strcmp(personArr[i].lastName, personArr[j].lastName);//compare last names
    return result;
} 

/******************
* Function Name:comparePersonByWeight.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: negative 1, 0 or 1.
* Function Operation: the function is getting certain array and 2 indexes and it will check for us which
of the 2 indexes we got has a bigger weight number. if the in the i place there is a bigger weight it will return
1 if in the j place there is a bigger weight then it will return a negative 1. if
the weights are equal it will return 0
******************/
int comparePersonByWeight(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person struct features
    int res = 0;
    if (personArr[i].weight - personArr[j].weight < 0.0) {
        res = -1;//the j weight is bigger
    }
    else if (personArr[i].weight - personArr[j].weight > 0.0) {
        res = 1;//the i weight is bigger
    }
    return res;
} 

/******************
* Function Name:comparePersonByHeight.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: a negative number, 0 or a postive number.
* Function Operation: the function is getting certain array and 2 indexes and it will check for us which
of the 2 indexes we got has a bigger height number. if the in the i place there is a bigger height number it will return
postive number if in the j place there is a bigger height number then it will return a negative number. if
the heights are equal it will return 0
******************/
int comparePersonByHeight(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person struct features
    int res = personArr[i].height - personArr[j].height;// the result depends on which is bigger
    return res;
} 

/******************
* Function Name:comparePersonByBMI.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: negative 1, 0 or 1.
* Function Operation: the function is getting certain array and 2 indexes and it will check and calculate! for us which
of the 2 indexes we got has a bigger BMI number. if the in the i place there is a bigger BMI it will return
1 if in the j place there is a bigger BMI then it will return a negative 1. if
the BMI's are equal it will return 0
******************/
int comparePersonByBMI(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person struct features

    double meters = personArr[i].height / 100.0;
    double powHeight = meters * meters;
    double BMIofI = personArr[i].weight / powHeight;
    //calculatin the BMI of i, the result in BMIofI

    meters = personArr[j].height / 100.0;
    powHeight = meters * meters;
    double BMIofJ = personArr[j].weight / powHeight;
    //calculating the BMI of j, the result in BMIofj 

    int res = 0;
    if (BMIofI - BMIofJ < 0.0) {
        res = -1;//the j BMI is bigger
    }
    else if (BMIofI - BMIofJ > 0.0) {
        res = 1;//the i BMI is bigger
    }
    return res;
} 

/******************
* Function Name:comparePersonByDate.
* Input: a pointer to any type(arr), frist index named i, second index named j.
* Output: a negative number, 0 or a postive number.
* Function Operation: the function is getting certain array and 2 indexes and it will check for us which
of the 2 indexes we got is a younger person. if the in the i place there is a younger person it will return
postive number if in the i place there is a younger person then it will return a negative number. if
the age are equals it will return 0
******************/
int comparePersonByDate(void* arr, int i, int j) {
    Person* personArr = (Person*)arr; //so we can work with the Person struct features
    if (personArr[i].dateOfBirth.year != personArr[j].dateOfBirth.year) {//if they don't have the same birth year
        return personArr[i].dateOfBirth.year - personArr[j].dateOfBirth.year;
        //postive for i is younger, negative for j is younger
    } 
    else if (personArr[i].dateOfBirth.month != personArr[j].dateOfBirth.month) {//if they don't have the same birth month
        return personArr[i].dateOfBirth.month - personArr[j].dateOfBirth.month;
        //postive for i is younger, negative for j is younger
    } 
    else {
        return personArr[i].dateOfBirth.day - personArr[j].dateOfBirth.day;
        //0 for same age, postive for i is younger , negative for j is younger 
    }
} 

/******************
* Function Name:swapPersons
* Input:a pointer to any type(arr), frist index (i), second index (j).
* Output:none
* Function Operation:the function is getting certain array and 2 indexes of the array and it will swap 
the persons places. the person in the i place will be in J place. the person in J place will be in i place
******************/
void swapPersons(void* arr, int i, int j) {
    Person* personArr = (Person*)arr;//so we can work with the Person type 
    Person temp = personArr[i]; 
    personArr[i] = personArr[j];
    personArr[j] = temp;
    //swap persons done
} 

/******************
* Function Name: save.
* Input: output txt file(const char * type), the array of persons (type Person[]),the number of persons that there are in the array(int type)
* Output:none.
* Function Operation: the function is getting the persons array ,the numbers of person and an output txt file and 
it will fill the output file with the details (in a string) of the persons that there are in the array .
the output file will be in the order they are placed in the array.
there.
******************/
void save(const char* outputFile, Person persons[], int numOfPersons) {
    FILE* output = fopen(outputFile, "a");//open the output file
    if (!output) {//if there is an error in opening
        printf("Error with file: %s\n", outputFile);
        return;
    }  

    char str[MAX_STR_LEN];// a string that will hold the details of every person
    for (int i = 0; i < numOfPersons; i++) {
        strOfPerson(persons, i, str);//str will have the string of the person in place i
        fprintf(output, "%s", str);//fill the output file with the string of the i place person
        fprintf(output, "\n");//down to a new line for the next person string
    }

    if (fclose(output)) {//closing the output file
        printf("Error with closing file: %s\n", outputFile);
        //print if there is an error with closing
    }
   
}