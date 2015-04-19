/**
 * File utilities like path manipulation
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef FILE_H
#define FILE_H

#include <string>

//TODO: Move to cpputils
std::string replaceFileExtension(const std::string& filePath, const std::string& extension)
{
	char c;
	for(int i = filePath.size() - 1; i >= 0; --i)
	{
		c = filePath[i];
		switch(c)
		{
			case '.':
				return filePath.substr(0, i + 1) + extension;
 			// If we encounter a directory slash, then we obviously don't have a file with an extension on it.
			case '\\':
			case '/':
				return filePath + "." + extension;
			default:
				break;
		}
	}
	return filePath + "." + extension;
}

std::string baseFileName(const std::string& filePath)
{
	char c;
	for(int i = filePath.size() - 1; i >= 0; --i)
	{
		c = filePath[i];
		switch(c)
		{
			case '\\':
			case '/':
				return filePath.substr(i + 1);
			default:
				break;
		}
	}
	return filePath;
}

#endif