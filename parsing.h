/**
 * 
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PARSING_H
#define PARSING_H

// Similar to C#'s "tryParse"
template<typename T>
bool tryParseNumber(T& storage)
{
	std::string rawInput = "";
	getline(std::cin, rawInput);
	std::stringstream ss;
	ss.str(rawInput);
	return ss >> storage;
}

#endif