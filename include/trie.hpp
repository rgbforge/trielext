#pragma once

#include <unordered_map>
#include <string>
#include <vector>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end;
    long long w1;
    long long w2;
    TrieNode() {
        is_end = false;
        w1 = 0;
        w2 = 0; 
    }
};

void insert_word(TrieNode* root, const std::string& word, long long num);
void assign_priority(TrieNode* root);
long long search_weight(TrieNode* root, const std::string& word);
long long search_priority(TrieNode* root, const std::string& word);
std::unordered_map<char, TrieNode*> search_word_children(TrieNode* root, const std::string& word);
bool search_root(TrieNode* root2);
void sum_weights(TrieNode* root, const std::string& word);
bool search_weight_accident(TrieNode* root, const std::string& word);
std::vector<std::string> trieValid(TrieNode* root, int numValidReturns, std::string curr_word);
bool loadWordWeights(TrieNode* root, const std::string& filename);
