#ifndef DEFAULT_SOCKET_H_
#define DEFAULT_SOCKET_H_
#include "CommonSocket.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#pragma comment(lib, "Ws2_32.lib")
#else
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		#include <winsock2.h>
	#else
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
		#include <fcntl.h> 
		#include <errno.h> 

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
	#endif
#endif
NS_FR_BEGIN

class DefaultSocket:
	public CommonSocket
{
public:
	DefaultSocket();
	~DefaultSocket();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	static bool initWinSock2_0();
#endif
public:
	int peerSocket;
	bool connectSocket(const char* serverIP, int serverPort);
	void closeSocket();
	bool hasError();
	int sendData(const char* data, int len);
	int	readData(std::vector <char> &vectorBuffer,int len);
private:
	int hClientSocket ;
};
NS_FR_END
#endif // !1
