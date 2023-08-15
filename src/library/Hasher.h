#pragma once

#include <vector>



class Hasher
{
public:
	virtual ~Hasher() = default;

	using Hash = std::vector<unsigned int>;
	virtual Hash process_bytes(const std::vector<char> &buffer) const = 0;
};



class HasherCrc32 : public Hasher
{
public:
	Hash process_bytes(const std::vector<char> &buffer) const override;
};



class HasherMd5 : public Hasher
{
public:
	Hash process_bytes(const std::vector<char> &buffer) const override;
};



class HasherSha1 : public Hasher
{
public:
	Hash process_bytes(const std::vector<char> &buffer) const override;
};
