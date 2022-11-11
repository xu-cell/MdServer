set(SRC
    Channel.cpp
    Epoll.cpp
    EventLoop.cpp
    EventLoopThread.cpp
    EventLoopThreadPool.cpp
    HttpData.cpp
    Main.cpp
    Server.cpp
    Timer.cpp
    Util.cpp
    )

add_executable(WebServer ${SRC})
target_link_libraries(WebServer libserver_base)
