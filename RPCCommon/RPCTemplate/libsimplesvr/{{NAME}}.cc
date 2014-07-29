/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/OPTIONS}}
 *  DATE: {{#DATE}}{{YEAR}}/{{MONTH}}/{{DAY}}{{/DATE}}
 *
--*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/select.h>

#include <utility>
#include <string>
#include <vector>
#include <map>

#include <boost/format.hpp>

#include "PoolObject.hpp"
#include "Pool.hpp"
#include "Configure.hpp"
#include "Timer.hpp"
#include "Log.hpp"

#include "{{NAME}}.hh"

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}{{SERVICE_NAME}}::{{SERVICE_NAME}}() :
	m_dwVersion(RPC_PROTOCOL_VERSION),
	m_ddwSequence(0)
{
}

{{SERVICE_NAME}}::~{{SERVICE_NAME}}()
{
	Disconnect();
}

{{#METHODS}}{{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} {{SERVICE_NAME}}::{{METHOD_NAME}}({{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in)
{
	char buffer[65535];
	uint32_t dwRetryTimes = 0;

	timeval tv;
	bzero(&tv, sizeof(timeval));
	do
	{
		if(dwRetryTimes > 3)
			throw RPCServiceException(E_UNAVAILABLE, "service unavailable");
		else if(dwRetryTimes > 0 || !this->IsConnected())
			ConnectService();

		RPCProtocol stRequestMsg;
		stRequestMsg.Head.set_version(m_dwVersion);
		stRequestMsg.Head.set_sequence(m_ddwSequence);
		stRequestMsg.Head.set_timestamp(time(NULL));

		RPCCommand* pCommand = stRequestMsg.Head.mutable_command();
		pCommand->set_commandcode({{#OPTIONS}}{{#OPTION_7001}}{{OPTION_VALUE}}{{/OPTION_7001}}{{/OPTIONS}});
		pCommand->set_resultcode(0);

		stRequestMsg.Body = in.SerializeAsString();

		IOBuffer stOutBuf(buffer, 65535);
		stOutBuf << stRequestMsg;
		this->Send(stOutBuf);

		tv.tv_usec = 100000; // 100ms timeout
		++dwRetryTimes;
	}
	while(0 == PoolObject<EventScheduler>::Instance().Wait(this, EventScheduler::PollType::POLLIN, &tv));

	++m_ddwSequence;

	IOBuffer stInBuf(buffer, 65535);
	if(this->Recv(stInBuf) == 0)
		throw RPCServiceException(E_UNAVAILABLE, "service close connection");

	RPCProtocol stResponseMsg;
	stInBuf >> stResponseMsg;

	RPCCommand stCommand = stResponseMsg.Head.command();
	if(stCommand.resultcode() != 0)
	{
		std::string strErrorMsg;
		if(stCommand.has_resultmessage())
			strErrorMsg = stCommand.resultmessage();
		throw RPCServiceException(stResponseMsg.Head.command().resultcode(), strErrorMsg);
	}

    {{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} out;
	out.ParseFromString(stResponseMsg.Body);
    return out;
}

{{/METHODS}}
void {{SERVICE_NAME}}::ConnectService()
{
	uint32_t dwRetryTimes = 0;
	timeval tv;
	bzero(&tv, sizeof(timeval));
	do
	{
		if(dwRetryTimes > 3)
			throw RPCServiceException(E_UNAVAILABLE, "service connect timeout");
		
		sockaddr_in addr;
		bzero(&addr, sizeof(sockaddr_in));
		addr.sin_family = PF_INET;
		addr.sin_addr.s_addr = inet_addr("0.0.0.0");
		addr.sin_port = htons(1234);

		this->Connect(addr);

		tv.tv_usec = 100000;
		++dwRetryTimes;
	}
	while(0 == PoolObject<EventScheduler>::Instance().Wait(this, EventScheduler::PollType::POLLOUT, &tv));
}

void {{SERVICE_NAME}}::OnMessage(ChannelType& channel, IOBuffer& in)
{
    LOG("receive [%s:%d] message.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

	// receive service data
	
}

void {{SERVICE_NAME}}::OnConnected(ChannelType& channel)
{
    LOG("[%s:%d] connected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}

void {{SERVICE_NAME}}::OnDisconnected(ChannelType& channel)
{
    LOG("[%s:%d] disconnected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}

{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

