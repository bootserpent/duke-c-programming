#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "future.h"
#include "deck.h"
#define EXIT_FAILURE -1

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
	
	//is fc NULL?
	if (fc == NULL) {
		fprintf(stderr, "Expected fc not to be NULL.\n");
		return EXIT_FAILURE;
	}
	
	//is ptr valid?
	if (ptr == NULL) {
		fprintf(stderr, "Provided card pointer not valid.\n");
		return EXIT_FAILURE;
	}
	
	//allocate for index # of decks
	if (fc->n_decks <= index) {
		deck_t* deckTemp = realloc(fc->decks, sizeof(deck_t) * (index + 1));
		if (deckTemp) {
			fc->decks = deckTemp;
		}
		else {
			fprintf(stderr, "fc decks realloc failed!\n");
			return EXIT_FAILURE;
		}
		//set all decks' cards to NULL for error handling
		for (int i = fc->n_decks; i < index + 1; i++) {
			fc->decks[i].cards = NULL;
			fc->decks[i].n_cards = 0;
		}
		fc->n_decks = index + 1;
	}

	//add card ptr to fc
		//since decks are NULL, first allocate space for that deck
	card_t ** cardTemp = realloc(fc->decks[index].cards, sizeof(card_t*) * (fc->decks[index].n_cards + 1));
	if (cardTemp) {
		fc->decks[index].cards = cardTemp;
	}
	else {
		fprintf(stderr, "deck card realloc failed!\n");
		return EXIT_FAILURE;
	}

	//we can do this because n_cards was set to zero
		//there also could be something already in the deck, so ++ is used
	fc->decks[index].n_cards++;
	fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;

}

void future_cards_from_deck(deck_t* deck, future_cards_t* fc) {
	/*This function takes a deck(which has been shuffled),
		and a future_cards_t(which has been filled in with
			all the pointers to placeholders) and draws cards from
		the deck and assigns their values and suits to the
		placeholders pointed to in fc.
		For example if the deck is
		As Kh 8c ....
		and fc was created from the input
		3c 4c ?0 ?1 ?2
		5h 9d ?0 ?1 ?2
		then this function will draw As for ? 0,
		and fill in the two placeholders for ? 0 (which
			you can find with the pointers in fc, as described
			in the video).Then it will draw Kh for ? 1,
		and so on.Think about a case where this function would need to
		print an error message.*/

	if (deck == NULL) {
		fprintf(stderr, "provided deck is NULL, no cards to draw from\n");
		return EXIT_FAILURE;
	}

	//handle NULL fc
	if (fc == NULL) {
		fprintf(stderr, "provided fc is NULL or no work to do\n");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < fc->n_decks; i++) {
		if (fc->decks[i].n_cards != 0) {
			for (int j = 0; j < fc->decks[i].n_cards; j++) {
				*(fc->decks[i].cards[j]) = *(deck->cards[i]);
			}
		}
	}
}
