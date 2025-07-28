#ifndef DONGA_LOGGER_H
#define DONGA_LOGGER_H

#include <mutex>
#include <memory>

class DongaLogger
{
public:

    void writeFile(const char *zFormat);
	static DongaLogger* getInstance();

    ~DongaLogger() = default;   // when unique_ptr needs destroyed, destructor should be accible public


    // avoids to copy or copy assignment objects
    DongaLogger(const DongaLogger&) = delete;
    DongaLogger& operator=(const DongaLogger&) = delete;

    // optional: avoids implicit move to another objects
    DongaLogger(DongaLogger&&) = delete;
    DongaLogger& operator=(DongaLogger&&) = delete;

private:

    // privent object creation
    DongaLogger() = default;

	static std::unique_ptr<DongaLogger> dongaLogger_;
    static std::mutex mutex_;

};


void _dongaLogDebug(const char *zFormat, ...);

// set this to 0 to disable logging
#define LOG_ENABLED 1

#define LOG_FILE_NAME "dongaLog.log"

// wrapper for _dongaLogDebug
#define LogDebug(...) { if(LOG_ENABLED) { _dongaLogDebug(__VA_ARGS__); } }

// to return the current function name only
#define __SEE_FUNCTION__ __FUNCTION__

#endif // DONGA_LOGGER_H