
#ifndef NativeService_h__
#define NativeService_h__

#include <string>
#include "../../FrameworkMacros.h"

NS_FR_BEGIN

class NativeService{
public:
	static void applicationDidFinishLaunching();
	static std::string getFolderUpdateAssets();
};

NS_FR_END
#endif // NativeService_h__
