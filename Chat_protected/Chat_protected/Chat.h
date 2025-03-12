#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Message.h"
#include "TrieNode.h"
#include "Hash_table.h"
#include "Graph.h"
using namespace std;

class Chat {
private:
    HashTable users;
    vector<string> onlineUsers;
    vector<Message> publicMessages;
    map<string, vector<Message>> privateMessages;
public:
    unique_ptr<Graph> friends = make_unique<Graph>();
    unique_ptr<Trie> trie = make_unique<Trie>();

    bool registerUser(const string& login, const string& password, const string& name) {

        if (users.find(login) != -1) {
            cout << "Error: login is already taken." << endl;
            return false; // Логин уже занят
        }    
        int pass = users.hfunc(password);
        users.add(name, login, pass);
        string log = login;
        friends->vname.push_back(log);
        int value = friends->vname.size() - 1;
        friends->addVertex(value);
        cout << "User  " << name << " successfully registered!" << endl;
        return true;
    }

    bool loginUser(const string& login, const string& password) {
        if (users.find(login) == -1) {
            cout << "Error: incorrect login or password." << endl;
            return false; // User does not exist
        }

        // Retrieve the stored hash and compare it with the hash of the provided password
        int stored_hash = users.find(login);
        int provided_hash = users.hfunc(password);

        if (stored_hash != provided_hash) {
            cout << "Error: incorrect login or password." << endl;
            return false; // Incorrect password
        }

        onlineUsers.push_back(login); // Add user to online list
        cout << "User   " << login << " logged in." << endl;
        return true;
    }


    void logoutUser(const string& login) {
        onlineUsers.erase(remove(onlineUsers.begin(), onlineUsers.end(), login), onlineUsers.end());
        cout << "User  " << login << " logged out." << endl;
    }

    void sendMessage(const string& senderLogin, const string& message, const string& recipient = "") {

        if (!recipient.empty()) { // Личное сообщение
            if (users.find(recipient) == -1) {
                cout << "Error: user " << recipient << " not found." << endl;
                return;
            }
            privateMessages[senderLogin].emplace_back(senderLogin, message, recipient);
            privateMessages[recipient].emplace_back(senderLogin, message, recipient);
            cout << senderLogin << " (to " << recipient << "): " << message << endl;
        }

        else { // Сообщение всем
            publicMessages.emplace_back(senderLogin, message);
            cout << senderLogin << " (to everyone): " << message << endl;
        }
    }

    void listUsers(string login) const {
        friends->findMinDistancesFloyd(login);
    }

    void viewMessages(const string& login) const {
        cout << "Chat messages for " << login << ":" << endl;

        // Публичные сообщения
        for (const auto& msg : publicMessages) {
            cout << msg.sender << " (to everyone): " << msg.content << endl;
        }

        // Личные сообщения для данного пользователя
        if (privateMessages.count(login)) {
            for (const auto& msg : privateMessages.at(login)) {
                cout << msg.sender << " (to " << msg.recipient << "): " << msg.content << endl;
            }
        }
    }
    void addFriend(const string& user_name) {
        cout << endl << "Who do you want to add as a friend? If you want to cancel press - 0." << endl;
        listUsers(user_name);
        bool found = false;
        string friend_name;

        do {
            cout << "Enter the username of the user you want to add as a friend: ";
            cin >> friend_name;

            if (friend_name == "0") {
                break; // Пользователь отменил добавление
            }

            if (users.find(friend_name) == -1) {
                cout << "Error: user " << friend_name << " not found." << endl;
                continue; // Пользователь не найден
            }

            if (friend_name == user_name) {
                cout << "You cannot add yourself as a friend." << endl;
                continue; // Нельзя добавить самого себя
            }
            int index_st;
            int index_user;
            for (int i = 0; i < friends->vname.size(); i++) {
                if (friends->vname[i] == friend_name)
                    index_st = i;
                if (friends->vname[i] == user_name)
                    index_user = i;
            }
            if (friends->edgeExists(index_user, index_st)) {
                cout << "You're already friends!" << endl;
                break;
            }

            friends->addEdge(user_name, friend_name);
            cout << "You have successfully added a friend: " << friend_name << endl;
            found = true;

        } while (!found);
    }

    string T9() {
        string input;
        cout << "Enter a prefix to autocomplete: " << endl;
        string itog;
        while (true) {
            cout << "> ";
            input = "";
            cin.ignore();
            getline(cin, input);
            vector<string> suggestions = trie->autocomplete(input);
            if (suggestions.empty()) {
                cout << "No suggestions found." << endl;
                cout << "Write your own message to send: ";
                input = "";
                getline(cin, input);
                itog = input;
                trie->insert(input);
                break;
            }
            else {
                cout << "Suggestions: ";
                int i = 1;
                for (const string& suggestion : suggestions) {
                    cout << i << " - " << suggestion << " ";
                }
                cout << endl;
                cout << "Enter the supplement that suits you, write its number or write 0 and write your own message: ";
                int choice;
                cin >> choice;
                if (choice == 0) {
                    cout << "Enter the message you wanted to enter : ";
                    string str;
                    cin.ignore();
                    getline(cin, str);
                    trie->insert(str);
                    itog = str;
                    break;
                }
                else {
                    itog = suggestions[choice - 1];
                    break;
                }
            }
        }
        return itog;
    }

    void insert_lib() {
        trie->insert("Hello");
        trie->insert("How");
        trie->insert("are");
        trie->insert("you");
        trie->insert("Hi");
    }
};