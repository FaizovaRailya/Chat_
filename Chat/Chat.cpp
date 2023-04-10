#include <iostream>
#include<string>
#include "Chat.h"
#include "Sha1.h"

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const {			// указатель на логин пользователя
	for (auto& user : UserSpisok) {
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const {		// указатель на имя пользователя
	for (auto& user : UserSpisok) {
		if (name == user.getName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}


std::shared_ptr<User> Chat::getCurrentUser() const {
	return currentUser;
}

void Chat::Menu() {
	bool f = true;
	while (f) {
		char a;
		std::cout << "Количество пользователей: " << UserSpisok.size() << std::endl;
		std::cout << "------Введите действие:------\n1 - вход\n2 - регистрация\n0 - выход\n";
		std::cin >> a;
		std::cin.ignore(100, '\n');

		switch (a) {
		case '1':
			SignIn();								//вход по логину и паролю
			break;
		case '2':									// регистрация нового пользователя
			try {
				NewUser();					//вызываем метод добавления нового пользователя			
				currrenNull();
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			f = false;
			break;
		default:
			std::cout << "Неверный ВВОД!\n" << std::endl;
			break;
		}
	}
}

void Chat::SignIn() {								//вход по логину и паролю
	std::string log, pas;
	std::cout << "----Введите----\nЛогин: ";
	std::cin >> log;
	std::cout << "Пароль: ";
	std::cin >> pas;
	if (UserSearch(log, pas)) {
		bool f1 = true;
		while (f1) {
			std::cout << "\n------Введите действиe:------\n1 - Прочитать сообщениe\n2 - Написать сообщение\n0 - Назад\n";
			char b;
			std::cin >> b;
			std::cin.ignore(100, '\n');
			switch (b) {
			case '1':
				if (messageList.empty())
					std::cout << "У вас еще нет входящих сообщений!\n" << std::endl;
				else
					ShowMessage();							//прочитать сообщения	
				break;
			case '2':										//написать сообщение
				setAddMessage();
				break;
			case '0':										//назад
				currrenNull();
				f1 = false;
				break;
			default:
				std::cout << "Неверный ВВОД!\n" << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "\nНеверный логин или пароль!!!\n";
}

void Chat::ShowMessage() const {									//прочитать сообщения
	std::cout << "\n------Введите действиe:------\n1 - Личные\n2 - Общие\n0 - Назад\n";
	char d;
	std::cin >> d;
	std::cin.ignore(100, '\n');
	switch (d) {
	case '1':
		setPrivateShowChat();   //вызываем метод вывода личных сообщений  
		break;
	case '2':
		setAllShowChat();		 //вызываем метод вывода общих сообщений
	case '0':
		break;
	default:
		std::cout << "Неверный ВВОД!\n" << std::endl;
		break;
	}
}


bool Chat::FindName(const std::string& name) {								 //метод проверки имени
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getName() == name)
			return true;
	}
	return false;
}

bool Chat::FindLogin(const std::string& login) {								//метод проверки логина
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getLogin() == login)
			return true;
	}
	return false;
}

void Chat::NewUser() {					//метод создания нового пользователя
	std::string name, login, password;
	std::cout << "---- Введите данные для регистрации ----\n";
	std::cout << "Имя: ";
	bool n = true;
	while (n) {
		std::cin >> name;
		if (name == "all") {			// исключение
			throw NameExp();
		}
		if (FindName(name)) {
			std::cout << "Данное имя уже занято выберите другое!\n\n";
			std::cout << "------- Введите -------\nИмя: ";
		}
		else {
			n = false;
		}
	}

	std::cout << "Логин: ";
	bool l = true;
	while (l) {
		std::cin >> login;
		if (login == "all") {       // исключение
			throw LoginExp();
		}

		if (FindLogin(login)) {
			std::cout << "Данный логин уже занят выберите другой!\n\n";
			std::cout << "------- Введите -------\nЛогин: ";
		}
		else {
			l = false;
		}
	}
	std::cout << "Пароль: ";
	std::cin >> password;

	User user(name, login, sha1((char*)password.data(), password.length()));				//создаем объект класа User

	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::app);
	user_file << user << endl;

	UserSpisok.push_back(user);						// добавляем пользователя в массив
	currentUser = std::make_shared<User>(user);		//создаем указатель на текущего пользователя
	std::cout << "Пользователь зарегистрирован!\n\n";

}


bool Chat::UserSearch(const std::string& login, const std::string& password) {	//метод поиска пользователя по логину и паролю	
	//int i = 0;
	//while (i < UserSpisok.size()) {
		/*std::string l = ;
		unsigned int* p = ;*/

	for (const auto& user : UserSpisok) {

		if (login == user.getLogin() && memcmp(user.getPassword(), sha1((char*)password.data(), password.length()), SHA1HASHLENGTHBYTES) == 0) {
			currentUser = getUserByLogin(login);   //указатель на текущего пользователя
			//userLogin = i;
			std::cout << std::endl << "--------------------------Пользователь: " << currentUser->getName() << " ----------------------\n";
			return true;
		}
		/*else { ++i; }*/
	}
	return false;
}

void Chat::PrintNamesUsers() {				    //метод получения списка зарегестрированных пользователей
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		std::cout << it->getName() << std::endl;
	}
}

int Chat::FindUserinUserSpisok(const std::string& name) {	//метод проверяет корректно ли введено имя
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getName() == name)
			return 0;
	}
	return -1;
}

void Chat::setPrivateShowChat() const {				//метод чтения личных сообщений
	std::string from;
	std::string to;
	std::cout << currentUser->getName() << std::endl;
	std::cout << "--------------ЧАТ--------------\n";
	for (auto& message : messageList) {
		if (currentUser->getName() == message.getFromMessage() || currentUser->getName() == message.getToMessage()) {//если текущий пользователь
			from = (currentUser->getName() == message.getFromMessage()) ? "Меня" : message.getFromMessage();

			to = (currentUser->getName() == message.getToMessage()) ? "Мне" : message.getToMessage();
			//если текущее имя равно to, то отправляем сообщение самому себе, если нет, то получаем имя пользователя и присваиваем его значение полю to

			if (message.getToMessage() != "all")
				std::cout << "от " << from << " кому " << to << ": " << message.getText() << std::endl;
		}
	}
	std::cout << "-------------------------------" << std::endl;
}

void Chat::setAllShowChat() const {							// метод чтения общих сообщений
	std::string from;
	std::string to;
	std::cout << "-----------ОБЩИЙ ЧАТ-----------\n";
	for (auto& message : messageList) {
		if (currentUser->getName() == message.getFromMessage() || currentUser->getName() == message.getToMessage() || message.getToMessage() == "all") {//если текущий пользователь
			from = (currentUser->getName() == message.getFromMessage()) ? "Меня" : message.getFromMessage();
			if (message.getToMessage() == "all") 						//сообщение всем пользователям
				std::cout << "от " << from << ": " << message.getText() << std::endl;
		}
	}
	std::cout << "-------------------------------" << std::endl;
}

void Chat::setAddMessage() {						    	//метод добавления сообщения в массив
	std::string inputName;
	std::string message;
	std::cout << "\nВведите имя кому отправить сообщение:\n";
	PrintNamesUsers();									  //выводим список пользователей
	std::cout << "all - отправить всем\n";

	std::cin >> inputName;
	if (inputName == "all") {							  //отправка всем пользователям
		std::cout << "\nВведите текст сообщения: \n";

		getline(std::cin, message, '\n');
		getline(std::cin, message, '\n');
		messageList.push_back(Message(currentUser->getName(), "all", message));
		std::cout << "Сообщение разослано всем пользователям!\n";
	}
	else {													//отправка личных сообщений
		int t = -1;
		t = FindUserinUserSpisok(inputName);
		if (t == -1) {
			std::cout << "Пользователь с данным именем не найден\n";
		}
		else {
			std::cout << "Введите текст сообщения: \n";
			getline(std::cin, message, '\n');
			getline(std::cin, message, '\n');
			messageList.push_back(Message(currentUser->getName(), inputName, message));
		}
	}
}

void Chat::currrenNull() {
	currentUser = nullptr;
}

