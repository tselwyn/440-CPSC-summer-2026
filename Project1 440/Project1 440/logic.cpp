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