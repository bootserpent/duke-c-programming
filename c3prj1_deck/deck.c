#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "deck.h"


void print_hand(deck_t* hand) {
  int count = hand->n_cards;
  for (int i = 0; i < count; i++) {
    // iterates through cards
    print_card(*(hand->cards[i]));
  }
}

int deck_contains(deck_t* d, card_t c) {
  int count = d->n_cards;
  for (int i = 0; i < count; i++) {
    // checking that cards are equal
    card_t card = *(d->cards[i]);
    if (card.value == c.value && card.suit == c.suit) {
      return 1;
    }
  }
  return 0;
}


void shuffle(deck_t* d) {
  int count = d->n_cards;

  int randCardIndex;
  for (int idx = 0; idx < count; idx++) {
    randCardIndex = rand() % count;
    //swapping card at idx with card randCardIndexs
    card_t* temp = d->cards[randCardIndex];
    d->cards[randCardIndex] = d->cards[idx];
    d->cards[idx] = temp;
  }
  /*printf("\n");
    print_hand(d);*/
}
void shuffle_bak(deck_t* d) {
  int count = d->n_cards;
  card_t* shuffledCards = (card_t*)malloc(count * sizeof(card_t));
  int randCard;
  for (int idx = 0; idx < count; idx++) {
    randCard = rand() % count;
    while (d->cards[randCard] == NULL) {
      randCard = rand() % count;
    }
    shuffledCards[idx] = *(d->cards[randCard]);
    //free(d->cards[randCard]);
    d->cards[randCard] = NULL;
  }
  /*printf("\n");*/
  for (int i = 0; i < count; i++) {
    d->cards[i] = &shuffledCards[i];

  }
  // print_hand(d);

}

deck_t makeFullDeck() {
  deck_t d;

  d.n_cards = 52;
  d.cards = (card_t**)malloc(d.n_cards * sizeof(card_t*));
  for (int j = 0; j < d.n_cards; j++) {
    card_t* card = (card_t*)malloc(sizeof(card_t));
    if (card) {
      *card = card_from_num(j);
      d.cards[j] = card;
    }
    else {
      printf("memory alloc failed\n");
    }

  }
  return d;
}

void assert_full_deck(deck_t* d) {
  int count = d->n_cards;
  assert(count == 52);
  // make full deck
  deck_t fd = makeFullDeck();
  // check for one of each card in the full deck and our deck
  for (int i = 0; i < count; i++) {
    card_t c = *(fd.cards[i]);
    int dc = deck_contains(d, c);
    assert(dc == 1);
  }
}
