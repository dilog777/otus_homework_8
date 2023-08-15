#include "File.h"

#include <boost/filesystem.hpp>



File::File(const std::string &path, const std::shared_ptr<Hasher> &hasher, size_t blockSize)
	: _path { path }
	, _hasher { hasher }
	, _blockSize { blockSize }
{
	_size = boost::filesystem::file_size(_path);
	
	_blockCount = _size / blockSize;
	if (_size % blockSize)
		++_blockCount;
	
	_blockHashes.resize(_blockCount);
}



File::~File()
{
	streamClose();
}



bool File::operator==(const File &other) const
{
	if (_size != other._size)
		return false;

	bool isEqual = true;
	for (size_t i = 0; i < _blockCount; ++i)
	{
		if (blockHash(i) != other.blockHash(i))
		{
			isEqual = false;
			break;
		}
	}

	streamClose();
	other.streamClose();
	return isEqual;
}



bool File::operator!=(const File &other) const
{
	return !(*this == other);
}



File::BlockHash File::blockHash(size_t index) const
{
	if (index < _blocksRead)
	{
		return _blockHashes.at(index);
	}

	if (index == _blocksRead)
	{
		streamOpen();

		std::vector<char> buffer(_blockSize);
		_fileStream->read(buffer.data(), _blockSize);
		auto blockHash = _hasher->process_bytes(buffer);
		_blockHashes[_blocksRead++] = blockHash;
		return blockHash;
	}
	
	assert(false);
	return {};
}



void File::streamOpen() const
{
	if (!_fileStream)
	{
		_fileStream = std::make_shared<std::ifstream>(_path, std::ios::binary);
		_fileStream->seekg(_blockSize * _blocksRead, std::ifstream::beg);
	}
}



void File::streamClose() const
{
	if (_fileStream)
	{
		_fileStream->close();
		_fileStream.reset();
	}
}