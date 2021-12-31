#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "deck.h"
#define MAX 10
#define FULL_DECK 52

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

deck_t* makeFullDeck() {
	deck_t* d = (deck_t*)malloc(sizeof(deck_t));

	d->n_cards = FULL_DECK;
	d->cards = (card_t**)malloc(d->n_cards * sizeof(card_t*));
	for (unsigned j = 0; j < d->n_cards; j++) {
		card_t* card = (card_t*)malloc(sizeof(card_t));
		if (card) {
			*card = card_from_num(j);
			d->cards[j] = card;
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
	deck_t* fd = makeFullDeck();
	// check for one of each card in the full deck and our deck
	for (int i = 0; i < count; i++) {
		card_t c = *(fd->cards[i]);
		int dc = deck_contains(d, c);
		assert(dc == 1);
	}
}

void add_card_to(deck_t* deck, card_t c) {
	//does the provided deck exist?
	if (deck == NULL) {
		printf("deck is null\n");
		return;
	}

	//is the deck new?
	if (deck->n_cards != 0) {
		deck->cards = (card_t**)realloc(deck->cards, sizeof(card_t*) * (deck->n_cards + 1));
	}
	else { // allocate for cards pointer in deck struct
		deck->cards = (card_t**)malloc(sizeof(card_t*));
	}

	//allocate for actual card
	deck->cards[deck->n_cards] = (card_t*)malloc(sizeof(card_t));

	//add suit and value to allocated slot
	deck->cards[deck->n_cards]->suit = c.suit;
	deck->cards[deck->n_cards]->value = c.value;
	deck->n_cards += 1;
}

card_t* add_empty_card(deck_t* deck) {

	//does the provided deck exist?
	if (deck == NULL) {
		printf("no deck found!\n");
		return NULL;
	}

	//placeholder card
	card_t c;
	c.suit = SUIT_PLACEHOLDER;
	c.value = VALUE_PLACEHOLDER;

	add_card_to(deck, c);

	//return pointer to recently added placeholder
	return deck->cards[deck->n_cards - 1];
}

deck_t* make_deck_exclude(deck_t* excluded_cards) {
	//create full deck
	deck_t* fullDeck = makeFullDeck();

	//make new deck
	deck_t* newDeck = (deck_t*)malloc(sizeof(deck_t));
	if (newDeck == NULL) {
		printf("memory allocation failed\n");
		return NULL;
	}


	newDeck->n_cards = 0;
	//loop through full deck
	for (int i = 0; i < FULL_DECK; i++) {
		//copy non excluded cards to new deck
		if (deck_contains(excluded_cards, *(fullDeck->cards[i])) == 0) {
			add_card_to(newDeck, *(fullDeck->cards[i]));
		}
	}

	//free full deck
	free_deck(fullDeck);

	//return new deck
	return newDeck;
}

int is_card_valid(card_t* c) {
	if (c->value == 0 && c->suit == 0) {
		return 0;
	}
	return 1;
}

deck_t* build_remaining_deck(deck_t** hands, size_t n_hands) {

	//malloc exclude_cards
	deck_t* exclude_cards = (deck_t*)malloc(sizeof(deck_t));
	exclude_cards->n_cards = 0;

	//add cardCount to n_cards field of exclude_cards
	for (int i = 0; i < (int)n_hands; i++) {

		//add each card from hands to exclude cards (add_card_to)
		for (int j = 0; j < (int)(hands[i]->n_cards); j++) {

			//check if cards are valid (0 means not valid)
			int isValid = is_card_valid(hands[i]->cards[j]);

			if (isValid == 0) {
				continue;
			}

			add_card_to(exclude_cards, *(hands[i]->cards[j]));
		}
	}

	//pass exclude_cards to make_deck_exclude
	deck_t* excludedDeck = make_deck_exclude(exclude_cards);
	free_deck(exclude_cards);

	//return remaining deck
	return excludedDeck;
}

void free_deck(deck_t* deck) {
	for (unsigned i = 0; i < deck->n_cards; i++) {
		if (deck->cards[i] != NULL) {
			free(deck->cards[i]);
			deck->cards[i] = NULL;
		}
		
	}
	free(deck);
}