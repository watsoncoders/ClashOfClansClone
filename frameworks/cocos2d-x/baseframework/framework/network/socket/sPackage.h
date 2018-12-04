#ifndef sPackage_h__
#define sPackage_h__

#include "../../../FrameworkMacros.h"
#include "cocos2d.h"
#include <vector>
/*
package type
*/
NS_FR_BEGIN

enum PackageType
{
	kTypeConnectionOpened = 0,
	kTypeData,
	kTypeConnectionClosed
};

class sPackage :
	public cocos2d::Ref
{
public:
	int _size;
	PackageType packageType;
	char* _data;
	bool result;
public:
	sPackage();
	~sPackage();
	bool process(std::vector<char> buff, int size);
};
NS_FR_END
#endif // sPackage_h__
