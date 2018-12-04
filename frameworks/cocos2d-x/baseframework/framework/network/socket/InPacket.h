#ifndef InPacket_h__
#define InPacket_h__

#include "../../../FrameworkMacros.h"
#include <string>
#include "cocos2d.h"
#include "sPackage.h"

NS_FR_BEGIN

class InPacket:
	public cocos2d::Ref
{
public:
	InPacket();
	~InPacket();
	void init(sPackage* pkg);
public:
	int getCmdId();
	int getControllerId();
	int getError();
public:
	char* getBytes(int size);
	int getByte();
	int getShort();
	unsigned short getUnsignedShort();
	int getInt();
	long long getLong();
	bool getBool();
	double getDouble();
	char* getCharArray(int& size);
	std::string getString();
private:
	char parseByte();
	const char* _data;
	int _length;
	int _pos;
	int _cmdId;
	char _controllerId;
	char _error;
};

NS_FR_END
#endif // InPacket_h__
