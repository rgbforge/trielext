#include "trie.hpp"
#include "lextsuggest.hpp"
#include "config.hpp"
#include <iostream>
#include <filesystem>

int main() {
    TrieNode* root = new TrieNode();
    std::string dataFile = std::string(DATA_DIR) + "/commonwords.txt";
    if (!loadWordWeights(root, dataFile)) {
        std::cerr << "Error loading words file" << std::endl;
        return 1;
    }
    processUserInput(root);
    return 0;
}
