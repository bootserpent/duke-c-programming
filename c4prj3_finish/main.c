//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//comment everything above when done
#include <stdio.h>
//#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#pragma warning(disable : 4996)
#define DEFAULT_TEST_TRIALS 10000


int main(int argc, char** argv) {

	//Check command line arguments/report errors
	if (argc == 1) {
		printf("Not enough arguments.\nExpected at least 1 argument.\nUsage: $ executable filename <num_trials>\n");
		return 1;
	}

	//Open input file, read hands inside (read_input)
	FILE* inputFile = fopen(argv[1], "r");
	int num_trials = argc < 3 ? DEFAULT_TEST_TRIALS: atoi(argv[2]);
	
	int* n_hands = (int*)malloc(sizeof(int));
	future_cards_t* fc = (future_cards_t*)malloc(sizeof(future_cards_t));
	fc->decks = NULL;
	fc->n_decks = 0;

	deck_t** hands = read_input(inputFile, n_hands, fc);
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

	//repeat Monte Carlo trial num_trials times
	for (int i = 0; i < num_trials; i++) {

		//shuffle the deck of remaining cards
		shuffle(remainingDeck);
	
	//assign unknown cards from the shuffled deck (future_cards_from_deck)
		future_cards_from_deck(remainingDeck, fc);

	//compare_hand to determine winner
		compare_n_hands(hands, gameResults, num_hands);

	}

	//print results after tests completed
	print_game_results(num_hands, num_trials, gameResults);

	//free memory allocated
	free(n_hands);

	//free memory allocated to hands
	for (int i = 0; i < num_hands; i++) {
		free_deck(hands[i]);
	}
	free(hands);
	
	//free memory allocated to drawing future cards
	free_deck(remainingDeck);
 
	free_game_results(gameResults, num_hands);

	free_future_cards(fc);

	//close files
	fclose(inputFile);

	//uncomment if debug memory leak on windows
	/*_CrtDumpMemoryLeaks();*/
	return EXIT_SUCCESS;
}

