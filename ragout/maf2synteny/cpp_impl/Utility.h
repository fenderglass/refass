#pragma once

#include <iterator>
#include <utility>
#include <string>
#include <vector>

//taken from http://stackoverflow.com/questions/14826893
template <typename FwdIt> class adjacent_iterator 
{
public:
    adjacent_iterator(FwdIt first, FwdIt last)
        : m_first(first), m_next(first == last ? first : std::next(first)) { }

    bool operator!=(const adjacent_iterator& other) const 
	{
        return m_next != other.m_next; // NOT m_first!
    }

    adjacent_iterator& operator++() 
	{
        ++m_first;
        ++m_next;
        return *this;
    }

    typedef typename std::iterator_traits<FwdIt>::reference Ref;
    typedef std::pair<Ref, Ref> Pair;

    Pair operator*() const 
	{
        return Pair(*m_first, *m_next); // NOT std::make_pair()!
    }

private:
    FwdIt m_first;
    FwdIt m_next;
};

template <typename FwdIt> class adjacent_range 
{
public:
    adjacent_range(FwdIt first, FwdIt last)
        : m_first(first), m_last(last) { }

    adjacent_iterator<FwdIt> begin() const 
	{
        return adjacent_iterator<FwdIt>(m_first, m_last);
    }

    adjacent_iterator<FwdIt> end() const 
	{
        return adjacent_iterator<FwdIt>(m_last, m_last);
    }

private:
    FwdIt m_first;
    FwdIt m_last;
};

template <typename C> auto make_adjacent_range(C& c) -> 
	adjacent_range<decltype(c.begin())> 
{
    return adjacent_range<decltype(c.begin())>(c.begin(), c.end());
}


/////////////
split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) 
	{
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
