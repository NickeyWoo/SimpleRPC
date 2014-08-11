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

#include <utility>
#include <string>
#include <vector>
#include <map>

#include <boost/format.hpp>

#include "PoolObject.hpp"
#include "Pool.hpp"
#include "Configure.hpp"
#include "Timer.hpp"
#include "Log.hpp"

#include "{{NAME}}Service.hh"

{{#PACKAGES}}namespace {{PACKAGE_NAME}} {
{{/PACKAGES}}
{{#SERVICES}}void {{SERVICE_NAME}}Service::OnMessage(ChannelType& channel, IOBuffer& in)
{
    // receive message
    RPCProtocol stRequestMsg;
    in >> stRequestMsg;

    RPCProtocol stResponseMsg;
    stResponseMsg.Head.CopyFrom(stRequestMsg.Head);

    try 
    {
        uint32_t dwCommandCode = stRequestMsg.Head.command().commandcode();
        LOG("receive client [%s:%d] message(CommandCode:0x%04X).", 
                inet_ntoa(channel.address.sin_addr), 
                ntohs(channel.address.sin_port),
                dwCommandCode);

        switch(dwCommandCode)
        {
        {{#METHODS}}case {{#METHOD_OPTIONS}}{{#OPTION_7001}}{{OPTION_VALUE}}{{/OPTION_7001}}{{/METHOD_OPTIONS}}:
            {
                {{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}} stRequestData;
                if(!stRequestData.ParseFromString(stRequestMsg.Body))
                    throw RPCUnknownProtocolException((boost::format("unpack CommandCode(0x%04X) protocol body fail") 
													  % dwCommandCode).str());

                {{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}} stResponseData;
                On{{METHOD_NAME}}(channel, stRequestData, stResponseData);

                stResponseMsg.Head.mutable_command()->set_resultcode(E_SUCCESS);
                stResponseMsg.Body = stResponseData.SerializeAsString();
            }
            break;
        {{/METHODS}}default:
            throw RPCUnknownProtocolException((boost::format("unknown CommandCode(0x%04X)") 
											  % dwCommandCode).str());
            break;
        }
    }
    catch(RPCServiceException& error)
    {
        RPCCommand* pCommand = stResponseMsg.Head.mutable_command();
        pCommand->set_resultcode(error.error());
        pCommand->set_resultmessage(error.what());
        stResponseMsg.Body.clear();

        std::string strDumpInfo;
        in.Dump(strDumpInfo);
        LOG("[ERROR]: %s, dump:\n%s", error.what(), strDumpInfo.c_str());
    }

    char buffer[65535];
    IOBuffer out(buffer, 65535);
    out << stResponseMsg;
    channel << out;
}

void {{SERVICE_NAME}}Service::OnConnected(ChannelType& channel)
{
    LOG("client [%s:%d] connected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}

void {{SERVICE_NAME}}Service::OnDisconnected(ChannelType& channel)
{
    LOG("client [%s:%d] disconnected.", inet_ntoa(channel.address.sin_addr), ntohs(channel.address.sin_port));

    // client connected service

}

{{#METHODS}}void {{SERVICE_NAME}}Service::On{{METHOD_NAME}}(ChannelType& channel, {{#INPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/INPUT_TYPE}}& in, {{#OUTPUT_TYPE}}::{{#PACKAGES}}{{PACKAGE_NAME}}::{{/PACKAGES}}{{TYPE_NAME}}{{/OUTPUT_TYPE}}& out)
{
    // implement rpc logic


}

{{/METHODS}}
{{/SERVICES}}{{#PACKAGES}}} // namespace {{PACKAGE_NAME}}
{{/PACKAGES}}



