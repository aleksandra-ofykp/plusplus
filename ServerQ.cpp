// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"


//#include "pch.h"
#include "stdio.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>

#pragma warning(disable: 4996)
SOCKET Connections[100]; //Массив сокетов. Для подключения нескольких клиентов.
int Count = 0; //Индекс соединения.


void ClientH(int index) {//Функция для отправки сообщения клиента другим клиентам.
	char m[256]; //Переданное клиентом сообщение.
	while (true) {
		recv(Connections[index], m, sizeof(m), 0); //Принимает сообщения клиента.
		for (int i = 0; i < Count; i++) {
			if (i == index) {//Для одноразового выведения сообщения клиента.
				continue;
			}

			send(Connections[i], m, sizeof(m), 0); //Отправка остальным клиентам.
		}
	}
}

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData; //структура
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) { // 1-ый параметр: версия библиотеки, 2-ой - ссылка на структуру. Проверка загрузки библиотеки.
		std::cout << "Error" << std::endl;
		exit(1);
	}
	// Информации об адресе сокета.
	SOCKADDR_IN addr; // Структура.
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес
	addr.sin_port = htons(1111); //Порт для идентификации программы поступающими данными
	addr.sin_family = AF_INET; // Семейство протоколов.

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0); //Сокет (Ипользуется семейство интернет-протоколов.)
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Привязка адреса сокету.
	listen(sListen, SOMAXCONN); //Прослушивание порта для ожидания клиента.

	SOCKET newConnection; //Сокет для удерживания соединения с клиентами.
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);//возвращает указатель на новый сокет

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected\n";

			Connections[i] = newConnection; //Запись нового соединения в массив.
			Count++;


			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientH, (LPVOID)(i), NULL, NULL);//(Многопоточное программирование). 
			//Одновременно в функции main принимаются новые соединения, в процедуре ClientH ожидаются и отправляются сообщения клиентам.
		}
	}
	
	

	system("pause");
	return 0;
}
