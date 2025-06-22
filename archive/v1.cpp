#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

struct TrieNode {
    unordered_map < char, TrieNode* > children;
    bool is_end;
    long long w1;
    long long w2;
    TrieNode() {
        is_end = false;
        w1 = 0;
        w2 = 0; 
    }
};

void insert_word(TrieNode* root, const string& word, long long num) {
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

long long search_weight(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return -1;  
        }
        curr = curr->children[c];
    }
    return curr->w1;
}

long long search_priority(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return -1;  
        }
        curr = curr->children[c];
    }
    return curr->w2;
}

unordered_map<char, TrieNode*> search_word_children(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) return {};
        curr = curr->children[c];
    }

    for (const auto& d : curr->children) {
        if (d.second->is_end) {
            cout << word << d.first;
        }
	cout<< ", ";
    }
    return curr->children;
}

//returns iterator listing of keys(characters) for the root TrieNode
bool search_root(TrieNode* root2) {
    for (const auto& pair : root2->children) {
        cout << pair.first << " ";
    }
    return root2->is_end;
}

void sum_weights(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->is_end = true;
    //curr->w1 = num;
}
bool search_weight_accident(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.count(c)) {
            return false;
        }
        curr = curr->children[c];
    }
    return curr->is_end;
}

void print(std::vector <string> const &a){
  std::cout << "word so far: " ;
  for(int kk=0; kk<a.size();kk++)
    std::cout << a.at(kk) << " ";
}

bool loadWordWeights(TrieNode* root, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string word, alpha, digits;
    while (getline(file, word)) {
        alpha.clear(); digits.clear();
        for (char c : word) {
            if (isalpha(c)) alpha += tolower(c);
            if (isdigit(c)) digits += c;
        }
        try {
            insert_word(root, alpha, stoll(digits));
        }
        catch (...) {
            return false;
        }
    }
    return true;
}


void checkWord(TrieNode* root) {
    string word;
    cout << "Enter a word to search: ";
    cin >> word;
    if (search_weight_accident(root, word)) {
        cout << "Found " << word << ", weight: " << search_weight(root, word) << endl;
    }
    else {
        cout << word << " not found." << endl;
    }
}


vector<string> trieValid(TrieNode* root, int numValidReturns, string curr_word) {
    vector<pair<string, long long>> validWords;
    if (curr_word.back() == '#' && curr_word.length() > 1) {
        curr_word.pop_back();
        curr_word.pop_back();
    }
    TrieNode* curr = root;
    for (char c : curr_word) {
        if (!curr->children.count(c)) return {};
        curr = curr->children[c];
    }
    stack<pair<TrieNode*, string>> s;
    s.push({ curr, curr_word });
    while (!s.empty()) {
        pair<TrieNode*, string> current = s.top();
        s.pop();
        if (current.first->is_end) validWords.push_back({ current.second, current.first->w1 });
        for (const auto& child : current.first->children)
            s.push({ child.second, current.second + child.first });
    }
    sort(validWords.begin(), validWords.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    vector<string> result;
    for (int i = 0; i < min(numValidReturns, (int)validWords.size()); i++)
        result.push_back(validWords[i].first);
    return result;
}
void processUserInput(TrieNode* root) {
    char letter;
    string curr_word;
    vector<string> word_history{ "" };
    vector<string> alphabet{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };

    while (cin >> letter) {
        if (letter == '#' && !curr_word.empty()) {
            curr_word.pop_back();
            word_history[0].pop_back();
        }
        else {
            curr_word += letter;
            word_history[0] += letter;
        }
        cout << "======================"<<endl;

        // top suggestions
        vector<string> suggestions = trieValid(root, 5, curr_word);
        cout << endl<<"Top suggestions:"<<endl;
        for (const auto& sugg : suggestions) {
            cout << sugg << endl;
        }
        cout << "\n...valid terminating children...\n";
        search_word_children(root, curr_word);
        cout << "\n...valid terminating current...\n";
        if (search_weight_accident(root, curr_word)) {
	  cout << curr_word << ", ";
        }

        cout << "\n...valid first swaps...\n";
        for (const auto& alpha : alphabet) {
            string swapped = curr_word;
            swapped.replace(0, 1, alpha);
            if (search_weight_accident(root, swapped)) {
	      cout << swapped << ", ";
            }
        }
	cout << endl<< "======================"<<endl;
	cout<<endl;
	print(word_history);
	cout<<endl<<"Enter a letter (# is backspace): ";
    }
}

int main() {
    //creates a TRIE from text file with weights
    TrieNode* root = new TrieNode();
    if (!loadWordWeights(root, "commonwords.txt")) {
        cerr << "Error loading words file" << endl;
        return 1;
    }
    cout<< "Enter a letter (# is backspace): ";
    processUserInput(root);

}
   
