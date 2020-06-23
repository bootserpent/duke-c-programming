#include "cards.h"
#include <assert.h>
#include <stdio.h>

void test_card_from_num();
int main(void) {
  test_card_from_num();


}


void test_assert() {
  card_t c1;
  c1.value = VALUE_KING;
  c1.suit = SPADES;
  printf("testing card Ks, expect pass\n");
  assert_card_valid(c1);

  card_t c2;
  c2.value = VALUE_ACE;
  c2.suit = NUM_SUITS;
  printf("testing card An, expect fail\n");
  assert_card_valid(c2);
}

void test_value_letter() {
  //value 13, should output king (K)
  card_t kingCard;
  kingCard.value = 13;
  kingCard.suit = SPADES;
  const char result = value_letter(kingCard);
  printf("kingCard result = %c\n", result);
  assert(result == 'K');
  printf("kingCard passed\n");

  //value 10, should output 10 '0'
  card_t tenCard;
  tenCard.value = 10;
  tenCard.suit = CLUBS;
  const char result2 = value_letter(tenCard);
  printf("tenCard result = %c\n", result2);
  assert(result2 == '0');
  printf("tenCard passed\n");

  //value 2, should output '2'
  card_t twoCard;
  twoCard.value = 2;
  twoCard.suit = HEARTS;
  const char result3 = value_letter(twoCard);
  printf("twoCard result = %c\n", result3);
  assert(result3 == '2');
  printf("twoCard passed\n");
}

void test_suit_letter() {
  //suit spades, should output 's'
  card_t spadesCard;
  spadesCard.value = VALUE_ACE;
  spadesCard.suit = SPADES;
  const char result = suit_letter(spadesCard);
  printf("spadesCard result = %c\n", result);
  assert(result == 's');
  printf("spadesCard passed\n");

  //suit hearts, should output 'h'
  card_t heartsCard;
  heartsCard.value = 4;
  heartsCard.suit = HEARTS;
  const char result2 = suit_letter(heartsCard);
  printf("heartsCard result = %c\n", result2);
  assert(result2 == 'h');
  printf("heartsCard passed\n");

  //suit diamonds, should output 'd'
  card_t diamondsCard;
  diamondsCard.value = 10;
  diamondsCard.suit = DIAMONDS;
  const char result3 = suit_letter(diamondsCard);
  printf("diamondsCard result = %c\n", result3);
  assert(result3 == 'd');
  printf("diamondsCard passed\n");

  //suit clubs, should output 'c'
  card_t clubsCard;
  clubsCard.value = 5;
  clubsCard.suit = CLUBS;
  const char result4 = suit_letter(clubsCard);
  printf("clubsCard result = %c\n", result4);
  assert(result4 == 'c');
  printf("clubsCard passed\n");

  //invalid suit, should default
  /*
    card_t invalidCard;
    invalidCard.value = 3;
    invalidCard.suit = NUM_SUITS;
    const char result5 = suit_letter(invalidCard);
  */
}

void test_card_from_letters() {
  //Kh (king of hearts)
  card_t c1 = card_from_letters('K', 'h');
  print_card(c1);

  //Ac (ace of clubs)
  card_t c2 = card_from_letters('A', 'c');
  print_card(c2);

  //2s (two of spades)
  card_t c3 = card_from_letters('2', 's');
  print_card(c3);

  //Dn (invalid case)
  card_t c4 = card_from_letters('D', 'n');
  print_card(c4);
}

void test_card_from_num() {
  //31, should return 9c
  unsigned num = 31;
  card_t result = card_from_num(num);
  print_card(result);

  //24, should return 8s
  unsigned num2 = 24;
  card_t result2 = card_from_num(num2);
  print_card(result2);

  //32, should return 0s
  unsigned num4 = 32;
  card_t result4 = card_from_num(num4);
  print_card(result4);

  //36, should return Js
  unsigned num3 = 36;
  card_t result3 = card_from_num(num3);
  print_card(result3);

  //51, should return Ac
  unsigned num5 = 51;
  card_t result5 = card_from_num(num5);
  print_card(result5 );
}
