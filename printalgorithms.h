/**
 * Printing algorithms for more involved (but common) data structures
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PRINTALGORITHMS_H
#define PRINTALGORITHMS_H
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

// Stream functor that prints random-access ranges of the form "[a, b, c]"
// TODO: Get rid of .size() call for true random-access interface
template<typename T, template <typename = T, typename...> class Range>
class print_range
{
private:
	static const int DYNAMIC_SIZING = -1;
	Range<T>& range;
	long int offset = 0;
	long int length = DYNAMIC_SIZING;

public:
	print_range(Range<T>& r) : range(r) {}
	// Use this ctor if you need to manually specify length and/or offset
	// 
	print_range(Range<T>& r, int o, int l) : range(r), offset(o), length(l){}

	friend ostream& operator<<(ostream& os, const print_range& pr)
	{
		os << '[';
		if(pr.length == DYNAMIC_SIZING)
		{
			auto size = pr.range.size();
			switch(size)
			{
				case 0:
					break;
				case 1:
					os << pr.range[0];
					break;
				default:
					copy(pr.range.begin() + pr.offset, pr.range.end() - 1, ostream_iterator<T>(os, ", "));
					os << pr.range[size - 1];
					break;	
			}
		}
		else
		{
			auto begin = pr.range.begin() + pr.offset;
			copy(begin, pr.range.begin() + pr.offset + pr.length - 1, ostream_iterator<T>(os, ", "));
			os << *++begin;
		}
		return os << ']';
	}
};
#endif