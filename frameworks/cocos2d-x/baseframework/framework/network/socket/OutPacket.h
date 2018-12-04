#ifndef OutPacket_h__
#define OutPacket_h__

#include "cocos2d.h"
#include "../../../FrameworkMacros.h"
#include <string>

NS_FR_BEGIN
class OutPacket:
	public cocos2d::Ref
{
public:
	OutPacket();
	~OutPacket();
	void initData(int capacity);
	void reset();
public:

	OutPacket* putByte(int b);
	OutPacket* putBytes(const char* bytes, int size);
	OutPacket* putByteArray(const char* bytes, int size);
	OutPacket* putShort(int v);
	OutPacket* putInt(int v);
	OutPacket* putLong(long long v);
	OutPacket* putString(std::string str);
	OutPacket* putUnsignedShort(unsigned short v);
	
	void updateUnsignedShortAtPos(unsigned short v, int pos);
	char* getData(int& size);
	void packHeader();
	void updateSize();
	void setCmdId(int cmdId)
	{
		_cmdId = cmdId;
	}
	void setControllerId(int controllerId)
	{
		_controllerId = controllerId;
	}
protected:
	void checkSizeAndExtendsIfNeed(int sizeAdded);
	int _pos;
	int _capacity;
	char* _data;
	int _length;
	bool _isPackedHeader;
	int _cmdId;
	char _controllerId;
};
NS_FR_END
#endif // OutPacket_h__
