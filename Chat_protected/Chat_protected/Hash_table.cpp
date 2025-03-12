#include "Hash_table.h"
#include <iostream>
#include <string>
using namespace std;

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {

}

int HashTable::hfunc(string password) {
    int sum = 0;
    for (int i = 0; i < password.size(); i++) {
        sum += password[i];
    }
    const double A = 0.7;
    const int M = 10;
    return int(M * (A * sum - int(A * sum)));
}

void HashTable::resize() {

    Pair* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    array = new Pair[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        Pair& old_pair = save[i];
        if (old_pair.status == enPairStatus::engaged) {
            add(old_pair.name, old_pair.login, old_pair.password);
        }
    }

    delete[] save;
}
void HashTable::add(string _name, string _login, int _password) {

    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::free || array[index].status == enPairStatus::deleted) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    if (i >= mem_size) {
        resize();
        add(_name, _login, _password);
    }
    else {
        array[index] = Pair(_name,_login, _password);
        count++;
    }
}

int HashTable::hash_func(string _login, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < _login.size(); i++) {
        sum += _login[i];
    }
    // метот квадратичного пробирования
    return (sum % mem_size + offset * offset) % mem_size;
}

void HashTable::del(string _login) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::engaged && array[index].login == _login) {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

int HashTable::find(string _login) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(_login, i);
        if (array[index].status == enPairStatus::engaged && array[index].login == _login) {
            return array[index].password;
        }
        else if (array[index].status == enPairStatus::free) {
            return -1;
        }
    }
    return -1;
}

