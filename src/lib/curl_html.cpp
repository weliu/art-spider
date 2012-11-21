#include "curl_html.h"
#include "log.h"
#include "myconfig.h"

using namespace std;

long writer(char *data, int size, int nmemb, string *content)
{
	if (content == NULL) {
		return 0;
	}
	unsigned long sizes = size * nmemb;
	content->append(data, sizes);
	return sizes;
}

bool CurlInit(CURL *&curl, const char* url,string &content)
{
	CURLcode code;
	char error[1024];
	curl = curl_easy_init();
	if (curl == NULL) {
		art_log(ERROR, "Failed to create CURL connection\n");
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set error buffer [%d]\n", code );
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_URL, url);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set URL [%s]\n", error);
		return false;
	}

	int time_out = 10;
	if (!Config::instance().get_int_conf("curl_timeout", time_out)) {
		art_log(WARN, "Failed to get curl_timeout in configuration file, use default value 10\n");
	}
	code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, time_out);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set CURLOPT_TIMEOUT option [%s]\n", error );
		return false;
	}

	int max_redir = 3;
	if (!Config::instance().get_int_conf("curl_maxredir", max_redir)) {
		art_log(WARN, "Failed to get curl_maxredir in configuration file, use default value 3\n");
	}
	code = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, max_redir);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set CURLOPT_MAXREDIRS option [%s]\n", error );
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set redirect option [%s]\n", error );
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set writer [%s]\n", error);
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to set write data [%s]\n", error );
		return false;
	}

	return true;
}


bool GetURLDataBycurl(const char* URL,	string &content)
{
	CURL *curl = NULL;
	CURLcode code;

	if (!CurlInit(curl, URL, content)) {
		art_log(ERROR, "Failed to global init default!\n");
		curl_easy_cleanup(curl);
		return false;
	}
	code = curl_easy_perform(curl);
	if (code != CURLE_OK) {
		art_log(ERROR, "Failed to get '%s'\n", URL);
		curl_easy_cleanup(curl);
		return false;
	}
	long retcode = 0;
	code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE , &retcode);
	if ( (code == CURLE_OK) && retcode == 200 ) {
		double length = 0;
		code = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD , &length);
		art_log(INFO, "Successed to get '%s'\n", URL);
		curl_easy_cleanup(curl);
		return true;
	} else {
		art_log(ERROR, "Failed to get '%s'\n", URL);
		curl_easy_cleanup(curl);
		return false;
	}
}

