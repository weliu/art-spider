#ifndef LOG_H
#define LOG_H

#include <log4cplus/loglevel.h>
#include <log4cplus/ndc.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <iomanip>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <cstdarg>
#include <cstdio>
#include <string>

using namespace log4cplus;
using namespace log4cplus::helpers;

enum LOG_LEVEL {
	TRACE,
	DEBUG,
	INFO,
	WARN,
	ERROR,
	FATAL
};

void art_log(LOG_LEVEL level, const char *fmt, ...);

class Log
{
public:
	bool open_log();
	static Log& instance();
	static Logger _logger;
private:
	Log();
	virtual ~Log();
	LogLevel string_to_log_level(const std::string& level);
};

#endif

