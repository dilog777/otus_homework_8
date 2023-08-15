#include "Hasher.h"

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>



Hasher::Hash HasherCrc32::process_bytes(const std::vector<char> &buffer) const
{
	boost::crc_32_type result;
	result.process_bytes(buffer.data(), buffer.size());
	return { result.checksum() };
}



Hasher::Hash HasherMd5::process_bytes(const std::vector<char> &buffer) const
{
	boost::uuids::detail::md5 hash;
	boost::uuids::detail::md5::digest_type digest;
	hash.process_bytes(buffer.data(), buffer.size());
	hash.get_digest(digest);
	return { std::begin(digest), std::end(digest) };
}



Hasher::Hash HasherSha1::process_bytes(const std::vector<char> &buffer) const
{
	boost::uuids::detail::sha1 hash;
	boost::uuids::detail::sha1::digest_type digest;
	hash.process_bytes(buffer.data(), buffer.size());
	hash.get_digest(digest);
	return { std::begin(digest), std::end(digest) };
}
