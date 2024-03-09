
#include <unordered_map>
#include <list>
#include <utility>

template <class key_type, class value_type, size_t CAPACITY = 10>
class LRUCache
{
private:
    std::unordered_map<key_type, typename std::list<std::pair<key_type, value_type>>::iterator> __hash_map;
    std::list<std::pair<key_type, value_type>> __lru_list;
    size_t __capacity = CAPACITY;

public:
    LRUCache() {}
    value_type get(key_type key)
    {
        auto res = __hash_map.find(key);
        if (res == __hash_map.end())
            return -1;
        // 更新链表节点位置
        auto it = res->second;
        __lru_list.splice(__lru_list.begin(), __lru_list, it);
        return it->second;
    }
    void put(key_type key, value_type value)
    {
        // 1. 新增 2. 更新
        auto res = __hash_map.find(key);
        if (res == __hash_map.end())
        {
            if (__capacity == __hash_map.size())
            {
                auto back = __lru_list.back();
                __hash_map.erase(back.first);
                __lru_list.pop_back();
            }
            // 加入数据
            __lru_list.push_front(std::make_pair(key, value));
            __hash_map[key] = __lru_list.begin();
        }
        else
        {
            // 更新
            auto it = res->second;
            it->second = value; // 更新
            __lru_list.splice(__lru_list.begin(), __lru_list, it);
        }
    }

public:
    void clear()
    {
        __hash_map.clear();
        __lru_list.clear();
    }
    size_t size() { return __hash_map.size(); }
    bool empty() { return this->size() == 0; }
};