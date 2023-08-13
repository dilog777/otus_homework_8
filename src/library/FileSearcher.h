#pragma once

#include <string>
#include <vector>



class FileSearcher
{
public:
	struct Settings
	{
		std::vector<std::string> _searchPaths;
		std::vector<std::string> _excludePaths;
		int _level { 0 };
		int _size { 0 };
		std::vector<std::string> _masks;
	};

	FileSearcher(const Settings &settings);
	~FileSearcher();

	std::vector<std::string> findAll() const;

private:
	class Impl;
	Impl *_impl { nullptr };
};
