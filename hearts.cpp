/* Lecture code 7.0
 *
 * Hearts example!
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <utility>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sstream>
#include <iterator>
using namespace std;

/* Type: suitT
 * A type that stores the suit of a playing card.
 */
enum suitT {Hearts, Diamonds, Clubs, Spades};

/* Type: valueT
 * A type that stores the value of playing card.
 * Note that the values are sorted in increasing
 * order here, so you can compare cards by
 * value.
 */
enum valueT {Two, Three, Four, Five, Six, Seven,
             Eight, Nine, Ten, Jack, Queen, King,
			 Ace};

/* Type: cardT
 * A type that represents a playing card.
 */
struct cardT {
	suitT suit;
	valueT value;
};

/* Type: deckT
 * A deque of cards.
 */
typedef deque<cardT> deckT;

/* The number of cards in each player's hand. */
const size_t kNumCards = 13;

/* The number of players in this game. */
const size_t kNumPlayers = 4;

/* The number of total points to play to. */
const int kMaxPoints = 100;

/* The names of the players in this game, who coincidentally are all
 * awesome people.
 */
const string kPlayerNames[kNumPlayers] = 
	{ "Alonzo Church", // Inventor of the lambda calculus, an formalism used in functional
	                   // programming and theory of computation.
	  "Haskell Curry", // Logician responsible for much of the early development of computability
	                   // theory.  His work into intuitionistic logic paved the way for the
	                   // Curry-Howard isomorphism, characterizing computer programs as
	                   // mathematical proofs.
	  "Donald Knuth",  // Father of algorithmic analysis, and perhaps the reason that computer
	                   // science exists as an academic discipline.  He's also still around
	                   // Stanford if you know where to look!
	  "Alan Turing"    // Father of computer science and inventor of the Turing Machine
	                   // whose halting problem is one of the most famous results in theoretical
	                   // computer science.
	};

/* Type: playerT
 * A player in the game.
 */
struct playerT {
	deckT hand;
	int pointsTotal;
	string name;
};


/* Randomize()
 * Seeds the randomizer so random shuffling will work
 * correctly.  Look into <cstdlib> and <ctime> for more
 * info on the functions here.
 */
void Randomize() {
	srand((unsigned int)time(NULL));
}

/* GetLine()
 * Gets a string from the user.
 */
string GetLine() {
	string result;
	getline(cin, result);
	return result;
}

/* PrintCard(cardT &card)
 * Prints a card's value and suit.  This uses some low-order
 * ASCII characters and other hackery; apologies in advance.
 */
void PrintCard(cardT &card) {
	switch(card.value) {
	case Ten:   cout << 'T'; break;
	case Jack:  cout << 'J'; break;
	case Queen: cout << 'Q'; break;
	case King:  cout << 'K'; break;
	case Ace:   cout << 'A'; break;
	default:
		cout << (card.value + 2);
	}
	
	/* Low-order ASCII characters are playing card suits! */
	cout << (char(card.suit + '\x03')) << ' ';
}

/* InitPlayers(players)
 * Initializes the players to have no points and the
 * correct name.
 */
void InitPlayers(vector<playerT> &players) {
	for(vector<playerT>::iterator itr = players.begin(); itr != players.end(); ++itr) {
		itr->pointsTotal = 0;
		itr->name = kPlayerNames[itr - players.begin()];
	}
}

/* FillDeck(deck)
 * Fills the deck of cards with all 52 cards, in sorted
 * order.
 */
void FillDeck(deckT &deck) {
	/* For each suit. */
	for(suitT suit = Hearts; suit <= Spades; suit = suitT(suit + 1)) {
		/* For each card. */
		for(valueT value = Two; value <= Ace; value = valueT(value + 1)) {
			cardT card = {suit, value};
			deck.push_back(card);
		}
	}
}

/* GetWinningPlayerIndex(deck)
 * Returns the zero-based index of the player who
 * won the trick.  Later, when we cover functors,
 * you'll see a very concise and powerful way to
 * write this function.
 */
size_t GetWinningPlayerIndex(deckT &playedCards) {
	/* Get the suit. */
	suitT toFollow = playedCards.front().suit;

	/* Track the value and index of the winning player. */
	size_t index = 0;
	valueT value = Two;

	for(size_t i = 0; i < playedCards.size(); i++) {
		/* Update to max player. */
		if(playedCards[i].suit == toFollow && playedCards[i].value > value) {
			index = i;
			value = playedCards[i].value;
		}
	}

	return index;
}

/* GetPoints(trick)
 * Returns the number of points in the specified trick.
 */
int GetPoints(deckT &trick) {
	int total = 0;
	for(deckT::iterator itr = trick.begin(); itr != trick.end(); ++itr) {
		/* Hearts are one point. */
		if(itr->suit == Hearts)
			total++;
		/* Queen of spades is worth 13. */
		if(itr->suit == Spades && itr->value == Queen)
			total += 13;
	}

	return total;
}

/* PrintAllHands(players)
 * Prints out each player's hand.
 */
void PrintAllHands(vector<playerT> &players) {
	for(size_t i = 0; i < players.size(); i++) {
		cout << players[i].name << " has: " << endl;
		for(size_t j = 0; j < players[i].hand.size(); j++)
			PrintCard(players[i].hand[j]);
		cout << endl;
	}
}

/* Randomly shuffles the deck. */
void ShuffleDeck(deckT &deck) {
	random_shuffle(deck.begin(), deck.end());
}

/* Compares two cards, first by suit, then by value.  Used as a callback
 * for DealCards.
 */
bool CompareTwoCards(cardT one, cardT two) {
	if(one.suit < two.suit)
		return true;
	if(one.suit > two.suit)
		return false;
	return one.value < two.value;
}

/* Deals 13 cards to each player, then sorts those cards. */
void DealCards(deckT &deck, vector<playerT> &players) {
	for(size_t i = 0; i < players.size(); ++i) {
		copy(deck.begin() + kNumCards * i, deck.begin() + kNumCards * (i + 1),
			back_inserter(players[i].hand));
		sort(players[i].hand.begin(), players[i].hand.end(), CompareTwoCards);
	}
}

/* Compares two cards by value only and by suit only, respectively. */
bool CompareByValueOnly(cardT one, cardT two) {
	return one.value < two.value;
}
bool CompareBySuitOnly(cardT one, cardT two) {
	return one.suit < two.suit;
}

/* Plays a card when the player is first to act.  We play the lowest card in the
 * hand, considering only value.
 */
void PlayFirstCard(playerT &player, deckT &playedCards) {
	deckT::iterator toPlay = min_element(player.hand.begin(), player.hand.end(), CompareByValueOnly);
	playedCards.push_back(*toPlay);
	player.hand.erase(toPlay);
}

/* Plays a card when the player is not first to act.  We play the lowest card in the
 * suit if we have a card of the suit and the highest card in our hand otherwise.
 */
void PlayFollowingCard(playerT &player, deckT &playedCards) {
	/* Use equal_range to get the range of cards in our hand that have the
	 * same suit as the first card played.
	 */
	pair<deckT::iterator, deckT::iterator> allOfSuit =
		equal_range(player.hand.begin(), player.hand.end(), playedCards.front(), CompareBySuitOnly);

	/* Now, if there are no cards of that suit, pick the largest card in our hand.
	 * Otherwise, pick the lowest card of the suit.  Since cards are suited by sort in
	 * increasing order, this is the first element of that suit.
	 */
	deckT::iterator toPlay;
	if(allOfSuit.first == allOfSuit.second)
		toPlay = max_element(player.hand.begin(), player.hand.end(), CompareByValueOnly);
	else
		toPlay = allOfSuit.first;

	playedCards.push_back(*toPlay);
	player.hand.erase(toPlay);


void PlayRound(vector<playerT> &players) {
	for(int round = 0; round < kNumCards; ++round) {
		deckT trick;
		for(int index = 0; index < kNumPlayers; ++index) {
			if(index == 0)
				PlayFirstCard(players[index], trick);
			else
				PlayFollowingCard(players[index], trick);

			cout << players[index].name << " plays: ";
			PrintCard(trick.back());
			cout << endl;
		}

		size_t winnerIndex = GetWinningPlayerIndex(trick);
		cout << players[winnerIndex].name << " takes the trick." << endl << endl;
		players[winnerIndex].pointsTotal += GetPoints(trick);

		/* Put the winning play in the front. */
		rotate(players.begin(), players.begin() + winnerIndex, players.end());
	}
}

void PrintResult(vector<playerT> &players) {
	for(vector<playerT>::iterator itr = players.begin(); itr != players.end(); ++itr)
		cout << itr->name << " has " << itr->pointsTotal << " points." << endl;
}

bool HasTooManyPoints(playerT player) {
	return player.pointsTotal >= kMaxPoints;
}

bool IsGameOver(vector<playerT> &players) {
	return find_if(players.begin(), players.end(), HasTooManyPoints) != players.end();
}

int main() {
	deckT deck;
	vector<playerT> players(kNumPlayers);
	InitPlayers(players);
	Randomize();
	FillDeck(deck);

	/* At this point, all players are initialized correctly, and we have a
	 * standard 52-card deck.  All that's left to do now is to play the game!
	 */

	while(!IsGameOver(players)) {
		ShuffleDeck(deck);
		DealCards(deck, players);
		PrintAllHands(players);
		PlayRound(players);
		PrintResult(players);
		GetLine();
	}
	
	return 0;
}