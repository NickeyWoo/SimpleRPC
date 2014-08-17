/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#FILE_OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/FILE_OPTIONS}}
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
	m_bLoadConfigure(false),
	m_dwVersion(RPC_PROTOCOL_VERSION),
	m_ddwSequence(0)
{
	m_bLoadConfigure = m_stLoadBalance.LoadConfigure("/etc/SimpleRPC/{{#DATA}}{{SERVICEPATH}}/{{/DATA}}{{NAME}}.conf");
}

{{SERVICE_NAME}}::~{{SERVICE_NAME}}()
{
	Disconnect();
}

{{#METHODS}}{{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} {{SERVICE_NAME}}::{{METHOD_NAME}}({{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in)
{
	if(!m_bLoadConfigure)
		throw RPCServiceException(E_INTERNALERROR, "load RPC configure failure");

	char buffer[65535];
	IOBuffer stInBuf(buffer, 65535);
	uint32_t dwRetryTimes = 0;

	sockaddr_in addr;
	bzero(&addr, sizeof(sockaddr_in));
	do
	{
		if(dwRetryTimes > 3)
			throw RPCServiceException(E_UNAVAILABLE, "service unavailable");

		if(dwRetryTimes > 0 || !this->IsConnected())
		{
			Disconnect();
			m_stLoadBalance.Route(&addr);
			if(!ConnectService(addr))
			{
				m_stLoadBalance.Failure(&addr);
				++dwRetryTimes;
				continue;
			}
		}

		RPCProtocol stRequestMsg;
		stRequestMsg.Head.set_version(m_dwVersion);
		stRequestMsg.Head.set_sequence(m_ddwSequence);
		stRequestMsg.Head.set_timestamp(time(NULL));

		RPCCommand* pCommand = stRequestMsg.Head.mutable_command();
		pCommand->set_commandcode({{#METHOD_OPTIONS}}{{#OPTION_7001}}{{OPTION_VALUE}}{{/OPTION_7001}}{{/METHOD_OPTIONS}});
		pCommand->set_resultcode(0);

		stRequestMsg.Body = in.SerializeAsString();

		IOBuffer stOutBuf(buffer, 65535);
		stOutBuf << stRequestMsg;
		this->Send(stOutBuf);

		timeval tv;
		bzero(&tv, sizeof(timeval));
		tv.tv_usec = 100000; // 100ms timeout
		if(0 == PoolObject<EventScheduler>::Instance().Wait(this, EventScheduler::PollType::POLLIN, &tv))
		{
			m_stLoadBalance.Failure(&addr);
			++dwRetryTimes;
			continue;
		}

		if(this->Recv(stInBuf) == 0)
		{
			m_stLoadBalance.Failure(&addr);
			++dwRetryTimes;
			continue;
		}

		m_stLoadBalance.Success(&addr);
		break;
	}
	while(true);

	// short connection
	Disconnect();

	++m_ddwSequence;

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

{{/METHODS}}bool {{SERVICE_NAME}}::ConnectService(sockaddr_in& addr)
{
	this->Connect(addr);

	timeval tv;
	bzero(&tv, sizeof(timeval));
	tv.tv_usec = 100000;

	return (0 != PoolObject<EventScheduler>::Instance().Wait(this, EventScheduler::PollType::POLLOUT, &tv));
}

void {{SERVICE_NAME}}::OnConnected(ChannelType& channel)
{
    LOG("[%s:%d] connected.", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

    // client connected service

}

void {{SERVICE_NAME}}::OnDisconnected(ChannelType& channel)
{
    LOG("[%s:%d] disconnected.", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

    // client connected service

}

void {{SERVICE_NAME}}::OnMessage(ChannelType& channel, IOBuffer& in)
{
    LOG("receive [%s:%d] message.", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

	// receive service data
	
}
{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

