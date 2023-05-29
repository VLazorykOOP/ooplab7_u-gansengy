#include <regex>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include "Class.cpp"

using namespace std;


bool PayForTheExam(User& customer) {
    cout << "For one try you need to pay 100$. Enter your amount of cash :";
    short cash;
    do {
        cin >> cash;
        if (cash < 100) cout << "Try again.";
        else {
            cout << "Your payement is accepted! Good luck on your exam!\n" << endl;
            customer.changeAccess(true);
            return true;
        }
    } while (cash < 100);
    return false;
}

int EnglishExam() {
    int score = 0;
    string answer;

    // Question 1
    cout << "Which of the following is correct?" << endl;
    cout << "a) They were going to the store." << endl;
    cout << "b) They were go to the store." << endl;
    cout << "c) They where going to the store." << endl;
    cin >> answer;
    if (answer == "a" || answer == "A") {
        cout << "Correct!" << endl;
        score++;
    }
    else {
        cout << "Incorrect. The correct answer is a) They were going to the store." << endl;
    }

    // Question 2
    cout << "Which of the following is a pronoun?" << endl;
    cout << "a) Run" << endl;
    cout << "b) She" << endl;
    cout << "c) Jump" << endl;
    cin >> answer;
    if (answer == "b" || answer == "B") {
        cout << "Correct!" << endl;
        score++;
    }
    else {
        cout << "Incorrect. The correct answer is b) She." << endl;
    }

    // Question 3
    cout << "Which of the following is a preposition?" << endl;
    cout << "a) Car" << endl;
    cout << "b) On" << endl;
    cout << "c) Sing" << endl;
    cin >> answer;
    if (answer == "b" || answer == "B") {
        cout << "Correct!" << endl;
        score++;
    }
    else {
        cout << "Incorrect. The correct answer is b) On." << endl;
    }

    cout << "Your score is " << score << " out of 3." << endl;

    return score;
}

void saveToFile(User user) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << user.getName() << ", " << user.getEmail() << ", " << user.getPassword()
            << ", " << user.getScore() << ", " << user.getAccess() << ", " << user.getExamPassStatus() << endl;
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void printAllUsers() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void print() {
    string answer;
    do {
        answer = "";
        cout << "Enter admin password :";
        cin >> answer;
        if (answer.compare("Kittens") == 0) {
            printAllUsers();
            return;
        }
        else cout << "Password incorrect, try again or exit by pressing E\n";
    } while (answer != "e" && answer != "E");
}



void Start() {
    string name, email, password;

    bool valid_input = false;
    while (!valid_input) {
        cout << "Please enter your name: ";
        try {
            cin >> name;
            for (int i = 0; i < name.length(); i++) {
                if (isdigit(name[i])) throw invalid_argument("Invalid input: name should not contain digits");
                if (!isalpha(name[i])) throw invalid_argument("Invalid input: name should contain only letters");
            }

            cout << "Please enter your email: ";
            cin >> email;
            regex email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
            if (!regex_match(email, email_regex)) throw invalid_argument("Invalid input: not a valid email address");

            cout << "Please enter your password: ";
            cin >> password;
            if (password.length() > 30) throw invalid_argument("Invalid input: password should not be longer than 30 characters");

            valid_input = true;
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }

    User Customer(name, email, password);


    bool result;
    cout << "Do you want to pay for your exam now (Y/N)? :";
    char answ;
    cin >> answ;
    if (answ != 'y' && answ != 'Y') {
        cout << "Come back later!";
        saveToFile(Customer);
        return;
    }
    else result = PayForTheExam(Customer);

    if (result) {
        int score = EnglishExam();
        Customer.changeExamStatus(true);
        Customer.changeAccess(false);
        Customer.addScore(score);
        saveToFile(Customer);
    }
}

int main()
{
    char answer;
    do {
        cout << "List:\n";
        cout << "1: Register and try to pass the exam\n";
        cout << "2: Give list of all customers (admin only)\n";
        cout << "Press E to exit\n";

        cin >> answer;

        switch (answer) {
        case '1': { Start(); continue; }
        case '2': { print(); continue; }
        case 'e': case 'E': return 0;
        default: cout << "Your data is incorrect. Please try again.\n" << endl;
        }
    } while (answer != 'E' && answer != 'e');
}
