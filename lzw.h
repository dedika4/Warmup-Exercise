#include <string>
#include <vector>

// LZW Compression
std::vector<int> compressLZW(const std::string& input);

// LZW Decompression
std::string decompressLZW(const std::vector<int>& input);
