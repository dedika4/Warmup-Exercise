#include "lzw.h"
#include <map>

std::vector<int> compressLZW(const std::string& input) {
    std::map<std::string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[std::string(1, i)] = i;
    }

    std::string p;
    std::vector<int> output;
    for (char c : input) {
        std::string pc = p + c;
        if (dictionary.count(pc)) {
            p = pc;
        } else {
            output.push_back(dictionary[p]);
            dictionary[pc] = dictionary.size();
            p = std::string(1, c);
        }
    }
    if (!p.empty()) {
        output.push_back(dictionary[p]);
    }
    return output;
}

std::string decompressLZW(const std::vector<int>& input) {
    std::map<int, std::string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = std::string(1, i);
    }

    std::string w(1, input[0]);
    std::string result = w;
    std::string entry;
    for (size_t i = 1; i < input.size(); i++) {
        int k = input[i];
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictionary.size()) {
            entry = w + w[0];
        }

        result += entry;
        dictionary[dictionary.size()] = w + entry[0];
        w = entry;
    }
    return result;
}
