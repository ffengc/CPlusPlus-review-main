
#include <unordered_map>
#include <list>
#include <utility>

class LRUCache
{
private:
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> __hash_map;
    std::list<std::pair<int, int>> __lru_list;
    size_t __capacity;

public:
    LRUCache(int capacity)
        : __capacity(capacity) {}
    int get(int key)
    {
        auto res = __hash_map.find(key);
        if (res == __hash_map.end())
            return -1;
        // 更新链表节点位置
        auto it = res->second;
        /*
            方法一: erase + push_front
                注意记得erase之后更新迭代器，防止迭代器失效
            方法二：转移节点的接口，stl::list提供了
        */
        __lru_list.splice(__lru_list.begin(), __lru_list, it);
        return it->second;
    }

    void put(int key, int value)
    {
        // 1. 新增 2. 更新
        auto res = __hash_map.find(key);
        if (res == __hash_map.end())
        {
            // 新增，如果满了，先删除数据
            /*
                这里用哈希表求size比较细节，这里一定是O(1)
                但是list有些版本下入过没有维护size这个字段，求一次size()就是O(n)了
            */
            if (__capacity == __hash_map.size())
            {
                std::pair<int, int> back = __lru_list.back();
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
};