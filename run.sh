#!/bin/bash

# Define your input files and algorithms
declare -a files=("Texts/binary_image.txt" "Texts/high_entropy.txt" "Texts/lorem_ipsum.txt" "Texts/reccurent_text.txt")
declare -a algorithms=("RLE" "LZW")

# Ensure the compressor is built
g++ -g -o compressor main.cpp rle.cpp lzw.cpp file_io.cpp -std=c++11

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Run the compressor with Valgrind Massif on each file
for algorithm in "${algorithms[@]}"; do
    for file in "${files[@]}"; do
        echo "Running $algorithm compression on $file..."
        
        # Run the compressor under Massif
        valgrind --tool=massif --massif-out-file=massif.out ./compressor $file $algorithm
        
        # Generate a human-readable Massif report
        ms_print massif.out > "${file}_${algorithm}_massif.txt"
        
        # Output the filename of the Massif report
        echo "Massif report generated: ${file}_${algorithm}_massif.txt"
    done
done

echo "All done."
