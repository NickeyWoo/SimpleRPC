/*++
 *
 *  Kafka Message Queue
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/15
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

#include "BrokerService.hh"
#include "BrokerApp.hh"

void BrokerService::OnConnected(ChannelType& channel)
{
	LOG("[%s:%d] connected", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

	// set connection heartbeat timeout
	channel.Data.HeartbeatTimerId = PoolObject<Timer<ChannelType*, KAFKA_TIMERINTERVAL> >::Instance().SetTimeout(
										boost::bind(&BrokerService::OnHeartbeatTimeout, this, _1), 
										BrokerApp::Instance().GetConnectionTimeout(),
										&channel);

}

void BrokerService::OnDisconnected(ChannelType& channel)
{
	LOG("[%s:%d] disconnected", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

	PoolObject<Timer<ChannelType*, KAFKA_TIMERINTERVAL> >::Instance().Clear(channel.Data.HeartbeatTimerId);
}

void BrokerService::OnMessage(ChannelType& channel, IOBuffer& in)
{
	LOG("receive [%s:%d] message", inet_ntoa(channel.Address.sin_addr), ntohs(channel.Address.sin_port));

	// delay connection heartbeat timeout
	PoolObject<Timer<ChannelType*, KAFKA_TIMERINTERVAL> >::Instance().Clear(channel.Data.HeartbeatTimerId);
	channel.Data.HeartbeatTimerId = PoolObject<Timer<ChannelType*, KAFKA_TIMERINTERVAL> >::Instance().SetTimeout(
										boost::bind(&BrokerService::OnHeartbeatTimeout, this, _1), 
										BrokerApp::Instance().GetConnectionTimeout(),
										&channel);


}

void BrokerService::OnHeartbeatTimeout(ChannelType* pstChannel)
{
	LOG("[%s:%d] OnHeartbeatTimeout, will close this connection", inet_ntoa(pstChannel->Address.sin_addr), ntohs(pstChannel->Address.sin_port));

	Disconnect(*pstChannel);
}




