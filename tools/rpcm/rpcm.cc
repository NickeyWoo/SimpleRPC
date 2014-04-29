#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "tools/rpcm/module_template.h"

void print_usage()
{
	printf("usage: rpcm [module]\n"
		   "  rpcm 用来创建标准RPC模块，支持生成默认服务端代码以及相关文件。\n");
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		print_usage();
		return -1;
	}


	return 0;
}

