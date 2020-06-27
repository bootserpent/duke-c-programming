#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1



void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= 14);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  char buffer[30];
  memset(buffer, '\0', sizeof(buffer));
  char * bufferptr = buffer;

  switch (r) {
  case STRAIGHT_FLUSH:
    strcpy(buffer, "straight flush");
    break;
  case FOUR_OF_A_KIND:
    strcpy(buffer, "four of a kind");
    break;
  case FLUSH:
    strcpy(buffer, "flush");
    break;
  case STRAIGHT:
    strcpy(buffer, "straight");
    break;
  case THREE_OF_A_KIND:
    strcpy(buffer, "three of a kind");
    break;
  case TWO_PAIR:
    strcpy(buffer, "two pairs");
    break;
  case PAIR:
    strcpy(buffer, "a pair");
    break;
  case NOTHING:
    strcpy(buffer, "nothing");
    break;
  default:
    printf("oh no, hit unexpected case %d", r);
    strcpy(buffer, "oh no, hit expected case");
  }

  printf("In function ranking_to_string, buffer returned is %s", buffer);
  return bufferptr;
}

char value_letter(card_t c) {
  char buffer2[1];
  memset(buffer2, '\0', sizeof(buffer2));
  if (c.value >= 2 && c.value <= 9) {
    buffer2[0] = '0' + c.value;
    return buffer2[0];
  }
  switch (c.value) {
  case 10:
    buffer2[0] = '0';
    break;
  case 11:
    buffer2[0] = 'J';
    break;
  case 12:
    buffer2[0] = 'Q';
    break;
  case 13:
    buffer2[0] = 'K';
    break;
  case 14:
    buffer2[0] = 'A';
    break;
  default:
    printf("invalid input received at value_letter: %d\n", c.value);
  }
  return buffer2[0];
}


char suit_letter(card_t c) {
  char x;
  switch (c.suit) {
  case SPADES:
    x = 's';
    break;
  case HEARTS:
    x = 'h';
    break;
  case DIAMONDS:
    x = 'd';
    break;
  case CLUBS:
    x = 'c';
    break;
  default:
    printf("invalid suit\n");
  }
  return x;
}

void print_card(card_t c) {
  char vl = value_letter(c);
  char sl = suit_letter(c);
  printf("%c%c", vl, sl);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if ('2' <= value_let && value_let <= '9') {
    temp.value = value_let - '0';
  }
  else {
    switch (value_let)
      {
      case '0':
	temp.value = 10;
	break;
      case 'J':
	temp.value = 11;
	break;
      case 'Q':
	temp.value = 12;
	break;
      case 'K':
	temp.value = 13;
	break;
      case 'A':
	temp.value = 14;
	break;
      default:
	printf("invalid value");
      }
  }

  switch (suit_let) {
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
  default:
    printf("invalid suit\n");
    temp.suit = NUM_SUITS;
  }
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {

  card_t temp;
  c += 8;
  int value = c / 4;
  int suit = c % 4;
  temp.value = value;
  switch (suit) {
  case 0:
    temp.suit = SPADES;
    break;
  case 1:
    temp.suit = HEARTS;
    break;
  case 2:
    temp.suit = DIAMONDS;
    break;
  case 3:
    temp.suit = CLUBS;
    break;
  default:
    printf("invalid suit value: %d\n", suit);
  }
  return temp;
}
