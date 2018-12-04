#include "Downloader.h"
#include "cocos2d.h"
#include <curl/curl.h>
#include <curl/easy.h>
NS_FR_BEGIN


size_t fileWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

Downloader* Downloader::_downloader = NULL;

Downloader::Downloader()
{

}

Downloader::~Downloader()
{
	if (_subThreadInstance->joinable())
	{
		_subThreadInstance->join();
	}
    CC_SAFE_DELETE(_subThreadInstance);
}

Downloader* Downloader::getInstance()
{
	if (!_downloader)
	{
		_downloader = new Downloader();
	}
	return _downloader;
}

void Downloader::destroyInstance()
{
	if (_downloader)
	{
		_downloader->need_quit = true;
		delete _downloader;
		_downloader = NULL;
	}
	
}
void Downloader::createThread()
{
	need_quit = false;
	_subThreadInstance = new std::thread(&Downloader::threadEntryFunc, this);
}
void Downloader::threadEntryFunc()
{
	while (true)
	{
		if (need_quit)
		{
			break;
		}
		process();
	}
}
void Downloader::checkToStartDownload()
{

}

void Downloader::processDownload(DownloadItem* downloadItem)
{
	CURL *curl = curl_easy_init();
	bool success = true;
	if (curl) {
		// Open up writable temp graphic.
		FILE *file = fopen(downloadItem->filePath.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, downloadItem->url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fileWriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

		// Write the image to the file.
		int result = curl_easy_perform(curl);
		if (result)
			success = false;
		fclose(file);
		if (success)
			finishDownload(E_RESULT_SUCCESS, downloadItem);
		else
		{
			finishDownload(E_RESULT_DOWNLOAD_ERROR, downloadItem);
		}
	}
	curl_easy_cleanup(curl);
}

void Downloader::finishDownload(DownloadResult result, DownloadItem* downloadItem)
{
	isDownloading = false;
	if (downloadItem->listener)
	{
		downloadItem->listener(result, downloadItem->url.c_str(), downloadItem->filePath.c_str());
	}
	delete downloadItem;
}

void Downloader::process()
{
	s_downloadQueueMutex.lock();
	if (isDownloading || _downloadQueue.empty())
	{
		s_downloadQueueMutex.unlock();
		return;
	}

	DownloadItem* downloadItem = _downloadQueue.front();
	_downloadQueue.pop();
	s_downloadQueueMutex.unlock();
	bool isDownloading = true;
	processDownload(downloadItem);
}

void Downloader::downloadFile(const char* url, const char* filePath, const DownloadListener& listener)
{
	DownloadItem* downloadItem = new DownloadItem();
	downloadItem->filePath = filePath;
	downloadItem->url = url;
	downloadItem->listener = listener;
	s_downloadQueueMutex.lock();
	_downloadQueue.push(downloadItem);
	s_downloadQueueMutex.unlock();
	checkToStartDownload();
}


NS_FR_END