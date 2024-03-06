#include "rle.h"
#include "lzw.h"
#include "file_io.h"

#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <cstring>

using namespace std;

string generateRandomString(size_t length) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);

    string random_string;
    random_string.reserve(length);

    // Use a better random number generator
    mt19937 rng(random_device{}()); // Use the Mersenne Twister engine
    uniform_int_distribution<> dist(0, max_index - 1);

    // Create a random string
    for (size_t i = 0; i < length; ++i) {
        random_string += charset[dist(rng)];
    }

    return random_string;
}

void benchmarkCompression(const string& algorithm,const string& inputData) {
    using namespace chrono;

    cout << "Algorithm: " << algorithm << endl;
    if ((algorithm == "RLE") || (algorithm == "All")) {
        string rle_compressed = compressRLE(inputData);
        auto rle_start = high_resolution_clock::now();
        string rle_decompressed = decompressRLE(rle_compressed);
        auto rle_end = high_resolution_clock::now();
        auto rle_duration = duration_cast<microseconds>(rle_end - rle_start).count();
        double rle_compressionRatio = static_cast<double>(inputData.size()) / rle_compressed.size();
    
        //cout << "RLE Compression Result: " << rle_compressed << endl;
        cout << "RLE Compression Ratio: " << rle_compressionRatio << ", RLE Decompression Time: " << rle_duration << " microseconds" << endl;
    } 
    if ((algorithm == "LZW") || (algorithm == "All")){
        auto lzw_compressed = compressLZW(inputData);  
        auto lzw_start = high_resolution_clock::now();
        string lzw_decompressed = decompressLZW(lzw_compressed);
        auto lzw_end = high_resolution_clock::now();
        auto lzw_duration = duration_cast<microseconds>(lzw_end - lzw_start).count();
        double lzw_compressionRatio = static_cast<double>(inputData.size()) / lzw_compressed.size();

        //cout << "LZW Compression Result: " << lzw_decompressed << endl;
        cout << "LZW Compression Ratio: " << lzw_compressionRatio << ", LZW Decompression Time: " << lzw_duration << " microseconds" << endl;
    }
}

int main(int argc, char** argv) {
    string filename;
    string algorithm;
    
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << "<input_file>/<input_text> <algorithm> " << endl;
        return 1;
    } 
    if (argc >= 2){
        filename = argv[1];
        algorithm = "All";
    } 
    if (argc >= 3){
        if (strcmp(argv[2], "RLE") != 0 && strcmp(argv[2], "LZW") != 0){
            cerr << "Algorithm available only 'RLE' and 'LZW' " << endl;
            return 1;
        }
        algorithm = argv[2];
    }

    string inputData = readTextFile(filename);
    //cout << inputData;
    cout << endl;
    benchmarkCompression(algorithm,inputData);
    cout << endl;

    return 0;
}
