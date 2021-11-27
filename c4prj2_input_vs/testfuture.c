#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "future.h"
#include "deck.h"
#include "input.h"
#pragma warning(disable : 4996)

void test_add_future_card();
future_cards_t* make_future_deck(size_t n_decks);
void test_future_cards_from_deck();
deck_t* myMakeDeckFromNums(int* nums, size_t num_cards);
void test_hand_from_string();
void test_hand_from_string_4_cards();
void test_add_future_card_nodecks();
void test_read_input();
void test_read_input_3_cards();

int main() {
	//test_add_future_card();
	//test_add_future_card_nodecks();
	//test_future_cards_from_deck();
	//test_hand_from_string();
	//test_hand_from_string_4_cards()
	//test_read_input();
	test_read_input_3_cards();
}

//usage:
//int nums[3] = { 12, 35, 8 };
//deck_t d = makeDeckFromNums(nums);
deck_t* myMakeDeckFromNums(int* nums, size_t num_cards) {
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

void test_add_future_card_nodecks() {
	int handOneNums[5] = { 1, 2, 3, 4, 5 };
	deck_t* hand1 = myMakeDeckFromNums(handOneNums, 5);
	card_t* emptyCard = add_empty_card(hand1);
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->n_decks = 0;
	add_future_card(fc, 3, emptyCard);

 	assert(fc->n_decks == 4);

}

void test_add_future_card() {
	//start with fc with 3 decks 
	future_cards_t* fc = make_future_deck(3);

	int handOneNums[5] = { 1, 2, 3, 4, 5 };
	deck_t* hand1 = myMakeDeckFromNums(handOneNums, 5);
	add_empty_card(hand1);
	add_empty_card(hand1);
	//add a future card to fc, index of 3 adds a deck to fc
	add_future_card(fc, 3, hand1->cards[5]);

	//assert that fc has the right amount of decks
	assert(fc->n_decks == 4);

	//checking in the deck added
	deck_t deck3 = fc->decks[3];

	//deck always has one card
	assert(deck3.n_cards == 1);
	//placeholder value and suit
	assert(hand1->cards[5]->value == deck3.cards[0]->value);
	assert(hand1->cards[5]->suit == deck3.cards[0]->suit);
}

future_cards_t* make_future_deck(size_t n_decks) {

	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));

	fc->n_decks = n_decks;
	fc->decks = (deck_t*)malloc(sizeof(deck_t) * n_decks);

	//individual decks start with zero cards
	for (int i = 0; i < (int)n_decks; i++) {
		fc->decks[i].n_cards = 0;
	}

	return fc;
}

void test_future_cards_from_deck() {
	//step 1: create input parameters
	int drawingCardNums[3] = { 48, 45, 27 };
	deck_t* drawingCards = myMakeDeckFromNums(drawingCardNums, 3);

	int hand1cards[2] = { 7, 11 };
	deck_t* hand1 = myMakeDeckFromNums(hand1cards, 2);

	int hand2cards[2] = { 13, 30 };
	deck_t* hand2 = myMakeDeckFromNums(hand2cards, 2);

	card_t* hand1card0 = add_empty_card(hand1); // ?0
	card_t* hand1card1 = add_empty_card(hand1); // ?1
	card_t* hand1card2 = add_empty_card(hand1); // ?2

	card_t* hand2card0 = add_empty_card(hand2); // ?0
	card_t* hand2card1 = add_empty_card(hand2); // ?1
	card_t* hand2card2 = add_empty_card(hand2); // ?2

	future_cards_t* fc = make_future_deck(3);

	fc->decks[0].n_cards = 2;
	fc->decks[0].cards = (card_t**)malloc(sizeof(card_t*) * fc->decks[0].n_cards);
	fc->decks[0].cards[0] = hand1card0;
	fc->decks[0].cards[1] = hand2card0;

	fc->decks[1].n_cards = 2;
	fc->decks[1].cards = (card_t**)malloc(sizeof(card_t*) * fc->decks[1].n_cards);
	fc->decks[1].cards[0] = hand1card1;
	fc->decks[1].cards[1] = hand2card1;

	fc->decks[2].n_cards = 2;
	fc->decks[2].cards = (card_t**)malloc(sizeof(card_t*) * fc->decks[2].n_cards);
	fc->decks[2].cards[0] = hand1card2;
	fc->decks[2].cards[1] = hand2card2;

	//step 2: call function
	future_cards_from_deck(drawingCards, fc);

	//step 3: validation
	assert(fc != NULL);
	for (int i = 0; i < fc->n_decks; i++) {
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
			assert(fc->decks[i].cards[j]->suit == drawingCards->cards[i]->suit);
			assert(fc->decks[i].cards[j]->value == drawingCards->cards[i]->value);
		}
	}
}

void test_hand_from_string() {
	const char* handStr = "3c 4c ?0 ?1 ?2";

	future_cards_t* fc = (future_cards_t *) malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	//populate fc with handStr future cards
	deck_t* hand = hand_from_string(handStr, fc);

	assert(hand->n_cards == 5);

	assert(hand->cards[0]->suit == CLUBS);
	assert(hand->cards[0]->value == 3);

	assert(hand->cards[1]->suit == CLUBS);
	assert(hand->cards[1]->value == 4);

	//assert placeholder cards match fc value and suit
	for (int i = 2; i < 5; i++) {
		assert(hand->cards[i]->suit == 0);
		assert(hand->cards[i]->value == 0);
	}

	assert(fc->n_decks == 3);

	for (int i = 0; i < fc->n_decks; i++) {
		assert(fc->decks[i].cards[0]->suit == 0);
		assert(fc->decks[i].cards[0]->value == 0);
		assert(fc->decks[i].n_cards == 1);
	}
}

void test_hand_from_string_4_cards() {
	//assert exit with EXIT_FAILURE
}

void test_read_input() {
	FILE* f = fopen("test1.txt", "r");
	size_t* n_hands = (size_t*)malloc(sizeof(size_t));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	deck_t** decks = read_input(f, n_hands, fc);
	int numHands = *n_hands;
	//check both hands regular cards and # of hands
	assert(numHands == 2);
	for (int i = 0; i < numHands; i++) {
		assert(decks[i]->n_cards == 5);
		switch (i) {
		case 0:
			assert(decks[i]->cards[0]->suit == CLUBS);
			assert(decks[i]->cards[0]->value == 3);
			assert(decks[i]->cards[1]->suit == CLUBS);
			assert(decks[i]->cards[1]->value == 4);
			break;
		case 1:
			assert(decks[i]->cards[0]->suit == HEARTS);
			assert(decks[i]->cards[0]->value == 5);
			assert(decks[i]->cards[1]->suit == DIAMONDS);
			assert(decks[i]->cards[1]->value == 9);
			break;

		}
	}

	//check fc and future cards
	assert(fc->n_decks == 3);
	for (int i = 0; i < fc->n_decks; i++) {
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
			assert(fc->decks[i].cards[j]->suit == 0);
			assert(fc->decks[i].cards[j]->value == 0);
		}
	}

	//check future cards added to hands properly
	future_cards_t* fcEmpty = (future_cards_t*)malloc(sizeof(future_cards_t));
	fcEmpty->decks = NULL;
	fcEmpty->n_decks = 0;

	deck_t* keyDeck = hand_from_string("As Kh 8c", fcEmpty);
	future_cards_from_deck(keyDeck, fc);
	for (int i = 0; i < numHands; i++) {
		for (int j = 2; j < decks[i]->n_cards; j++) {
			assert(decks[i]->cards[j]->suit == keyDeck->cards[j - 2]->suit);
			assert(decks[i]->cards[j]->value == keyDeck->cards[j - 2]->value);
		}
	}

}

void test_read_input_3_cards() {
	FILE* f = fopen("testthreecards.txt", "r");
	size_t* n_hands = (size_t*)malloc(sizeof(size_t));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	int errorCode = read_input(f, n_hands, fc);
	assert(errorCode == EXIT_FAILURE);
	
}