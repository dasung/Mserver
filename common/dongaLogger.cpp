#include "dongaLogger.h"
#include <cstdio>
#include <cstdarg>

// definition for static memebrs
std::unique_ptr<DongaLogger> DongaLogger::dongaLogger_ = nullptr;   // initialize logger to allocates memory
std::mutex DongaLogger::mutex_;                                     // initialize mutex to allocates memory


void _dongaLogDebug(const char *zFormat, ...)
{
    char zDesc[1000];

    // initialize the va_list
    va_list ap;
    va_start(ap, zFormat);

    // format the string and store it in the buffer
    vsnprintf(zDesc, sizeof(zDesc), zFormat, ap);

    // clean up the va_list
    va_end(ap);

    DongaLogger::getInstance()->writeFile(zDesc);
}


void DongaLogger::writeFile(const char *buferStr)
{
    FILE *logFile = fopen(LOG_FILE_NAME, "a"); // Open the log file in append mode
    if (logFile != nullptr)
    {
        fprintf(logFile, "%s\n", buferStr);
        fclose(logFile);
    }
}

DongaLogger* DongaLogger::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if(dongaLogger_ == nullptr)
	{
		dongaLogger_.reset(new DongaLogger());  // reset() used to make sure always deletes previous pointer in case.

        FILE* logFile = fopen(LOG_FILE_NAME, "r");
        if (logFile)
        {
            fclose(logFile);
            std::remove(LOG_FILE_NAME); // delete previous log file
        }
	}

	return dongaLogger_.get();
}                           // automatically unlocks the mutex using RAII principle

/* RAII is a programming idiom where resources are acquired during the creation (construction) of an object and released when the object is destroyed. */