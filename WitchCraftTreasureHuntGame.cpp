#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to display the vector
void displayVector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i < vec.size() - 1 ? " " : "");
    }
    cout << endl;
}

// Generate unique random numbers within a given range and count
vector<int> generateUniqueNumbers(int count, int min, int max, bool isOdd) {
    vector<int> numbers;
    while (numbers.size() < count) {
        int num = rand() % (max - min + 1) + min;
        if ((num % 2 == isOdd) && find(numbers.begin(), numbers.end(), num) == numbers.end()) {
            numbers.push_back(num);
        }
    }
    return numbers;
}

// Validate if a number is in the list and has the correct parity
bool isValidChoice(int num, const vector<int>& list, bool isOdd) {
    return (num % 2 == isOdd) && (find(list.begin(), list.end(), num) != list.end());
}

int main() {
    srand(time(0)); // Seed for random number generation

    cout << "Welcome to the Witch Craft Treasure Hunt Game!\n\n";

    // Generate numbers
    vector<int> oddNumbers = generateUniqueNumbers(15, 1, 50, true);
    vector<int> evenNumbers = generateUniqueNumbers(15, 1, 50, false);
    vector<int> numbers = oddNumbers; // Combine odd and even numbers
    numbers.insert(numbers.end(), evenNumbers.begin(), evenNumbers.end());

    cout << "Your mystical numbers are:\n";
    displayVector(numbers);
    cout << "\nChoose 3 odd and 3 even numbers wisely!\n";

    int attempts = 2;
    while (attempts > 0) {
        vector<int> selectedOdd, selectedEven;

        // User selects odd numbers
        cout << "\nChoose 3 odd numbers:\n";
        while (selectedOdd.size() < 3) {
            int num;
            cin >> num;
            if (isValidChoice(num, numbers, true)) {
                selectedOdd.push_back(num);
                numbers.erase(find(numbers.begin(), numbers.end(), num));
                cout << num << " added.\n";
            } else {
                cout << "Invalid choice. Choose an odd number from the list.\n";
            }
        }

        // User selects even numbers
        cout << "\nChoose 3 even numbers:\n";
        while (selectedEven.size() < 3) {
            int num;
            cin >> num;
            if (isValidChoice(num, numbers, false)) {
                selectedEven.push_back(num);
                numbers.erase(find(numbers.begin(), numbers.end(), num));
                cout << num << " added.\n";
            } else {
                cout << "Invalid choice. Choose an even number from the list.\n";
            }
        }

        // Calculate total power
        int totalPower = 0;
        for (int num : selectedOdd) totalPower += num;
        for (int num : selectedEven) totalPower += num;

        // Generate random monster power
        int monsterPower = rand() % 131 + 120; // Range 120-250
        cout << "\nA monster appears with power level " << monsterPower << "!\n";
        cout << "Your combined power: " << totalPower << "\n";

        if (totalPower > monsterPower) {
            cout << "Congratulations! You defeated the monster.\n";
            break;
        } else if (totalPower == monsterPower) {
            cout << "It's a tie! The monster retreats.\n";
            break;
        } else {
            cout << "You lose this round. Try again!\n";
            attempts--;
            cout << "Remaining attempts: " << attempts << "\n";
        }
    }

    if (attempts == 0) {
        cout << "\nGame Over! Better luck next time.\n";
    }

    return 0;
}
