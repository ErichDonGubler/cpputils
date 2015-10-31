#ifndef INDENTEDLOGGER_H
#define INDENTEDLOGGER_H

#include "printalgorithms.h"

class IndentedLogger
{
public:
	std::string indentString;
	int indentation = 0;
	
	IndentedLogger(const std::string& indentString)
		: indentString(indentString)
	{}

	template<typename...Ts>
	void log(std::ostream& os, Ts...ts)
	{
		for(auto i = 0; i < indentation; ++i)
			write(os, indentString);
		writeln(os, ts...);
	}
};

#endif