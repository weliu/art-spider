#include "log.h"
#include "myconfig.h"

#define LOG_FILE_NAME "../log/art_spider.log"

Logger Log::_logger = log4cplus::Logger::getInstance("main_log");

Log& Log::instance()
{
	static Log log;
	return log;
}

Log::~Log()
{
}

Log::Log()
{
}

bool Log::open_log()
{
	std::string level;
	if (!Config::instance().get_str_conf("log_level", level)) {
		std::cout << "Can not get log_level in configuration file!" << std::endl;
		return false;
	}
	LogLevel Log_level = string_to_log_level(level);

	/* step 1: Instantiate an appender object */
	SharedAppenderPtr _append(new RollingFileAppender(LOG_FILE_NAME, 1000*1024, 5));
	_append->setName("file log test");

	/* step 2: Instantiate a layout object */
	std::string pattern = "[%p] [%D{%m/%d/%y %H:%M:%S}] [%l] - %m %n";
	std::auto_ptr<Layout> _layout(new PatternLayout(pattern));

	/* step 3: Attach the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4: Instantiate a logger object */

	/* step 5: Attach the appender object to the logger  */
	_logger.addAppender(_append);

	/* step 6: Set a priority for the logger  */
	_logger.setLogLevel(Log_level);

	return true;
}

void art_log(LOG_LEVEL level, const char *fmt, ...)
{
	va_list ap;
	char log_buffer[1024];

	if (fmt == NULL || *fmt == '\0') {
		return;
	}

	va_start(ap, fmt);
	vsnprintf(log_buffer, 1024, fmt, ap);
	va_end(ap);

	switch (level) {
		case TRACE:
			LOG4CPLUS_TRACE(Log::_logger, log_buffer);
			break;
		case DEBUG:
			LOG4CPLUS_DEBUG(Log::_logger, log_buffer);
			break;
		case INFO:
			LOG4CPLUS_INFO(Log::_logger, log_buffer);
			break;
		case WARN:
			LOG4CPLUS_WARN(Log::_logger, log_buffer);
			break;
		case ERROR:
			LOG4CPLUS_ERROR(Log::_logger, log_buffer);
			break;
		case FATAL:
			LOG4CPLUS_FATAL(Log::_logger, log_buffer);
			break;
		default:
			break;
	}
	return;
}

LogLevel Log::string_to_log_level(const std::string& level)
{
	if (level == "OFF") {
		return OFF_LOG_LEVEL;
	}
	if (level == "FATAL") {
		return FATAL_LOG_LEVEL;
	}
	if (level == "ERROR") {
		return ERROR_LOG_LEVEL;
	}
	if (level == "WARN") {
		return WARN_LOG_LEVEL;
	}
	if (level == "INFO") {
		return INFO_LOG_LEVEL;
	}
	if (level == "DEBUG") {
		return DEBUG_LOG_LEVEL;
	}
	if (level == "TRACE") {
		return TRACE_LOG_LEVEL;
	}
	return NOT_SET_LOG_LEVEL;
}


