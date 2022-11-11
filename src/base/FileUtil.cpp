#include "FileUtil.h"

AppendFile::AppendFile(std::string filename):fp_(fopen(filename.c_str(),"ae"))
{
    setbuffer(fp_,buffer_,sizeof buffer_);
}
AppendFile::~AppendFile()
{
    fclose(fp_);
}

// append向文件写
void AppendFile::append(const char *logline, const size_t len)
{
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while (remain > 0)
    {
        size_t x = this->write(logline + n, remain);
        if (x == 0)
        {
            int err = ferror(fp_);
            if (err)
            {
                fprintf(stderr, "AppendFile::append() faild !\n");
                break;
            }
        }
        n += x;
        remain = len - n;
    }
}
void AppendFile::flush()
{
    //fflush()会强迫将缓冲区内的数据写回参数stream 指定的文件中。
    fflush(fp_);
}
size_t AppendFile::write(const char *logline, size_t len)
{
    //使用无锁的写，提高了效率。要求外部单线程运行，或者加锁运行
    return fwrite_unlocked(logline,1,len,fp_);
}