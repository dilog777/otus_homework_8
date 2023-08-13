#pragma once

#include <string>
#include <vector>



struct ProgramOptions
{
	enum class Hash
	{
		Undef,
		CRC32,
		MD5
	};

	std::vector<std::string> _pathList;
	std::vector<std::string> _excludeList;
	int _level{ 0 };
	int _size{ 0 };
	std::vector<std::string> _maskList;
	int _blockSize{ 0 };
	Hash _hash{ Hash::CRC32 };

	static std::string hashToString(Hash hash);
	static Hash hashFromString(const std::string &hashStr, bool *isOk = nullptr);
};
