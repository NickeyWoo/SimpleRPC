/*++
 *
 *  Kafka Message Queue
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/15
 *
--*/
#ifndef __KAFKA_BROKERSERVICE_HH__
#define __KAFKA_BROKERSERVICE_HH__

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Channel.hpp"
#include "IOBuffer.hpp"
#include "Server.hpp"
#include "Timer.hpp"
#include "TcpServer.hpp"

// 64kb connect cache
#define KAFKA_CONNECTIONSTATUS_CACHE_SIZE	65535

// timer interval 1s
#define KAFKA_TIMERINTERVAL	1000

struct ChannelType;

struct ConnectionStatus
{
	Timer<ChannelType*, KAFKA_TIMERINTERVAL>::TimerID HeartbeatTimerId;
	uint64_t Sequence;
	char IOCache[KAFKA_CONNECTIONSTATUS_CACHE_SIZE];
};

class BrokerService :
	public TcpServer<BrokerService, ConnectionStatus>
{
public:

	// network event callback
	void OnConnected(ChannelType& channel);
	void OnDisconnected(ChannelType& channel);
	void OnMessage(ChannelType& channel, IOBuffer& in);
	void OnHeartbeatTimeout(ChannelType* pstChannel);

};


#endif // define __KAFKA_BROKERSERVICE_HH__
