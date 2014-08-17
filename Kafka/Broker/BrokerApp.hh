/*++
 *
 *  Kafka Message Queue
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/15
 *
--*/
#ifndef __KAFKA_BROKERAPP_HH__
#define __KAFKA_BROKERAPP_HH__

#include "Application.hpp"
#include "BrokerService.hh"

class BrokerApp :
    public Application<BrokerApp>
{
public:
    bool Initialize(int argc, char* argv[]);

	inline int GetConnectionTimeout()
	{
		return m_dwConnectionTimeout;
	}

	BrokerService m_Service;

private:
	int m_dwConnectionTimeout;
};


#endif // define __KAFKA_BROKERAPP_HH__
