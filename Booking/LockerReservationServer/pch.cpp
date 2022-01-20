// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32")

#include <WinSock2.h>
// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.
