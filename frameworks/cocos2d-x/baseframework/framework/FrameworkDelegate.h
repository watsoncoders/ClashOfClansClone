#ifndef FrameworkDelegate_h__
#define FrameworkDelegate_h__

#include "../FrameworkMacros.h"
#include <string>

NS_FR_BEGIN
class FrameworkDelegate
{
public:
	FrameworkDelegate();
	~FrameworkDelegate();
	static FrameworkDelegate* getInstance();
public:
	virtual void applicationFinished();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
public:
	void prepareUpdateAssets();
	void setFolderAssets(std::string folderApp, std::string manifestPath);
	std::string getFolderAssetsName()
	{
		return _folderApp;
	}
private:
	void destroyAllInstance();
	static FrameworkDelegate* _frameworkDelegate;
	std::string _folderApp;
	std::string _manifestPath;
};
NS_FR_END
#endif // FrameworkDelegate_h__

