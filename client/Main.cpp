#include "pch.h"

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/strings/str_format.h>
#include <condition_variable>
#include <glog/logging.h>
#include <grpcpp/channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>
#include <mutex>
#include <myproto/grpc_test.grpc.pb.h>
#include <myproto/grpc_test.pb.h>

ABSL_FLAG(std::string, target, "localhost:3000", "Server address");
ABSL_FLAG(std::string, name, "World", "Server address");

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

      if (!status.ok())
      {
        std::cout << status.error_code() << ":" << status.error_message()
          << std::endl;
        LOG(ERROR) << status.error_code() << ":" << status.error_message();
        return "RPC failed";
      }

      return reply.message();
    }

    std::string SayHelloStreaming(const std::string& user) {
      grpc_test::HelloRequest request;
      request.set_name(user);

      grpc_test::HelloReply reply;
      grpc::ClientContext context;

      std::unique_ptr<grpc::ClientReader<grpc_test::HelloReply>> reader(
          stub_->SayHelloStreaming(&context, request));

      while (reader->Read(&reply)) {
        LOG(INFO) << "Got response from server" << reply.message();
      }

      grpc::Status status = reader->Finish();

      if (!status.ok())
      {
        std::cout << status.error_code() << ":" << status.error_message()
          << std::endl;
        LOG(ERROR) << status.error_code() << ":" << status.error_message();
        return "RPC failed";
      }

      return "RPC Succeeded";
    }

  private:
    std::unique_ptr<grpc_test::Greeter::Stub> stub_;
};

int main (int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  google::InitGoogleLogging(argv[0]);
  FLAGS_timestamp_in_logfile_name = false;
  FLAGS_logbufsecs = 0;
  FLAGS_logbuflevel = google::INFO;

  std::string target_str = absl::GetFlag(FLAGS_target);
  std::string name_str = absl::GetFlag(FLAGS_name);
  GreeterClient greeter(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  LOG(INFO) << "Got reponse from server: " << greeter.SayHelloStreaming(name_str);

  return 0;
}
