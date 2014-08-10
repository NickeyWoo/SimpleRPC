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
{{#SERVICES}}{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}#include "TcpServer.hpp"{{/OPTION_6001_0}}{{#OPTION_6001_1}}#include "UdpServer.hpp"{{/OPTION_6001_1}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}{{/SERVICES}}

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
{{#PROTOLIB}}#include "{{#DATA}}{{SERVICEPATH}}/{{/DATA}}{{PROTOLIB_NAME}}.pb.h"{{/PROTOLIB}}

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}class {{SERVICE_NAME}}Service :
{{#SERVICE_OPTIONS}}{{#OPTION_6001}}    public {{#OPTION_6001_0}}TcpServer{{/OPTION_6001_0}}{{#OPTION_6001_1}}UdpServer{{/OPTION_6001_1}}<{{SERVICE_NAME}}Service, void>
{{/OPTION_6001}}{{/SERVICE_OPTIONS}}{
public:
	{{#METHODS}}void On{{METHOD_NAME}}(ChannelType& channel, {{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in, {{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}}& out);
	{{/METHODS}}
    void OnMessage(ChannelType& channel, IOBuffer& in);
{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}        void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);{{/OPTION_6001_0}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}
};

{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

#endif // define __{{NAME}}SERVICE_HH__
