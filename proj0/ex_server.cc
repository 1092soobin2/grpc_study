#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "ex.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
// using PACKAGE_NAME::OBJECT_NAME;
using proj0::RemoteFunctionCall;
using proj0::Param;
using proj0::Retval;

// : 연산자 - 상속 시 부모의 생성자 호출
class RemoteFunctionCallImpl final : public RemoteFunctionCall::Service {
    
    Status remote_function_call(ServerContext* context, const Param* param, Retval* retval) override {
        int number = 1;
        retval->set_retval0(param->param0() + number);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:15128");
    RemoteFunctionCallImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}



int main(void) {

    RunServer();

    return 0;
}