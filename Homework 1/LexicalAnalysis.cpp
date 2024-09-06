// Wendy Catalan 
// Compiler Design Homework 1

#include <iostream>
#include <fstream>


using namespace std;

// Function to process the file and display words and punctuation marks
void processFile(const string& filename) 
{
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
    }

    string word;
    char c;
    while (file.get(c)) {
        if (isalpha(c) || c == '\'') {
            word += c;
        } else {
            if (!word.empty()) {
                cout << word << endl;
                word.clear();
            }
            if (ispunct(c)) {
                cout << c << endl;
            }
        }
    }
    if (!word.empty()) {
        cout << word << endl;
    }
    file.close();
}

int main() 
{
    string filename = "C:\Users\windo\OneDrive\Desktop\University\
                La Verne\Compiler Design\Homework 1\Document.txt";

    processFile(filename);

    return 0;
}
