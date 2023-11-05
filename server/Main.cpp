#include "pch.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <myproto/grpc_test.grpc.pb.h>
#include <myproto/grpc_test.pb.h>

class GreeterService final : public grpc_test::Greeter::Service {
  public:
    virtual grpc::Status SayHello(grpc::ServerContext* context, 
        const grpc_test::HelloRequest* request, grpc_test::HelloReply* response)  {
      std::cout << "Server: SayHello for [" << request->name() << "]" << std::endl;
      response->set_message("Hello, " + request->name());

      return grpc::Status::OK;
    }
};

int main (int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Server starting";

  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

  GreeterService greeter;
  builder.RegisterService(&greeter);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
  
  return 0;
}
