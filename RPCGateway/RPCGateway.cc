/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/9
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

#include "RPCGateway.hh"


RPCGateway::RPCGateway() :
	m_bLoadConfigure(false),
	m_dwVersion(RPC_PROTOCOL_VERSION),
	m_ddwSequence(0)
{
	m_bLoadConfigure = m_stLoadBalance.LoadConfigure("/etc/SimpleRPC/RPCGateway/RPCGateway.conf");
}

RPCGateway::~RPCGateway()
{
	Disconnect();
}

::CommandSetupInfo RPCGateway::Setup(::CommandInfo& in)
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
		pCommand->set_commandcode(0x1001);
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

    ::CommandSetupInfo out;
	out.ParseFromString(stResponseMsg.Body);
    return out;
}


bool RPCGateway::ConnectService(sockaddr_in& addr)
{
	this->Connect(addr);

	timeval tv;
	bzero(&tv, sizeof(timeval));
	tv.tv_usec = 100000;

	return (0 != PoolObject<EventScheduler>::Instance().Wait(this, EventScheduler::PollType::POLLOUT, &tv));
}

void RPCGateway::OnMessage(ChannelType& channel, IOBuffer& in)
{
    LOG("receive [%s:%d] message.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

	// receive service data
	
}

void RPCGateway::OnConnected(ChannelType& channel)
{
    LOG("[%s:%d] connected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}

void RPCGateway::OnDisconnected(ChannelType& channel)
{
    LOG("[%s:%d] disconnected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}



