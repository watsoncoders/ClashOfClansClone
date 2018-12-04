#include "DefaultSocket.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
NS_FR_BEGIN
DefaultSocket::DefaultSocket()
{
}

DefaultSocket::~DefaultSocket()
{
}
//khoi tao cho win32
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
bool DefaultSocket::initWinSock2_0()
{
	WSADATA wsaData ;
	WORD wVersion = MAKEWORD( 2, 0 ) ;
	if ( ! WSAStartup( wVersion, &wsaData ) )
		return true ;
	return false ;
}
#endif
//Mo ket noi
bool DefaultSocket::connectSocket(const char* serverIP, int serverPort)
{
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32|| CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		if(!initWinSock2_0())
			return false;
	#endif	
		hClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hClientSocket == INVALID_SOCKET)
	{
		log("Unable to init socket");
		closeSocket();
		return false ;
	}
	//bKeepAlive
	if (true)
	{
		int		optval = 1;
		if (setsockopt(hClientSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)))
		{
			log("Unable to setsockopt");
			closeSocket();
			return false;
		}
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32|| CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	DWORD nMode = 1;
	int nRes = ioctlsocket(hClientSocket, FIONBIO, &nMode);
	if (nRes == SOCKET_ERROR) {

		log("Unable to ioctlsocket");

		closeSocket();
		return false;
}
#else
	fcntl(hClientSocket, F_SETFL, O_NONBLOCK);
#endif	

	unsigned long serveraddr = inet_addr(serverIP);
	if (serveraddr == INADDR_NONE)	// 检查IP地址格式错误
	{
		log("Unable to serveraddr: %d", serveraddr);
		closeSocket();
		return false;
	}
	// Create the structure describing various Server parameters
	struct sockaddr_in serverAddr ;

	serverAddr . sin_family = AF_INET ;     // The address family. MUST be AF_INET
	serverAddr . sin_addr . s_addr = inet_addr( serverIP ) ;
	serverAddr . sin_port = htons( serverPort ) ;

	// Connect to the server
	if ( connect( hClientSocket, ( struct sockaddr * ) &serverAddr, sizeof( serverAddr ) ) < 0 )
	{
		

		if (hasError()) {
			closeSocket();
			log("Unable to connect to server ");
			return false;
		}
		else	// WSAWOLDBLOCK
		{
			timeval timeout;
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;
			fd_set writeset, exceptset;
			FD_ZERO(&writeset);
			FD_ZERO(&exceptset);
			FD_SET(hClientSocket, &writeset);
			FD_SET(hClientSocket, &exceptset);

			int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
			if (ret == 0 || ret < 0) {
				closeSocket();
				return false;
			}
			else	
			{
				ret = FD_ISSET(hClientSocket, &exceptset);
				if (ret)		
				{
					closeSocket();
					return false;
				}
			}
		}
	}

	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	setsockopt(hClientSocket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	return true;
}
bool DefaultSocket::hasError()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32|| CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	int err = WSAGetLastError();
	if (err != WSAEWOULDBLOCK) {
#else
	int err = errno;
	if (err != EINPROGRESS && err != EAGAIN) {
#endif
		return true;
	}

	return false;
	
}
//Gui du lieu
int DefaultSocket::sendData(const char* data, int nLength)
{
	return send(hClientSocket, data, nLength, 0);
}

int	DefaultSocket::readData(vector <char> &vectorBuffer, int len)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	return recv(hClientSocket, &vectorBuffer[0], len, 0);
	#else
	return recv(hClientSocket, &vectorBuffer[0], len, 0);
	#endif
}

void DefaultSocket::closeSocket(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		shutdown(hClientSocket, SD_SEND);
		closesocket( hClientSocket ) ;
		WSACleanup() ;
	#else
		close(hClientSocket);
	#endif
}
NS_FR_END