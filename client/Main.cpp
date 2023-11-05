#include "pch.h"

// #include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
// #include <absl/flags/internal/flag.h>
#include <grpcpp/channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <myproto/grpc_test.grpc.pb.h>
#include <myproto/grpc_test.pb.h>

// ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

class GreeterClient {
  public:
    GreeterClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(grpc_test::Greeter::NewStub(channel)) {}

    std::string SayHello(const std::string& user) {
      grpc_test::HelloRequest request;
      request.set_name(user);

      grpc_test::HelloReply reply;
      grpc::ClientContext context;
      grpc::Status status = stub_->SayHello(&context, request, &reply);
      if (status.ok()) 
        return reply.message();

      std::cout << status.error_code() << ":" << status.error_message()
        << std::endl;
      return "RPC failed";
    }

  private:
    std::unique_ptr<grpc_test::Greeter::Stub> stub_;
};

int main (int argc, char *argv[]) {
  // absl::ParseCommandLine(argc, argv);
  google::InitGoogleLogging(argv[0]);

  // std::string target_str = absl::GetFlag(FLAGS_target);
  std::string target_str = "localhost:3000";
  GreeterClient greeter(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::cout << "Got reponse from server: " << greeter.SayHello("venky") << std::endl;

  return 0;
}
