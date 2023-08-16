#include "DublicateFinder.h"

#include <algorithm>
#include <cassert>

#include "File.h"



class DublicateFinder::Impl
{
public:
	Impl(size_t blockSize, ProgramOptions::Hash hashType);

	std::vector<SameFiles> findDublicates(const std::vector<std::string> &filePaths);

private:
	size_t _blockSize { 0 };
	ProgramOptions::Hash _hashType { ProgramOptions::Hash::Undef };

	std::shared_ptr<Hasher> makeHasher(ProgramOptions::Hash hashType) const;
};



DublicateFinder::Impl::Impl(size_t blockSize, ProgramOptions::Hash hashType)
	: _blockSize { blockSize }
	, _hashType { hashType }
{
}



std::vector<DublicateFinder::SameFiles> DublicateFinder::Impl::findDublicates(const std::vector<std::string> &filePaths)
{
	std::vector<File> files;
	auto hasher = makeHasher(_hashType);
	
	for (const auto &filePath : filePaths)
		files.emplace_back(filePath, hasher, _blockSize);

//	auto compare = [](File &file1, File &file2) -> bool
//	{
//		return file1 < file2;
//	};

	std::sort(files.begin(), files.end());

	std::vector<SameFiles> result;
	auto addGroup = [&](auto beg, auto end) {
		SameFiles sameFiles(std::distance(beg, end));
		std::transform(beg, end, sameFiles.begin(), [](const File &file)
			{ return file.path(); });
		result.push_back(std::move(sameFiles));
	};

	auto prev = files.begin();
	auto start = prev;
	for (auto current = std::next(prev); current != files.end(); ++current)
	{
		if (*prev != *current)
		{
			if (start != prev)
			{
				addGroup(start, current);
			}
			start = current;
		}
		prev = current;
	}

	if (start != prev)
		addGroup(start, files.end());

	return result;
}



std::shared_ptr<Hasher> DublicateFinder::Impl::makeHasher(ProgramOptions::Hash hashType) const
{
	std::shared_ptr<Hasher> hasher;
	switch (hashType)
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

	return hasher;
}



DublicateFinder::DublicateFinder(size_t blockSize, ProgramOptions::Hash hashType)
	: _impl { new Impl(blockSize, hashType) }
{
}



DublicateFinder::~DublicateFinder()
{
	delete _impl;
}



std::vector<DublicateFinder::SameFiles> DublicateFinder::findDublicates(const std::vector<std::string> &filePaths)
{
	return _impl->findDublicates(filePaths);
}
