/*++
 *
 *  !!AUTO GENERATE CODE!!
 *
 *  DESCRIPTION: 
 *  AUTHOR: {{#FILE_OPTIONS}}{{#OPTION_5001}}{{OPTION_VALUE}}{{/OPTION_5001}}{{/FILE_OPTIONS}}
 *  DATE: {{#DATE}}{{YEAR}}/{{MONTH}}/{{DAY}}{{/DATE}}
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

#include "{{NAME}}.hh"

{{#SERVICES}}{{#METHODS}}void Test_{{SERVICE_NAME}}_{{METHOD_NAME}}()
{
	{{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}} stIn;

	// set parameters
	

	{{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} stOut;
	try
	{
		::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{SERVICE_NAME}} stRpc;
		stOut = stRpc.{{METHOD_NAME}}(stIn);
	}
	catch(RPCServiceException& error)
	{
		printf("error(%u): %s\n", error.error(), error.what());
		exit(0);
	}

	printf("send msg: %s", stIn.DebugString().c_str());
	printf("recv msg: %s", stOut.DebugString().c_str());
}

{{/METHODS}}{{/SERVICES}}
int main(int argc, char* argv[])
{
	{{#SERVICES}}{{#METHODS}}Test_{{SERVICE_NAME}}_{{METHOD_NAME}}();
	{{/METHODS}}{{/SERVICES}}
    return 0;
}


