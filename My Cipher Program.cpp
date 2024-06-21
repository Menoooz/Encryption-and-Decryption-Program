// Name: My Cipher Program
// Program Description: the program is used to encrypt or decrypt a message using 4 diffrent ciphers (vignere , route , baconian , morse code).

#include <iostream>
#include <string>
#include <limits>   // For using numeric_limits
#include <cctype>   // For toupper and isalpha
#include <algorithm> // For find
#include <sstream>   // For istringstream

using namespace std;

//____Route Cipher encryption____
string routeCipherEncryption(const string& sentence, int key) {
    string word, encrypt;
    // Convert the sentence to uppercase and remove non-alphabetic characters
    for (char c : sentence) {
        if (isalpha(c)) {
            word += toupper(c); // Convert character to uppercase and append to word
        }
    }
    // Padding with 'X' to make the length of word a multiple of key
    int i = word.length();
    while (i % key != 0) {
        word += 'X'; // Append 'X' characters to the word
        i += 1;
    }

    int rows = word.length() / key; // Calculate the number of rows
    int cols = key; // Number of columns is equal to the key
    int index = 0;
    char matrix[rows][cols];

    // Creating the matrix
    // Iterate over each row of the matrix
    for (int i = 0; i < rows; ++i) {
        // Iterate over each column of the matrix
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = word[index];
            index += 1;
        }
    }

    int x = 1;
    int y = 0;

    // Loop until the length of the encrypted message matches the length of the word
    while (encrypt.length() < word.length()) {
        // Right column
        for (int i = y; i < rows - y && encrypt.length() < word.length(); ++i) {
            int j = cols - x;
            encrypt += matrix[i][j]; // Append character to the encrypted string
        }
        // Bottom row
        for (int j = cols - 1 - x; j >= y && encrypt.length() < word.length(); --j) {
            int i = rows - x;
            encrypt += matrix[i][j]; // Append character to the encrypted string
        }
        // Left column
        for (int i = rows - x - 1; i >= y && encrypt.length() < word.length(); --i) {
            int j = y;
            encrypt += matrix[i][j]; // Append character to the encrypted string
        }
        // Top row
        for (int j = y + 1; j < cols - x && encrypt.length() < word.length(); ++j) {
            int i = y;
            encrypt += matrix[i][j]; // Append character to the encrypted string
        }
        x += 1; // Move between rows and columns
        y += 1; // Move between rows and columns
    }

    return encrypt; // Return the encrypted message
}

//____Route Cipher Decryption____
string routeDecipher(string word, int key) {
    string mes; // Variable to store the deciphered message
    int rows = word.length() / key + (word.length() % key != 0); // Calculate the number of rows (considering any remaining characters)
    int cols = key; // Number of columns is equal to the key

    char matrix[rows][cols]; // Create a matrix to store the characters

    // Initialize variables for traversing the matrix
    int x = 1;
    int y = 0;
    int index = 0;

    // Fill the matrix with characters from the word
    while (index < word.length()) {
        for (int i = y; i < rows - y && index < word.length(); i++) {
            int j = cols - x;
            matrix[i][j] = word[index++];
        }
        for (int j = cols - 1 - x; j >= y && index < word.length(); j--) {
            int i = rows - x;
            matrix[i][j] = word[index++];
        }
        for (int i = rows - x - 1; i >= y && index < word.length(); i--) {
            int j = y;
            matrix[i][j] = word[index++];
        }
        for (int j = y + 1; j < cols - x && index < word.length(); j++) {
            int i = y;
            matrix[i][j] = word[index++];
        }
        x += 1; // Move between rows and columns
        y += 1; // Move between rows and columns
    }

    // Extract the message from the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != ' ') {
                mes += matrix[i][j]; // Append non-space characters to the message
            }
        }
    }

    return mes; // Return the deciphered message
}

//____Vignere functions____
// Function to filter out non-alphabetic characters from a string
string only_alpha(const string& str) {
    string alpha;
    for (char c : str) {
        if (isalpha(c)) {
            alpha += c; // Append alphabetic characters to the result
        }
    }
    return alpha;
}

// Function to check if the keyword is valid
bool valid_key(const string& word) {
    if (word.length() > 8) {
        return false; // If word length is more than 8, return false
    }
    for (char c : word) {
        if (!isalpha(c)) {
            return false; // If any character is not alphabetic, return false
        }
    }
    return true; // If all conditions are met, return true
}

// Function to convert a string to uppercase
string toupper(const string& str) {
    string upper;
    for (char c : str) {
        upper += toupper(c); // Convert each character to uppercase and append to result
    }
    return upper;
}

// Function to perform Vigenere encryption
string encryptVigenere(const string& message, const string& keyword) {
    // Convert message and keyword to uppercase
    string upmes = toupper(message);
    string upkey = toupper(keyword);

    // Initialize arrays for message and key
    char mes[upmes.length()], key[upmes.length()];

    // Populate message array with uppercase letters from the message
    for (int i = 0; i < upmes.length(); ++i) {
        mes[i] = upmes[i];
    }

    // Populate key array, wrapping around if necessary
    int keyIndex = 0;
    for (int i = 0; i < upmes.length(); ++i) {
        key[i] = upkey[keyIndex];
        keyIndex = (keyIndex + 1) % upkey.length();
    }

    // Encrypt the message
    string encrypted_message;
    for (int i = 0; i < upmes.length(); ++i) {
        if (isalpha(mes[i])) {
            int ASCIImes = mes[i];
            int ASCIIkey = key[i];
            int ASCIIencrypt = ((ASCIImes + ASCIIkey - 130) % 26) + 65;
            char letter = ASCIIencrypt;
            encrypted_message += letter;
        } else {
            encrypted_message += upmes[i];
        }
    }

    return encrypted_message;
}

// Function to decrypt a message using Vigenère cipher
string decryptVigenere(const string& encrypted_message, const string& keyword) {
    string up_encrypted_message = toupper(encrypted_message);
    string up_key = toupper(keyword);

    char encrypted_mes[up_encrypted_message.length()], key[up_encrypted_message.length()];

    // Populate the arrays with uppercase letters
    for (int i = 0; i < up_encrypted_message.length(); ++i) {
        encrypted_mes[i] = up_encrypted_message[i]; // Assign each character of the word to the array
    }

    // Populate the key array, wrapping around if necessary
    int keyIndex = 0;
    for (int i = 0; i < up_encrypted_message.length(); ++i) {
        key[i] = up_key[keyIndex]; // Assign character from the word to the array
        keyIndex = (keyIndex + 1) % up_key.length(); // Move to the next character in the word, wrapping around if necessary
    }

    // Perform decryption
    string decrypted_message;
    for (int i = 0; i < up_encrypted_message.length(); ++i) {
        if (isalpha(encrypted_mes[i])) {
            int ASCIImes = encrypted_mes[i];
            int ASCIIkey = key[i];
            int ASCIIdecrypt = ((ASCIImes - ASCIIkey + 26) % 26) + 65;
            char letter = ASCIIdecrypt;
            decrypted_message += letter;
        } else {
            decrypted_message += up_encrypted_message[i];
        }
    }

    return decrypted_message;
}

//____Baconian functions___
// Function to check if a message contains only alphabetic characters
bool isAlphaMessage(const string& message) {
    for (char c : message) {
        if (!isalpha(c)) {
            return false; // If any character is not alphabetic, return false
        }
    }
    return true; // If all characters are alphabetic, return true
}

// Function to convert a string to uppercase
string toUpper(const string& str) {
    string upper;
    for (char c : str) {
        upper += toupper(c); // Convert each character to uppercase and append to result
    }
    return upper;
}

// Function to encrypt a message using the Baconian cipher
string encryptBaconian(const string& message) {
    string encrypted;
    string upmes = toUpper(message);

    // Alphabets array and Baconian cipher representations
    char alphabets[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    string baconian[] = {"aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabab", "aabba",
                         "aabbb", "abaaa", "abaab", "ababa", "ababb", "abbaa", "abbab",
                         "abbba", "abbbb", "baaaa", "baaab", "baaba", "baabb", "babaa",
                         "babab", "babba", "babbb", "bbaaa", "bbaab"};

    for (int i = 0; i < message.length(); i++) {
        auto letter = find(begin(alphabets), end(alphabets), upmes[i]);
        if (letter != end(alphabets)) {
            int index = distance(begin(alphabets), letter);
            encrypted += baconian[index] + " ";
        }
    }
    return encrypted;
}
// Function to decrypt a message using the Baconian cipher
string decryptBaconian(const string& encrypted) {
    string decrypted;

    // Alphabets array and Baconian cipher representations
    char alphabets[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    string baconian[] = {"aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabab", "aabba",
                         "aabbb", "abaaa", "abaab", "ababa", "ababb", "abbaa", "abbab",
                         "abbba", "abbbb", "baaaa", "baaab", "baaba", "baabb", "babaa",
                         "babab", "babba", "babbb", "bbaaa", "bbaab"};

    // Process the encrypted message
    string token;
    istringstream iss(encrypted);
    while (iss >> token) {
        auto it = find(begin(baconian), end(baconian), token);
        if (it != end(baconian)) {
            int index = distance(begin(baconian), it);
            decrypted += alphabets[index];
        } else {
            // If the token is not found in the Baconian cipher, assume it's a space
            decrypted += ' ';
        }
    }

    return decrypted;
}

//____Morse Code functions___
// Function to check if a string contains only alphanumeric characters and spaces
bool isValidInput(const string& str) {
    for (char c : str) {
        if (!isalnum(c) && c != ' ') {
            return false; // If any character is not alphanumeric or space, return false
        }
    }
    return true; // If all characters are alphanumeric or space, return true
}

// Function to convert a string to uppercase
string toUpperMorse(const string& str) {
    string upper;
    for (char c : str) {
        upper += toupper(c); // Convert each character to uppercase and append to result
    }
    return upper;
}

// Function to encrypt a message using the Morse code cipher
string encryptMorse(const string& message) {
    string encrypted;
    string upmes = toUpper(message); // Convert the input message to uppercase

    // Arrays to store the alphabet and its corresponding Morse code
    char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    string morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
                          "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                          "-.--", "--..",
                          ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

    // Iterate through each character in the input message
    for (int i = 0; i < message.length(); i++) {
        // Check if the character is alphanumeric or space
        if (isalnum(upmes[i]) || upmes[i] == ' ') {
            auto letter = find(begin(alpha), end(alpha), upmes[i]); // Find the character in the alphabet array
            if (letter != end(alpha)) { // If the character is found in the alphabet
                int index = distance(begin(alpha), letter); // Get the index of the character in the alphabet
                encrypted += morseCode[index] + " "; // Append the Morse code for the character
            }
        }
    }
    return encrypted;
}
// Function to decrypt a message using the Morse code cipher
string decryptMorse(const string& encrypted) {
    string decrypted;

    // Arrays to store the alphabet and its corresponding Morse code
    char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    string morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
                          "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                          "-.--", "--..",
                          ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

    // Tokenize the encrypted message
    istringstream iss(encrypted);
    string token;
    while (iss >> token) {
        auto it = find(begin(morseCode), end(morseCode), token); // Find the Morse code in the Morse code array
        if (it != end(morseCode)) { // If the Morse code is found
            int index = distance(begin(morseCode), it); // Get the index of the Morse code in the Morse code array
            decrypted += alpha[index]; // Append the corresponding character to the decrypted message
        }
    }

    return decrypted;
}
//____________________
// Going into the main function containing the main program
int main() {
    int programChoice, num;
    string message, newMessage;
    int cipher, decipher;
    // Welcoming the user into the program
    cout << "\n___Welcome User to the Cipher Program___\n";
    while (true) {
        // asking the user what he wants to do
        cout << "\nWhat would you like to do ?\n1- Cipher a message\n2- Decipher a message\n3- Exit\n";
        // Validate user input for program choice
        while (!(cin >> programChoice) || (programChoice < 1 || programChoice > 3)) {
            cout << "Please enter a valid choice (1, 2, or 3): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // Clear the newline character from the input buffer
        cin.ignore();
        // Handle the user's choice
        // if the user chooses 1, then he wants to cipher a message
        if (programChoice == 1) {
            while (true) {
                // Asking the user to choose which cipher program he wants to use
                cout << "\nWhich Cipher would you like to use?\n1- Vignere Cipher\n2- Route Cipher\n3- Baconian Cipher\n4- Morse Code Cipher" << endl;

                // Validate user input
                while (!(cin >> cipher) || (cipher < 1 || cipher > 4)) {
                    cout << "Please enter a valid choice (1, 2, 3, or 4): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Clear the newline character from the input buffer
                cin.ignore();
                // calling the Vignere encryption function if the user chooses 1
                if (cipher == 1) {
                    cout << "___Welcome to 'Vignere Cipher' program___" << endl << endl;
                    string message, keyword;
                    // Input message and validate its length
                    while(true) {
                        cout << "Enter the message you want to encrypt: ";
                        getline(cin, message);
                        string alpha = only_alpha(message);
                        if (alpha.length() <= 80) {
                            break;
                        } else {
                            cout << "Please don't enter more than 80 characters." << endl;
                        }
                    }
                    // Input keyword and validate its length and characters
                    while (true) {
                        cout << "Enter your keyword: ";
                        getline(cin, keyword);
                        if (valid_key(keyword)) {
                            break;
                        } else {
                            cout << "Not valid, please make sure the keyword is (less than 8 characters, alphabetic only)." << endl;
                        }
                    }
                    // Encrypt the message and print the result
                    string encrypted_message = encryptVigenere(message, keyword);
                    cout << "Encrypted message: " << encrypted_message << endl;
                    break;

                    // calling the route encryption function if the user chooses 2
                } else if (cipher == 2) {
                    cout << "___Welcome to 'Route Cipher' program___" << endl << endl;
                    string sentence, word;
                    int key;
                    // Get the message from the user
                    while (true) {
                        // Prompt the user to enter the sentence
                        cout << "Please enter your message: ";
                        getline(cin, sentence);
                        // Check if the word length is less than or equal to 3
                        if (sentence.length() <= 3) {
                            cout << "Please make sure the number of letters in your message is > 3." << endl;
                        } else {
                            break; // Exit the loop if the condition is met
                        }
                    }
                    // Convert the sentence to uppercase and remove non-alphabetic characters
                    for (char c : sentence) {
                        if (isalpha(c)) {
                            word += toupper(c); // Convert character to uppercase and append to word
                        }
                    }
                    // Get the secret key from the user
                    while (true) {
                        cout << "Enter your secret key : ";
                        if (cin >> key && key > 1 && key <= int((word.length() + 1) / 2)) {
                            break;
                        } else {
                            cout << "Not a valid number." << endl << "Please make sure that the (1 < key < " << int((word.length() + 1) / 2) + 1 << ")." << endl;
                            cin.clear(); // Clear error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        }
                    }
                    // Perform Route Cipher encryption
                    string encryptedMessage = routeCipherEncryption(sentence, key);
                    cout << endl << "Your Encrypted message using the Route Cipher : " << encryptedMessage << "." << endl<<endl; // Output the encrypted message
                    break;

                    // calling the Baconian encryption function if the user chooses 3
                } else if (cipher == 3) {
                    cout << "___Welcome to 'Baconian Cipher' program___" << endl << endl;
                    string message, encrypt;
                    // Input message and validate its length
                    while (true) {
                        cout << "Enter the message you want to encrypt: ";
                        getline(cin, message);
                        if (isAlphaMessage(message)) {
                            break;
                        } else {
                            cout << "Invalid, make sure the message contains only alphabetic characters." << endl;
                        }
                    }
                    encrypt = encryptBaconian(message); // Encrypt the message
                    cout << "The encrypted message is : " << encrypt << endl;
                    break;

                    // calling the morse code encryption function if the user chooses 4
                }else if (cipher == 4) {
                    cout << "___Welcome to 'Morse Code Cipher' program___" << endl << endl;
                    string message, encrypt;
                    // Input message with validation
                    while (true) {
                        cout << "Enter the message you want to encrypt (only letters, numbers, and spaces allowed): ";
                        getline(cin, message);
                        if (isValidInput(message)) {
                            break; // If the input is valid, exit the loop
                        } else {
                            cout << "Invalid input. Please enter only letters, numbers, and spaces." << endl;
                        }
                    }
                    encrypt = encryptMorse(message); // Encrypt the message
                    cout << "The encrypted message is: " << encrypt << endl;
                    break;

                    // if the user inputs an invalid input, he will be asked to re input a valid choice
                }else if (cin.fail() || cipher != 1 || cipher != 2 || cipher != 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please choose a suitable choice!\n";
                    continue;
                }
                break;
            }
        }
            // if the user chooses 2, then he wants to decipher a message
        else if (programChoice == 2) {
            while (true) {
                // Asking the user to choose which decipher program he wants to use
                cout << "\nWhich Decipher would you like to use?\n1- Vignere decipher\n2- Route decipher\n3- Baconian decipher\n4- Morse Code decipher" << endl;

                // Validate user input
                while (!(cin >> decipher) || (decipher < 1 || decipher > 4)) {
                    cout << "Please enter a valid choice (1, 2, 3, or 4): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Clear the newline character from the input buffer
                cin.ignore();

                // calling the Vignere decryption function if the user chooses 1
                if (decipher == 1) {
                    cout << "___Welcome to 'Vignere Decipher' program___" << endl << endl;
                    string encrypted_message, keyword;
                    // Input encrypted message and validate its length
                    while(true) {
                        cout << "Enter the encrypted message: ";
                        getline(cin, encrypted_message);
                        string alpha = only_alpha(encrypted_message);
                        if (alpha.length() <= 80) {
                            break;
                        } else {
                            cout << "Please don't enter more than 80 characters." << endl;
                        }
                    }
                    // Input keyword and validate its length and characters
                    while (true) {
                        cout << "Enter the keyword: ";
                        getline(cin, keyword);
                        if (valid_key(keyword)) {
                            break;
                        } else {
                            cout << "Not valid, please make sure the keyword is (less than 8 characters, alphabetic only)." << endl;
                        }
                    }
                    // Decrypt the message and print the result
                    string decrypted_message = decryptVigenere(encrypted_message, keyword);
                    cout << "Decrypted message: " << decrypted_message << endl;
                    break;

                    // calling the route decryption function if the user chooses 2
                } else if (decipher == 2) {
                    cout << "___Welcome to 'Route Decipher' program___" << endl << endl;
                    string sentence, word, mes;
                    int key;
                    // Prompt the user to enter the sentence
                    cout << "Please enter your message: ";
                    getline(cin, sentence);
                    // Convert the sentence to uppercase and remove non-alphabetic characters
                    for (char c : sentence) {
                        if (isalpha(c)) {
                            word += toupper(c); // Convert character to uppercase and append to word
                        }
                    }
                    // Check if the word length is less than or equal to 3
                    if (word.length() <= 3) {
                        cout << "Please make sure the number of letters in your message is > 3." << endl;
                    } else {
                        // Get the secret key from the user
                        while (true) {
                            cout << "Enter your secret key : ";
                            if (cin >> key && key > 1 && key <= int((word.length() + 1) / 2)) {
                                break;
                            } else {
                                cout << "Not a valid number." << endl << "please make sure that the (1 < key < " << int((word.length() + 1) / 2) + 1 << ")." << endl;
                                cin.clear(); // Clear error flags
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                        }
                        cout << endl;
                        // Call the routeDecipher function and store the result in mes
                        mes = routeDecipher(word, key);
                        // Output the decrypted message
                        cout << "Your decrypted message is: " << mes << "." << endl<<endl;
                    }
                    break;

                    // calling the Baconian decryption function if the user chooses 3
                } else if (decipher == 3) {
                    cout << "___Welcome to 'Baconian Decipher' program___" << endl << endl;
                    string encrypted, decrypted;
                    // Input the encrypted message
                    cout << "Enter the encrypted message: ";
                    getline(cin, encrypted);
                    // Decrypt the message
                    decrypted = decryptBaconian(encrypted);
                    // Output the decrypted message
                    cout << "The decrypted message is: " << decrypted << endl;
                    break;

                    // calling the morse code decryption function if the user chooses 4
                } else if (decipher == 4) {
                    cout << "___Welcome to 'Morse Code Decipher' program___" << endl << endl;
                    string encrypted, decrypted;
                    // Input the encrypted message
                    cout << "Enter the encrypted message: ";
                    getline(cin, encrypted);
                    // Decrypt the message
                    decrypted = decryptMorse(encrypted);
                    // Output the decrypted message
                    cout << "The decrypted message is: " << decrypted << endl;
                    break;

                }else if (cin.fail() || decipher != 1 || decipher != 2 || decipher != 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please choose a suitable choice!!!\n";
                    continue;
                }
            }
        }
            // if the user at the beginning of the program chooses 3, then he will exit from the program
        else if (programChoice == 3) {
            cout << "\nThank you for using the program";
            break;
        }
            // if the user inputs an invalid input, he will be asked to re input a valid choice
        else {
            cout << "Please enter a valid choice (1, 2, or 3).\n";
        }
    }
    return 0;
}

