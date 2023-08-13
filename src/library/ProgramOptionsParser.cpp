#include "ProgramOptionsParser.h"

#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;



std::istream &operator>>(std::istream &in, ProgramOptions::Hash &hash)
{
	std::string hashStr;
	in >> hashStr;

	bool isOk;
	hash = ProgramOptions::hashFromString(hashStr, &isOk);
	if (!isOk)
		throw po::validation_error(po::validation_error::invalid_option_value);

	return in;
}



std::ostream &operator<<(std::ostream &out, const ProgramOptions::Hash &hash)
{
	out << ProgramOptions::hashToString(hash);
	return out;
}



class ProgramOptionsParser::Impl
{
public:
	Impl();

public:
	ProgramOptions _opt;
	po::variables_map _vm;
	po::options_description _desc { "Options" };
};



ProgramOptionsParser::Impl::Impl()
{
	_desc.add_options()
		("help", "This screen")
		("path,P", po::value<std::vector<std::string>>(&_opt._pathList), "Directories to scan (there may be several)")
		("exclude,E", po::value<std::vector<std::string>>(&_opt._excludeList), "Directories to exclude from scanning")
		("level,L", po::value<int>(&_opt._level)->default_value(1), "Scan level")
		("size,S", po::value<int>(&_opt._size)->default_value(1), "Minimum file size")
		("mask,M", po::value<std::vector<std::string>>(&_opt._maskList), "Masks of file names allowed for comparison")
		("block,B", po::value<int>(&_opt._blockSize)->default_value(512), "Block size, which reads files")
		("hash,H", po::value<ProgramOptions::Hash>(&_opt._hash)->default_value(ProgramOptions::Hash::CRC32), "Hashing algorithm (crc32, md5)");
}



ProgramOptionsParser::ProgramOptionsParser()
	: _impl { new Impl }
{
}



ProgramOptionsParser::~ProgramOptionsParser()
{
	delete _impl;
}



bool ProgramOptionsParser::parse(int argc, char *argv[], std::string &error)
{
	try
	{
		po::store(parse_command_line(argc, argv, _impl->_desc), _impl->_vm);
	}
	catch (const std::exception &e)
	{
		error = e.what();
		return false;
	}

	po::notify(_impl->_vm);
	return true;
}



ProgramOptions ProgramOptionsParser::programOptions() const
{
	return _impl->_opt;
}



bool ProgramOptionsParser::hasHelpOption() const
{
	return _impl->_vm.count("help");
}



void ProgramOptionsParser::printHelp(std::ostream &out) const
{
	out << _impl->_desc << std::endl;
}
