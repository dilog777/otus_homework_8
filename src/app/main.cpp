#include <cassert>
#include <iostream>
#include <iterator>

#include "File.h"
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

	std::shared_ptr<Hasher> hasher;
	switch (opt._hash)
	{
		case ProgramOptions::Hash::CRC32:
			hasher = std::make_shared<HasherCrc32>();
			break;
		case ProgramOptions::Hash::MD5:
			hasher = std::make_shared<HasherMd5>();
			break;
		case ProgramOptions::Hash::SHA1:
			hasher = std::make_shared<HasherSha1>();
			break;
		default:
			assert(false);
	}

	std::vector<File> files;
	for (const auto &filePath : fileList)
	{
		files.emplace_back(filePath, hasher, opt._blockSize);
	}

	//bool b = files.at(0) == files.at(1);

	return 0;
}
