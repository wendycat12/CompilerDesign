// Wendy Catalan 
// Compiler Design Homework 1

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Read the content of file
string readFile(string filename) 
{
    ifstream file(filename);
    string content;

    if (file.is_open()) {
        // Read file into the string
        getline(file, content, '\0'); // Read until null 
        file.close();
        return content;
    }
    else {
        cerr << "Error opening file: " << filename << endl;
        return ""; // Error by returning empty string
    }
}

int main() 
{
    string filename = "C:\\Users\\windo\\source\\repos\\CompilerDesignHW1.cpp\\Document.rtf";
    string content = readFile(filename);

    if (content.empty()) {
        // Handle error if reading failed
        cerr << "Error reading file." << endl;
        return 1;
    }

    cout << content << endl;

    return 0;
}