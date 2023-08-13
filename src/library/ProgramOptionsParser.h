#pragma once

#include <iostream>

#include "ProgramOptions.h"



class ProgramOptionsParser
{
public:
	ProgramOptionsParser();
	~ProgramOptionsParser();

	bool parse(int argc, char *argv[], std::string &error);
	ProgramOptions programOptions() const;

	bool hasHelpOption() const;
	void printHelp(std::ostream &out) const;

private:
	class Impl;
	Impl *_impl { nullptr };
};
