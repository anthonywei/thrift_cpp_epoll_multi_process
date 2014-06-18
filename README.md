thrift_cpp_epoll_multi_process
==============================
this version support thrift with c++ server use epoll and multiprocess

add four files as follows:
------------------------------
server/TEpollServer.h
server/TEpollServer.cpp

transport/TServerEpollSocket.h
transport/TServerEpollSocket.cpp
------------------------------

Thus server can start by the follow codes:
------------------------------
int main(int argc, char **argv) {

    
    int port = 9090;
    int processnum = 5; //process num

    shared_ptr<exampleHandler> handler(new exampleHandler());    

    shared_ptr<TProcessor> processor(new exampleProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerEpollSocket(port, 1000, 1000));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TEpollServer server(processor, serverTransport, transportFactory, protocolFactory);
    
    server.listen();
    for(int i = 1; i <= processnum; ++i){
        if(fork() == 0){

            fprintf(stderr, "Process %d start serve()\n", getpid());
            server.epoll();

            server.serve();
            break;
        }
    }
    exit(0);
    return 0;
}
-------------------------------

Advantags:
we use epoll to watch the connections events, not use recv() and timeout. more effective. And also it is even more effective 
than recv() + timeout + multi-thread

and also it is of simlity. you do not need to care about thread-safe class, objects and anything.

中文：
我们使用epoll来监听所有的客户端连接，相比较原来的recv()+timeout的方式，更加高效，更加符合高效编程的思想，另外即使相比较Nonblocking
性能也不输。
而且，实现更加简单，实际上大多数的网络框架还是要简单点，避免在使用线程安全或者需要加锁的场景的复杂情况。框架还是简单点好。

