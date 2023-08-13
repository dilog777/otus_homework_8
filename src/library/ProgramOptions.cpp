#include "ProgramOptions.h"

#include "EnumConverter.hpp"



static const EnumConverter<ProgramOptions::Hash> HASH_CONV =
{
	{ ProgramOptions::Hash::Undef, "Undef" },
	{ ProgramOptions::Hash::CRC32, "CRC32" },
	{ ProgramOptions::Hash::MD5,   "MD5"   }
};



std::string ProgramOptions::hashToString(Hash hash)
{
	return HASH_CONV.toString(hash);
}



ProgramOptions::Hash ProgramOptions::hashFromString(const std::string &hashStr, bool *isOk)
{
	return HASH_CONV.fromString(hashStr, isOk);
}
