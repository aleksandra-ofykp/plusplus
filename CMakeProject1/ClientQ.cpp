//#include "stdio.h"
//#include "pch.h"
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma warning(disable: 4996) 
SOCKET Connection;

void ClientH() { //Функция для принятия отправленного сервером сообщения.
	char m[256]; //Хранение переданной строки.
	while (true) {
		recv(Connection, m, sizeof(m), NULL); // Принятие сообщения.
		std::cout << m << std::endl; //Вывод на экран.
	}
}

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData; //Структура.
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
	//Адрес сокета.
	SOCKADDR_IN addr; //Структура.
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111); //Порт для идентификации.
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Сокет для соединения с сервером.
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { //Проверка соединения клиента с сервером.
		std::cout << "Error\n";
		return 1;
	}
	std::cout << "Connected\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientH, NULL, NULL, NULL); //(Многопоточное программирование). 
			//Одновременно в функции main принимаются новые соединения, в процедуре ClientH ожидаются и отправляются сообщения клиенту.

	char m[256]; //Переменная для хранения сообщения.
	while (true) {
		std::cin.getline(m, sizeof(m)); //Запись сообщения.
		send(Connection, m, sizeof(m), NULL); //Отправка сообщения.
		Sleep(10);
	}

	system("pause");
	return 0;
}