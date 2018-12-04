#include "NativeService.h"
#include "cocos2d.h"
#include "../FrameworkDelegate.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "plugin/protocols/include/PluginManager.h"
using namespace cocos2d::plugin;

PluginProtocol* nativeServicePlugin = nullptr;
#endif

NS_FR_BEGIN

void NativeService::applicationDidFinishLaunching()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	nativeServicePlugin = PluginManager::getInstance()->loadPlugin("Platform");
#endif
}
std::string NativeService::getFolderUpdateAssets()
{
	std::string appFolder = FrameworkDelegate::getInstance()->getFolderAssetsName();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	PluginParam _appFolder(appFolder.c_str());
	return nativeServicePlugin->callStringFuncWithParam("getFolderUpdateAssets",&_appFolder,nullptr);
#endif
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + appFolder;
}

NS_FR_END