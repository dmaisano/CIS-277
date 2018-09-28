/* Domenico Maisano */
/* CS-288-101 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i;

/* define boolean type */
typedef enum { false, true } bool;

/* global word variable */
const char ACTUAL_WORD[] = "JAVASCRIPT";

/* function prototypes */
void game(char *);

int main() {
  /* will not contain more than 80 chars */
  char word[81] = {};

  /* fill the array with placeholders */
  for (i = 0; i < strlen(ACTUAL_WORD); i++) {
    word[i] = '*';
  }

  /* welcome message */
  printf("Welcome to Hangman!\n");
  printf("Try to guess the secret word one letter at a time.\n");

  /* play the game */
  game(word);
}

void game(char *word) {
  char letter;
  int guesses = 6;

  bool matches = false;

  /* loop until an exit condition is met */
  while (true) {

    /* print win message and exit */
    if (!strcmp(word, ACTUAL_WORD)) {
      printf("\nCongratulations, You solved the word: '%s'\n", word);
      break;
    }

    /* print message if player lost and exit */
    if (guesses <= 0) {
      printf("\nYou ran out of guesses and lost.\n");
      break;
    }

    printf("\n# misses left = %i\tword = %s\nenter a letter: ", guesses, word);
    scanf(" %c", &letter);

    letter = toupper(letter);

    for (i = 0; i < strlen(ACTUAL_WORD); i++) {
      /* reset foundWord to false */
      if (i == 0) {
        matches = false;
      }

      if (ACTUAL_WORD[i] == letter) {
        /* found match */
        matches = true;
        word[i] = letter;
      }

      /* if a match was not found for the char... */
      /* decrement # of guesses user has left */
      else if (matches == false && i == strlen(ACTUAL_WORD) - 1) {
        --guesses;
      }
    }
  }
}
