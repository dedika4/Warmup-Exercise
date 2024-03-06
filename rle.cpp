#include "rle.h"
using namespace std;

string compressRLE(const string& input) {
    string output;
    for (size_t i = 0; i < input.length(); i++) {
        int count = 1;
        while (i + 1 < input.length() && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        output += input[i] + to_string(count);
    }
    return output;
}

string decompressRLE(const string& input) {
    string output;
    for (size_t i = 0; i < input.length(); i += 2) {
        output.append(stoi(string(1, input[i + 1])), input[i]);
    }
    return output;
}