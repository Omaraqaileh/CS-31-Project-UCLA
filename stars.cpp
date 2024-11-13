#include "utilities.h"
#include <cctype>
#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

const char WORDFILENAME[] = "C:/Users/LOQ/source/repos/CS Project 5/CS Project 5/wordtext.txt";



int runOneRound(const char words[][7], int nWords, int wordnum) {
    int numtries = 0;
    
    const char* secret = words[wordnum];


    if (nWords < 0 || wordnum < 0 || wordnum >= nWords) {
        return -1;
    }
    while (true) {
        bool found = false;
        bool isThere = false;
        int stars = 0;
        int planets = 0;
        cout << "Trial word: ";
        char inpt[1000];
        cin >> inpt;
        bool issmaller = false;
        if (strlen(inpt) < 4 || strlen(inpt) > 6) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            issmaller = true;
            found = true;
        }
        else {
            for (int i = 0; i < strlen(inpt); i++) {
                if (!islower(inpt[i]) && inpt[i] != '/0') {
                    cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl; 
                    issmaller = true;
                    found = true;
                    break;

                }

            }

        }
        for (int i = 0; i < nWords; i++) {
            if (strcmp(inpt, words[i]) == 0) {
                isThere = true;
            }
        }
        if (!isThere && !issmaller) {
            cout << "I don't know that word." << endl;
            found = true;
        }

        bool secretUsed[7] = {false}, trialUsed[7] = {false};
        
        for (int i = 0; i < strlen(secret); i++) {
            if (secret[i] == inpt[i]) {
                stars++;
                secretUsed[i] = true;
                trialUsed[i] = true;
            }
        }

        // Second pass: count planets
        for (int i = 0; i < strlen(secret); i++) {
            if (trialUsed[i]) continue;
            for (int j = 0; j < strlen(secret); j++) {
                if (!secretUsed[j] && inpt[i] == secret[j]) {
                    planets++;
                    secretUsed[j] = true;
                    break;
                }
            }
        }
        if (!found && strcmp(secret, inpt) != 0){
            numtries++;
            cout << "Stars: " << stars;
            cout << ", Planets: " << planets << endl;
        }
        
        else if (strcmp(secret, inpt) == 0) {
            numtries++;
            return numtries;
            
       }
        
    }
}

int main()
{
    int numRounds;
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore(10000, '\n');

    char wordlist[8000][7];
    int num = getWords(wordlist, 8000, WORDFILENAME);

    

    if (numRounds <= 0) {
        cout << "The number of rounds must be positive" << endl;
    }
    if (num < 1) { 
        cout << "No words were loaded, so I can't play the game." << endl;

    }
    float total_tries = 0.00;
    int min_tries = 0;
    int max_tries = 0;
    int average_score = 0;

    for (int currentround = 1; currentround <= numRounds; currentround++) {

        int randword = randInt(0, num - 1);
 
        cout << "The random word in the list is " << wordlist[randword] << endl;
        int score = runOneRound(wordlist, num, randword);

        total_tries += score;
     

        if (score != -1 && score > 1) {
            cout << "You got it in " << score << " tries." << endl;


            if (score < min_tries && currentround!= 1) {
                min_tries = score;
            }
            else if (currentround == 1){
                min_tries = score;
            }
            if (score > max_tries) {
                max_tries = score;
            }
        }
        else if (score == 1) {
            cout << "You got it in 1 try." << endl;

         

            if (score < min_tries && currentround != 1) {
                min_tries = score;
            }
            else if (currentround == 1){
                min_tries = score;
            }
            if (score > max_tries) {
                max_tries = score;
            }
        }
        double avgScore = static_cast<double>(total_tries) / currentround;
        std::cout << "Average: " << fixed << setprecision(2) << avgScore;
        cout << " minimum: " << min_tries << ", ";
        cout << "maximum: " << max_tries << endl;
    }

}