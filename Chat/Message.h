#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Message {
	std::string fromMessage_;
	std::string toMessage_;
	std::string text_;
public:
	Message() = default;
	Message(const std::string& fromMessage, const std::string& toMessage, const std::string& text);
	~Message() = default;

	const std::string& getFromMessage() const;
	const std::string& getToMessage() const;
	const std::string& getText() const;

	friend std::fstream& operator >>(std::fstream& is, Message& msg);
	friend std::ostream& operator <<(std::ostream& os, const Message& msg);
};