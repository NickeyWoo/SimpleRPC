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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <utility>
#include <string>
#include <vector>
#include <map>

#include <boost/format.hpp>

#include "Configure.hpp"
#include "PoolObject.hpp"
#include "Pool.hpp"
#include "Timer.hpp"
#include "Application.hpp"

#include "BrokerService.hh"
#include "BrokerApp.hh"

bool BrokerApp::Initialize(int argc, char* argv[])
{
	if(!RegisterTcpServer(m_Service, "broker"))
	{
		printf("error: create broker service fail, %s\n", safe_strerror(errno));
		return false;
	}

	std::map<std::string, std::string> stTimeoutMap = Configure::Get("timeout");
	m_dwConnectionTimeout = strtoul(stTimeoutMap["connection"].c_str(), NULL, 10);

	return true;
}

AppRun(BrokerApp)

