#include "InPacket.h"
#include "GsnClient.h"

using namespace std;
USING_NS_CC;

NS_FR_BEGIN

InPacket::InPacket()
{
	retain();
}

InPacket::~InPacket()
{
}
void InPacket::init(sPackage* pkg)
{
	_pos = 0;
	_data = pkg->_data;
	_length = pkg->_size;
	_controllerId = parseByte();
	_cmdId = getShort();
	_error = parseByte();
}
int InPacket::getCmdId()
{
	return _cmdId;
}
int InPacket::getControllerId()
{
	return _controllerId;
}
int InPacket::getError()
{
	return _error;
}
char InPacket::parseByte()
{
	CCAssert(_pos < _length, "IndexOutOfBoundsException");
	char b = _data[_pos++];
	return b;
}
int InPacket::getByte() {
	return (int)parseByte();
}

bool InPacket::getBool() {
	CCAssert(_pos < _length, "IndexOutOfBoundsException");
	char b = _data[_pos++];
	return b > 0;
}

char* InPacket::getBytes(int size) {
	CCAssert(_pos + size <= _length, "IndexOutOfBoundsException");
	char *bytes = new char[size];
	for (int i = 0; i < size; i++) {
		bytes[i] = parseByte();
	}
	return bytes;
}

int InPacket::getShort() {
	CCAssert(_pos + 2 <= _length, "IndexOutOfBoundsException");
	if (_pos + 2 > _length) {
		return 0;
	}
	return (short)((parseByte() << 8) + (parseByte() & 255));
}

unsigned short InPacket::getUnsignedShort() {
	CCAssert(_pos + 2 <= _length, "IndexOutOfBoundsException");
	int a = (parseByte() & 255) << 8;
	int b = (parseByte() & 255) << 0;
	return a + b;
}

int InPacket::getInt() {
	CCAssert(_pos + 4 <= _length, "IndexOutOfBoundsException");
	return ((parseByte() & 255) << 24) +
		((parseByte() & 255) << 16) +
		((parseByte() & 255) << 8) +
		((parseByte() & 255) << 0);
}

long long InPacket::getLong(){
	CCAssert(_pos + 8 <= _length, "IndexOutOfBoundsException");
	return ((long long)(parseByte() & 255) << 56) +
		((long long)(parseByte() & 255) << 48) +
		((long long)(parseByte() & 255) << 40) +
		((long long)(parseByte() & 255) << 32) +
		((long long)(parseByte() & 255) << 24) +
		((long long)(parseByte() & 255) << 16) +
		((long long)(parseByte() & 255) << 8) +
		((long long)(parseByte() & 255) << 0);
}
double InPacket::getDouble()
{
	char *byteArray = new char[8];
	for ( int i = 7; i >= 0; i--)
	{
		byteArray[i] = parseByte();
	}
	double final;
	memcpy(&final, byteArray, 8);
	return final;
}
char* InPacket::getCharArray(int& size) {
	size = getUnsignedShort();
	return getBytes(size);
}
string InPacket::getString(){
	int size = 0;
	char* out = getCharArray(size);
	std::string str(out, size);
	delete[]out;
	return str;
}

NS_FR_END