
#include "sPackage.h"
#include "PacketHeaderAnalyze.h"

USING_NS_CC;
NS_FR_BEGIN

sPackage::sPackage()
{
	_size = 0;
	packageType = kTypeData;
	_data = NULL;
}
sPackage::~sPackage()
{
}

bool sPackage::process(std::vector<char> buff, int size)
{
	const char* data = buff.data();
	int dataSize = PacketHeaderAnalyze::getDataSize(data);
	bool compress = PacketHeaderAnalyze::isCompress(data);
	bool bigSize = PacketHeaderAnalyze::isBigSize(data);
	//header size
	unsigned int headerSize = NORMAL_HEADER_SIZE;
	if (bigSize)
		headerSize = BIG_HEADER_SIZE;
	//compress?
	if (compress){
		unsigned char *deflated;
		unsigned int sizeHint = 256 * 1024;
		unsigned char *buffer = (unsigned char *)&buff[headerSize];

		int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, dataSize, &deflated, sizeHint);
		_data = new char[inflatedLen];
		_size = inflatedLen;
		memcpy(_data, deflated, _size);
	}
	else
	{
		_size = dataSize;
		_data = new char[_size];
		memcpy(_data, data + headerSize, _size);
	}
	//alway return true lol
	return true;
}

NS_FR_END