#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include <stdbool.h>
#include "deck.h"
#include "future.h"


struct letter_card_tag {
	char letters[2];
}; 

typedef struct letter_card_tag letter_card_t;

deck_t* hand_from_string(const char* str, future_cards_t* fc);
deck_t** read_input(FILE* f, size_t* n_hands, future_cards_t* fc);
bool is_line_empty(char* line);

#endif