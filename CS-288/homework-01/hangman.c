// Domenico Maisano
// CS-288-101

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define boolean type
typedef enum { false, true } bool;

const char ACTUAL_WORD[] = "STRENGTHEN";

// function prototypes
void game(char *);
void replace(char *, char, int *);

int main() {
  // will not contain more than 80 chars
  char word[100] = {};

  // fill the array with
  for (int i = 0; i < strlen(ACTUAL_WORD); i++) {
    word[i] = '*';
  }

  // welcome message
  printf("Welcome to Hangman!\n");
  printf("Try to guess the secret word one letter at a time.\n");

  // play the game
  game(word);

  return 0;
}

void game(char *word) {
  char letter;

  // allocate space for the pointers
  int *guesses = malloc(sizeof(int));
  bool *foundWord = malloc(sizeof(bool));

  // set # of guesses to 6
  *guesses = 6;

  // loop until exit condition is met
  while (true) {

    // print win message and exit
    if (strcmp(word, "STRENGTHEN") == 0) {
      printf("\nCongratulations you solved the word: '%s' with %i gusses remaining.\n", word, *guesses);
      break;
    }

    // print message if player lost and exit
    if (*guesses <= 0) {
      printf("\nYou ran out of guessed and lost.\n");
      break;
    }

    printf("\n# misses left = %i\tword = %s\nenter a letter: ", *guesses, word);
    scanf(" %c", &letter);

    letter = toupper(letter);

    for (int i = 0; i < strlen(ACTUAL_WORD); i++) {
      // reset foundWord to false
      if (i == 0) {
        *foundWord = false;
      }

      if (ACTUAL_WORD[i] == letter) {
        // specify that we found a match, so that the # of guesses isn't subtracted
        *foundWord = true;
        word[i] = letter;
      }

      // decrement # of guesses user has left
      else if (*foundWord == false && i == strlen(ACTUAL_WORD) - 1) {
        --(*guesses);
      }
    }
  }
}
