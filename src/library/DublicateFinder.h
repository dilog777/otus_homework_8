#pragma once

#include "ProgramOptions.h"



class DublicateFinder
{
public:
	DublicateFinder(size_t blockSize, ProgramOptions::Hash hashType);
	~DublicateFinder();

	using SameFiles = std::vector<std::string>;
	std::vector<SameFiles> findDublicates(const std::vector<std::string> &filePaths);

private:
	class Impl;
	Impl *_impl { nullptr };
};

