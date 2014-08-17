#
#   Kafka Message Queue
#
#   DESCRIPTION: 
#   AUTHOR: NickeyWoo
#   DATE: 2014/8/15
#

cc_binary(
	name = 'broker',
	srcs = [
		'BrokerApp.cc',
		'BrokerService.cc',
	],
	deps = [
		'//Kafka/Kafka:KafkaMQ'
	],
)

gen_rule(
	name = 'configure',
	cmd = 'SRC=`echo $OUTS`;SRC=`echo $${SRC#*/}`;cp $$SRC $OUTS',
	outs = ['broker.conf'],
	deps = [':broker']
)



