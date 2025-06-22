#include "trie.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>

void insert_word(TrieNode* root, const std::string& word, long long num) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->is_end = true;
    curr->w1 = (num >= 0) ? num : 0;  
}

void assign_priority(TrieNode* root) {
    if (!root) return;
    for (auto& pair : root->children) {
        pair.second->w2 = 2;
        assign_priority(pair.second);
    }
}

long long search_weight(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return -1;  
        }
        curr = curr->children[c];
    }
    return curr->w1;
}

long long search_priority(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return -1;  
        }
        curr = curr->children[c];
    }
    return curr->w2;
}

std::unordered_map<char, TrieNode*> search_word_children(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) return {};
        curr = curr->children[c];
    }

    for (const auto& d : curr->children) {
        if (d.second->is_end) {
            std::cout << word << d.first;
        }
        std::cout << ", ";
    }
    return curr->children;
}

bool search_root(TrieNode* root2) {
    for (const auto& pair : root2->children) {
        std::cout << pair.first << " ";
    }
    return root2->is_end;
}

void sum_weights(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->is_end = true;
}

bool search_weight_accident(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return false;
        }
        curr = curr->children[c];
    }
    return curr->is_end;
}

std::vector<std::string> trieValid(TrieNode* root, int numValidReturns, std::string curr_word) {
    std::vector<std::pair<std::string, long long>> validWords;
    if (curr_word.back() == '#' && curr_word.length() > 1) {
        curr_word.pop_back();
        curr_word.pop_back();
    }
    
    TrieNode* curr = root;
    for (char c : curr_word) {
        if (!curr->children.count(c)) return {};
        curr = curr->children[c];
    }
    
    std::stack<std::pair<TrieNode*, std::string>> s;
    s.push({curr, curr_word});
    
    while (!s.empty()) {
        std::pair<TrieNode*, std::string> current = s.top();
        s.pop();
        if (current.first->is_end) {
            validWords.push_back({current.second, current.first->w1});
        }
        for (const auto& child : current.first->children) {
            s.push({child.second, current.second + child.first});
        }
    }
    
    std::sort(validWords.begin(), validWords.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<std::string> result;
    for (int i = 0; i < std::min(numValidReturns, (int)validWords.size()); i++) {
        result.push_back(validWords[i].first);
    }
    return result;
}

bool loadWordWeights(TrieNode* root, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string word, alpha, digits;
    while (std::getline(file, word)) {
        alpha.clear(); digits.clear();
        for (char c : word) {
            if (std::isalpha(c)) alpha += std::tolower(c);
            if (std::isdigit(c)) digits += c;
        }
        try {
            insert_word(root, alpha, std::stoll(digits));
        }
        catch (...) {
            return false;
        }
    }
    return true;
}
