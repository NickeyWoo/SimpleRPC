/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#FILE_OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/FILE_OPTIONS}}
 *  DATE: {{#DATE}}{{YEAR}}/{{MONTH}}/{{DAY}}{{/DATE}}
 *
--*/
#ifndef __{{NAME}}_HH__
#define __{{NAME}}_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
{{#SERVICES}}{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}#include "TcpClient.hpp"{{/OPTION_6001_0}}{{#OPTION_6001_1}}#include "UdpServer.hpp"{{/OPTION_6001_1}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}{{/SERVICES}}
#include "LoadBalance.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
{{#PROTOLIB}}#include "{{#DATA}}{{SERVICEPATH}}/{{/DATA}}{{PROTOLIB_NAME}}.pb.h"{{/PROTOLIB}}

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}class {{SERVICE_NAME}} :
{{#SERVICE_OPTIONS}}{{#OPTION_6001}}    public {{#OPTION_6001_0}}TcpClient{{/OPTION_6001_0}}{{#OPTION_6001_1}}UdpServer{{/OPTION_6001_1}}<{{SERVICE_NAME}}, void>{{/OPTION_6001}}{{/SERVICE_OPTIONS}}
{
public:
	{{SERVICE_NAME}}();
	~{{SERVICE_NAME}}();
{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}	bool ConnectService(sockaddr_in& addr);
{{/OPTION_6001_0}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}
	{{#METHODS}}{{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} {{METHOD_NAME}}({{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in);
	{{/METHODS}}
    void OnMessage(ChannelType& channel, IOBuffer& in);
{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}        void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);{{/OPTION_6001_0}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}

private:
	bool m_bLoadConfigure;
	uint32_t m_dwVersion;
	uint64_t m_ddwSequence;
	LoadBalance<RoutePolicy> m_stLoadBalance;
};

{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

#endif // define __{{NAME}}_HH__
