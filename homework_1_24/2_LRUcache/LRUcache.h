#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int);

    int get(int key);
        /*if (map.find(key) == map.end()) return -1;
        auto key_value = *map[key];
        cache.erase(map[key]);
        cache.push_front(key_value);
        map[key] = cache.begin();
        return key_value.second;*/

    void put(int key, int value) {
        if (map.find(key) == map.end()) {
            if (cache.size() == capacity) {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        }
        else {
            cache.erase(map[key]);
        }
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;
};
