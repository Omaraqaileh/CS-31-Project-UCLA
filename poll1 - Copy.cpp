#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;
// Initializing the functions before writing them to make sure the code compiles.
bool isValidUppercaseStateCode(string code);
bool hasRightSyntax(string pollData);
int computeVotes(string pollData, char party, int& votecount);

int main() {
    assert(hasRightSyntax("R40TXD54CA"));
    assert(!hasRightSyntax("R40MXD54CA"));
    int votes;
    votes = -999;    // so we can detect whether computeVotes sets votes
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'd', votes) == 0 && votes == 82);
    votes = -999;    // so we can detect whether computeVotes sets votes
    assert(computeVotes("R40TXD54CA", '%', votes) == 3 && votes == -999);

        cout << "All tests succeeded" << endl;

}
bool isValidUppercaseStateCode(string code) {
    const string validCodes = "AL AK AZ AR CA CO CT DE DC FL GA HI ID IL IN IA KS KY LA ME MD MA MI MN MS MO MT NE NV NJ NH NM NY NC ND OH OK OR PA RI SC SD TN TX UT VT VA WA WV WI WY";
    return validCodes.find(code) != string::npos;
}
bool hasRightSyntax(string pollData) {
    int count = 0;
    while (count < pollData.size()) {
        // This checks if the first character of the state prediction is an alphabetical character and returns false if it isn't.
        if (!isalpha(pollData[count])) {
            return false;
        }

        count += 1;
        // This checks if the second character of the votecount is a digit.
        if (!isdigit(pollData[count])) {
            return false;
        }

        int digits = 0;
        // This counts the number of digits the votecount has in the state prediction.
        while (count < pollData.size() && isdigit(pollData[count])) {
            digits++;
            count += 1;
        }

        // If there are isn't a vote prediction, or there are more than 2 digits in the votecount, then it will return false.
        if (digits == 0 || digits > 2) {
            return false;
        }

        // This initializes the sub variable as the state code of the current state prediction.
        string sub = pollData.substr(count, 2);

        // This converts all of the characters in the sub variable to uppercase and then checks if it is a valid state code.
        for (int i = 0; i < sub.size(); i++) {
            sub[i] = toupper(sub[i]);
        }
        if (!isValidUppercaseStateCode(sub)) {
            return false;
        }

        // This moves on to the next state prediction in the pollData string if it exists.
        count += 2;
    }
    return true;
}
int computeVotes(string pollData, char party, int& voteCount) {
    // This uses the function defined above to check if the pollData string has the right syntax and returns 1 if it isn't.
    if (!hasRightSyntax(pollData)) {
        return 1;
    }

    
    int tempvoteCount = 0;
    int count = 0;

    while (count < pollData.size()) {
        char currentParty = toupper(pollData[count]);
        count++;
        int votes = 0;
        // This loops through the votecount and adds it to the votes variable, if there are two digits in the votecount it multiplies the first digit by 10 and then adds to second to digit to it. It then adds that value to votes.
        // It adds the votes to the votes variable by converting the char in the string to an int by subtracting it by '0'. It converts the characters into an int becuase subtracting by '0' results in an equivalent integer value through ASCII values.
        for (; count < pollData.size() && isdigit(pollData[count]); count++) {
            votes = votes * 10 + (pollData[count] - '0');
        }

        // This checks if the number of votes is 0 and returns 2 if it is.
        if (votes == 0) {
            return 2;
        }
        count += 2;
        //This adds the number of votes for each state prediction if the uppercase version of it matches the uppercase version of the party in the state prediction.
        if (currentParty == toupper(party)) {
            tempvoteCount += votes;
        }

    }

    // This checks if the character inputted into the function is alphabetical or not and returns 3 if it isn't.
    if (!isalpha(party)) {
        return 3;
    }

    // This sets the number of votes inputted into the function as the number of votes in the state prediction that matches the party character, and returns 0.
    voteCount = tempvoteCount;
    return 0;
}