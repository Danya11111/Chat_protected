#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // ������ ���������� �� �������� ����
    bool isEndOfWord; // ����, �����������, �������� �� ���� ������ �����

    // �����������
    TrieNode() {
        isEndOfWord = false; // ���������� ���� �� �������� ������ �����
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr; // ������������� ���������� �� nullptr
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode(); // ������� ����� �������� ����
    }

    // ���������� ��� ������������ ������
    ~Trie() {
        deleteTrie(root); // ����������� ������, ���������� ��� �����
    }

    // ����������� ����� ��� ������������ ������
    void deleteTrie(TrieNode* node) {
        if (node) {
            for (int i = 0; i < 26; i++) {
                deleteTrie(node->children[i]); // ���������� ����������� �������� ����
            }
            delete node; // ����������� ������� ����
        }
    }

    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    void searchSuggestions(TrieNode* node, const std::string& prefix, std::vector<std::string>& suggestions) {
        if (node == nullptr) {
            return; // ���� ���� ����� nullptr, ������ �������
        }

        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        for (const auto& pair : node->children) {
            searchSuggestions(pair.second, prefix + pair.first, suggestions);
        }
    }


    vector<std::string> autocomplete(const std::string& prefix) {
        TrieNode* node = root;
        std::vector<std::string> suggestions;

        // ����� ����, ��������������� ��������
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return suggestions; // ���� ������� �� ������, ���������� ������ ������
            }
            node = node->children[ch];
        }

        // ���������, ��� ���� �� ����� nullptr ����� ������� searchSuggestions
        if (node != nullptr) {
            searchSuggestions(node, prefix, suggestions);
        }

        return suggestions;
    }
};
