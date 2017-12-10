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
    
    std::vector<unsigned char> key;
    
//    std::cout << "Test: \n" << encrypted[2] <<std::endl;
//    std::string test_str(encrypted.begin(), encrypted.end());
//    std::cout << "Test: \n" << test_str <<std::endl;
    
    
//    std::cout << "result[0]: \n" << result[0] <<std::endl;
//    std::cout << "encrypted[0]: \n" << encrypted[0] <<std::endl;
//    std::cout << "result[1] ^ encrypted[1]: \n" << (result[1] ^ encrypted[1]) <<std::endl;
//
//    std::cout << "encrypted[12]: \n" << encrypted[12] <<std::endl;
//    std::cout << "(result[0] ^ encrypted[0]) ^ encrypted[12]: \n" << ((result[0] ^ encrypted[0]) ^ encrypted[12]) <<std::endl;

    //Ci = K + (Mi + Ci-1), --> K = Ci + (Mi + Ci-1)


    key.push_back((result[0] ^ encrypted[0]) ^ encrypted[12]);
    key.push_back((result[1] ^ encrypted[1]) ^ encrypted[13]);
    key.push_back((result[2] ^ encrypted[2]) ^ encrypted[14]);
    key.push_back((result[3] ^ encrypted[3]) ^ encrypted[15]);
    key.push_back((result[4] ^ encrypted[4]) ^ encrypted[16]);
    key.push_back((result[5] ^ encrypted[5]) ^ encrypted[17]);
    key.push_back((result[6] ^ encrypted[6]) ^ encrypted[18]);
    key.push_back((result[7] ^ encrypted[7]) ^ encrypted[19]);
    key.push_back((result[8] ^ encrypted[8]) ^ encrypted[20]);
    key.push_back((result[9] ^ encrypted[9]) ^ encrypted[21]);
    key.push_back((result[10] ^ encrypted[10]) ^ encrypted[22]);
    key.push_back((result[11] ^ encrypted[11]) ^ encrypted[23]);
//        key[12] = (result[12] ^ encrypted[12]) ^ encrypted[i+12];
    
        
//        temp.push_back(encrypted[i]);  // appends element i from the vector encrypted to temp.
    
    
    std::string key_str(key.begin(), key.end());
    std::cout << "Key: \n" << key_str <<std::endl;
    
    std::cout << "encrypted.size(): \n" << encrypted.size() <<std::endl;
    
    // Ci = K + (Mi + Ci-1) --> Mi = (Ci + K) + Ci-1
    for(int i = 12; i<encrypted.size(); i = i + 12){
        result.push_back((encrypted[i+12] ^ key[0]) ^ encrypted[i]);
        result.push_back((encrypted[i+13] ^ key[1]) ^ encrypted[i+1]);
        result.push_back((encrypted[i+14] ^ key[2]) ^ encrypted[i+2]);
        result.push_back((encrypted[i+15] ^ key[3]) ^ encrypted[i+3]);
        result.push_back((encrypted[i+16] ^ key[4]) ^ encrypted[i+4]);
        result.push_back((encrypted[i+17] ^ key[5]) ^ encrypted[i+5]);
        result.push_back((encrypted[i+18] ^ key[6]) ^ encrypted[i+6]);
        result.push_back((encrypted[i+19] ^ key[7]) ^ encrypted[i+7]);
        result.push_back((encrypted[i+20] ^ key[8]) ^ encrypted[i+8]);
        result.push_back((encrypted[i+21] ^ key[9]) ^ encrypted[i+9]);
        result.push_back((encrypted[i+22] ^ key[10]) ^ encrypted[i+10]);
        result.push_back((encrypted[i+23] ^ key[11]) ^ encrypted[i+11]);
    }
//    for(int i = 12; i<encrypted.size(); i++){
//        result.push_back((encrypted[(i % 12) + 12] ^ key[i % 12]) ^ encrypted[i]);
//    }
    
    
    // Work on the arrays (vectors) of bytes (unsigned chars).
    // In the end, construct a string as follows:
    std::string result_str(result.begin(), result.end());
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


