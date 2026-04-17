#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
using namespace std;

int main() {
    srand(time(0)); // Seed the random number generator

    int secretNumber = rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;

    cout << "Number Guessing Game" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl << endl;

    // Loop until the user guesses the correct number
    while (guess != secretNumber) {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++; // Increase attempt count

        if (guess > secretNumber) {
            cout << "You went as high as my Grandfather." << endl << endl;
        } else if (guess < secretNumber) {
            cout << "That was so low you could play tennis with a curb. Shawty." << endl << endl;
        } else {
            cout << "Great... You did it. Nerd." << secretNumber << " correctly!" << endl;
            cout << "It took you " << attempts << " guesses." << endl;
        }
    }

    return 0;
}
