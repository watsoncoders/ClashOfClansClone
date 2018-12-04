#include "FrameworkDelegate.h"
#include "cocos2d.h"
#include "network/download/Downloader.h"
#include "platform/NativeService.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
NS_FR_BEGIN

FrameworkDelegate* FrameworkDelegate::_frameworkDelegate = NULL;

FrameworkDelegate::FrameworkDelegate()
{
	this->_folderApp = "";
	this->_manifestPath = "";
}

FrameworkDelegate::~FrameworkDelegate()
{
}

FrameworkDelegate* FrameworkDelegate::getInstance()
{
	if (!_frameworkDelegate)
	{
		_frameworkDelegate = new FrameworkDelegate();
	}
	return _frameworkDelegate;
}

void FrameworkDelegate::applicationFinished()
{
	destroyAllInstance();
}
bool FrameworkDelegate::applicationDidFinishLaunching()
{
	NativeService::applicationDidFinishLaunching();

	prepareUpdateAssets();
	return true;
}
void FrameworkDelegate::prepareUpdateAssets()
{
	std::string folderUpdateAssets = NativeService::getFolderUpdateAssets().c_str();
	FileUtils::getInstance()->addSearchPath(folderUpdateAssets, true);

	Manifest* localManifest = new Manifest(_manifestPath);
	if (localManifest->isLoaded())
	{
		localManifest->prependSearchPaths();
	}


}
void FrameworkDelegate::setFolderAssets(std::string folderApp, std::string manifestPath)
{
	_folderApp = folderApp;
	_manifestPath = manifestPath;
}

void FrameworkDelegate::applicationDidEnterBackground()
{

}

void FrameworkDelegate::applicationWillEnterForeground()
{

}

void FrameworkDelegate::destroyAllInstance()
{
	
}

NS_FR_END