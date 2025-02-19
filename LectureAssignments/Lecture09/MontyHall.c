#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  // MontyHall sim. Pick a door and one is a winner. Reveal a wrong door
  // randomly

  // Declare options array of size 3
  int i;
  int options[3];
  // Inititalze all as losers
  for (i = 0; i < 3; i++) {
    options[i] = 0;
  }
  // Seed random so its random each time
  srand(time(NULL));
  // The winning index is decided here
  int winner = rand() % 3;
  options[winner] = 1;
  // Prompt the user to pick an option
  printf("Choose an options 1, 2, or 3 to win a prize!\n");
  int selected;
  // Read in the option
  scanf("%d", &selected);
  // Randomly pick a direction to start find a random loser.
  // Either start from end of array moving down or start moving up.
  // Cannot reveal the winner or reveal the option selected by the player
  int direction = rand() % 2;
  int keeps_original = -1;
  if (direction) {
    for (i = 0; i < 3; i++) {
      if (i == selected - 1) {
        continue;
      }
      if (options[i] == 0) {
        printf("Option %d is a loser. Would you like to change your answer?? "
               "(0 for yes, 1 for no)\n",
               i + 1);
        break;
      }
    }
  } else {
    for (i = 2; i >= 0; i--) {
      if (i == selected - 1) {
        continue;
      }
      if (options[i] == 0) {
        printf(
            "Option %d is a loser. Would you like to change your answer?? (0 "
            "for yes, 1 for no)\n",
            i + 1);
        break;
      }
    }
  }
  // Read in players choice to change
  scanf("%d", &keeps_original);
  // If he wants to change re scan selected
  if (!keeps_original) {
    printf("Pick a new option 1, 2, or 3\n");
    scanf("%d", &selected);
  }
  // AND THE RESULT????
  if (options[selected - 1] == 1) {
    // OMG!
    printf("Congrats you win the prize!!!!\n");
  } else {
    //.....
    printf("Sorry you lost.\n");
  }
  return 0;
}
