#ifndef LOGFILE_H
#define LOGFILE_H

#include <memory>
#include <string>
#include <FileUtil.h>
#include <MutexLock.h>
#include <noncopyable.h>

class LogFile : noncopyable
{
public:
    //每次append flushEveryN次，就flush一下，会将缓冲区的数据，往文件中写
    LogFile(const std::string &basename, int flushEveryN = 1024);
    ~LogFile();

    void append(const char *logline, int len);
    void flush();
    //文件滚动,暂不实现
    bool roolFile();

private:
    void append_unlocked(const char *logline, int len);
    const std::string basename_;
    const int flushEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};

#endif