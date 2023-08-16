#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "Hasher.h"



class File
{
public:
	using BlockHash = Hasher::Hash;

	File(const std::string &path, const std::shared_ptr<Hasher> &hasher, size_t blockSize);

	std::string path() const;
	size_t size() const;

	bool operator==(File &other);
	bool operator!=(File &other);

	bool operator<(File &other);

private:
	std::string _path;
	size_t _size { 0 };

	std::shared_ptr<Hasher> _hasher;
	size_t _blockSize { 0 };

	size_t _blockCount { 0 };
	size_t _blocksRead { 0 };
	std::vector<BlockHash> _blockHashes;
	std::unique_ptr<std::ifstream> _fileStream;

	BlockHash blockHash(size_t index);

	void streamOpen();
	void streamClose();
};

