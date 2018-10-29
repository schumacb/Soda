#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
#include <exception>

namespace soda {

typedef float f32;
typedef double f64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef int i32;

template <typename T> using Vector = std::vector<T>;
template <typename T> using HashSet = std::unordered_set<T>;
template <typename T> using Queue = std::queue<T>;
typedef std::invalid_argument InvalidArgumentException;

template <typename Key, typename Value>
class Dictionary
{
private:
    std::map<Key, Value> _map;
public:
    bool contains_key(const Key &key)
    {
        return _map.find(key) != _map.end();
    }

    Value& operator[](const Key& key)
    {
        _map[key];
    }
};

class String {
private:
    std::string _string;
public:
    String() {}
    String(char* c_string) : _string(c_string) {}
    String(const char* c_string) : _string(c_string) {}
    String(std::string std_string) : _string(std_string) { }

    bool starts_with(const String& short_string)
    {
        return _string.compare(0, short_string.length(), short_string) == 0;
    }

    size_t length() const
    {
        _string.length();
    }

    operator const std::string&() const
    {
        return _string;
    }

    friend const std::string operator+(const char* lhs, const String& rhs)
    {
        return lhs + rhs._string;
    }

    friend const std::string operator+(const std::string& lhs, const String& rhs)
    {
        return lhs + rhs._string;
    }

    friend bool operator<(const String& lhs, const String& rhs)
    {
        return lhs._string < rhs._string;
    }
};

} // namespace soda
