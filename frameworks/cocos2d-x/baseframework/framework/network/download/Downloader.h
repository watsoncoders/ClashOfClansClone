#ifndef Downloader_h__
#define Downloader_h__

#include "FrameworkMacros.h"
#include <string>
#include <queue>
#include <mutex>
#include <thread>
NS_FR_BEGIN

enum DownloadResult
{
	E_RESULT_SUCCESS,
	E_RESULT_DOWNLOAD_ERROR,
	E_RESULT_WRITE_ERROR
};

typedef std::function<void(DownloadResult result, const char* url, const char* filePath)> DownloadListener;

struct DownloadItem
{
	std::string url;
	std::string filePath;
	DownloadListener listener;
};
class Downloader
{
public:
	Downloader();
	~Downloader();
	static Downloader* getInstance();
	static void destroyInstance();
public:
	void downloadFile(const char* url, const char* filePath, const DownloadListener& listener);
	void threadEntryFunc();
private:
	void checkToStartDownload();
	void processDownload(DownloadItem* downloadItem);
	void finishDownload(DownloadResult result, DownloadItem* downloadItem);
	void process();
	void createThread();
	
private:
	static Downloader* _downloader;
	std::mutex  s_downloadQueueMutex;
	std::queue<DownloadItem*> _downloadQueue;
	std::thread* _subThreadInstance;
	bool need_quit;
	bool isDownloading;
};
NS_FR_END
#endif // Downloader_h__
