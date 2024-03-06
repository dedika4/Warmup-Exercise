#include "file_io.h"
#include <fstream>
#include <iterator>
#include <iostream>
using namespace std;

string readTextFile(const string& filename) {
    ifstream file(filename);
    cout << "Reading file : " << filename << endl;
    if (file) {
        return string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    }
    return ""; // Return an empty string if file couldn't be opened
}

bool writeTextFile(const string& filename, const string& text) {
    ofstream file(filename);
    if (file) {
        file << text;
        return true;
    }
    return false;
}


