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

#include "Configure.hpp"
#include "PoolObject.hpp"
#include "Pool.hpp"
#include "Timer.hpp"
#include "Application.hpp"

#include "{{NAME}}Service.hh"

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
class {{NAME}}App :
    public Application<{{NAME}}App>
{
public:
    bool Initialize(int argc, char* argv[])
    {
		{{#SERVICES}}{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}if(!RegisterTcpServer(m_{{SERVICE_NAME}}Service, "{{SERVICE_NAME}}Interface"))
            return false;
		{{/OPTION_6001_0}}{{#OPTION_6001_1}}if(!RegisterUdpServer<{{SERVICE_NAME}}Service>("{{SERVICE_NAME}}Interface"))
            return false;
		{{/OPTION_6001_1}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}{{/SERVICES}}
		// Initialize code
        

        return true;
    }
	{{#SERVICES}}{{#SERVICE_OPTIONS}}{{#OPTION_6001}}{{#OPTION_6001_0}}
	{{SERVICE_NAME}}Service m_{{SERVICE_NAME}}Service;
	{{/OPTION_6001_0}}{{/OPTION_6001}}{{/SERVICE_OPTIONS}}{{/SERVICES}}
};

{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}

AppRun({{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{NAME}}App);





