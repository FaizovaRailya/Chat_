#pragma once
#include "User.h"
#include "Message.h"
#include <vector>
#include <exception>
#include <memory>

class Chat {
	std::vector<User> UserSpisok;				 //список зарегистрированных пользователей
	std::vector<Message> messageList;			 //создаем вектор, который хранит сообщения в чате
	std::shared_ptr<User> currentUser = nullptr; //указатель указывает на текущего пользователя

public:
	Chat() = default;
	~Chat() = default;

	//int userLogin = 0;									// для индекса текущего логина
	std::shared_ptr<User>getCurrentUser() const;
	std::shared_ptr<User>getUserByName(const std::string& name) const;
	std::shared_ptr<User>getUserByLogin(const std::string& login) const;

	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);

	void Menu();
	void SignIn();														  //вход по логину и паролю
	void ShowMessage() const;											  //вход по логину и паролю
	bool FindName(const std::string& name);							      //проверка имени
	bool FindLogin(const std::string& login);							  //проверка логина
	void NewUser();														  //создание нового пользователя
	bool UserSearch(const std::string& login, const std::string& password);//поиск пользователя по логину и паролю
	void PrintNamesUsers();												  //получение списка зарегестрированных пользователей
	int FindUserinUserSpisok(const std::string& name);					  //проверка корректно ли введено имя
	void setPrivateShowChat() const;									  //чтение личных сообщений
	void setAllShowChat() const;										  //чтение общих сообщений
	void setAddMessage();												  //добавление сообщения в массив
	void currrenNull();
};

class LoginExp : public std::exception {			//исключение если введен логин "all"
public:
	const char* what() const noexcept override {
		return "ERROR: Логин занят!\n\n";
	}
};

class NameExp : public std::exception {			//исключение если введено имя "all"
public:
	const char* what()const noexcept override {
		return "ERROR: Имя пользователя занято!\n\n";
	}
};
