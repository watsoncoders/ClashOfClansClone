
#ifndef PacketHeaderAnalyze_h__
#define PacketHeaderAnalyze_h__

#include "../../../FrameworkMacros.h"

#define BIT_IS_BINARY_INDEX 7
#define BIT_IS_ENCRYPT_INDEX 6
#define BIT_IS_COMPRESS_INDEX 5
#define BIT_IS_BLUE_BOXED_INDEX 4
#define BIT_IS_BIG_SIZE_INDEX 3

#define BYTE_PACKET_SIZE_INDEX 1
#define BIG_HEADER_SIZE 5
#define NORMAL_HEADER_SIZE 3


NS_FR_BEGIN
class PacketHeaderAnalyze
{
	public:
		static bool getBit(const unsigned char& input, int index);
		//lay chieu dai thuc cua goi tin
		static int getValidSize(const char* data, int length);
		static bool isBigSize(const char* data);
		static bool isCompress(const char* data);
		static int getDataSize(const char* data);
		static int getCmdIdFromData(const char* data);
		static char genHeader(bool bigSize, bool compress);
private:
		
		static void setBit(unsigned char& input,int index,bool hasBit);
		static int getIntAt(const char* data, int index);
		static unsigned short getUnsignedShortAt(const char* data, int index);
		static short getShortAt(const char* data, int index);
};

NS_FR_END
#endif //PacketHeaderAnalyze_h__
