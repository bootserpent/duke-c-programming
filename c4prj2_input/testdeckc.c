#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "deck.h"
#include "eval.h"

void test_add_empty_card();
void test_add_empty_card_null_deck();
void test_add_empty_card_limit_deck();
void test_make_deck_exclude_five_cards();
void test_build_remaining_deck();
deck_t* make_hand(card_t c1, card_t c2, size_t n_empty_cards);
void test_get_match_counts();

int my_main() {
	//test_add_empty_card();
	//test_add_empty_card_null_deck();
	/*test_add_empty_card_limit_deck();*/
	/*test_make_deck_exclude_five_cards();*/
	test_build_remaining_deck();
	/*test_get_match_counts();*/
    return 0;
}

//usage:
//int nums[3] = { 12, 35, 8 };
//deck_t d = makeDeckFromNums(nums);
deck_t* makeDeckFromNums(int* nums, size_t num_cards) {
	deck_t* d = (deck_t*)malloc(sizeof(deck_t));
	d->n_cards = num_cards;
	d->cards = (card_t**)malloc(d->n_cards * sizeof(card_t*));
	for (unsigned int i = 0; i < num_cards; i++) {
		card_t* card = (card_t*)malloc(sizeof(card_t));
		if (card) {
			*card = card_from_num(nums[i]);
			d->cards[i] = card;
		}
		else {
			printf("memory allocation failed\n");
		}
	}
	return d;
}

void test_add_empty_card() {
    //1 card deck
	int nums[2] = { 15, 3 };
	deck_t* d = makeDeckFromNums(nums, 2);
	card_t* cPtr = add_empty_card(d);
	int contains = deck_contains(d, *cPtr);
	assert(contains == 1);
}

void test_add_empty_card_null_deck() { 
	//null deck, error
	deck_t* d = NULL;
	card_t* cPtr = add_empty_card(d);
	assert(cPtr == NULL);
}

void test_add_empty_card_limit_deck() {
	//10 cards, force realloc
	int nums[10] = { 10, 32, 35, 15, 23, 26, 14, 20, 18, 8 };
	deck_t* d = makeDeckFromNums(nums, 10);
	card_t* cPtr = add_empty_card(d);
	int contains = deck_contains(d, *cPtr);
	assert(contains == 1);
}

void test_make_deck_exclude_five_cards() {
	//5 cards to exclude
	int exclude[5] = { 46, 18, 21, 12, 15 };
	deck_t* d = makeDeckFromNums(exclude, 5);
	deck_t* excludedDeck = make_deck_exclude(d);

	//check cards from exclude not in excludedDeck
	for (int i = 0; i < 5; i++) {
		int contains = deck_contains(excludedDeck, *(d->cards[i]));
		assert(contains == 0);
	}
	assert(excludedDeck->n_cards == 47);

	//3 random cards to check for in excludedDeck
	int include[3] = { 36, 13, 47 };

	//check cards from include are in excludedDeck
	deck_t* includeDeck = makeDeckFromNums(include, 3);
	for (int i = 0; i < 3; i++) {
		int contains = deck_contains(excludedDeck, *(includeDeck->cards[i]));
		assert(contains == 1);
	}
}

void test_build_remaining_deck() {
	//build hand 1
	card_t c1 = card_from_letters('K', 'h');
	card_t c2 = card_from_letters('Q', 's');
	deck_t* hand1 = make_hand(c1, c2, 5);

	//build hand 2
	card_t c3 = card_from_letters('A', 's');
	card_t c4 = card_from_letters('A', 'c');
	deck_t* hand2 = make_hand(c3, c4, 5);

	deck_t* hands[2] = { hand1, hand2 };

	deck_t* newDeck = build_remaining_deck(hands, 2);

	assert(newDeck->n_cards == 48);

	card_t cards[4] = { c1, c2, c3, c4 };

	for (int i = 0; i < 4; i++) {
		assert(deck_contains(newDeck, cards[i]) == 0);
	}

	//3 random cards to check for in newDeck
	int include[3] = { 36, 13, 47 };

	//check cards from include are in excludedDeck
	deck_t* includeDeck = makeDeckFromNums(include, 3);
	for (int i = 0; i < 3; i++) {
		int contains = deck_contains(newDeck, *(includeDeck->cards[i]));
		assert(contains == 1);
	}

}

deck_t* make_hand(card_t c1, card_t c2, size_t n_empty_cards) {
	deck_t* hand = (deck_t*)malloc(sizeof(deck_t));
	hand->n_cards = 0;

	add_card_to(hand, c1);
	add_card_to(hand, c2);

	for (int i = 0; i < n_empty_cards; i++) {
		add_empty_card(hand);
	}

	return hand;
}

void test_get_match_counts() {
	int cards[8] = { 44, 45, 40, 41, 32, 30, 31, 29 };
	deck_t* hand = makeDeckFromNums(cards, 8);
	unsigned * matchCounts = get_match_counts(hand);
	unsigned expectedCounts[8] = { 2, 2, 2, 2, 1, 3, 3, 3 };

	for (int i = 0; i < 8; i++) {
		assert(matchCounts[i] == expectedCounts[i]);
	}
}