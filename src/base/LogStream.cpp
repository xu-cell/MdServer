#include "LogStream.h"
#include "LogStream.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits>

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;
template <typename T>
size_t convert(char buf[], T value) {
  T i = value;
  char* p = buf;

  do {
    int lsd = static_cast<int>(i % 10);
    i /= 10;
    *p++ = zero[lsd];
  } while (i != 0);

  if (value < 0) {
    *p++ = '-';
  }
  *p = '\0';
  std::reverse(buf, p);

  return p - buf;
}
template <int SIZE>
void FixedBuffer<SIZE>::append(const char *buf, size_t len)
{
    if (avail() > static_cast<int>(len))
    {
        memccpy(cur_, buf, len);
        cur_ += len;
    }
}
template <int SIZE>
const char *FixedBuffer<SIZE>::data() const
{
    return data_;
}
template <int SIZE>
int FixedBuffer<SIZE>::length() const
{
    return static_cast<int>(cur_ - data_);
}
template <int SIZE>
char *FixedBuffer<SIZE>::current()
{
    return cur_;
}
template <int SIZE>
int FixedBuffer<SIZE>::avail()
{
    return static_cast<int>(end() - cur_);
}
template <int SIZE>
void FixedBuffer<SIZE>::add(size_t len)
{
    cur_ += len;
}
template <int SIZE>
void FixedBuffer<SIZE>::reset()
{
    cur_ = data_;
}
template <int SIZE>
void FixedBuffer<SIZE>::bzero()
{
    memset(data_, 0, sizeof data_);
}
template <int SIZE>
const char *FixedBuffer<SIZE>::end() const
{
    return data_ + sizeof date_;
}

template class FixedBuffer<kSmallBuffer>;
template class FixedBuffer<kLargeBuffer>;

template <typename T>
void LogStream::formatInteger(T v)
{
      // buffer容不下kMaxNumericSize个字符的话会被直接丢弃
    if(buffer_.avail() >= kMaxNumericSize)
    {
        size_t len = convert(buffer_.current(),v);
        buffer_.add(len);
    }
}

LogStream &LogStream::operator<<(short v)
{
    *this << static_cast<unsigned int>(v);
    return *this;
}
LogStream &LogStream::operator<<(unsigned short v)
{
    *this << static_cast<unsigned int>(v);
    return *this;
}
LogStream &LogStream::operator<<(int v)
{
    formatInteger(v);
    return *this;
}
LogStream &LogStream::operator<<(unsigned int v)
{
    formatInteger(v);
    return *this;
}
LogStream &LogStream::operator<<(long v)
{
    formatInteger(v);
    return *this;
}
LogStream &LogStream::operator<<(unsigned long v)
{
    formatInteger(v);
    return *this;
}
LogStream &LogStream::operator<<(long long v)
{
    formatInteger(v);
    return *this;
}
LogStream &LogStream::operator<<(unsigned long long v)
{
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(double v)
{
    if (buffer_.avail() >= kMaxNumericSize)
    {
        int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12g", v);
        buffer_.add(len);
    }
    return *this;
}

LogStream &LogStream::operator<<(long double v)
{
    if (buffer_.avail() >= kMaxNumericSize)
    {
        int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12Lg", v);
        buffer_.add(len);
    }
    return *this;
}
LogStream &LogStream::operator<<(float v)
{
    *this << static_cast<double>(v);
}
LogStream &LogStream::operator<<(const char *str)
{
    if (str)
    {
        buffer_.append(str, strlen(str));
    }
    else
    {
        buffer_.append("(null)", 6);
    }
    return *this;
}
LogStream &LogStream::operator<<(const unsigned char *str)
{
    return operator<<(reinterpret_cast<const char *>(str));
}
LogStream &LogStream::operator<<(const std::string &v)
{
    buffer_.append(v.c_str(), v.size());
    return *this;
}
LogStream &LogStream::operator<<(char v)
{
    buffer_.append(&v, 1);
    return *this;
}
void LogStream::append(const char *data, int len)
{
    buffer_.append(data, len);
}
void LogStream::resetBuffer()
{
    buffer_.reset();
}
LogStream &LogStream::operator<<(bool v)
{
    buffer_.append(v ? "1" : "0", 1);
    return *this;
}
