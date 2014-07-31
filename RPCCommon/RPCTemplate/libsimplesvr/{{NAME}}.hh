/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/OPTIONS}}
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
#include "TcpClient.hpp"
#include "LoadBalance.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
{{#PROTOLIB}}#include "{{#DATA}}{{SERVICEPATH}}/{{/DATA}}{{PROTOLIB_NAME}}.pb.h"{{/PROTOLIB}}

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}class {{SERVICE_NAME}} :
    public TcpClient<{{SERVICE_NAME}}, void>
{
public:
	{{SERVICE_NAME}}();
	~{{SERVICE_NAME}}();
	bool ConnectService(sockaddr_in& addr);

	{{#METHODS}}{{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} {{METHOD_NAME}}({{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in);
	{{/METHODS}}
    void OnMessage(ChannelType& channel, IOBuffer& in);
    void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);

private:
	bool m_bLoadConfigure;
	uint32_t m_dwVersion;
	uint64_t m_ddwSequence;
	LoadBalance<RoutePolicy> m_stLoadBalance;
};

{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

#endif // define __{{NAME}}_HH__
