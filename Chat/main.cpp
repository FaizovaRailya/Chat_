#include <iostream>
#include <Windows.h>
#include "Chat.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		Chat chat;
		chat.Menu();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
