/**
 * 
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PARSING_H
#define PARSING_H

#include <iostream>
#include <string>

// Similar to C#'s "tryParse"
template<typename T>
bool tryParseNumber(T& storage, std::istream& is = std::cin)
{
	std::string rawInput = "";
	getline(is, rawInput);
	std::stringstream ss;
	ss.str(rawInput);
	return ss >> storage;
}

#endif