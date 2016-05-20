/**
 * Printing algorithms for more involved (but common) data structures
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PRINTALGORITHMS_H
#define PRINTALGORITHMS_H
#include <iostream>

void prettyprint(std::ostream& os, const char* t)
{
	os << '"' << t << '"';
}

void prettyprint(std::ostream& os, const std::string& t)
{
	prettyprint(os, t.c_str());
}

template<typename T>
void prettyprint(std::ostream& os, T&& t)
{
	os << t;
}

// Stream functor that prints random-access ranges of the form "[a, b, c]"
template<typename Iter>
class RangePrinter
{
private:
	Iter begin;
	Iter end;

public:
	RangePrinter(Iter b, Iter e)
		: begin(b), end(e)
	{}

	friend std::ostream& operator<<(std::ostream& os, RangePrinter&& rp)
	{
		os << '[';
		if(rp.begin != rp.end)
			prettyprint(os, *rp.begin++);
		while(rp.begin != rp.end)
		{
			os << ", ";
			prettyprint(os, *rp.begin++);
		}
		return os << ']';
	}

	friend std::ostream& operator<<(std::ostream& os, RangePrinter& rp)
	{
		return os << std::move(rp);
	}
};

template<typename T>
RangePrinter<T> range_printer(T begin, T end)
{
	return RangePrinter<T>(begin, end);
}

template<typename Iter, typename F>
class TransformedRangePrinter
{
private:
	Iter begin;
	Iter end;
	F func;

public:
	TransformedRangePrinter(Iter b, Iter e, F f)
		: begin(b), end(e), func(f)
	{}

	friend std::ostream& operator<<(std::ostream& os, TransformedRangePrinter&& trp)
	{
		os << '[';
		if(trp.begin != trp.end)
			prettyprint(os, trp.func(*trp.begin++));
		while(trp.begin != trp.end)
		{
			os << ", ";
			prettyprint(os, trp.func(*trp.begin++));
		}
		return os << ']';
	}

	friend std::ostream& operator<<(std::ostream& os, TransformedRangePrinter& trp)
	{
		return os << std::move(trp);
	}
};

template<typename T, typename F>
TransformedRangePrinter<T, F> transformed_range_printer(T begin, T end, F f)
{
	return TransformedRangePrinter<T, F>(begin, end, f);
}

template<typename M>
class MapPrinter
{
private:
	M& map;

public:
	MapPrinter(M& m)
		: map(m)
	{}

	friend std::ostream& operator<<(std::ostream& os, MapPrinter&& mp)
	{
		auto begin = mp.map.begin();
		auto end = mp.map.end();
		os << '{';
		if(begin != end)
		{
			auto& pair = *begin++;
			os << pair.first << ": " << pair.second;
		}
		while(begin != end)
		{
			auto& pair = *begin++;
			os << ", " << pair.first << ": " << pair.second;
		}
		return os << '}';
	}

	friend std::ostream& operator<<(std::ostream& os, MapPrinter& mp)
	{
		return os << std::move(mp);
	}
};

template<typename Map>
void map_printer(Map& m)//TODO: Make const!
{
	return MapPrinter<Map>(m);
}

void write(std::ostream& os){}

template<typename T>
void write(std::ostream& os, T&& t)
{
	os << t;
}

template<typename T, typename...Ts>
void write(std::ostream& os, T&& t, Ts&&...ts)
{
	write(os, t);
	write(os, ts...);
}

template<typename...Ts>
void writeln(std::ostream& os, Ts&&...ts)
{
	write(os, ts...);
	os << std::endl;
}

#endif