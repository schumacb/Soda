#include "core/types.hpp"

bool starts_with(const String& long_string, const String& short_string){
    return long_string.compare(0, short_string.length(), short_string) == 0;
}

template <typename Key, typename Value> bool contains_key(const Dictionary<Key, Value>& dictionary, Key key)
{
    return dictionary.find(key) != dictionary.end();
}

