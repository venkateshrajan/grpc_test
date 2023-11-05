#include "pch.h"

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/strings/str_format.h>
#include <glog/logging.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <myproto/grpc_test.grpc.pb.h>
#include <myproto/grpc_test.pb.h>

ABSL_FLAG(uint16_t, port, 3000, "Server port for the service");

class GreeterService final : public grpc_test::Greeter::Service {
  public:
    virtual grpc::Status SayHello(grpc::ServerContext* context, 
        const grpc_test::HelloRequest* request, grpc_test::HelloReply* response) override  {
      LOG(INFO)<< "Server: SayHello for " << request->name();
      response->set_message("Hello, " + request->name());

      return grpc::Status::OK;
    }

    virtual grpc::Status SayHelloStreaming(grpc::ServerContext* context, 
        const grpc_test::HelloRequest* request, grpc::ServerWriter<grpc_test::HelloReply>* writer) override  {
      LOG(INFO)<< "Server: SayHelloStreaming for " << request->name();

      grpc_test::HelloReply response;
      response.set_message("Hello, " + request->name());
      for (int i = 0; i < 10; i++)
        writer->Write(response);

      return grpc::Status::OK;
    }
};

int main (int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  google::InitGoogleLogging(argv[0]);
  FLAGS_timestamp_in_logfile_name = false;
  FLAGS_logbufsecs = 0;
  FLAGS_logbuflevel = google::INFO;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  grpc::ServerBuilder builder;
  std::string server_address = absl::StrFormat("localhost:%d", absl::GetFlag(FLAGS_port));
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  GreeterService greeter;
  builder.RegisterService(&greeter);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  server->Wait();
  
  return 0;
}

