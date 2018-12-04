#include "Packet.h"

Packet::Packet(){

}
Packet::Packet(int capacity):MessageBuffer(capacity){
	readHeader = false;
	controllerId = 1;
}
Packet::Packet(const char* data, int size):MessageBuffer(data,size){
	readHeader = false;
}
Packet::~Packet(void){

}
const char* Packet::getData(){
	return buf;
}
void Packet::parseHeader(){
	if(readHeader)
		return;
	readHeader = true;
	controllerId = getByte();
	cmdId = getShort();
	error =  getByte();
}
int Packet::getSize(){
	return getPosition();
}
void Packet::pack(){

}