#pragma once

#include <string>

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>



template <typename E>
class EnumConverter
{
	static_assert(std::is_enum<E>::value, "Type is not enum");

public:
	EnumConverter(const std::initializer_list<typename boost::bimap<E, std::string>::value_type> &list);

	std::string toString(E key) const;
	E fromString(const std::string &key, bool *isOk = nullptr) const;

private:
	using BimapType = boost::bimap<boost::bimaps::set_of<E>, boost::bimaps::set_of<std::string>>;
	BimapType _bimap;
};



template <typename E>
EnumConverter<E>::EnumConverter(const std::initializer_list<typename boost::bimap<E, std::string>::value_type> &list)
	: _bimap { list.begin(), list.end() }
{
}



template <typename E>
std::string EnumConverter<E>::toString(E key) const
{
	auto it = _bimap.left.find(key);
	if (it == std::end(_bimap.left))
		return {};

	return it->second;
}



template <typename E>
E EnumConverter<E>::fromString(const std::string &key, bool *isOk) const
{
	if (isOk)
		*isOk = false;

	auto it = _bimap.right.find(key);
	if (it == std::end(_bimap.right))
		return {};

	if (isOk)
		*isOk = true;

	return it->second;
}
