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

	void writeIndentation(std::ostream& os)
	{
		for(auto i = 0; i < indentation; ++i)
			write(os, indentString);
	}

	template<typename...Ts>
	void log(std::ostream& os, Ts...ts)
	{
		writeIndentation(os);
		write(os, ts...);
	}

	template<typename...Ts>
	void logln(std::ostream& os, Ts...ts)
	{
		log(os, ts...);
		writeln(os);
	}
};

#endif