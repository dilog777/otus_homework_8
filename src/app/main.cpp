#include "DublicateFinder.h"
#include "FileSearcher.h"
#include "ProgramOptionsParser.h"



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

	FileSearcher::Settings fsSettings = {
		opt._searchPaths,
		opt._excludePaths,
		opt._level,
		opt._size,
		opt._masks
	};

	FileSearcher searcer(fsSettings);
	auto filePaths = searcer.findAll();

	DublicateFinder df(opt._blockSize, opt._hash);
	auto dublicates = df.findDublicates(filePaths);

	for (const auto &dublicateGroup : dublicates)
	{
		for (const auto &filePath : dublicateGroup)
		{
			std::cout << filePath << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
