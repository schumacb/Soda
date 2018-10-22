#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
#include <exception>

typedef float f32;
typedef double f64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef int i32;

typedef std::string String;
template <typename T> using Vector =  std::vector<T>;
template <typename T> using HashSet = std::unordered_set<T>;
template <typename Key, typename Value> using Dictionary = std::map<Key, Value>;
template <typename T> using Queue = std::queue<T>;

typedef std::invalid_argument InvalidArgumentException;

// Extension Methods
bool starts_with(const String& long_string, const String& short_string);
template <typename Key, typename Value> bool contains_key(const Dictionary<Key, Value>& dictionary, Key key);
