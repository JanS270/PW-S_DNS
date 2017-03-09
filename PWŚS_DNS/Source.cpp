#define _CRT_SECURE_NO_WARNINGS

#include <winsock.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>	// Potrzebna do u�ywania polskich znak�w 

#pragma comment (lib, "Ws2_32.lib")// Potrzebne do dzia�ania !!

int main() {
	setlocale(LC_ALL, "Polish");// umo�liwia u�ywania polskich znak�w
	WSADATA wsaData;
	char buffer[256];
	while (true) {
		printf("Podaj Adres domeny: ");
		scanf("%s", &buffer);

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Zawsze Jest !! Pod��czenie do sieci
			printf("%s", WSAGetLastError());
			_getch();
			return 1;
		}
		hostent *hent = gethostbyname(buffer);
		if (hent == NULL) {//  Brak adresu
			printf("%d", WSAGetLastError());// Zwraca kod b��du
			_getch();
			return 2;
		}

		printf("Lista adres�w.\n");
		int i = 0;
		while (hent->h_addr_list[i]) {
			if (hent->h_addrtype == AF_INET) {// Wypisz Adresy....?
				printf("%s\n", ::inet_ntoa(*((in_addr*)hent->h_addr_list[i++])));
			}
		}
		_getch();
		WSACleanup();// Zamyka po��czenia sieciowe. must have
	}
	return 0;
}