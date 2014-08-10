/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/10
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

#include "RPCGateway.hh"

void Test_RPCGateway_Setup()
{
	::CommandInfo stIn;

	// set parameters
	

	::CommandSetupInfo stOut;
	try
	{
		::RPCGateway stRpc;
		stOut = stRpc.Setup(stIn);
	}
	catch(RPCServiceException& error)
	{
		printf("error(%u): %s\n", error.error(), error.what());
		exit(0);
	}

	printf("send msg: %s", stIn.DebugString().c_str());
	printf("recv msg: %s", stOut.DebugString().c_str());
}


int main(int argc, char* argv[])
{
	Test_RPCGateway_Setup();
	
    return 0;
}


