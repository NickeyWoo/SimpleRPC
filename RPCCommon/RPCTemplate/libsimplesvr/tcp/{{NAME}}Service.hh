/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#FILE_OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/FILE_OPTIONS}}
 *  DATE: {{#DATE}}{{YEAR}}/{{MONTH}}/{{DAY}}{{/DATE}}
 *
--*/
#ifndef __{{NAME}}SERVICE_HH__
#define __{{NAME}}SERVICE_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "TcpServer.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
{{#PROTOLIB}}#include "{{#DATA}}{{SERVICEPATH}}/{{/DATA}}{{PROTOLIB_NAME}}.pb.h"{{/PROTOLIB}}

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}class {{SERVICE_NAME}}Service :
    public TcpServer<{{SERVICE_NAME}}Service, void>
{
public:
	{{#METHODS}}void On{{METHOD_NAME}}(ChannelType& channel, {{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in, {{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}}& out);
	{{/METHODS}}
    void OnMessage(ChannelType& channel, IOBuffer& in);
    void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);
};

{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

#endif // define __{{NAME}}SERVICE_HH__
