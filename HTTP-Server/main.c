#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */

#ifndef UNICODE
#define UNICODE
#endif /* UNICODE */

#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include "Win32_stdint.h"

#pragma comment(lib, "Ws2_32.lib")

#define Atoi(val, buf)                                     \
	do {                                               \
		int v = (val);                             \
		int isNeg = 0;                             \
		char tmp[12];                              \
		int i = 0, j;                              \
		if (v == 0) {                              \
			(buf)[0] = '0';                    \
			(buf)[1] = '\0';                   \
			break;                             \
		}					   \
		if (v < 0) {                               \
			isNeg = 1;                         \
			v = -v;                            \
		}                                          \
		while (v != 0) {                           \
			tmp[i++] = (v % 10) + '0';         \
			v /= 10;                           \
		}                                          \
		if (isNeg) {                               \
			tmp[i++] = '-';                    \
		}                                          \
		for (j = 0; j < i; ++j) {                  \
			(buf)[j] = tmp[i - j - 1];         \
		}                                          \
		(buf)[j] = '\0';                           \
	} while(0)


static void handleiResult(HANDLE handle, const char *const sValue, int iResult, char *sResult);
static void printErrorMessage(const char *message, DWORD errorCode);

int main(void) {
	WSADATA wsaData;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int8 iResult;
	char *sResult = "";

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		handleiResult(handle, "WSAStartup failed: ", iResult, sResult);
		return 1;
	}

#define DEFAULT_PORT "27015"

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		handleiResult(handle, "getaddrinfo failed: ", iResult, sResult);
	}

	SOCKET ListenSocket = INVALID_SOCKET;
	
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printErrorMessage("Error at socket():", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printErrorMessage("bind failed with error:", WSAGetLastError);
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

#ifdef _DEBUG
	WriteConsoleA(handle, "[DEBUG] BUILD\n", (DWORD)lstrlenA("[DEBUG] BUILD\n"), NULL, NULL);
#endif

	return 0;
}

static void handleiResult(HANDLE handle, const char *const sValue, int iResult, char *sResult) {
	Atoi(iResult, sResult);
	WriteConsoleA(handle, sValue, (DWORD)lstrlenA(sValue), NULL, NULL);
	WriteConsoleA(handle, sResult, (DWORD)lstrlenA(sResult), NULL, NULL);
	WriteConsoleA(handle, "\n", (DWORD)lstrlenA("\n"), NULL, NULL);
}

static void printErrorMessage(const char *message, DWORD errorCode) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle != INVALID_HANDLE_VALUE) {
		char buffer[256];
		DWORD bytesWritten;
		int len = wsprintfA(buffer, "%s %lu\n", message, errorCode);
		WriteConsoleA(handle, buffer, len, &bytesWritten, NULL);
	}
}

static int memcmp_nocrt(const void *ptr1, const void *ptr2, SIZE_T num) {
	const unsigned char *p1 = (const unsigned char *)ptr1;
	const unsigned char *p2 = (const unsigned char *)ptr2;

	for (SIZE_T i = 0; i < num; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] - p2[i];
		}
	}
	return 0;
}

static void programStart(void) {
	int ExitCode = main();
	ExitProcess(ExitCode);
}