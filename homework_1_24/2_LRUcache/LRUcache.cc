#include "LRUcache.h"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

LRUCache::LRUCache(int cap)
: capacity(cap) {}

int LRUCache::get(int key)
{
    auto it = map.find(key);
    if(it == map.end())
    {
        return -1;
    }
    else
    {
        auto value = it->second;
        cache.erase(map[key]);
    }

        return it->second;
}
