#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // Массив указателей на дочерние узлы
    bool isEndOfWord; // Флаг, указывающий, является ли узел концом слова

    // Конструктор
    TrieNode() {
        isEndOfWord = false; // Изначально узел не является концом слова
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr; // Инициализация указателей на nullptr
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode(); // Создаем новый корневой узел
    }

    // Деструктор для освобождения памяти
    ~Trie() {
        deleteTrie(root); // Освобождаем память, выделенную для узлов
    }

    // Рекурсивный метод для освобождения памяти
    void deleteTrie(TrieNode* node) {
        if (node) {
            for (int i = 0; i < 26; i++) {
                deleteTrie(node->children[i]); // Рекурсивно освобождаем дочерние узлы
            }
            delete node; // Освобождаем текущий узел
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
            return; // Если узел равен nullptr, просто выходим
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

        // Найти узел, соответствующий префиксу
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return suggestions; // Если префикс не найден, возвращаем пустой список
            }
            node = node->children[ch];
        }

        // Проверяем, что узел не равен nullptr перед вызовом searchSuggestions
        if (node != nullptr) {
            searchSuggestions(node, prefix, suggestions);
        }

        return suggestions;
    }
};
