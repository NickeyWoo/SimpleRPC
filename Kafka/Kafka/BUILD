#
#   Kafka Message Queue
#
#   DESCRIPTION: 
#   AUTHOR: NickeyWoo
#   DATE: 2014/8/15
#

cc_library(
	name = 'KafkaMQ',
	srcs = [
		'Producer.cc',
		'Consumer.cc',
	],
)

cc_binary(
	name = 'kafka',
	srcs = [
		'KafkaCLI.cc',
	],
	deps = [
		':KafkaMQ',
	],
)

proto_library(
	name = 'KafkaProto',
	srcs = [
		'KafkaProtocol.proto',
	],
)


