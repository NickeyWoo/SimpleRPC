#
# Blade RPCM tool
# 2014/04/29
# NickeyWoo
#

cc_binary(
	name = 'rpcm-tool',
	srcs = [
		'rpcm.cc'
	],
	deps = [
		':module-template'
	]
)

gen_rule(
	name = 'rpcm',
	cmd = 'cp ./blade-bin/tools/rpcm/rpcm-tool ./tools/bin/rpcm',
	deps = [
		':rpcm-tool',
	],
	outs = ['./tools/bin/rpcm']
)

resource_library(
	name = 'module-template',
	srcs = [
		'templates/BUILD.template',
		'templates/service.cc.template'
	]
)


