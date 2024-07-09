#include <stdio.h>
#include "sorting.h"
#include "person.h"

#define MAX_LINES 600

const char* INPUTFILE = "persons.txt";
const char* OUTPUTFILE = "sorted.txt";
/*
void plot(const char* inputFile) {
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}*/
static void strOfPerson1(Person persons[], int i, char* str) {
    
    sprintf(str, "%s,%s,%d,%d,%d,%d,%.2f", persons[i].firstName, persons[i].lastName, persons[i].dateOfBirth.day, persons[i].dateOfBirth.month, persons[i].dateOfBirth.year, persons[i].height, persons[i].weight);
}

static void printPersonsArray(Person persons[], int* numOfPersonsPtr) {
    char str[MAX_STR_LEN];
    for (int i = 0; i < *numOfPersonsPtr; i++) {
        strOfPerson1(persons, i, str);
        printf("%s", str);
        printf("\n");
    }

}

int main() {
    double a = 5.7;
    double b = 6.3; 
    double x = a - b; 
    if (x < 0) {
        return -1;
    } 
    else if (x = 0) {
        return 1;
    }
    else
        return 0; 
    sortFunction(arr,)
    printf("%d", x);

    Person persons[MAX_LINES];
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
    save(OUTPUTFILE, persons, numOfPersons);
    return 0;
}
/*
Person persons[MAX_LINES];
int main() {
    
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
    printPersonsArray(persons, &numOfPersons);
    printf("\n");
    //quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
    //quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByLastName);
    //quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByDate);
    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByWeight);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByHeight);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByBMI); 
    printPersonsArray(persons, &numOfPersons);
    save(OUTPUTFILE, persons, numOfPersons);
    //plot(INPUTFILE);
    printf("sorting...");
    //plot(OUTPUTFILE);
    return 0;
}*/