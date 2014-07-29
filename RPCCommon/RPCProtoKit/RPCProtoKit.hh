/*++
 *
 *	RPC Protocol Kit
 *
 * 	DESCRIPTION: 
 *	AUTHOR: NickeyWoo <thenickey@gmail.com>
 *	DATE: 2014/07/29
 *
--*/
#ifndef __RPCPROTOKIT_HH__
#define __RPCPROTOKIT_HH__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <utility>
#include <string>
#include <exception>

#include "IOBuffer.hpp"
#include "RPCProto/RPCProto.pb.h"

#define RPC_PROTOCOL_VERSION	0x1

#define S_MAGICNO		0x02
#define E_MAGICNO		0x03

#define E_SUCCESS			0x00
#define E_UNKNOWNPROTOCOL	0x01
#define E_UNAVAILABLE		0x02

/*++
 *	RPC Protocol Format:
 *	=============================================================================
 *	PkgBuffer = S_MAGICNO + wHeadLen + cHead + wBodyLen + cBody + E_MAGICNO
 *	=============================================================================
--*/

struct RPCProtocol
{
	RPCProtoHead Head;
	std::string Body;
};

IOBuffer& operator << (IOBuffer& io, RPCProtocol& stProtocol);
IOBuffer& operator >> (IOBuffer& io, RPCProtocol& stProtocol);

class RPCServiceException :
	public std::exception
{
public:
	RPCServiceException(uint32_t dwErrorCode, std::string strErrorMessage);
	virtual ~RPCServiceException() throw();

	virtual const char* what() const throw();
	inline uint32_t error()
	{
		return m_dwErrorCode;
	}

private:
	uint32_t m_dwErrorCode;
	std::string m_strErrorMessage;
};

class RPCUnknownProtocolException :
	public RPCServiceException
{
public:
	RPCUnknownProtocolException(std::string strErrorMessage);
};

#endif // define __RPCPROTOKIT_HH__
