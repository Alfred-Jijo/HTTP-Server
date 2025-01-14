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

void putIResult(HANDLE handle, const char *const sValue, int iResult, char *sResult) {
	Atoi(iResult, sResult);
	WriteConsoleA(handle, sValue, (DWORD)lstrlenA(sValue), NULL, NULL);
	WriteConsoleA(handle, sResult, (DWORD)lstrlenA(sResult), NULL, NULL);
	WriteConsoleA(handle, "\n", (DWORD)lstrlenA("\n"), NULL, NULL);
}

int __cdecl main(void) {
	WSADATA wsaData;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int iResult;
	char *sResult = "";

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if ( iResult != 0 ) {
		putIResult(handle, "WSAStartup failed: ", iResult, sResult);
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
		putIResult(handle, "getaddrinfo failed: ", iResult, sResult);
	}

	return 0;
}