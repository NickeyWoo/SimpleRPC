/*++
 *
 *	RPC Protocol Kit
 *
 * 	DESCRIPTION: 
 *	AUTHOR: NickeyWoo <thenickey@gmail.com>
 *	DATE: 2014/07/29
 *
--*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include "RPCProtoKit.hh"

RPCServiceException::RPCServiceException(uint32_t dwErrorCode, std::string strErrorMessage) :
	m_dwErrorCode(dwErrorCode),
	m_strErrorMessage(strErrorMessage)
{
}

RPCServiceException::~RPCServiceException() throw()
{
}

const char* RPCServiceException::what() const throw()
{
	return m_strErrorMessage.c_str();
}

RPCUnknownProtocolException::RPCUnknownProtocolException(std::string strErrorMessage) :
	RPCServiceException(0x01, strErrorMessage)
{
}

IOBuffer& operator << (IOBuffer& io, RPCProtocol& stProtocol)
{
	io << (uint8_t)S_MAGICNO << stProtocol.Head.SerializeAsString() << stProtocol.Body << (uint8_t)E_MAGICNO;
	return io;
}

IOBuffer& operator >> (IOBuffer& io, RPCProtocol& stProtocol)
{
	char cSMagic, cEMagic;
	std::string strHead;
	io >> cSMagic >> strHead >> stProtocol.Body >> cEMagic;

	if(cSMagic != S_MAGICNO || cEMagic != E_MAGICNO)
		throw RPCUnknownProtocolException("not found S_MAGICNO or E_MAGICNO");

	if(!stProtocol.Head.ParseFromString(strHead))
		throw RPCUnknownProtocolException("parse RPC Protocol head fail");
	return io;
}


