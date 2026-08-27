#ifndef VALIDATION_H
#define VALIDATION_H

#include "globals.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// validate input
static inline int validateInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

// helper function
static inline bool hasLetters(const string& input){
    for(char c: input)
        if(isalpha(c)) return true;
    return false;
}

// validate string
static inline string validateString(const string& prompt, int maxLength = 100, bool lettersOnly = false){
    string input;
    while(true){
        cout<<prompt;
        getline(cin, input);
        if(input.empty()){
            cout<<"Input cannot be empty. Try again.\n";
            continue;
        }
        bool allSpaces = true;
        for(char c : input) if(c != ' '){allSpaces = false; break;}
        if(allSpaces){
            cout<<"Input cannot be blank. Try again.\n";
            // system("cls");
            continue;
        }
        if((int)input.length() > maxLength){
            cout<<"Input too long. Maximum length is "<<maxLength<<". Try again.\n";
            continue;
        }
        if(lettersOnly && !hasLetters(input)){
            cout<<"Must contain letters. Try again.\n";
            continue;
        }
        return input;
    }
}

// validate password
static inline string validatePassword(const string& prompt, int minLength = 6, int maxLength = 20){
    string input;
    while(true){
        cout<<prompt;
        getline(cin, input);
        if(input.empty()){
            cout<<"Password cannot be empty. Try again.\n";
            continue;
        }
        if((int)input.length() < minLength){
            cout<<"Password too short. Minimum length is "<<minLength<<". Try again.\n";
            continue;
        }
        if((int)input.length() > maxLength){
            cout<<"Password too long. Maximum length is "<<maxLength<<". Try again.\n";
            continue;
        }
        return input;
    }
}

// validate gender
static inline char validateGender(const string& prompt){
    string input;
    while(true){
        cout<<prompt;
        cin>>input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(input.length() == 1 && (input[0] == 'M' || input[0] == 'F' 
            || input[0] == 'm' || input[0] == 'f')){
            return toupper(input[0]);
        }
        cout<<"Invalid input. Please enter M or F.\n";
    }
}

// validate age
static inline int validateAge(const string& prompt, int min = 16, int max = 70){
    int input;
    while(true){
        cout<<prompt;
        cin>>input;
        if(cin.fail() || input < min || input > max){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid age. Enter a value between "<<min<<" and "<<max<<".\n";
        }else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

// validate year
static inline int validateYear(const string& prompt, int min = 1, int max = 5){
    int input;
    while(true){
        cout<<prompt;
        cin>>input;
        if(cin.fail() || input < min || input > max){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid year. Enter a value between "<<min<<" and "<<max<<".\n";
        }else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

// validate phone
static inline string validatePhone(const string& prompt){
    string input;
    while(true){
        cout<<prompt;
        getline(cin, input);
        if(input.empty()){
            cout<<"Phone number cannot be empty. Try again. \n";
            continue;
        }
        bool valid = true;
        for(char c : input){
            if(!isdigit(c)){ valid = false; break; }
        }
        if(!valid){
            cout<<"Phone number must contain digits only. Try again.\n";
            continue;
        }
        if(input.length() < 9 || input.length() > 13){
            cout<<"Invalid phone number length. Try again.\n";
            continue;
        }
        return input;
    }
}

// validate email
static inline string validateEmail(const string& prompt){
    string input;
    while(true){
        cout<<prompt;
        getline(cin, input);
        if(input.empty()){
            cout<<"Email cannot be empty. Try again.\n";
            continue;
        }
        size_t atPos = input.find('@');
        size_t dotPos = input.find('.', atPos);
        if(atPos == string::npos || dotPos == string::npos || atPos == 0 || dotPos == atPos + 1){
            cout<<"Invalid email format. Must contain @ and . Try again.\n";
            continue;
        }
        return input;
    }
}

// validate score
static inline float validateScore(const string& prompt, float min = 0, float max = 100){
    float input;
    cin>>input;
    if(cin.fail() || input < min || input > max){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid score. Enter a value between "<<min<<" and "<<max<<".\n";
    }else{
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return input;
    }
    return 0;
}

#endif