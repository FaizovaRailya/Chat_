#include "Message.h"
#include <string>

Message::Message(const std::string& fromMessage, const std::string& toMessage, const std::string& text) :
    fromMessage_(fromMessage), toMessage_(toMessage), text_(text) {}

const std::string& Message::getFromMessage() const { return fromMessage_; }
const std::string& Message::getToMessage() const { return toMessage_; }
const std::string& Message::getText() const { return text_; }

std::fstream& operator >>(std::fstream& is, Message& msg)
{
    ////////////////////std::string timestamp_string;
    getline(is, msg.fromMessage_, ' ');
    getline(is, msg.toMessage_, ' ');
    //////////////////// getline(is, timestamp_string, ' ');
    getline(is, msg.text_);
    /*std::chrono::system_clock::time_point timestamp(std::chrono::seconds(std::stoll(timestamp_string)));
    _msg._timestamp = std::chrono::system_clock::to_time_t(timestamp);*/
    return is;
}

std::ostream& operator <<(std::ostream& os, const Message& msg) {
    os << msg.getFromMessage();
    os << ' ';
    os << msg.getToMessage();
    os << ' ';
    os << msg.getText();
    return os;
}