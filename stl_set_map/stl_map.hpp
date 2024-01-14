

#ifndef __YUFC_STL_MAP__
#define __YUFC_STL_MAP__

#include "stl_tree.hpp"

namespace yufc
{
    template <class key, class value>
    class map
    {
    private:
        struct __map_key_of_value
        {
            // 对于map来说，key就是value.first
            const key &operator()(const std::pair<key, value> &kv) { return kv.first; }
        };

    private:
        rb_tree<key, std::pair<key, value>, __map_key_of_value> __tree;

    public:
        // 迭代器, 注意: 取类模版里面的类型记得加上typename!
        typedef typename rb_tree<key, std::pair<key, value>, __map_key_of_value>::iterator iterator;
        iterator begin() { return __tree.begin(); }
        iterator end() { return __tree.end(); }

    public:
        bool insert(const std::pair<key, value> &kv)
        {
            return __tree.Insert(kv);
        }
    };
} // namespace yufc

#endif