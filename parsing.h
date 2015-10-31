/**
 * 
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PARSING_H
#define PARSING_H

#include <iostream>
#include <string>
#include <sstream>

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

#include <vector>
/// This is based on the most popular solution from
/// [here](http://stackoverflow.com/questions/236129/split-a-string-in-c)
/// with some modifications
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim))
		elems.push_back(item);
	// Catch cases where:
	if(elems.empty() // string is empty
		|| (!s.empty() && s.back() == delim)) // delim is at end
		elems.push_back("");
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void stripLeft_inline(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));    
}

void stripRight_inline(std::string& s)
{
	auto i = s.size() - 1;
	for(; i >= 0; --i)
		if(!::isspace(s[i]))
			break;
	s.resize(i + 1);
}

void strip_inline(std::string& s)
{
	stripRight_inline(s);
	stripLeft_inline(s);
}

std::string stripLeft(const std::string& s)
{
	auto s2 = s;
	stripLeft_inline(s2);
	return s2;
}

std::string stripRight(const std::string& s)
{
	auto s2 = s;
	stripRight_inline(s2);
	return s2;
}

std::string strip(const std::string& s)
{
	auto s2 = s;
	strip_inline(s2);
	return s2;
}

// Chomp: take whitespace off the right

void chomp_inline(std::string& s)
{
	auto i = s.size() - 1;
	if(::isspace(s[i]))
		s.resize(i);
}

std::string chomp(const std::string& s)
{
	auto s2 = s;
	chomp_inline(s2);
	return s2;
}

// Chomp (variant): take a character off the right

void chomp_inline(std::string& s, char c)
{
	auto i = s.size() - 1;
	if(s[i] == c)
		s.resize(i);
}

std::string chomp(const std::string& s, char c)
{
	auto s2 = s;
	chomp_inline(s2, c);
	return s2;
}

#endif
