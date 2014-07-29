# Simple RPC Framework
  SimpleRPC is a RPC Framework.

## Install ##
```shell
	./INSTALL
	source ~/.bashrc
```

## Example ##
*1. create service project, it will be create project directory and service proto file*
```shell
	s create Echo
```

*2. edit service proto file, declare RPC service*
```proto
	import "RPCProto/RPCService.proto";

	option(Author) = "NickeyWoo";

	message EchoRequest {
		required string Message = 1;
	}

	message EchoResponse {
		required string Message = 1;
	}

	service Echo {
		rpc Echo(EchoRequest) returns(EchoResponse) {
			option(CommandCode) = "0x5B10";
		}
	}
```

*3. generate service code*
```shell
	cd Echo
	s build
```

*4. edit your service and compile it*
```shell
	vim EchoService.cc
	blade build
```






