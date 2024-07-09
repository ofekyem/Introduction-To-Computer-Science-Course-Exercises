#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <string.h> 

/***********************
* Ofek Yemini
* 5
***********************/ 

#define SIZE 1000 //the size of the input strings

int dictionaryIndex = 0; // the indicator of the number of the dicitionaries there are right now

typedef struct _Word {
    char** translations;
    struct _Word* next;
} Word;

typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;


/******************
* Function Name:freeWord()
* Input:pointer to a Word type (named as w) and the numbers of the translations in the specific word(named as length)
* Output:none
* Function Operation:the function is getting a pointer to a word and the word's number of transaltions and it's
free all the deatails of the word. it's freeing the transaltions, and the addres to the next word. 
we using this function when we wnat to delete a word
******************/
void freeWord(Word* w, int length) {
    if (w->translations != NULL)
    {
        for (int i = 0; i < length; i++) {

            free(w->translations[i]);//free every memory of every translte of this word
        }
        free(w->translations);//free the array of the transaltions
    }
    w->next = NULL;
    //putting the next word as NULL because we deleting the word and it's no longer indicate to something
    
}

/******************
* Function Name:freeDictionary()
* Input:a single Dictionary type named as dictio
* Output:none
* Function Operation:the function is getting a Dictionary an it's deleting all the details of the dictionary
the details are languages the words and the number of languages 
******************/
void freeDictionary(Dictionary dictio) {
    int length = dictio.numOfLanguages;
    if (dictio.languages != NULL)
    {
        for (int i = 0; i < length; i++) {

            free(dictio.languages[i]);//free all the memory of the languages
        }
        free(dictio.languages);//free the array of the languages
    }
    Word* temp1 = dictio.wordList;
    Word* temp2 = dictio.wordList;;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        freeWord(temp1, length);//freeword delete all deatails of the word
        free(temp1);//free the word itself
        temp1 = temp2;
    }
    dictio.wordList = NULL;//put the list to NULL because it will be no longer exist
}

/******************
* Function Name:createDictionary()
* Input:pointer to the array of dicitionaries that exist right now, and the number of them
* Output:the number of the dictionaries after the update
* Function Operation:the function is trying to create a new dictionary and it's adding the new dictionary to the
array of dictionaries. the function is getting the languages for the new dictionary from the user and it's trying to 
create a place for them in the dictionary if it's succeed to create a place for them it's adding the languages to the array
of languages of the new dictionary and it's updating the number of the languages depend on the input of the user
******************/
int createDictionary(Dictionary** dictionaries, int numOfDictionaries) {
    if (dictionaries == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return numOfDictionaries;
    }

    if (numOfDictionaries == 0) {

        *dictionaries = (Dictionary*)malloc(sizeof(Dictionary) * 1);
        //if there are no dictionaries, create the first one by giving a place for only one

    }

    else if (dictionaries != NULL) {
        Dictionary* temp = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * (numOfDictionaries + 1));
        //you add one more place for the new Dictionary
        if (temp != NULL) {
            *dictionaries = temp;//temp using for avoid warning
        }
        else {
            printf("The creation of the dictionary has failed!\n");
            //you dont have a place in memory for that so it failed
            return numOfDictionaries;
        }
    }

    if (*dictionaries == NULL) {
        printf("The creation of the dictionary has failed!\n");
        //you dont have a place in memory for that so it failed
        return numOfDictionaries;
    }
    printf("Define a new dictionary:\n");
    char* inputLanguages = malloc(SIZE * sizeof(char));
    //we creating a place for the input of the user

    scanf("%s", inputLanguages);
    //getting languages from user
    int i = 0;
    int numOfLanguages = 1;
    if (inputLanguages) {
        while (inputLanguages[i] != '\0') {
            if (inputLanguages[i] == ',') {
                numOfLanguages++; //counting the number of languages
            }
            i++;
        }
        (*dictionaries)[dictionaryIndex].wordList = NULL; //starting the wordlist in null because there not any yet
        (*dictionaries)[dictionaryIndex].numOfLanguages = numOfLanguages; //what we just counted
        (*dictionaries)[dictionaryIndex].languages = malloc(numOfLanguages * sizeof(char*));//a place for the array of languages
        if ((*dictionaries)[dictionaryIndex].languages) { //if there is a place for the array
            int start_index = 0;
            i = 0;
            int word_index = 0;

            while (inputLanguages[i] != '\0' && word_index < numOfLanguages)
            {
                if (inputLanguages[i] == ',') { //if the spesific language is over

                    int word_size = i - start_index;
                    (*dictionaries)[dictionaryIndex].languages[word_index] = malloc(word_size + 1);
                    //crate a place for the language itself
                    if ((*dictionaries)[dictionaryIndex].languages[word_index]) {//if there is a place for the language
                        strncpy((*dictionaries)[dictionaryIndex].languages[word_index], &inputLanguages[start_index], word_size);
                        //copy the langue to the place in array
                        (*dictionaries)[dictionaryIndex].languages[word_index][word_size] = '\0';//put \0 int the end to indicate the string is over
                        word_index++;//move to the next word
                    }
                    else {//if there is no place for the string of language
                        printf("The creation of the dictionary has failed!\n");
                        free((*dictionaries)[dictionaryIndex].languages[word_index]);//free the place of language
                        (*dictionaries)[dictionaryIndex].numOfLanguages = 0;//back the languages to 0
                        free((*dictionaries)[dictionaryIndex].languages);//fre the array of languages
                        Dictionary* temp = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * numOfDictionaries);
                        if (temp != NULL) { 
                            *dictionaries = temp;//return the array of dictionaries back to what is was before the adding
                        }
                        free(inputLanguages);//free the input from the user
                        return numOfDictionaries;
                    }
                    start_index = i + 1;//next place for check
                }
                i++;
            }


            //because last word doesnt have , then we check it separatley again for the last word 
            //its the same code for the other thing just here its check /0 and ,
            if (inputLanguages[i] == '\0' && word_index < numOfLanguages) {
                int word_size = i - start_index;
                (*dictionaries)[dictionaryIndex].languages[word_index] = malloc(word_size + 1);
                if ((*dictionaries)[dictionaryIndex].languages[word_index]) {
                    strncpy((*dictionaries)[dictionaryIndex].languages[word_index], &inputLanguages[start_index], word_size);
                    (*dictionaries)[dictionaryIndex].languages[word_index][word_size] = '\0';
                }
                else {
                    printf("The creation of the dictionary has failed!\n");
                    free((*dictionaries)[dictionaryIndex].languages[word_index]);
                    (*dictionaries)[dictionaryIndex].numOfLanguages = 0;
                    free((*dictionaries)[dictionaryIndex].languages);
                    Dictionary* temp = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * numOfDictionaries);
                    if (temp != NULL) {
                        *dictionaries = temp;
                    }
                    free(inputLanguages);
                    return numOfDictionaries;
                }
            }
            //if we get here we suceed to crate all the things for the diractory so we finaaly add it
            dictionaryIndex++;//increase the number of them
            numOfDictionaries++;
            printf("The dictionary has been created successfully!\n");
            free(inputLanguages);//fre the input
            return numOfDictionaries;

        }
        else {//if there is no place for the array of languages
            printf("The creation of the dictionary has failed!\n");

            free(inputLanguages);//free the input
            (*dictionaries)[dictionaryIndex].numOfLanguages = 0;
            free((*dictionaries)[dictionaryIndex].languages);//free the array of languages
            Dictionary* temp = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * numOfDictionaries);
            if (temp != NULL) {
                *dictionaries = temp;//return the previous size of array dictionaries
            }
            return numOfDictionaries;
        }
    }
    else {//if there is no place for the input from the user
        printf("The creation of the dictionary has failed!\n");
        Dictionary* temp = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * numOfDictionaries);
        if (temp != NULL) {
            *dictionaries = temp;//return to the previous size of array dicitionaries
        }
        free(inputLanguages);//free the input
        return numOfDictionaries;
    }

}

/******************
* Function Name:printDictionaryNumberI
* Input:the array of dictionaries and an index of the array we want to print
* Output:none
* Function Operation:the function print the lagnuages of the array in the place of the index we get
******************/
void printDictionaryNumberI(Dictionary* dictionaries, int i) {

    for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {

        printf("%s", dictionaries[i].languages[j]);
        if (j != dictionaries[i].numOfLanguages - 1) {
            printf(",");
        }
    }

}
/******************
* Function Name:flushInput()
* Input:none
* Output:none
* Function Operation:cleaning the buffer before scanf
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
* Function Name:Dictionary options
* Input:array of dictionaries
* Output:the chosen input from the user
* Function Operation:the function prints all the options of dictionaries there are right now and it's getting
* a number from the user that the represnt the number of dictionary the user wanted to choose and it return the input
******************/
int DictionaryOptions(Dictionary* dictionaries) {
    int input = 0;
    while (dictionaryIndex != 0) {
        printf("Choose a dictionary:\n");
        for (int i = 0; i < dictionaryIndex; i++) {
            printf("%d. ", i + 1);
            printDictionaryNumberI(dictionaries, i);
            printf("\n");
        }
        int res = scanf("%d", &input);
        if (res == 0) {//if it's not an integer
            flushInput();
            input = -1;//to make the program understand it's an invalid input

        }

        if (input > 0 && input <= dictionaryIndex) {
            break;
        }

        else {
            printf("Wrong option, try again:\n");
        }

    }

    input--;//for making it an index for the array
    return input;
}


/******************
* Function Name:addAWord
* Input:array of dictionaries
* Output:none
* Function Operation:the function is getting the array of dictionaries and is getting translates and a word in some language
*and it's adding the translators to the chosen Dictionary as a Word type. its creating a Wordtype that is adding to the
*wordslist of the dictionary that the user chose
******************/
void addAWord(Dictionary* dictionaries) {

    if (dictionaries == NULL) {
        printf("dictionaries is NULL\n");
        return;
    }
    int input = DictionaryOptions(dictionaries);//chose the dictionary he wants to add the word to
    int nbLang = dictionaries[input].numOfLanguages;//the number of translators that will be
    if (nbLang <= 0) {
        printf("nb lang less than zero\n");
        return;
    }

    printf("Enter a word in ");
    printDictionaryNumberI(dictionaries, input);
    printf(":\n");

    char* newWords = malloc(SIZE * sizeof(char));
    if (newWords == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    scanf("%s", newWords);//getting the translators and the origin word

    Word* tmpWord = malloc(sizeof(Word));//create a place for the word
    if (tmpWord != NULL) {//if there is a plce for the word
        tmpWord->next = NULL;
        tmpWord->translations = (char**)malloc(nbLang * sizeof(char*));//crate a place for the translators array
        if (tmpWord->translations) {
            int startIndex = 0;
            int i = 0;
            int wordIndex = 0;

            while (newWords[i] != '\0' && wordIndex < nbLang) {
                if (newWords[i] == ',') {

                    int wordSize = i - startIndex;
                    tmpWord->translations[wordIndex] = malloc(wordSize + 1);//a place for the transalte itself

                    if (tmpWord->translations[wordIndex]) {
                        strncpy(tmpWord->translations[wordIndex], &newWords[startIndex], wordSize);
                        //copy the translate from the inputstring to the word transaltion array
                        tmpWord->translations[wordIndex][wordSize] = '\0';
                        wordIndex++;//number of the  translate increased
                    }
                    else {//there is no place for the translate
                        printf("The addition of the word has failed!\n");
                        free(tmpWord->translations);// free the translate
                        free(tmpWord);//free the word
                        free(newWords);//free the string
                        return;
                    }
                    startIndex = i + 1;//next translate check
                }
                i++;
            }
            //last word checking because there is \0 in the end and no , the same as the previous transaltions

            if (newWords[i] == '\0' && wordIndex < nbLang) {

                int wordSize = i - startIndex;
                tmpWord->translations[wordIndex] = malloc((wordSize + 1) * sizeof(char));
                if (tmpWord->translations[wordIndex]) {
                    strncpy(tmpWord->translations[wordIndex], &newWords[startIndex], wordSize);
                    tmpWord->translations[wordIndex][wordSize] = '\0';
                }
                else {
                    printf("The addition of the word has failed!\n");
                    free(tmpWord->translations);
                    free(tmpWord);
                    free(newWords);
                    return;
                }

            }
            else {//the array of transilitons have no place
                printf("The addition of the word has failed!\n");
                free(tmpWord->translations);//free the array
                free(tmpWord);//free the word
                free(newWords);//free the input
                return;
            }
        }
        else {//there is no place for the new Word
            printf("The addition of the word has failed!\n");
            free(tmpWord);//free the word
            free(newWords);//free the string
            return;
        }
    }
    else {//there is no place for the string
        printf("The addition of the word has failed!\n");
        free(newWords);//free the string
        return;
    }
    //now lets add the word to the wordlist of dictionary
    if (dictionaries[input].wordList == NULL) {
        dictionaries[input].wordList = tmpWord;//if its the first word just put it as first
    }
    else {
        Word* temp = dictionaries[input].wordList;
        while (temp->next != NULL) {//reach to the end of the list
            temp = temp->next;
        }
        temp->next = tmpWord;//put it in the end
    }

    printf("The word has been added successfully!\n");
    
    free(newWords);//free string
    return;
}

void printOriginalLanguage(Dictionary* dictionaries, int input) {
    printf("Enter a word in ");
    printf("%s:\n", dictionaries[input].languages[0]);
}

void deleteAWord(Dictionary* dictionaries) {

    int input = DictionaryOptions(dictionaries);
    printOriginalLanguage(dictionaries, input);

    char* chosenWords = malloc(SIZE * sizeof(char));
    scanf("%s", chosenWords);
    printf("Are you sure? (y/n)\n");
    char answer;
    scanf(" %c", &answer);

    if (answer != 'y') {
        printf("The deletion of the word has been canceled\n");
        free(chosenWords);
        return;
    }

    if (chosenWords == NULL) {
        printf("The deletion of the word has failed!\n");
        free(chosenWords);
        return;
    }

    Word* temp1 = dictionaries[input].wordList;
    int nbLang = dictionaries[input].numOfLanguages;
    int res = strcmp(temp1->translations[0], chosenWords);
    if (res == 0) {
        dictionaries[input].wordList = temp1->next;
        freeWord(temp1, nbLang);
        free(temp1);
    }
    else {
        Word* temp2 = temp1->next;

        while (temp2 != NULL) {
            res = strcmp(temp2->translations[0], chosenWords);

            if (res == 0) {
                temp1->next = temp2->next;

                break;
            }
            else {
                temp1 = temp2;
                temp2 = temp2->next;
            }
        }

        if (temp2 == NULL) {
            printf("The deletion of the word has failed!\n");
            free(chosenWords);
            return;
        }
        else {
            freeWord(temp2, nbLang);
            free(temp2);
            
        }
    }
    printf("The word has been deleted successfully!\n"); 
    free(chosenWords);
    return;

}

void searchAWord(Dictionary* dictionaries) {

    int input = DictionaryOptions(dictionaries);
    printOriginalLanguage(dictionaries, input);
    char* chosenWords = malloc(SIZE * sizeof(char));//free it
    scanf("%s", chosenWords);
    if (chosenWords == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }
    Word* temp = dictionaries[input].wordList;
    while (temp != NULL) {
        int res = strcmp(temp->translations[0], chosenWords);
        if (res == 0) {
            printf("The translations are:\n");
            int nbLang = dictionaries[input].numOfLanguages;
            for (int i = 1; i < nbLang; i++) {
                printf("%s: %s", dictionaries[input].languages[i], temp->translations[i]);
                if (i != nbLang - 1) {
                    printf(", ");
                }
            }
            printf("\n");
            free(chosenWords);
            return;
        }
        else {
            temp = temp->next;
        }
    }
    printf("There are no translations for \"%s\" in this dictionary.\n", chosenWords);
    free(chosenWords);
    return;
}

int deleteADictionary(Dictionary** dictionaries, int numOfDictionaries) {
    int input = DictionaryOptions(*dictionaries);
    printf("Are you sure? (y/n)\n");
    char answer;
    scanf(" %c", &answer);
    if (answer != 'y') {
        printf("The deletion of the dictionary has been canceled.\n");
        return numOfDictionaries;
    }
    
    Dictionary temp = (*dictionaries)[input];
    if (dictionaryIndex == 1) { // only one dictionary
        temp = (*dictionaries)[0];
        freeDictionary(temp);
        *dictionaries = NULL;
        dictionaryIndex--;
        numOfDictionaries--;
        printf("The dictionary has been deleted successfully!\n");
        return numOfDictionaries;
    }
    else { 

        temp = (*dictionaries)[input];
        for (int i = input; i < dictionaryIndex - 1; i++) {
            (*dictionaries)[i] = (*dictionaries)[i + 1];
        }
        freeDictionary(temp);

        Dictionary* tempForRealloc = (Dictionary*)realloc(*dictionaries, sizeof(Dictionary) * (numOfDictionaries - 1));
        if (tempForRealloc != NULL) {
            *dictionaries = tempForRealloc;
            dictionaryIndex--;
            numOfDictionaries--;
            printf("The dictionary has been deleted successfully!\n");
        }
        else {
            printf("The deletion of the dictionary has failed!\n");

        }
        return numOfDictionaries; 

    }

}

void freeAll(Dictionary** dictionaries) {
    if (*dictionaries != NULL) {
        for (int i = 0; i < dictionaryIndex; i++) {
            freeDictionary((*dictionaries)[i]);
            (*dictionaries)[i].numOfLanguages = 0;
        }
        dictionaryIndex = 0;
        free(*dictionaries);
        *dictionaries = NULL;
    }
}

Dictionary* runMenu(Dictionary** dictionaries, int numOfDictionaries) {
    int input = 0;
    int flag = 0;
    while (input != 6) {
        if (flag != 1) {
            printf("Welcome to the dictionaries manager!\nChoose an option:\n1. Create a new dictionary.\n2. Add a word to a dictionary.\n3. Delete a word from a dictionary.\n4. Find a word in a dictionary.\n5. Delete a dictionary.\n6. Exit.\n");
        }
        flag = 0;
        int res = scanf("%d", &input);
        if (res == 0) {
            flushInput(); //if it's not an integer
            input = -1;
        }
        switch (input)
        {
        case 1:
            numOfDictionaries = createDictionary(dictionaries, numOfDictionaries);
            break;
        case 2:
            if (dictionaryIndex == 0) {
                printf("This option is not available right now, try again:\n");
                flag = 1;
            }
            else {
                addAWord(*dictionaries);
            }
            break;
        case 3:
            if (dictionaryIndex == 0) {
                printf("This option is not available right now, try again:\n");
                flag = 1;
            }
            else {
                deleteAWord(*dictionaries);
            }
            break;
        case 4:
            if (dictionaryIndex == 0) {
                printf("This option is not available right now, try again:\n");
                flag = 1;
            }
            else {
                searchAWord(*dictionaries);
            }
            break;
        case 5:
            if (dictionaryIndex == 0) {
                printf("This option is not available right now, try again:\n");
                flag = 1;
            }
            else {
                numOfDictionaries = deleteADictionary(dictionaries, numOfDictionaries);
            }
            break;
        case 6:
            freeAll(dictionaries);
            break;
        default:
            printf("Wrong option, try again:\n");
            break;
        }
    }

    return *dictionaries;

}

int main() {
    int numOfDictionaries = 0;

    Dictionary* dictionaries = NULL;

    dictionaries = runMenu(&dictionaries, numOfDictionaries);
    if (dictionaries != NULL) {

        free(dictionaries);


    }
    dictionaries = NULL;
    numOfDictionaries = 0;
    printf("Bye!");
    return 0;


}
