/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/16
 *
--*/
#ifndef __RPCGateway_HH__
#define __RPCGateway_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "UdpServer.hpp"
#include "LoadBalance.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
#include "RPCGateway/RPCGateway.pb.h"


class RPCGateway :
    public UdpServer<RPCGateway, void>
{
public:
	RPCGateway();
	~RPCGateway();

	::CommandSetupInfo Setup(::CommandInfo& in);
	
    void OnMessage(ChannelType& channel, IOBuffer& in);

private:
	bool m_bLoadConfigure;
	uint32_t m_dwVersion;
	uint64_t m_ddwSequence;
	LoadBalance<RoutePolicy> m_stLoadBalance;
};



#endif // define __RPCGateway_HH__
