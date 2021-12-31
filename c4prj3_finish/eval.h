#ifndef EVAL_H
#define EVAL_H
#include "deck.h"
struct hand_eval_tag {
	hand_ranking_t ranking;
	card_t* cards[5];
};
typedef struct hand_eval_tag hand_eval_t;

struct hand_result_tag {
	int wins;
	int losses;
	int ties;
};
typedef struct hand_result_tag hand_result_t;

hand_eval_t evaluate_hand(deck_t* hand);
int compare_hands(deck_t* hand1, deck_t* hand2);
void compare_n_hands(deck_t** hands, hand_result_t* gameResults, int numHands);
void print_game_results(int num_hands, int num_trials, hand_result_t* gameResults);
void free_game_results(hand_result_t* gameResults, int nHands);
#endif