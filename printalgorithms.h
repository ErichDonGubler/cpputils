#ifndef PRINTALGORITHMS_H
#define PRINTALGORITHMS_H
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

// Stream functor that prints random-access ranges of the form "[a, b, c]"
// TODO: Get rid of .size() call for true random-access interface
template<typename T>
class print_range
{
private:
	static const int DYNAMIC_SIZING = -1;
	T& t;
	long int offset = 0;
	long int length = DYNAMIC_SIZING;

public:
	print_range(T& t) : t(t) {}
	// Use this ctor if you need to manually specify length and/or offset
	// 
	print_range(T& t, int o, int l) : t(t), offset(o), length(l){}

	friend ostream& operator<<(ostream& os, const print_range& pr)
	{
		os << '[';
		if(pr.length == DYNAMIC_SIZING)
		{
			auto size = pr.t.size();
			switch(size)
			{
				case 0:
					break;
				case 1:
					os << pr.t[0];
					break;
				default:
					copy(pr.t.begin() + pr.offset, pr.t.end() - 1, ostream_iterator<string>(os, ", "));
					os << pr.t[size - 1];
					break;	
			}
		}
		else
		{
			auto begin = pr.t.begin() + pr.offset;
			copy(begin, pr.t.begin() + pr.offset + pr.length - 1, ostream_iterator<string>(os, ", "));
			os << *++begin;
		}
		return os << ']';
	}
};
#endif