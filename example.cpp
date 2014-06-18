// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "MtTairThriftProxy.h"
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TServerEpollSocket.h>
#include <thrift/server/TEpollServer.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/protocol/TBinaryProtocol.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class exampleHandler: virtual public exampleIf {
public
  int32_t ex_fun(const int32_t area){
    return ret;
  }
};

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
