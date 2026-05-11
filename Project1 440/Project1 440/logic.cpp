// logic.cpp
// Implementation of the word scramble game logic
// CPSC 440 - Program 1

#include "logic.h"
#include <allegro5/allegro.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Reference the global variables from program1Game.cpp
extern bool timeUp;
extern string userInput;
extern bool inputReceived;
extern void* inputThread(ALLEGRO_THREAD* thread, void* arg);

// Constructor - set everything to zero
logic::logic() {
    numCorrect = 0;
    smallWordLength = 0;
    mediumWordLength = 0;
    largeWordLength = 0;
}

// Display the game introduction
void logic::introduction() {
    cout << "=================================" << endl;
    cout << "   WORD SCRAMBLE CHALLENGE" << endl;
    cout << "=================================" << endl;
    cout << "Think you're smart? Prove it!" << endl;
    cout << "Unscramble 5 words to test your brainpower." << endl;
    cout << "You get 60 seconds per word. No pressure." << endl;
    cout << "=================================" << endl;
    cout << endl;
}


// Read dictionary.txt and sort words into the three arrays
bool logic::createLists() {
    ifstream file("dictionary.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open dictionary.txt" << endl;
        return false;
    }

    string word;

    while (file >> word) {
        int len = word.length();

        // 4-5 letter words go in small array
        if (len >= 4 && len <= 5 && smallWordLength < 50) {
            smallWords[smallWordLength] = word;
            smallWordLength++;
        }
        // 6-7 letter words go in medium array
        else if (len >= 6 && len <= 7 && mediumWordLength < 50) {
            mediumWords[mediumWordLength] = word; 
            mediumWordLength++;
        }
        // 8+ letter words go in large array
        else if (len >= 8 && largeWordLength < 50) {
            largeWords[largeWordLength] = word;
            largeWordLength++;
        }
    }

    file.close(); 

    // Make sure we have enough words for the game
    if (smallWordLength < 2 || mediumWordLength < 2 || largeWordLength < 1) {
        cout << "Not enough words in each category to play." << endl;
        return false;
    }

    return true;
}

// Scramble a word by shuffling its letters
string logic::scrambler(string word) {
    string scrambled = word;
    int len = scrambled.length();

    // Fisher-Yates shuffle
    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }

    // If it came out the same, just swap first two letters
    if (scrambled == word && len > 1) {
        char temp = scrambled[0];
        scrambled[0] = scrambled[1];
        scrambled[1] = temp;
    }

    return scrambled;
}
