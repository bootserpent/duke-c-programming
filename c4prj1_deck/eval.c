#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "eval.h"
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

bool is_ace_low_straight_at(deck_t* hand, size_t index, suit_t fs);
unsigned* get_match_counts(deck_t* hand);
void printEvalHand(hand_eval_t handEval);

int card_ptr_comp(const void* vp1, const void* vp2) {
	//trying to make const void* to const card_t* const*
	const card_t* const* cp1 = (const card_t* const*)vp1;
	const card_t* const* cp2 = (const card_t* const*)vp2;

	const card_t* c1 = *cp1;
	const card_t* c2 = *cp2;
	//printf("comparing (%d, %d) with (%d, %d)\n", c1->value, c1->suit, c2->value, c2->suit);

	if (c1->value != c2->value) {
		return c2->value - c1->value;
	}
	else {
		return c2->suit - c1->suit;
	}

	return 0;
}

suit_t flush_suit(deck_t* hand) {
	card_t** cards = hand->cards;
	// store suit counters in counterArr, ordered spades, hearts, diamonds, clubs
	int counterArr[4] = { 0, 0, 0, 0 };
	for (unsigned i = 0; i < hand->n_cards; i++) {
		suit_t cardSuit = cards[i]->suit;
		// add 1 for every instance of suit
		counterArr[cardSuit]++;

	}
	int suitIndex;
	for (suitIndex = 0; suitIndex < 4; suitIndex++) {
		if (counterArr[suitIndex] >= 5) {
			return (suit_t)suitIndex;
		}
	}
	// if no flush:
	return NUM_SUITS;
}

unsigned get_largest_element(unsigned* arr, size_t n) {
	unsigned lv;
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return arr[0];
	}
	lv = arr[0];
	for (unsigned i = 0; i < n; i++) {
		if (arr[i] > lv) {
			lv = arr[i];
		}
	}
	return lv;
}


size_t get_match_index(unsigned* match_counts, size_t n, unsigned n_of_akind) {
	for (unsigned i = 0; i < n; i++) {
		if (match_counts[i] == n_of_akind) {
			return i;
		}
	}
	return -1;
}
ssize_t  find_secondary_pair(deck_t* hand,
	unsigned* match_counts,
	size_t match_idx) {
	unsigned cardValue = hand->cards[match_idx]->value;
	for (unsigned i = 0; i < hand->n_cards; i++) {
		if (match_counts[i] > 1) {
			if (hand->cards[i]->value != cardValue) {
				return i;
			}
		}
	}
	return -1;
}

int is_straight_at(deck_t* hand, size_t index, suit_t fs) {
	int counter = 1;
	// deduct the number of cards before index
	if (hand->n_cards - index < 5) {
		return 0;
	}
	// check whether or not there is an ace low straight
	bool isAceLowStraight = is_ace_low_straight_at(hand, index, fs);

	if (isAceLowStraight == true) {
		return -1;
	}
	//size_t ix = index + 1;
	card_t comparisonCard = *(hand->cards)[index];
	//is the suit of our comparisonCard the same as the fs?
	if (fs != NUM_SUITS && comparisonCard.suit != fs) {
		return 0;
	}
	for (unsigned i = index + 1; i < hand->n_cards; i++) {
		card_t currentCard = *(hand->cards)[i];
		if (fs != NUM_SUITS) {
			if (currentCard.suit != fs && fs != NUM_SUITS) {
				continue;
			}
		}
		if (currentCard.value == comparisonCard.value - 1 && (currentCard.suit == fs || fs == NUM_SUITS)) {
			//increment counter and update comparisonCard
			counter++;
			comparisonCard = currentCard;
		}
	}
	if (counter >= 5) {
		return 1;
	}
	return 0;
}

bool is_ace_low_straight_at(deck_t* hand, size_t index, suit_t fs) {
	card_t card = *(hand->cards[index]);
	if (card.value != VALUE_ACE || (fs != NUM_SUITS && card.suit != fs)) {
		return false;
	}
	bool detect5 = false;
	bool detect4 = false;
	bool detect3 = false;
	bool detect2 = false;
	for (unsigned i = index + 1; i < hand->n_cards; i++) {
		card_t c = *(hand->cards)[i];
		switch (c.value) {
		case 5:
			if (c.suit == fs || fs == NUM_SUITS) {
				detect5 = true;
			}
			break;
		case 4:
			if (c.suit == fs || fs == NUM_SUITS) {
				detect4 = true;
			}
			break;
		case 3:
			if (c.suit == fs || fs == NUM_SUITS) {
				detect3 = true;
			}
			break;
		case 2:
			if (c.suit == fs || fs == NUM_SUITS) {
				detect2 = true;
			}
			break;
		}
	}
	//when done with loop:
	if (detect5 && detect4 && detect3 && detect2) {
		return true;
	}
	return false;
}

hand_eval_t build_hand_from_match(deck_t* hand,
	unsigned n,
	hand_ranking_t what,
	size_t idx) {
	hand_eval_t ans;
	ans.ranking = what;
	// iterate over cards from ans.cards and copy the right card to each of them
	// copy first n cards from hand
	int index = idx;
	if (ans.ranking == NOTHING && n == 0) {
		for (int j = 0; j < 5; j++) {
			ans.cards[j] = hand->cards[j];
		}
	}
	int i = n;
	for (unsigned i = 0; i < n; i++) {
		ans.cards[i] = hand->cards[index];
		index++;
	}
	// when done, fill in rest of slots with highest cards
	for (unsigned j = 0; j < hand->n_cards; j++) {
		if (hand->cards[j]->value != ans.cards[0]->value || n == 0) {
			ans.cards[i] = hand->cards[j];
			i++;
		}
		if (i == 5) {
			break;
		}
	}
	return ans;
}

int compare_hands(deck_t* hand1, deck_t* hand2) {
	//That means that to implement compare_hands, you should

	//(a) sort each hand using qsort on the hand's cards
	//and your card_ptr_comp[from earlier]

	qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
	qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);
	// printf("\n\n... after qsort ...\n");
	// print_hand(hand1);
	// printf("\n");
	// print_hand(hand2);

	//(b) Call evaluate_hand on each hand, which gives you a hand_eval_t
	//for each hand.
	hand_eval_t evalH1 = evaluate_hand(hand1);
	hand_eval_t evalH2 = evaluate_hand(hand2);

	// printf("\n\nafter evaluation \n");
	// printEvalHand(evalH1);
	// printEvalHand(evalH2);

	//printf("hand1 ranking = %d, hand2 ranking = %d\n", evalH1.ranking, evalH2.ranking);
	//(c)Check if the rankings in the hand_eval_t are the same
	//or different.If they are different, you can just use
	//the ranking to determine the winner.
	if (evalH1.ranking < evalH2.ranking) {
		return 1;
	}
	if (evalH1.ranking > evalH2.ranking) {
		return -1;
	}
	//(d)If they are the same, then you need to look
	//at the values in the cards array of each hand_eval_t
	//to break the tie. The way that we constructed
	//the hand_eval_t's cards array means that
	//the cards are already ordered from most significant(at index 0)
	//to least significant(at index 4). You can just
	//do a lexicographic comparison on the values in the arrays.
	//(Its like comparing strings, but you are comparing values
	//of cards-- - if element 0 is the different, use that difference
	//to determine your answer.If element 0 is the same,
	//look at element 1, and so on).
	//Note that compare hands should return a positive number
	//if hand 1 is better, 0 if the hands tie, and a negative number
	//if hand 2 is better.
	for (int i = 0; i < 5; i++) {
		if (evalH1.cards[i]->value < evalH2.cards[i]->value) {
			return -1;
		}
		else if (evalH1.cards[i]->value > evalH2.cards[i]->value) {
			return 1;
		}
	}
	return 0;
}

void updateCounts(unsigned* array, int startIndex, int cardCounter) {
	for (int i = startIndex; i < startIndex + cardCounter; i++) {
		array[i] = cardCounter;
	}
}

//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned* get_match_counts(deck_t* hand) {
	// hand already sorted
	unsigned* counts = (unsigned*)malloc(hand->n_cards * sizeof(unsigned));
	// startIndex tells loop where to start writing
	int startIndex = 0;
	// cardCounter tracks
	int cardCounter = 0;
	unsigned temp;
	for (unsigned idx = 0; idx < hand->n_cards; idx++) {
		if (idx == 0) {
			temp = hand->cards[idx]->value;
		}
		if (temp != hand->cards[idx]->value) {
			updateCounts(counts, startIndex, cardCounter);
			// reset cardCounter
			cardCounter = 1;
			// reset startIndex
			startIndex = idx;
			// reset temp
			temp = hand->cards[idx]->value;
		}
		else {
			cardCounter++;
		}
	}
	// write final value into counts
	updateCounts(counts, startIndex, cardCounter);
	return counts;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t** to, deck_t* from, size_t ind, suit_t fs, size_t count) {
	assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
	unsigned nextv = from->cards[ind]->value;
	size_t to_ind = 0;
	while (count > 0) {
		assert(ind < from->n_cards);
		assert(nextv >= 2);
		assert(to_ind < 5);
		if (from->cards[ind]->value == nextv &&
			(fs == NUM_SUITS || from->cards[ind]->suit == fs)) {
			to[to_ind] = from->cards[ind];
			to_ind++;
			count--;
			nextv--;
		}
		ind++;
	}
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t* hand, suit_t fs, hand_eval_t* ans) {
	if (hand->n_cards < 5) {
		return 0;
	}
	for (size_t i = 0; i <= hand->n_cards - 5; i++) {
		int x = is_straight_at(hand, i, fs);
		// printf("\nis_straight_at i=%ld, fs=%d, result=%d\n", i, fs, x);
		if (x != 0) {
			if (x < 0) { //ace low straight
				assert(hand->cards[i]->value == VALUE_ACE &&
					(fs == NUM_SUITS || hand->cards[i]->suit == fs));
				ans->cards[4] = hand->cards[i];
				size_t cpind = i + 1;
				while (hand->cards[cpind]->value != 5 ||
					!(fs == NUM_SUITS || hand->cards[cpind]->suit == fs)) {
					cpind++;
					assert(cpind < hand->n_cards);
				}
				copy_straight(ans->cards, hand, cpind, fs, 4);
			}
			else {
				copy_straight(ans->cards, hand, i, fs, 5);
			}
			return 1;
		}
	}
	return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t* hand) {
	suit_t fs = flush_suit(hand);
	hand_eval_t ans;
	if (fs != NUM_SUITS) {
		if (find_straight(hand, fs, &ans)) {
			ans.ranking = STRAIGHT_FLUSH;
			return ans;
		}
	}
	unsigned* match_counts = get_match_counts(hand);
	unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
	assert(n_of_a_kind <= 4);
	size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
	ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
	free(match_counts);
	if (n_of_a_kind == 4) { //4 of a kind
		return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
	}
	else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
		ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
		ans.cards[3] = hand->cards[other_pair_idx];
		ans.cards[4] = hand->cards[other_pair_idx + 1];
		return ans;
	}
	else if (fs != NUM_SUITS) { //flush
		ans.ranking = FLUSH;
		size_t copy_idx = 0;
		for (size_t i = 0; i < hand->n_cards; i++) {
			if (hand->cards[i]->suit == fs) {
				ans.cards[copy_idx] = hand->cards[i];
				copy_idx++;
				if (copy_idx >= 5) {
					break;
				}
			}
		}
		return ans;
	}
	else if (find_straight(hand, NUM_SUITS, &ans)) {     //straight
		ans.ranking = STRAIGHT;
		return ans;
	}
	else if (n_of_a_kind == 3) { //3 of a kind
		return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
	}
	else if (other_pair_idx >= 0) {     //two pair
		assert(n_of_a_kind == 2);
		ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
		ans.cards[2] = hand->cards[other_pair_idx];
		ans.cards[3] = hand->cards[other_pair_idx + 1];
		if (match_idx > 0) {
			ans.cards[4] = hand->cards[0];
		}
		else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
		  //if other_pair_idx > 2, then, e.g. A A K Q Q
			ans.cards[4] = hand->cards[2];
		}
		else {       //e.g., A A K K Q
			ans.cards[4] = hand->cards[4];
		}
		return ans;
	}
	else if (n_of_a_kind == 2) {
		return build_hand_from_match(hand, 2, PAIR, match_idx);
	}
	return build_hand_from_match(hand, 0, NOTHING, 0);
}

void printEvalHand(hand_eval_t handEval) {
	const char* ranking = ranking_to_string(handEval.ranking);
	printf("ranking is %s\n", ranking);
	for (int i = 0; i < 5; i++) {
		print_card(*(handEval.cards[i]));
	}
	printf("\n");
}
