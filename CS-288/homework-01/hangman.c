#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototype
void game(char *, int *);

int main() {
  char word[] = "**********"; // "STRENGTHEN"
  int guesses = 6;

  // welcome message
  printf("Welcome to Hangman!\n");
  printf("Try to guess the secret word one letter at a time.\n");

  // play the game
  game(word, &guesses);

  return 0;
}

void game(char *word, int *guesses) {
  char letter = '\0';

  // loop until exit condition is met
  while (1) {

    // print win message and exit
    if (strcmp(word, "STRENGTHEN") == 0) {
      printf("\nCongratulations you solved the word: '%s' with %i gusses remaining.\n", word, *guesses);
      break;
    }

    // print message is player lost and exit
    if (*guesses <= 0) {
      printf("\You ran out of guessed and lost.\n");
      break;
    }

    printf("\n# misses left = %i\tword = %s\nenter a letter: ", *guesses, word);
    scanf(" %c", &letter);

    letter = toupper(letter);

    // "STRENGTHEN"
    switch (letter) {
    case 'S':
      word[0] = 'S';
      break;

    case 'T':
      word[1] = 'T';
      word[6] = 'T';
      break;

    case 'R':
      word[2] = 'R';
      break;

    case 'E':
      word[3] = 'E';
      word[8] = 'E';
      break;

    case 'N':
      word[4] = 'N';
      word[9] = 'N';
      break;

    case 'G':
      word[5] = 'G';
      break;

    case 'H':
      word[7] = 'H';
      break;

    default:
      // decrement # of guesses user has left
      --(*guesses);
      break;
    }
  }
}
