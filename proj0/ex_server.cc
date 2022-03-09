#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/health_check_service_interface.h>

#include "ex.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
// using PACKAGE_NAME::OBJECT_NAME;
using proj0::RemoteFunction;
using proj0::Param;
using proj0::Retval;

// : 연산자 - 상속 시 부모의 생성자 호출
class RemoteFunctionCallImpl final : public proj0::Service {
    
    Status remote_function_call(Servercontext* context, const Param* param, Retval* retval) override {
        int number = 1;
        retval->set_message(param->param0() + number);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:15128");
    RemoteFunctionCallImpl service;
}



int main(void) {

    RunServer();

    return 0;
}