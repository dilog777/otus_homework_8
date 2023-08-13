#include <iostream>
#include <iterator>

#include "ProgramOptionsParser.h"



template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
	if (!v.empty())
	{
		out << "[";
		std::copy(v.begin(), --v.end(), std::ostream_iterator<T>(out, ", "));
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
	std::cout << "pathList: " << opt._pathList << std::endl;
	std::cout << "_excludeList: " << opt._excludeList << std::endl;
	std::cout << "_level: " << opt._level << std::endl;
	std::cout << "_size: " << opt._size << std::endl;
	std::cout << "_maskList: " << opt._maskList << std::endl;
	std::cout << "_blockSize: " << opt._blockSize << std::endl;
	std::cout << "_hash: " << ProgramOptions::hashToString(opt._hash) << std::endl;

	return 0;
}
