#include <iostream>
#include<string>
#include "Chat.h"
#include "Sha1.h"

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const {			// ��������� �� ����� ������������
	for (auto& user : UserSpisok) {
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const {		// ��������� �� ��� ������������
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
		std::cout << "���������� �������������: " << UserSpisok.size() << std::endl;
		std::cout << "------������� ��������:------\n1 - ����\n2 - �����������\n0 - �����\n";
		std::cin >> a;
		std::cin.ignore(100, '\n');

		switch (a) {
		case '1':
			SignIn();								//���� �� ������ � ������
			break;
		case '2':									// ����������� ������ ������������
			try {
				NewUser();					//�������� ����� ���������� ������ ������������			
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
			std::cout << "�������� ����!\n" << std::endl;
			break;
		}
	}
}

void Chat::SignIn() {								//���� �� ������ � ������
	std::string log, pas;
	std::cout << "----�������----\n�����: ";
	std::cin >> log;
	std::cout << "������: ";
	std::cin >> pas;
	if (UserSearch(log, pas)) {
		bool f1 = true;
		while (f1) {
			std::cout << "\n------������� �������e:------\n1 - ��������� ��������e\n2 - �������� ���������\n0 - �����\n";
			char b;
			std::cin >> b;
			std::cin.ignore(100, '\n');
			switch (b) {
			case '1':
				if (messageList.empty())
					std::cout << "� ��� ��� ��� �������� ���������!\n" << std::endl;
				else
					ShowMessage();							//��������� ���������	
				break;
			case '2':										//�������� ���������
				setAddMessage();
				break;
			case '0':										//�����
				currrenNull();
				f1 = false;
				break;
			default:
				std::cout << "�������� ����!\n" << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "\n�������� ����� ��� ������!!!\n";
}

void Chat::ShowMessage() const {									//��������� ���������
	std::cout << "\n------������� �������e:------\n1 - ������\n2 - �����\n0 - �����\n";
	char d;
	std::cin >> d;
	std::cin.ignore(100, '\n');
	switch (d) {
	case '1':
		setPrivateShowChat();   //�������� ����� ������ ������ ���������  
		break;
	case '2':
		setAllShowChat();		 //�������� ����� ������ ����� ���������
	case '0':
		break;
	default:
		std::cout << "�������� ����!\n" << std::endl;
		break;
	}
}


bool Chat::FindName(const std::string& name) {								 //����� �������� �����
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getName() == name)
			return true;
	}
	return false;
}

bool Chat::FindLogin(const std::string& login) {								//����� �������� ������
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getLogin() == login)
			return true;
	}
	return false;
}

void Chat::NewUser() {					//����� �������� ������ ������������
	std::string name, login, password;
	std::cout << "---- ������� ������ ��� ����������� ----\n";
	std::cout << "���: ";
	bool n = true;
	while (n) {
		std::cin >> name;
		if (name == "all") {			// ����������
			throw NameExp();
		}
		if (FindName(name)) {
			std::cout << "������ ��� ��� ������ �������� ������!\n\n";
			std::cout << "------- ������� -------\n���: ";
		}
		else {
			n = false;
		}
	}

	std::cout << "�����: ";
	bool l = true;
	while (l) {
		std::cin >> login;
		if (login == "all") {       // ����������
			throw LoginExp();
		}

		if (FindLogin(login)) {
			std::cout << "������ ����� ��� ����� �������� ������!\n\n";
			std::cout << "------- ������� -------\n�����: ";
		}
		else {
			l = false;
		}
	}
	std::cout << "������: ";
	std::cin >> password;

	User user(name, login, sha1((char*)password.data(), password.length()));				//������� ������ ����� User

	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::app);
	user_file << user << endl;

	UserSpisok.push_back(user);						// ��������� ������������ � ������
	currentUser = std::make_shared<User>(user);		//������� ��������� �� �������� ������������
	std::cout << "������������ ���������������!\n\n";

}


bool Chat::UserSearch(const std::string& login, const std::string& password) {	//����� ������ ������������ �� ������ � ������	
	//int i = 0;
	//while (i < UserSpisok.size()) {
		/*std::string l = ;
		unsigned int* p = ;*/

	for (const auto& user : UserSpisok) {

		if (login == user.getLogin() && memcmp(user.getPassword(), sha1((char*)password.data(), password.length()), SHA1HASHLENGTHBYTES) == 0) {
			currentUser = getUserByLogin(login);   //��������� �� �������� ������������
			//userLogin = i;
			std::cout << std::endl << "--------------------------������������: " << currentUser->getName() << " ----------------------\n";
			return true;
		}
		/*else { ++i; }*/
	}
	return false;
}

void Chat::PrintNamesUsers() {				    //����� ��������� ������ ������������������ �������������
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		std::cout << it->getName() << std::endl;
	}
}

int Chat::FindUserinUserSpisok(const std::string& name) {	//����� ��������� ��������� �� ������� ���
	for (std::vector<User>::iterator it = UserSpisok.begin(); it != UserSpisok.end(); ++it) {
		if (it->getName() == name)
			return 0;
	}
	return -1;
}

void Chat::setPrivateShowChat() const {				//����� ������ ������ ���������
	std::string from;
	std::string to;
	std::cout << currentUser->getName() << std::endl;
	std::cout << "--------------���--------------\n";
	for (auto& message : messageList) {
		if (currentUser->getName() == message.getFromMessage() || currentUser->getName() == message.getToMessage()) {//���� ������� ������������
			from = (currentUser->getName() == message.getFromMessage()) ? "����" : message.getFromMessage();

			to = (currentUser->getName() == message.getToMessage()) ? "���" : message.getToMessage();
			//���� ������� ��� ����� to, �� ���������� ��������� ������ ����, ���� ���, �� �������� ��� ������������ � ����������� ��� �������� ���� to

			if (message.getToMessage() != "all")
				std::cout << "�� " << from << " ���� " << to << ": " << message.getText() << std::endl;
		}
	}
	std::cout << "-------------------------------" << std::endl;
}

void Chat::setAllShowChat() const {							// ����� ������ ����� ���������
	std::string from;
	std::string to;
	std::cout << "-----------����� ���-----------\n";
	for (auto& message : messageList) {
		if (currentUser->getName() == message.getFromMessage() || currentUser->getName() == message.getToMessage() || message.getToMessage() == "all") {//���� ������� ������������
			from = (currentUser->getName() == message.getFromMessage()) ? "����" : message.getFromMessage();
			if (message.getToMessage() == "all") 						//��������� ���� �������������
				std::cout << "�� " << from << ": " << message.getText() << std::endl;
		}
	}
	std::cout << "-------------------------------" << std::endl;
}

void Chat::setAddMessage() {						    	//����� ���������� ��������� � ������
	std::string inputName;
	std::string message;
	std::cout << "\n������� ��� ���� ��������� ���������:\n";
	PrintNamesUsers();									  //������� ������ �������������
	std::cout << "all - ��������� ����\n";

	std::cin >> inputName;
	if (inputName == "all") {							  //�������� ���� �������������
		std::cout << "\n������� ����� ���������: \n";

		getline(std::cin, message, '\n');
		getline(std::cin, message, '\n');
		messageList.push_back(Message(currentUser->getName(), "all", message));
		std::cout << "��������� ��������� ���� �������������!\n";
	}
	else {													//�������� ������ ���������
		int t = -1;
		t = FindUserinUserSpisok(inputName);
		if (t == -1) {
			std::cout << "������������ � ������ ������ �� ������\n";
		}
		else {
			std::cout << "������� ����� ���������: \n";
			getline(std::cin, message, '\n');
			getline(std::cin, message, '\n');
			messageList.push_back(Message(currentUser->getName(), inputName, message));
		}
	}
}

void Chat::currrenNull() {
	currentUser = nullptr;
}

