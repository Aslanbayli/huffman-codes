#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include <map>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

class HuffmanTree : HuffmanTreeBase {
private:
    int size;
    HuffmanNode* root;
// provided functions
public:
    string compress(const string inputStr);
    string serializeTree() const;
    string decompress(const string inputCode, const string serializedTree);

// Custom functions
public:
    void preorderTraverse(const HuffmanNode* node, map<char, string>& codes, string code); // traverse the tree recursively to generate the Huffman Codes
    map<char, string> codes; // A map for storing the Huffman code for each character
    string huffmanCode; // The compressed Huffman code
    void postorderTraverse(const HuffmanNode* node, string& outStr) const;
};

#endif