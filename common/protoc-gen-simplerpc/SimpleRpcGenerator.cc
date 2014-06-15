#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <boost/format.hpp>
#include <google/protobuf/compiler/cpp/cpp_generator.h>

#include <vector>
#include <utility>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>

#include "SimpleRpcGenerator.hpp"

SimpleRpcGenerator::SimpleRpcGenerator() {}

SimpleRpcGenerator::~SimpleRpcGenerator() {}

bool SimpleRpcGenerator::Generate(const google::protobuf::FileDescriptor* file,
								  const std::string& parameter,
								  google::protobuf::compiler::GeneratorContext* generator_centext,
								  std::string* error) const
{

	std::vector<std::pair<std::string, std::string> > options;
	google::protobuf::compiler::ParseGeneratorParameter(parameter, &options);

	std::string strLog("\n");
	strLog.append((boost::format("file: %s\n") % file->name()).str());
	for(int i=0; i<file->message_type_count(); ++i)
	{
		const google::protobuf::Descriptor* pDesc = file->message_type(i);
		strLog.append((boost::format("  [%d] message: %s\n") % i % pDesc->name()).str());
	}

	*error = strLog;
	return false;
}



