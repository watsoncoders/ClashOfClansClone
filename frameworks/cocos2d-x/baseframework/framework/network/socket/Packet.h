#ifndef _Packet_H_
#define _Packet_H_
#include <string>
#include "MessageBuffer.h"

using namespace std;
class Packet:
public MessageBuffer{
public:
	Packet();
	Packet(int capacity);
	Packet(const char* data, int size);
	virtual ~Packet(void);
private:
	//da loc du lieu header
	bool readHeader;
public:
	// ma goi tin
	short cmdId;
	int controllerId;
	char error;
	const char* getData();
	
	void parseHeader();
	int getSize();
	void pack();
	static bool isBigSize(const char* data){

		return true;
	}
	static short getCmdId(const char* data){
		return (data[4]<<8)+(data[5]&255);
	};
};
#endif // _Packet_H_
