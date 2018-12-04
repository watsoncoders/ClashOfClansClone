#ifndef _COMMON_SOCKET_H_
#define _COMMON_SOCKET_H_
#include <vector>
#include "../../../FrameworkMacros.h"

NS_FR_BEGIN
class CommonSocket{
public:
    ~CommonSocket(){};
	virtual bool connectSocket(const char* serverIP, int serverPort) = 0;

	virtual int	readData(std::vector <char> &vectorBuffer,int len) = 0;
	virtual int sendData(const char* data, int len) = 0;
	virtual void closeSocket() = 0;
	virtual bool hasError() = 0;
};

NS_FR_END
#endif // !1
