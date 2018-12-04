#include "OutPacket.h"
#include "PacketHeaderAnalyze.h"

USING_NS_CC;
using namespace std;
NS_FR_BEGIN

#define  INDEX_SIZE_PACKET 1 

OutPacket::OutPacket():_controllerId(1)
{
	retain();
	reset();
}
void OutPacket::initData(int capacity)
{
	_data = new char[capacity];
	_capacity = capacity;
}
OutPacket::~OutPacket()
{

}
void OutPacket::reset()
{
	_pos = 0;
	_length = 0;
	_isPackedHeader = false;
}
void OutPacket::packHeader()
{
	if (_isPackedHeader)
	{
		return;
	}
	_isPackedHeader = true;
	
	char header = PacketHeaderAnalyze::genHeader(false, false);
	putByte(header);
	putUnsignedShort(_length);
	putByte(_controllerId);
	putShort(_cmdId);
}
OutPacket* OutPacket::putByte(int b){
	checkSizeAndExtendsIfNeed(1);
	_data[_pos++] = (char)b;
	_length = _pos;
	return this;
}
OutPacket* OutPacket::putByteArray(const char* bytes, int size){
	putShort(size);
	putBytes(bytes, size);
	return this;
}

OutPacket* OutPacket::putBytes(const char* bytes, int size){
	for (int i = 0; i < size; i++) {
		putByte(bytes[i]);
	}
	return this;
}

OutPacket* OutPacket::putShort(int v) {
	putByte((v >> 8) & 0xFF);
	putByte((v >> 0) & 0xFF);
	return this;
}
OutPacket* OutPacket::putUnsignedShort(unsigned short v){
	putByte(v >> 8);
	putByte(v >> 0);
	return this;
}
OutPacket* OutPacket::putInt(int v) {
	putByte((v >> 24) & 0xff);
	putByte((v >> 16) & 0xff);
	putByte((v >> 8) & 0xff);
	putByte((v >> 0) & 0xff);
	return this;
}

OutPacket* OutPacket::putLong(long long v) {
	putByte((v >> 56) & 0xff);
	putByte((v >> 48) & 0xff);
	putByte((v >> 40) & 0xff);
	putByte((v >> 32) & 0xff);
	putByte((v >> 24) & 0xff);
	putByte((v >> 16) & 0xff);
	putByte((v >> 8) & 0xff);
	putByte((v >> 0) & 0xff);
	return this;
}

OutPacket* OutPacket::putString(string str) {
	int size = str.size();
	putByteArray(str.c_str(), size);
	return this;
}

void OutPacket::updateUnsignedShortAtPos(unsigned short v, int pos)
{
	_data[pos] = v >> 8;
	_data[pos + 1] = v >> 0;
}
void OutPacket::checkSizeAndExtendsIfNeed(int sizeAdded)
{
	if (_pos + sizeAdded > _capacity)
	{
		int newSize = _capacity * 1.5f;
		char* temp = new char[newSize];
		std::copy(_data, _data + _capacity, temp);
		delete[] _data;
		_data = temp;
		_capacity = newSize;
	}
}
void OutPacket::updateSize()
{
	updateUnsignedShortAtPos(_length - 3, INDEX_SIZE_PACKET);
}
char* OutPacket::getData(int& size)
{
	size = _length;
	return _data;
}
NS_FR_END