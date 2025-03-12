#pragma once
#include <string>
using namespace std;

class Message {
public:
    string sender;
    string recipient;
    string content;

    Message(const string& sender, const string& content, const string& recipient = "")
        : sender(sender), content(content), recipient(recipient) {}
};