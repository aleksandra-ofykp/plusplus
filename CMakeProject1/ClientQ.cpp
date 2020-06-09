//#include "stdio.h"
//#include "pch.h"
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma warning(disable: 4996) 
SOCKET Connection;

void ClientH() { //������� ��� �������� ������������� �������� ���������.
	char m[256]; //�������� ���������� ������.
	while (true) {
		recv(Connection, m, sizeof(m), NULL); // �������� ���������.
		std::cout << m << std::endl; //����� �� �����.
	}
}

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData; //���������.
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
	//����� ������.
	SOCKADDR_IN addr; //���������.
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111); //���� ��� �������������.
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL); //����� ��� ���������� � ��������.
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { //�������� ���������� ������� � ��������.
		std::cout << "Error\n";
		return 1;
	}
	std::cout << "Connected\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientH, NULL, NULL, NULL); //(������������� ����������������). 
			//������������ � ������� main ����������� ����� ����������, � ��������� ClientH ��������� � ������������ ��������� �������.

	char m[256]; //���������� ��� �������� ���������.
	while (true) {
		std::cin.getline(m, sizeof(m)); //������ ���������.
		send(Connection, m, sizeof(m), NULL); //�������� ���������.
		Sleep(10);
	}

	system("pause");
	return 0;
}