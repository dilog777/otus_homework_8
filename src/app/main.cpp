#include <iostream>
#include <iterator>

#include "FileSearcher.h"
#include "ProgramOptionsParser.h"



template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
	if (!v.empty())
	{
		out << "[";
		std::copy(v.begin(), --v.end(), std::ostream_iterator<T>(out, ",\n"));
		out << v.back() << "]";
	}

	return out;
}



int main(int argc, char *argv[])
{
	std::string error;
	ProgramOptionsParser optionsParser;
	if (!optionsParser.parse(argc, argv, error))
	{
		std::cerr << "Error: " << error << std::endl;
		optionsParser.printHelp(std::cout);
		return 1;
	}

	if (optionsParser.hasHelpOption())
	{
		optionsParser.printHelp(std::cout);
		return 0;
	}

	ProgramOptions opt = optionsParser.programOptions();
	std::cout << "_searchPaths: " << opt._searchPaths << std::endl;
	std::cout << "_excludePaths: " << opt._excludePaths << std::endl;
	std::cout << "_level: " << opt._level << std::endl;
	std::cout << "_size: " << opt._size << std::endl;
	std::cout << "_masks: " << opt._masks << std::endl;
	std::cout << "_blockSize: " << opt._blockSize << std::endl;
	std::cout << "_hash: " << ProgramOptions::hashToString(opt._hash) << std::endl;

	FileSearcher::Settings fsSettings = {
		opt._searchPaths,
		opt._excludePaths,
		opt._level,
		opt._size,
		opt._masks
	};

	FileSearcher searcer(fsSettings);
	auto fileList = searcer.findAll();

	std::cout << "Founded: " << fileList << std::endl;
	std::cout << "Founded size: " << fileList.size() << std::endl;

	return 0;
}
