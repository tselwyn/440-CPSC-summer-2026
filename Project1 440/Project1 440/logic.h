// logic.h
// Class definition for the word scramble game logic
// CPSC 440 - Program 1
//Tyler Selwyn 

#ifndef LOGIC_H
#define LOGIC_H

#include <string>
using namespace std;

class logic {
public:
    logic();
     // Constructor - initializes all variables
    void introduction();
    // Displays game intro to the player
    bool createLists();
    // Opens dictionary.txt and sorts words into arrays by length
    // Returns true if successful, false if file not found
    bool playGame();
    // Runs the 5-round word  scramble game
    // Returns true if player wins (3+ correct)
    string scrambler(string word);
    // Takes a word and scrambles the letters randomly
    // Returns the scrambled version
    void end();
    // Displays final score and intellect  rating

private:
    int numCorrect;         // how many words the player got right
    int smallWordLength;    // count of 4-5 letter words loaded
    int mediumWordLength;   // count of 6-7 letter words loaded
    int largeWordLength;    // count of 8+ letter words loaded
    string smallWords[50];  // array of 4-5 letter words
    string mediumWords[50]; // array of 6-7 letter words
    string largeWords[50];  // array of 8+ letter words
};

#endif
