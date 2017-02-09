/** @file hw4.cpp
@author Douglas Yao
@date 2/1/2016

Creates iterator WordCrawler that indexes a string word by word. Performs several functions using WordCrawler that finds word count, number of 'the's, every other word, and words in reverse for user-inputted string

*/

#include <iostream>
#include <string>

/** @class WordCrawler
@brief Indexes a string word by word

This class is designed to mimic a pointer that indexes a string word by word, rather than character by character.

*/

class WordCrawler {
public:

	WordCrawler(std::string s);
	WordCrawler& operator++();
	WordCrawler& operator--();
	WordCrawler& operator-=(int n);
	WordCrawler& operator+=(int n);

	int get_index() const;

	std::string operator*();
	std::string operator[](int n);

private:
	std::string words;
	char* current_word;
	int index;
};


int word_count(const std::string& words);
int the_count(const std::string& words);
void every_other_in(const std::string& words);
void print_in_reverse(const std::string& words);



int main() {

	std::string words;

	std::cout << "Please input some words:\n";
	std::getline(std::cin, words);

	std::cout << "The total number of words is: " << word_count(words) << std::endl;

	std::cout << "The total number of the times 'the' appears is: " << the_count(words) << std::endl;

	std::cout << "Every other word is: "; every_other_in(words);
	std::cout << std::endl;

	std::cout << "The words in reverse order are: "; print_in_reverse(words);
	std::cout << std::endl;

	return 0;
}




/** Constructor for WordCrawler class. Stores a copy of the user-inputted string and creates a pointer to the first character of the string.

@param s is the user-inputted string

*/

WordCrawler::WordCrawler(std::string s) {
	words = s;
	current_word = &words[0];
	index = 0; // position of pointer
}




/** Increments WordCrawler pointer by one word

@return incremented WordCrawler

*/


WordCrawler& WordCrawler::operator++() {

	// while pointer is not pointing to a space and is not at the end of the string, it is incremented until it encounters a space
	while (*current_word != ' ' && index < (words.size() - 1)) {
		++current_word;
		++index;
	}

	// unless pointer is at end of string, it is incremented to first character of next word
	if (index < (words.size() - 1)) {
		++current_word;
		++index;
	}

	return *this;
}




/** Decrements WordCrawler pointer by one word

@return decremented WordCrawler

*/

WordCrawler& WordCrawler::operator--() {

	// if pointer is at end of string, it is decremented until the beginning of the last word
	if (index == (words.size() - 1)) {
		while (index >= 0 && *current_word != ' ') {
			--current_word;
			--index;
		}
		++current_word;
		++index;
	}

	// if pointer is not at beginning of string
	if (index > 0) {

		// pointer is decremented until the end of the previous word
		current_word -= 2;
		index -= 2;

		// pointer is decremented until it encounters a space or until it reaches the beginning of the string
		while (index > 0 && *current_word != ' ') {
			--current_word;
			--index;
		}

		// pointer is incremented to first character of previous word
		if (index > 0) {
			++current_word;
			++index;
		}
	}

	return *this;
}




/** Increments WordCrawler pointer by a certain amount of words. Assumes that operator++ is defined.

@param n is the number of words to increment
@return incremented WordCrawler

*/

WordCrawler& WordCrawler::operator+=(int n) {

	// increments pointer by n amount of times
	for (int i = 0; i<n; ++i) {
		++(*this);
	}

	return *this;
}




/** Decrements WordCrawler pointer by a certain amount of words. Assumes that operator-- is defined.

@param n is the number of words to decrement
@return decremented WordCrawler

*/

WordCrawler& WordCrawler::operator-=(int n) {

	// decrements pointer by n amount of times
	for (int i = 0; i<n; ++i) {
		--(*this);
	}
	return *this;
}




/** Dereferencer for WordCrawler pointer. Returns the word that the pointer is pointing to.

@return the word the pointer is pointing to

*/

std::string WordCrawler::operator*() {
	std::string s;
	char* p = current_word;
	int n = index;

	// characters are added to string until a space is encountered. If the word is the last word in the string, the loop stops before the last character.
	while (*current_word != ' ' && index < (words.length() - 1)) {
		s.push_back(*current_word);
		++current_word;
		++index;
	}

	// if the word is the last word in the string, the last character is added.
	if (index == (words.length() - 1))
		s.push_back(*current_word);

	// returns WordCrawler to beginning of word
	current_word = p;
	index = n;
	return s;
}




/** Offset operator for WordCrawler. Assumes that operator* and operator+= are defined.

@param n is the position of the word to be outputted
@return word

*/

std::string WordCrawler::operator[] (int n) {

	// positions pointer at beginning of string
	current_word = &words[0];

	// increments pointer by n amount of words
	*this += n;

	// returns word that pointer is pointing to
	std::string s = *(*this);
	return s;
}




/** Accessor for private index value

@return index value

*/

int WordCrawler::get_index() const {
	return index;
}




/** Counts the number of words in a string. Assumes that operator++ is defined.

@param words is the string that contains the words
@return number of words in string

*/

int word_count(const std::string& words) {

	WordCrawler p(words);
	int count = 0;

	// scans the string and adds one to tally every time pointer moves to a new word
	while (p.get_index() < (words.length() - 1)) {
		++count;
		++p;
	}

	return count;
}




/** Counts the number of time the word 'the' occurs in string. Assumes that operator++ and operator* are defined.

@param words is the string that contains the words
@return number of words in string

*/

int the_count(const std::string& words) {

	WordCrawler p(words);
	int the_count = 0;

	// scans the string and adds one to tally every time pointer points to a 'the'
	while (p.get_index() < (words.length() - 1)) {
		if (*p == "the")
			++the_count;
		++p;
	}

	return the_count;
}




/** Prints every other word of a string. Assumes that operator+= and operator* are defined.

@param words is the string that contains the words

*/

void every_other_in(const std::string& words) {

	WordCrawler p(words);
	std::string s;

	// concatenates every other word to a string
	for (int i = 0, n = word_count(words) / 2; i < n; ++i) {
		s += *p += " ";
		p += 2;
	}

	// if there are an odd amount of words, an extra word must be added since division rounds down
	if (word_count(words) % 2 == 1)
		s += *p;

	// outputs string
	std::cout << s;
}




/** Prints out string in reverse. Assumes that operator* and operator-- are defined.

@param words is the string that contains the words

*/

void print_in_reverse(const std::string& words) {

	WordCrawler p(words);
	std::string s;
	int n = word_count(words);

	// positions pointer at last word of string
	p += (n - 1);

	// adds words backwards
	for (int i = 0; i < (n - 1); ++i) {
		s += *p += " ";
		--p;
	}
	s += *p;

	// outputs string
	std::cout << s;
}




