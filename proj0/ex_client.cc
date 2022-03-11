#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "ex.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
// using PACKAGE_NAME::OBJECT_NAME;
using proj0::RemoteFunctionCall;
using proj0::Param;
using proj0::Retval;

class RemoteFunctionCallClient {
	public:
	RemoteFunctionCallClient(std::shared_ptr<Channel> channel)
		: stub_(RemoteFunctionCall::NewStub(channel)) {}
	
	int SayHello(const std::string& user) {
		
		Param param;
		param.set_param0(0);

		Retval retval;

		ClientContext context;

		Status status = stub_->remote_function_call(&context, param, &retval);

		if (status.ok()) {
			return retval.retval0();
		} else {
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			return EXIT_FAILURE;
		}
	}

	private:
		std::unique_ptr<RemoteFunctionCall::Stub> stub_;
};

int main(void) {

	
	
    return 0;
}