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


// Run the 5-round game
bool logic::playGame() {
    srand(time(0));
    numCorrect = 0;

    string gameWords[5];

    // Pick 2 random small words
    int idx1 = rand() % smallWordLength;
    int idx2;
    do {
        idx2 = rand() % smallWordLength;
    } while (idx2 == idx1 && smallWordLength > 1);
    gameWords[0] = smallWords[idx1];
    gameWords[1] = smallWords[idx2];

    // Pick 2 random medium words
    idx1 = rand() % mediumWordLength;
    do {
        idx2 = rand() % mediumWordLength;
    } while (idx2 == idx1 && mediumWordLength > 1);
    gameWords[2] = mediumWords[idx1];
    gameWords[3] = mediumWords[idx2];

    // Pick 1 random large word
    gameWords[4] = largeWords[rand() % largeWordLength];

    // Play each round
    for (int i = 0; i < 5; i++) {
        string scrambled = scrambler(gameWords[i]);

        cout << "\n--- Round " << (i + 1) << " of 5 ---" << endl;
        cout << "Unscramble this: " << scrambled << endl;
        cout << "You have 60 seconds!" << endl;
        cout << "Your answer: ";

        // Reset the global flags
        timeUp = false;
        inputReceived = false;
        userInput = "";

        // Start a thread to get user input
        ALLEGRO_THREAD* inThread = al_create_thread(inputThread, NULL);
        al_start_thread(inThread);

        // Timer loop - wait up to 60 seconds
        double startTime = al_get_time();
        while (!inputReceived && !timeUp) {
            if (al_get_time() - startTime >= 60.0) { 
                timeUp = true;
            }
            al_rest(0.05);
        }




        // Check what happened
        if (inputReceived && !timeUp) {
            if (userInput == gameWords[i]) {
                cout << "Correct! Nice one!" << endl;
                numCorrect++;
            }
            else {
                cout << "Nope! The answer was: " << gameWords[i] << endl;
            }
        }
        else {
            cout << "\nTime's up! The answer was: " << gameWords[i] << endl;
        }

        al_destroy_thread(inThread);
    }

    return (numCorrect >= 3);
}

// Display the final results and intellect rating
void logic::end() {
    cout << "\n=================================" << endl;
    cout << "   FINAL RESULTS" << endl;
    cout << "=================================" << endl;
    cout << "You got " << numCorrect << " out of 5 correct!" << endl;
    cout << endl;

    if (numCorrect <= 1) {
        cout << "Oof... maybe words aren't your thing. Try checkers?" << endl;
    }
    else if (numCorrect == 2) {
        cout << "Novice Thinker! Your brain is just getting warmed up." << endl;
    }
    else if (numCorrect == 3) {
        cout << "Sharp Mind! You're smarter than the average bear." << endl;
    }
    else if (numCorrect == 4) {
        cout << "Word Wizard! Seriously impressive brainpower." << endl;
    }
    else {
        cout << "GENIUS LEVEL! You absolutely crushed it!" << endl;
    }

    cout << "=================================" << endl;
    cout << "Thanks for playing!" << endl;
}