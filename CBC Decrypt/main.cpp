#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

/**
 * Recover the encrypted message, knowing the first block of plain text. The
 * encrypted text is of the form IV | C0 | C1 | ... where each block is 12 bytes
 * long.
 **/
std::string recoverMessage(
                           std::vector<unsigned char> first_block,
                           std::vector<unsigned char> encrypted) {
    
    std::vector<unsigned char> result = first_block;
    std::vector<unsigned char> temp;
    
    
    for(int i = 0; i<encrypted.size(); i = i + 12){
        result[i] = result[i] ^ encrypted[i];
        result[i+1] = result[i+1] ^ encrypted[i+1];
        result[i+2] = result[i+2] ^ encrypted[i+2];
        result[i+3] = result[i+3] ^ encrypted[i+3];
        result[i+4] = result[i+4] ^ encrypted[i+4];
        result[i+5] = result[i+5] ^ encrypted[i+5];
        result[i+6] = result[i+6] ^ encrypted[i+6];
        result[i+7] = result[i+7] ^ encrypted[i+7];
        result[i+8] = result[i+8] ^ encrypted[i+8];
        result[i+9] = result[i+9] ^ encrypted[i+9];
        result[i+10] = result[i+10] ^ encrypted[i+10];
        result[i+11] = result[i+11] ^ encrypted[i+11];
        result[i+12] = result[i+12] ^ encrypted[i+12];
        
        
//        temp.push_back(encrypted[i]);  // appends element i from the vector encrypted to temp.
    }
    
    
    
    
//      ^ - XOR
//      http://en.cppreference.com/w/cpp/container/vector vector help
//    // Create a vector containing integers
//    std::vector<int> v = {7, 5, 16, 8};
//
//    // Add two more integers to vector
//    v.push_back(25);
//    v.push_back(13);
//
//    // Iterate and print values of vector
//    for(int n : v) {
//        std::cout << n << '\n';
//    }
//
    
    
    
    
    
    
    // Work on the arrays (vectors) of bytes (unsigned chars).
    // In the end, construct a string as follows:
    std::string result_str(result.begin(), result.end());
    std::cout << "Result: \n" << result_str <<std::endl;
    return result_str;
}

// Helper for parsing.
unsigned int toInt(char c) {
    if (c >= '0' && c <= '9') return      c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1;
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    
    std::getline(infile, line);
    
    std::vector<unsigned char> first_block(line.begin(), line.end());
    
    std::getline(infile, line);
    const char * input = line.c_str();
    const size_t numdigits = std::strlen(input) / 2;
    std::vector<unsigned char> encrypted;
    for (size_t i = 0; i != numdigits; ++i)
        encrypted.push_back(16 * toInt(input[2*i]) + toInt(input[2*i+1]));
    
    std::string message = recoverMessage(first_block, encrypted);
    std::cout << "Recovered message: " << message << std::endl;
    
    return 0;
}


