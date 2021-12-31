#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#pragma warning(disable : 4996)

void test_compare_n_hands_2_hands();
void test_compare_n_hands_3_hands();
void test_compare_n_hands_3_hands_tie();

int testmain() {
	//test_compare_n_hands_2_hands();
	//test_compare_n_hands_3_hands();
	//test_compare_n_hands_3_hands_tie();

	return 0;
}

void test_compare_n_hands_2_hands() {
	FILE* f = fopen("test1.txt", "r");
	int* n_hands = (int*)malloc(sizeof(int));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	deck_t** hands = read_input(f, n_hands, fc);
	int num_hands = *n_hands;

	//Create a deck with the remaining cards (build_remaining_deck)
	deck_t* remainingDeck = build_remaining_deck(hands, num_hands);

	//Create array to count wins and ties (e.g. two hands requires 3 elements)
	hand_result_t* gameResults = (hand_result_t*)malloc(num_hands * sizeof(hand_result_t));
	for (int i = 0; i < num_hands; i++) {
		gameResults[i].wins = 0;
		gameResults[i].losses = 0;
		gameResults[i].ties = 0;
	}

	compare_n_hands(hands, gameResults, num_hands);

	assert(num_hands == 2);

	assert(gameResults[0].losses == 0);
	assert(gameResults[0].wins == 1);
	assert(gameResults[0].ties == 0);
	
	assert(gameResults[1].losses == 1);
	assert(gameResults[1].wins == 0);
	assert(gameResults[1].ties == 0);
}

void test_compare_n_hands_3_hands() {
	FILE* f = fopen("threehandtest.txt", "r");
	int* n_hands = (int*)malloc(sizeof(int));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	deck_t** hands = read_input(f, n_hands, fc);
	int num_hands = *n_hands;

	//Create a deck with the remaining cards (build_remaining_deck)
	deck_t* remainingDeck = build_remaining_deck(hands, num_hands);

	//Create array to count wins and ties (e.g. two hands requires 3 elements)
	hand_result_t* gameResults = (hand_result_t*)malloc(num_hands * sizeof(hand_result_t));
	for (int i = 0; i < num_hands; i++) {
		gameResults[i].wins = 0;
		gameResults[i].losses = 0;
		gameResults[i].ties = 0;
	}

	compare_n_hands(hands, gameResults, num_hands);

	assert(num_hands == 3);

	assert(gameResults[0].losses == 1);
	assert(gameResults[0].wins == 0);
	assert(gameResults[0].ties == 0);
	
	assert(gameResults[1].losses == 1);
	assert(gameResults[1].wins == 0);
	assert(gameResults[1].ties == 0);
	
	assert(gameResults[2].losses == 0);
	assert(gameResults[2].wins == 1);
	assert(gameResults[2].ties == 0);
}

void test_compare_n_hands_3_hands_tie() {
	FILE* f = fopen("threehandtie.txt", "r");
	int* n_hands = (int*)malloc(sizeof(int));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	deck_t** hands = read_input(f, n_hands, fc);
	int num_hands = *n_hands;

	//Create a deck with the remaining cards (build_remaining_deck)
	deck_t* remainingDeck = build_remaining_deck(hands, num_hands);

	//Create array to count wins and ties (e.g. two hands requires 3 elements)
	hand_result_t* gameResults = (hand_result_t*)malloc(num_hands * sizeof(hand_result_t));
	for (int i = 0; i < num_hands; i++) {
		gameResults[i].wins = 0;
		gameResults[i].losses = 0;
		gameResults[i].ties = 0;
	}

	compare_n_hands(hands, gameResults, num_hands);

	assert(num_hands == 3);

	assert(gameResults[0].losses == 0);
	assert(gameResults[0].wins == 0);
	assert(gameResults[0].ties == 1);
	
	assert(gameResults[1].losses == 0);
	assert(gameResults[1].wins == 0);
	assert(gameResults[1].ties == 1);
	
	assert(gameResults[2].losses == 0);
	assert(gameResults[2].wins == 0);
	assert(gameResults[2].ties == 1);
}
