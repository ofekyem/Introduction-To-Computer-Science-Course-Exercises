#include <stdio.h>
#include <math.h>
#include <string.h> 
/***********************
* Ofek Yemini
* 4
***********************/
#define ROW_LENGTH 21/*every word can contain 20 letters or less. the another one is for '\0'*/
#define COL_LENGTH 16/*number of words can be 15 or less. the extra one is for the clue*/  
#define GUESS_LENGTH 26/*there are 5 more than 20 for every wrong letter and the extra for'\0'*/
int numOfWords = 0;/*contains how many words there are in options*/
int mistakes = 0; /*how many mistakes you have done till now*/
int letterIsHere = 0;/*if the letter is right it will change to 1*/
char words[COL_LENGTH][ROW_LENGTH]; /*the array contains the clue and the words the user put. clue is in 0 row and the other words below him*/
char guess[GUESS_LENGTH];/*guess letters list*/
char currentWord[ROW_LENGTH];/*the array contains the right words the user had found and all the other words are '_' or space*/


/******************
* Function Name:PreRunGame();
* Input:none
* Output:-1 if the user didn't enter any word. else it returns the option the user has chose to play on 
* Function Operation: the function first getting the clue and words from user(if the user didn't enterany words
the function is returning -1 )and then it organize the working input in array so the clue is in the first row 
of the array. and the other words are in the other rowsnorganize in ASCCI value order.
and then the fuction is printing the options of words and then the user choosing  the option he wants to play
and the function returns the option he chose.
******************/

int preRunGame(){
    
    printf("Enter your words:\n");
    
    char input;
    for (int i = 0; i < COL_LENGTH; i++) {

        for (int j = 0; j < ROW_LENGTH; j++) {
            scanf("%c", &input);
            if (i == 0 && j == 0 && input == '\n') {
                return -1;/*the user just pressed Enter button with no words*/

            }
            if (input == ':' || input == ',' || input == '\n') {
                words[i][j] = '\0';/*if its : , or \n then its the end of the word, put \0 so we can know where is the end*/
                break;
            }
            else {
                words[i][j] = input;/*put the char in the array*/

            }
        }

        numOfWords++;/*there is one more word in array*/
        if (input == '\n') {
            break;/*if it's the end of the input, then out*/
        }

    } 
    char temp[ROW_LENGTH];/*temp for the bubble sort of words, the loop will start from 1 and not 0 because 
                            0 represnet the clue which we don't need to change its place*/
    for (int i = 1; i < numOfWords - 1; i++) {
        for (int j = i + 1; j < numOfWords; j++) {
            int res = strcmp(words[i], words[j]);
            if (res > 0) {/*if the next word is smaller*/
                strcpy(temp, words[j]); /*swap*/
                strcpy(words[j], words[i]);
                strcpy(words[i], temp);
            }
        }
        
    }
     
    printf("choose an option:\n");
    char letter; 
    /*this loop prints the options the user can choose from the words array.
      it starting from 1 and not 0 because 0 is the clue*/
    for (int i = 1; i < numOfWords; i++) {

        printf("%d: ", i);

        for (int j = 0; j < ROW_LENGTH; j++) {
            letter = words[i][j];
            if (words[i][j] == '\0') {
                break;
            }
            printf("%c", words[i][j]);

        }
        printf("\n");

    } 
    int option;
    scanf("%d", &option); 
    return option;/*the option the user chose is returned*/
    
} 
/******************
* Function Name:currentWordSetUp()
* Input:the option the user chose
* Output:none
* Function Operation: the function sets up the word that the user is suppose to guess which is the option
  place in the array.for every letter its putting a'_' instead. and for every space it's keeping it as sapce 
  the hiding word is placed in the array currentWord.
******************/

void currentWordSetUp(int option) {

    for (int i = 0; i < ROW_LENGTH; i++) {
        char letter = words[option][i];
        if (letter == '\0') {
            currentWord[i] = '\0';
            break;
        }
        else if (letter == ' ') {
            currentWord[i] = ' ';
        }
        else {
            currentWord[i] = '_';
        }
    } 
    

}

/******************
* Function Name:printMan()
* Input:number of mistakes yet
* Output:none
* Function Operation:the function is printing the status of the man by the number of mistakes the user has made
  there are 6 options the man can be printed.  
******************/

void printMan(int mistakes) {
    
            printf(" _________________\n");
        switch (mistakes) {
        case 0:
            printf("|                |\n");
            printf("|                |\n");
            printf("|                |\n");
            printf("|                |\n");
            printf("|                |\n");
            break;
        case 1:
            printf("|                |\n");
            printf("|  **            |\n");
            printf("|  **            |\n");
            printf("|                |\n");
            printf("|                |\n"); 
            break;
        case 2:
            printf("|                |\n");
            printf("|  **        **  |\n");
            printf("|  **        **  |\n");
            printf("|                |\n");
            printf("|                |\n"); 
            break;
        case 3:
            printf("|  --            |\n");
            printf("|  **        **  |\n");
            printf("|  **        **  |\n");
            printf("|                |\n");
            printf("|                |\n"); 
            break; 
        case 4:
            printf("|  --        --  |\n");
            printf("|  **        **  |\n");
            printf("|  **        **  |\n");
            printf("|                |\n");
            printf("|                |\n"); 
            break; 
        case 5:
            printf("|  --        --  |\n");
            printf("|  **        **  |\n");
            printf("|  **        **  |\n");
            printf("|                |\n");
            printf("| \\/\\/\\/\\/\\/\\/\\  |\n");
            break;
        }
        
        printf("|________________|\n");
        
    
} 

/******************
* Function Name: PrintCurrent()
* Input:the option the user chose
* Output:none
* Function Operation: the function prints the array of the hidding word(CurrentWord). if the user has already
*found some letters then the function will print the Letters in normal way (it's printing what is showing in the 
 currentWord array).
******************/

void printCurrent(int option) {
    for (int i = 0; i < ROW_LENGTH; i++) {
        if (currentWord[i] == '\0') {
            break;
        }
        printf("%c", currentWord[i]);
    }
    printf("\n");

} 

/******************
* Function Name:printGuess()
* Input:none
* Output:none
* Function Operation:the function prints which words the user already found. its printing the guess array which
* is holding the previous inputs the user put.
******************/

void printGuess() {
    printf("The letters that you already tried:");
    int i = 0;
    if (guess[i] != '\0') {
        printf(" "); /*if the array is empty there is no use for the space*/
    }
    while (guess[i] != '\0')
    {
        printf("%c", guess[i]);
        if (guess[i + 1] != '\0') {
            printf(", ");/*if there will be another letter then put ','*/
        }
        i++;
    }
    printf("\n");
} 

/******************
* Function Name:printClue()
* Input:none
* Output:none
* Function Operation: the function prints the clue that is in the 0 row of the array words[] 
******************/

void printClue() {
    printf("the clue is: ");
    for (int i = 0; i < ROW_LENGTH; i++) {
        if (words[0][i] == '\0') {
            break;
        }
        printf("%c", words[0][i]);
    }
    printf(".\n");
} 

/******************
* Function Name:updateCurrent()
* Input:the option of word the user chose. and the last input the letter put.
* Output:none
* Function Operation:the function is updating the hiding word if the input is in the real word(words[option]).
  if it is in there, the value of'_' in currentWord[]in the input place will change to the input.
  if it's not in there then the user made mistake so "mistakes" is raising up.
******************/

void updateCurrent(int option,char input) {

    
    for (int i = 0; i < ROW_LENGTH; i++) { 
        if (currentWord[i] == '\0') {
            break;
        }
        if (input == words[option][i]) {
            currentWord[i] = input;  
            letterIsHere = 1;/*the letter is here becomes true*/
        }
        
    }

    if (letterIsHere == 0) {/*if the letterIsHere still false and the letter isn't in the original word*/
        mistakes++;
    }
    
} 

/******************
* Function Name: updateGuess()
* Input:the last input Letter the user put
* Output:
* Function Operation:the function is adding the last input to the guess array
it's adding it in the last place of the array.
******************/

void updateGuess(int input) {
    if (input != '_') {/*if it's the first round of the game with no input then there is no need to add it*/
        for (int j = 0; j < GUESS_LENGTH - 1; j++) {
            if (guess[j] == '\0') {
                guess[j] = input;
                guess[j + 1] = '\0'; /*puts the input in the current index and making the next one \0 
                                     so the next one will be the end of the array*/
                break;/*the guess list over so out*/
            }
        }
    }
    
} 

/******************
* Function Name:checkGuessInput()
* Input: the last input letter the user put
* Output:1 if the input is already in the guess list. 0 if it isn't there
* Function Operation: the function gets the input and it's checking if the input is already been in the guess list,
  meaning: if the user already chose this letter before. if it is then the function returns 1
  else, the function returns 0
******************/

int checkGuessInput(char input) {
    int i = 0;
    while (guess[i] != '\0') {
        if (input == guess[i]) {
            return 1;
        } 
        i++;
    } 
    return 0;
} 

/******************
* Function Name:runGame()
* Input:the option the user chose from the words
* Output:0 for win, 1 for loose
* Function Operation: this is the main function of the game. it's running till there is a win or a loose.
the function is using the functions cuurentWordSetUp(),PrintMan(),PrintCurrent(),PrintGuess(),PrintClue(),
updateCurrent(),checkGuessInput() and updateGuess() which are described upwards in the code.
******************/

int runGame(int option) { 
    int clue = 1; /*there is one clue in the begining, it will change if someone will use it*/
    char input = '_';/*the user didn't already put an input so we put'_' till he will choose it*/
    currentWordSetUp(option);/*calling the function which is setting Currentword[] to be the hidden chosen word*/
    guess[0] = '\0';/*there are no already guess so we indicate that the list is empty*/
    /*the loops is going till there is a win or loose*/
    while (1) {
        
        printMan(mistakes);/*print the current status of the Man*/
        if (mistakes == 5) {/*if there are 5 mistakes then the shape of the man is the last one and the user lost*/
            return 1;/*lost the game so return 1*/
        }
        
        int res = strcmp(words[option], currentWord);
        /*compare the hidden word with the real word. if the hidden word(currentWord[]) already discovered fully
        then the words will be eqaul and res will be 0, else res will not be 0 and the words arent eqaul*/
        if (res == 0) {
            return 0;/*win the game so return 0*/
        }
        
        printCurrent(option);/*print the current hidden word depends on the values of cuurentWords[]*/
        if (clue == 1) {
            /*if the user haven't already used the clue so he can choose it so it prints
            if he want to use it*/
            printf("do you want a clue? press -> *\n");
        }
        printGuess();/*prints the guess list(the letters that were choosen previously)
                     the print depends on the values of guess[]*/
        
        letterIsHere = 0;/*set to zero before the input*/
        printf("please choose a letter:");  
        scanf(" %c", &input); 
        printf("\n"); 

        if (input == '*') {/*if the user wants a clue*/
            if (clue == 1) {/*it he haven't already used the clue*/
                printClue();/*print the clue*/
                clue = 0;/*change it to 0 so we will know he already used it*/
            } 
        }
        else {/*if the input isn't '*' */
            updateCurrent(option, input);/*update the hidden word with the new input if needed*/

            res = checkGuessInput(input);/*check if the input already been in the guessed letters list*/
            
            if (res == 1) {/*if the letter is in there*/
                printf("You've already tried that letter.\n");
                
                if (letterIsHere == 0) {/*if the letter isn't in in the original word*/
                    mistakes--;
                    /*it isn't a mistake cause the letter already been chose previously.the mistake has counted earlier in 
                    the function updateCurrent() so we will remove it from "mistakes" in this case */
                }
                
            } 
            else {/*the letter isn't in guess[] so add it*/
                updateGuess(input);
            }
            
        }
         
    } 

    return 0;

}

/******************
* Function Name:endGame()
* Input:the result of the game(if 1 is lose and 0 is win), and the option the user chose from the words in the begining
* Output:none
* Function Operation: the function is getting the result of the game and prints for 1 a losing message,
  and for 0 a win message. the function prints the choosen option word for both cases. 
******************/

void endGame(int res,int option) {
    
    printf("The word is ");
    int i = 0;
    while (words[option][i] != '\0') {
        printf("%c", words[option][i]);/*prints the choosen option word*/
        i++;
    }

    if (res == 0) {
        printf(", good job!");
        return;/*win*/
    }
    else {
        printf(", GAME OVER!");
        return;/*lose*/
    }
} 

int main() { 
    int option=preRunGame(); /*the function returns the option number the user chose from the words
                             it retruns -1 if clue and words haven't been put*/
    if (option != -1) {/*if the user did put words and clue*/
        int res = runGame(option);/*call the function.res will have the game result 1 or 0 for lose or win precisely*/
        endGame(res, option);/*print win or lose meesage depends on res value(1 or 0)*/
    }
    return 0;/*end program*/

    
}
