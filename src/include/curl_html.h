#ifndef CURL_HTML_H
#define CURL_HTML_H

#include <curl/curl.h>
#include <string>

bool GetURLDataBycurl(const char* URL,  std::string &content);
#endif
