#pragma once

#include <string>
#include <vector>



struct ProgramOptions
{
	enum class Hash
	{
		Undef,
		CRC32,
		MD5,
		SHA1
	};

	std::vector<std::string> _searchPaths;
	std::vector<std::string> _excludePaths;
	int _level { 0 };
	size_t _size { 0 };
	std::vector<std::string> _masks;
	int _blockSize { 0 };
	Hash _hash { Hash::CRC32 };

	static std::string hashToString(Hash hash);
	static Hash hashFromString(const std::string &hashStr, bool *isOk = nullptr);
};
