#
#   RPCGateway Service
#
#   DESCRIPTION: 
#   AUTHOR: NickeyWoo
#   DATE: 2014/8/6
#

proto_library(
    name = 'RPCGatewayProto',
    srcs = [
        'RPCGateway.proto'
    ]
)

cc_binary(
    name = 'RPCGatewayService',
    srcs = [
        'RPCGatewayApp.cc',
        'RPCGatewayService.cc',
    ],
    deps = [
        '//RPCProto:RPCProto',
        '//RPCCommon/RPCProtoKit:RPCProtoKit',
        ':RPCGatewayProto'
    ]
)

cc_library(
    name = 'RPCGateway',
    srcs = [
        'RPCGateway.cc'
    ],
    deps = [
        ':RPCGatewayProto',
        '//RPCProto:RPCProto',
        '//RPCCommon/RPCProtoKit:RPCProtoKit'
    ]
)

cc_binary(
    name = 'client',
    srcs = [
        'client.cc'
    ],
    deps = [
        '//RPCProto:RPCProto',
        '//RPCCommon/RPCProtoKit:RPCProtoKit',
        ':RPCGatewayProto',
        ':RPCGateway',
		':RPCGatewayService'
    ]
)

gen_rule(
	name = 'configure',
	cmd = 'SRC=`echo $OUTS`;SRC=`echo $${SRC#*/}`;cp $$SRC $OUTS',
	outs = ['RPCGateway.conf'],
	deps = [':RPCGatewayService']
)






