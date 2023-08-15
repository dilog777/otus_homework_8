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
	~File();

	bool operator==(const File &other) const;
	bool operator!=(const File &other) const;

private:
	std::string _path;
	size_t _size { 0 };

	std::shared_ptr<Hasher> _hasher;
	size_t _blockSize { 0 };

	size_t _blockCount { 0 };
	mutable size_t _blocksRead { 0 };
	mutable std::vector<BlockHash> _blockHashes;
	mutable std::shared_ptr<std::ifstream> _fileStream;

	BlockHash blockHash(size_t index) const;

	void streamOpen() const;
	void streamClose() const;
};

