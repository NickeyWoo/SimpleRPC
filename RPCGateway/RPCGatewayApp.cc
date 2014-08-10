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

#include "RPCGatewayService.hh"


class RPCGatewayApp :
    public Application<RPCGatewayApp>
{
public:
    bool Initialize(int argc, char* argv[])
    {
		if(!RegisterTcpServer(m_RPCGatewayService, "RPCGatewayInterface"))
            return false;
		
		// Initialize code
        

        return true;
    }

	RPCGatewayService m_RPCGatewayService;
	
};



AppRun(RPCGatewayApp);





