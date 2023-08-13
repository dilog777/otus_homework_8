#include "FileSearcher.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace fs = boost::filesystem;



class FileSearcher::Impl
{
public:
	Impl(const Settings &settings);

	std::vector<std::string> findAll() const;

public:
	std::vector<std::string> _searchPaths;
	std::vector<fs::path> _excludePaths;
	int _level { 0 };
	size_t _size { 0 };
	std::vector<boost::regex> _masks;	

private:
	bool isExcludePath(const fs::path &path) const;
	bool isMatchMask(const std::string &fileName) const;
};



FileSearcher::Impl::Impl(const Settings &settings)
	: _searchPaths { settings._searchPaths }
	, _excludePaths { settings._excludePaths.begin(), settings._excludePaths.end() }
	, _level { settings._level }
	, _size { settings._size }
{
	for (const auto &mask : settings._masks)
	{
		auto rxMask = '^' + mask + '$';
		boost::replace_all(rxMask, ".", "\\.");
		boost::replace_all(rxMask, "*", ".*");
		boost::replace_all(rxMask, "?", ".");
		_masks.push_back(boost::regex(rxMask, boost::regex::icase));
	}
}



std::vector<std::string> FileSearcher::Impl::findAll() const
{
	std::vector<std::string> result;

	for (const auto &searchPath : _searchPaths)
	{
		for (fs::recursive_directory_iterator dirIt(searchPath), end; dirIt != end; ++dirIt)
		{
			if (_level >= 0 && dirIt.depth() > _level)
			{
				dirIt.disable_recursion_pending();
				continue;
			}

			auto &path = dirIt->path();

			if (fs::is_directory(path))
			{
				if (isExcludePath(path))
				{
					dirIt.disable_recursion_pending();
					continue;
				}
			}
			else if (fs::is_regular_file(path))
			{
				auto size = fs::file_size(path);
				if (size < _size)
					continue;

				if (!isMatchMask(path.filename().string()))
					continue;

				result.push_back(path.string());
			}
		}
	}

	return result;
}



bool FileSearcher::Impl::isExcludePath(const fs::path &path) const
{
	for (const auto &exclPath : _excludePaths)
	{
		if (fs::equivalent(exclPath, path))
		{
			return true;
		}
	}
	return false;	
}



bool FileSearcher::Impl::isMatchMask(const std::string &fileName) const
{
	if (_masks.empty())
		return true;

	for (const auto &rxMask : _masks)
	{
		if (boost::regex_match(fileName, rxMask))
		{
			return true;
		}
	}

	return false;
}



FileSearcher::FileSearcher(const Settings &settings)
	: _impl { new Impl(settings) }
{
}



FileSearcher::~FileSearcher()
{
	delete _impl;
}



std::vector<std::string> FileSearcher::findAll() const
{
	return _impl->findAll();
}
