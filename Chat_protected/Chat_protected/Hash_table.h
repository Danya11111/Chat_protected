#pragma once

#include <string>

using namespace std;

class HashTable { // хэш таблица
public:

    HashTable();
    ~HashTable();
    void add(string name, string login, int password);
    
    int hfunc(string password);
    void del(string login);
    int find(string login);
private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // пара ключ-значение

        Pair() :
            login(""),
            password(-1),
            status(enPairStatus::free)
        {}
        ~Pair() {}
        Pair(string _name, string _login, int _password):name(_name),login(_login) {
            password = _password;
            status = engaged;
        }
        Pair& operator = (const Pair& other) {
            name = other.name;
            login = other.login;
            password = other.password;
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || ((password == other.password) && (login == other.login) && (name == other.name)));
        }
        string name;
        string login;
        int password;

        enPairStatus status;
    };

    void resize();
    int hash_func(string login, int offset);

    Pair* array;
    int mem_size;
    int count;
};