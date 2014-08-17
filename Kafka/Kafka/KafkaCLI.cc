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
#include <termios.h>
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
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

int ProcessCommand(const char* szCommand)
{
	std::string strCommand = std::string(szCommand);
	boost::trim(strCommand);

	return 0;
}

int PrintHelp(const char* szCommand)
{
	std::string strCommand = std::string(szCommand);
	boost::trim(strCommand);

	return 0;
}

int main(int argc, char* argv[])
{
	printf("Kafka Message Queue CLI 1.01\n");
	printf("Type \"help\", \"copyright\" for more information.\n");
	printf(">> ");
	fflush(stdout);

	termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	size_t offset = 0;
	char cache[4096];
	bzero(cache, 4096);
	ssize_t size = 0;
	while((size = read(STDIN_FILENO, &cache[offset], 4096)) != -1)
	{
		if(cache[offset + size - 1] == '\r' || cache[offset + size - 1] == '\n')
		{
			if(ProcessCommand(cache) != 0)
				break;

			bzero(cache, offset + size);
			offset = 0;
			printf(">> ");
			fflush(stdout);
			continue;
		}
		else if(cache[offset + size - 1] == '\t')
		{
			PrintHelp(cache);
			fflush(stdout);
			continue;
		}

		offset += size;
		if(offset >= 4095)
		{
			bzero(cache, offset);
			offset = 0;
			printf("error: unknown command.\n");
			printf(">> ");
			fflush(stdout);
			continue;
		}
	}
	printf("bye bye!\n");
	return 0;
}


