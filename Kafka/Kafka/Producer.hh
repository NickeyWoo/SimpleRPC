/*++
 *
 *  Kafka Message Queue
 *
 *  DESCRIPTION: 
 *  AUTHOR: NickeyWoo
 *  DATE: 2014/8/15
 *
--*/
#ifndef __KAFKA_PRODUCER_HH__
#define __KAFKA_PRODUCER_HH__

#include <boost/nocopyable.hpp>

#include <google/protobuf/message_lite.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

class KafkaProducer	:
	public boost::nocopyable
{
public:

	template<typename MessageT>
	void Push(std::string strTopic, std::string strGroupId, MessageT* pstMessage)
	{
	}

private:

};


#endif // define __KAFKA_PRODUCER_HH__
