#include "PacketHeaderAnalyze.h"
#include "base/ZipUtils.h"

NS_FR_BEGIN

int PacketHeaderAnalyze::getDataSize(const char* data)
{
	bool bigSize = isBigSize(data);
	if (bigSize)
		return getIntAt(data, BYTE_PACKET_SIZE_INDEX);
	else
		return getUnsignedShortAt(data, BYTE_PACKET_SIZE_INDEX);
}
//data chi la phan du lieu sau byte length, ko phai toan bo goi tin
int PacketHeaderAnalyze::getCmdIdFromData(const char* data)
{
	return getShortAt(data, 1);
}
bool PacketHeaderAnalyze::isBigSize(const char* data)
{
	return getBit(data[0], BIT_IS_BIG_SIZE_INDEX);
}
bool PacketHeaderAnalyze::isCompress(const char* data)
{
	return getBit(data[0], BIT_IS_COMPRESS_INDEX);
}

int PacketHeaderAnalyze::getValidSize(const char* data, int length)
{
	unsigned char header = data[0];
	bool bigSize = isBigSize(data);
	int dataSize = 0;
	int addSize = 0;
	if(bigSize)
	{
		if (length < BIG_HEADER_SIZE)
			return -1;
		dataSize = getIntAt(data, BYTE_PACKET_SIZE_INDEX);
		addSize = BIG_HEADER_SIZE;
	}
	else{
		if (length < NORMAL_HEADER_SIZE)
			return -1;
		dataSize = getUnsignedShortAt(data, BYTE_PACKET_SIZE_INDEX);
		addSize = NORMAL_HEADER_SIZE;
	}
	return dataSize + addSize;
}
bool PacketHeaderAnalyze::getBit(const unsigned char& input, int index){
	int result = input&(1<<index);
	return (result!=0);
}
char PacketHeaderAnalyze::genHeader(bool bigSize, bool compress)
{
	unsigned char header = 0;
	//set bit dau la binary hay ko
	setBit(header,7,true);
	//bit 2: ko ma hoa
	setBit(header,6,false);
	//bit 3: ko nen 
	setBit(header,5,compress);
	//bit 4: isBlueBoxed?
	setBit(header,4,true);
	//bit 5: isBigSize?
	setBit(header,3,bigSize);
	return header;
}
void PacketHeaderAnalyze::setBit(unsigned char& input, int index, bool hasBit){
	if(hasBit){
		input |= 1 << index;
	}else{
		input &= ~(1 << index);
	}
}
int PacketHeaderAnalyze::getIntAt(const char* data, int index)
{
	return ((data[index] & 255) << 24) +
		((data[index+1] & 255) << 16) +
		((data[index+2] & 255) << 8) +
		((data[index+3] & 255) << 0);
}
unsigned short PacketHeaderAnalyze::getUnsignedShortAt(const char* data, int index)
{
	int a = (data[index] & 255) << 8;
	int b = (data[index + 1] & 255) << 0;
	return a + b;
}
short PacketHeaderAnalyze::getShortAt(const char* data, int index)
{
	return (short)((data[index] << 8) + (data[index + 1] & 255));
}

NS_FR_END