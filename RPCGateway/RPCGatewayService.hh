/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/6
 *
--*/
#ifndef __RPCGatewaySERVICE_HH__
#define __RPCGatewaySERVICE_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "TcpServer.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
#include "RPCGateway/RPCGateway.pb.h"


class RPCGatewayService :
    public TcpServer<RPCGatewayService, void>
{
public:
	void OnSetup(ChannelType& channel, ::CommandInfo& in, ::CommandSetupInfo& out);
	
    void OnMessage(ChannelType& channel, IOBuffer& in);
    void OnConnected(ChannelType& channel);
    void OnDisconnected(ChannelType& channel);
};



#endif // define __RPCGatewaySERVICE_HH__
