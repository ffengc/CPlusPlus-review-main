

#ifndef __YUFC_STL_SET__
#define __YUFC_STL_SET__

#include "stl_tree.hpp"

namespace yufc
{
    template <class key>
    class set
    {
    private:
        struct __set_key_of_value
        {
            const key &operator()(const key &k) { return k; }
        };

    private:
        rb_tree<key, key, __set_key_of_value> __tree;

    public:
        // 迭代器, 注意: 取类模版里面的类型记得加上typename!
        typedef typename rb_tree<key, key, __set_key_of_value>::iterator iterator;
        iterator begin() { return __tree.begin(); }
        iterator end() { return __tree.end(); }

    public:
        bool insert(const key &k)
        {
            return __tree.Insert(k);
        }
    };
} // namespace yufc

#endif