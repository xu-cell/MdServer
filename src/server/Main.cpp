#include <getopt.h>
#include <string>
#include "EventLoop.h"
#include "Server.h"
#include "Logging.h"

int main(int argc,char *argv[])
{
    int threadNum = 4;
    int port = 9999;
    std::string logpath = "./WebServer.log";

    int opt;
    const char *str = "t:l:p";
    while((opt = getopt(argc,argv,str)) != -1)
    {
        switch(opt)
        {
            case  't':
            {
                threadNum = atoi(optarg);
                break;
            }

            case 'l':
            {
                logpath = optarg;
                if(logpath.size() < 2 || optarg[0] !='/')
                {
                    printf("logpath should start with \"/\"\n");
                    abort();
                }
                break;
            }

            case 'p':
            {
                port = atoi(optarg);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    Logger::setLogFileName(logpath);
    #ifndef _PTHREADS
        LOG << "_PTHREADS is not define!";
    #endif

    EventLoop mainloop;
    Server MyHttpServer(&mainloop,threadNum,port);
    MyHttpServer.start();
    mainloop.loop();
    return 0;
}
