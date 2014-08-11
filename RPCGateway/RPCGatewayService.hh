/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/11
 *
--*/
#ifndef __RPCGatewaySERVICE_HH__
#define __RPCGatewaySERVICE_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "UdpServer.hpp"

#include "RPCProto/RPCProto.pb.h"
#include "RPCCommon/RPCProtoKit/RPCProtoKit.hh"
#include "RPCGateway/RPCGateway.pb.h"


class RPCGatewayService :
    public UdpServer<RPCGatewayService, void>
{
public:
	void OnSetup(ChannelType& channel, ::CommandInfo& in, ::CommandSetupInfo& out);
	
    void OnMessage(ChannelType& channel, IOBuffer& in);

};



#endif // define __RPCGatewaySERVICE_HH__
