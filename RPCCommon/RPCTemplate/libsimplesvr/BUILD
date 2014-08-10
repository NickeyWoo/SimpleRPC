#
#   {{NAME}} Service
#
#   DESCRIPTION: 
#   AUTHOR: {{#FILE_OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/FILE_OPTIONS}}
#   DATE: {{#DATE}}{{YEAR}}/{{MONTH}}/{{DAY}}{{/DATE}}
#

{{#PROTOLIB}}proto_library(
    name = '{{NAME}}Proto',
    srcs = [
        '{{FILE}}'
    ]
){{/PROTOLIB}}

cc_binary(
    name = '{{NAME}}Service',
    srcs = [
        '{{NAME}}App.cc',
        '{{NAME}}Service.cc',
    ],
    deps = [
        '//RPCProto:RPCProto',
        '//RPCCommon/RPCProtoKit:RPCProtoKit',
        ':{{NAME}}Proto'
    ]
)

cc_library(
    name = '{{NAME}}',
    srcs = [
        '{{NAME}}.cc'
    ],
    deps = [
        {{#PROTOLIB}}':{{NAME}}Proto',
        {{/PROTOLIB}}'//RPCProto:RPCProto',
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
        {{#PROTOLIB}}':{{NAME}}Proto',
        {{/PROTOLIB}}':{{NAME}}',
		':{{NAME}}Service'
    ]
)

gen_rule(
	name = 'configure',
	cmd = 'SRC=`echo $OUTS`;SRC=`echo $${SRC#*/}`;cp $$SRC $OUTS',
	outs = ['{{NAME}}.conf'],
	deps = [':{{NAME}}Service']
)






