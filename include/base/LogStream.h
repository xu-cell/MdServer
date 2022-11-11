//LogStream主要用来格式化输出，重载了<<运算符，同时也有自己的一块缓冲区，这里缓冲区的存在是为了缓存一行，把多个<<的结果连成一块。
#ifndef LOGSTREAM_H
#define LOGSTREAM_H
#include <assert.h>
#include <string.h>
#include <string>
#include "noncopyable.h"

class AsyncLogging;
const int  kSmallBuffer = 4000;
const int  kLargeBuffer = 4000 * 1000;

template <int SIZE>
class FixedBuffer : noncopyable
{
public:
    FixedBuffer():cur_(data_){}
    ~FixedBuffer();

    void append(const char* buf,size_t len);
    const char* data()const;
    int length()const;
    char* current();
    int avail();
    void add(size_t len);
    void reset();
    void bzero();
private:
    const char* end()const;
    const data_[SIZE];
    char* cur_; 
};


class LogStream : noncopyable
{
public:
    using Buffer = FixedBuffer<kSmallBuffer>;
    LogStream& operator<< (bool v);
    LogStream &operator<<(short);
    LogStream &operator<<(unsigned short);
    LogStream &operator<<(int);
    LogStream &operator<<(unsigned int);
    LogStream &operator<<(long);
    LogStream &operator<<(unsigned long);
    LogStream &operator<<(long long);
    LogStream &operator<<(unsigned long long);
    LogStream &operator<<(const void *);
    LogStream &operator<<(double);
    LogStream &operator<<(long double);

    LogStream &operator<<(float v);
    LogStream &operator<<(const char *str);
    LogStream &operator<<(const unsigned char *str);
    LogStream &operator<<(const std::string &v);
    LogStream &operator<<(char v);
    void append(const char *data, int len);
    const Buffer &buffer()const;
    void resetBuffer();

private:


    template <typename T>
    void formatInteger(T);

    Buffer buffer_;

    static const int kMaxNumericSize = 32;
};

#endif