// Ali Aslanbayli, Chloe Berry
#include "HuffmanTree.hpp"

using namespace std;

// Function definiton for recursively traversing the tree in preorder fashion
void HuffmanTree::preorderTraverse(const HuffmanNode* node, map<char, string>& codes, string code) {
    if (node == nullptr) {
        return;
    }
    
    if (node->isLeaf()) {
        codes[node->getCharacter()] = code;
    }
    
    preorderTraverse(node->left, codes, code + "0");
    preorderTraverse(node->right, codes, code + "1");
}

// Compress the Huffman Tree into a Huffman Code
string HuffmanTree::compress(const std::string inputStr) {
    // create a map with frequencies of the characters
    map<char, int> freqMap;
    for (char c: inputStr) {
        if (freqMap.find(c) == freqMap.end()) {
            freqMap[c] = 1;
        } else {
            freqMap[c] += 1;
        }
    }
    
    // Creating the Priority Queue
    HeapQueue<HuffmanNode *, HuffmanNode::Compare> HQ;
    for (map<char, int>::iterator it = freqMap.begin(); it != freqMap.end(); ++it) {
        HuffmanNode* node = new HuffmanNode(it->first, it->second);
        HQ.insert(node);
    }

    // Creating the Huffman Tree
    while (HQ.size() > 1) {
        HuffmanNode* n1 = HQ.min();
        HQ.removeMin();
        HuffmanNode* n2 = HQ.min();
        HQ.removeMin();
        int freq = n1->getFrequency() + n2->getFrequency();
        HuffmanNode* parent = new HuffmanNode('\0', freq, nullptr, n1, n2);
        n1->parent = parent;
        n2->parent = parent;
        HQ.insert(parent);
    }

    // Root node
    root = HQ.min();

    // Traverse the tree and assign 0 and 1 codes
    map<char, string> codes;
    string code = "";

    for (map<char, int>::iterator it = freqMap.begin(); it != freqMap.end(); ++it) {
        preorderTraverse(root, codes, code);
    }

    for (char c: inputStr) {
        huffmanCode += codes[c];
    }

    return huffmanCode;
}

// Recursively Traverse the tree in post order and serialize it
void HuffmanTree::postorderTraverse(const HuffmanNode* node, string& outStr) const {
    if (node == nullptr) {
        return;
    }

    postorderTraverse(node->left, outStr);
    postorderTraverse(node->right, outStr);

    if (node->isLeaf()) {
        outStr += "L";
        outStr += node->getCharacter();
    }

    if (node->isBranch()) {
        outStr += "B";
    }
}

// Generate a serialized strigng from the HuffmanTree
string HuffmanTree::serializeTree() const {
    if (root == nullptr) {
        return "";
    }

    string out;
    postorderTraverse(root, out);

    return out;
}

// Decompress the tree back to the original string
string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    string output = "";
    stack<HuffmanNode*> treeStack;
   
    // Reconstruct the tree from serializedTree string
    for(auto character : serializedTree) {
        if (character == 'L') {
            continue;
        } else if ((character != 'L') && (character != 'B')) {
            HuffmanNode* huffNode = new HuffmanNode(character, 0);
            treeStack.push(huffNode);        
        } else if (character == 'B') {
            HuffmanNode* right = treeStack.top();
            treeStack.pop();
            HuffmanNode* left = treeStack.top();
            treeStack.pop();
            HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
            treeStack.push(branch);
            right->parent = branch;
            left->parent = branch;
        } 
    }

    // Add the rest of the stack to the tree
    HuffmanNode* root = treeStack.top();
    treeStack.pop();

    // Decompress the original string from the code using the built huffman tree
    HuffmanNode* curr = root;
    for (auto character : inputCode) {
        if (character == '0')
            curr = curr->left;
        else 
            curr = curr->right;

        //once hit the leaf, this is the full character, add the char to output, start over from the root.
        if (curr->isLeaf()) {
            output += curr->getCharacter();
            curr = root;
        }
    }   
    return output;
}