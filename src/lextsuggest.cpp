#include "lextsuggest.hpp"
#include <iostream>

void print(std::vector<std::string> const &a) {
    std::cout << "word so far: " ;
    for(int kk=0; kk<a.size(); kk++)
        std::cout << a.at(kk) << " ";
}

void checkWord(TrieNode* root) {
    std::string word;
    std::cout << "Enter a word to search: ";
    std::cin >> word;
    if (search_weight_accident(root, word)) {
        std::cout << "Found " << word << ", weight: " << search_weight(root, word) << std::endl;
    }
    else {
        std::cout << word << " not found." << std::endl;
    }
}

void processUserInput(TrieNode* root) {
    char letter;
    std::string curr_word;
    std::vector<std::string> word_history{""};
    std::vector<std::string> alphabet{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };

    std::cout << "Enter a letter (# is backspace): ";
    while (std::cin >> letter) {
        if (letter == '#' && !curr_word.empty()) {
            curr_word.pop_back();
            word_history[0].pop_back();
        }
        else {
            curr_word += letter;
            word_history[0] += letter;
        }
        std::cout << "======================"<<std::endl;

        // top suggestions
        std::vector<std::string> suggestions = trieValid(root, 5, curr_word);
        std::cout << std::endl<<"Top suggestions:"<<std::endl;
        for (const auto& sugg : suggestions) {
            std::cout << sugg << std::endl;
        }
        std::cout << "\n...valid terminating children...\n";
        search_word_children(root, curr_word);
        std::cout << "\n...valid terminating current...\n";
        if (search_weight_accident(root, curr_word)) {
            std::cout << curr_word << ", ";
        }

        std::cout << "\n...valid first swaps...\n";
        for (const auto& alpha : alphabet) {
            std::string swapped = curr_word;
            swapped.replace(0, 1, alpha);
            if (search_weight_accident(root, swapped)) {
                std::cout << swapped << ", ";
            }
        }
        std::cout << std::endl<< "======================"<<std::endl;
        std::cout<<std::endl;
        print(word_history);
        std::cout<<std::endl<<"Enter a letter (# is backspace): ";
    }
}
