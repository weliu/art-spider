#include <iostream>
#include <string>

#include "log.h"
#include "curl_html.h"
#include "myconfig.h"

void init()
{
	if (!Config::instance().open_config()) {
		std::cout << "Config::open_config() failed" << std::endl;
		exit(-1);
	}

	if (!Log::instance().open_log()) {
		std::cout << "Log::open_log() failed" << std::endl;
		exit(-1);
	}

	CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (code != CURLE_OK)
	{
		art_log(FATAL, "Failed to global init default curl!");
		exit(-1);
	}
}

int main()
{
	init();
	std::string content;
	GetURLDataBycurl("http://news.99ys.com/", content);
	std::cout << content << std::endl;
	return 0;
}
