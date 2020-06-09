//#include "stdio.h"
//#include "pch.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>
#pragma warning(disable: 4996) 
#include <cstring>

SOCKET Connection;

std::string n;
void ClientH() { //Функция для принятия сообщение клиентом с сервера.
	char m[256]; //Переданное сообщение.
	while (true) {
		recv(Connection, m, sizeof(m), NULL);
		std::cout << m << std::endl; //Выводит сообщение.
	}
}

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData; //структура.
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) { // 1-ый параметр: версия библиотеки, 2-ой - ссылка на структуру. Проверка загрузки библиотеки.
		std::cout << "Error" << std::endl;
		exit(1);
	}
	//Информация об адресе сокета.
	SOCKADDR_IN addr; //Структура.
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111); //Порт для идентификации.
	addr.sin_family = AF_INET;

	
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { 
		std::cout << "Error\n";
		return 1;
	}
	else {
		std::cout << "Connected\n";
		std::cin >> n; 
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientH, NULL, NULL, NULL); //(Многопоточное программирование)
	//Одновременно в функции main принимаются новые соединения, в процедуре ClientH ожидаются и отправляются сообщения клиентам.

	char m[256];
	while (true) {
		std::cin.getline(m, sizeof(m)); 
		std::string text = n + m;
		send(Connection, text.c_str() , text.size() , NULL);
	}

	system("pause");
	return 0;
}