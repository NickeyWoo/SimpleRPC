/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/9
 *
--*/
#ifndef __RPCGateway_HH__
#define __RPCGateway_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "TcpClient.hpp"
#include "LoadBalance.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
#include "RPCGateway/RPCGateway.pb.h"


class RPCGateway :
    public TcpClient<RPCGateway, void>
{
public:
	RPCGateway();
	~RPCGateway();
	bool ConnectService(sockaddr_in& addr);

	::CommandSetupInfo Setup(::CommandInfo& in);
	
    void OnMessage(ChannelType& channel, IOBuffer& in);
    void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);

private:
	bool m_bLoadConfigure;
	uint32_t m_dwVersion;
	uint64_t m_ddwSequence;
	LoadBalance<RoutePolicy> m_stLoadBalance;
};



#endif // define __RPCGateway_HH__
