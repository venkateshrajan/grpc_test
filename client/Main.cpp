#include "pch.h"

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <myproto/grpc_test.grpc.pb.h>
#include <myproto/grpc_test.pb.h>

int main (int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  grpc_test::HelloRequest request;
  grpc_test::HelloReply reply;
  request.set_name("venky");

  auto channel = grpc::CreateChannel("localhost::50051", grpc::InsecureChannelCredentials());
  std::unique_ptr<grpc_test::Greeter::Stub> stub = grpc_test::Greeter::NewStub(channel);
  grpc::ClientContext context;
  grpc::Status status = stub->SayHello(&context, request, &reply);

  LOG(INFO) << "Got reponse from server: " << reply.message().c_str();
  std::cout << "Got reponse from server: " << reply.message().c_str() << std::endl;

  return 0;
}
