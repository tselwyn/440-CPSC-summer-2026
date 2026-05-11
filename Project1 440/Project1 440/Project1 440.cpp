// program1Game.cpp
// Main file - handles Allegro timer and threading
// CPSC 440 - Program 1: Word Scramble Game

#include <allegro5/allegro.h>
#include <iostream>
#include <string>
#include "logic.h"

using namespace std;

// Three global variables for timer/thread communication
bool timeUp = false;
string userInput = "";
bool inputReceived = false;

// Input thread function - reads user input on separate thread
// so the timer can keep counting in main
void* inputThread(ALLEGRO_THREAD* thread, void* arg) {
    string input;
    getline(cin, input);
    if (!timeUp) {
        userInput = input;
        inputReceived = true;
    }
    return NULL;
}
int main() {
    // Initialize Alllegro
    al_init();

    // Create game logic object
    logic game;

    // Show intro
    game.introduction();

    // Load dicctionary
    if (!game.createLists()) {
        cout << "Could not load dictionary. Make sure dictionary.txt is in the right folder." << endl;
        return 1;
    }

    // Play the game
    game.playGame();

    // Show results
    game.end();

    return 0;
}