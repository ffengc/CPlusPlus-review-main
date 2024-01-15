

#ifndef __YUFC_STL_SET__
#define __YUFC_STL_SET__

#include "stl_tree.hpp"
#include <initializer_list>

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
        set() {}
        set(const std::initializer_list<key> &init_lst)
        {
            __make_by_iter(init_lst.begin(), init_lst.end());
        }
        template <class InputIterator>
        set(InputIterator first, InputIterator last)
        {
            __make_by_iter(first, last);
        }
        template <class iterator_type>
        void __make_by_iter(iterator_type first, iterator_type end)
        {
            while (first != end)
            {
                insert(*first);
                ++first;
            }
        }
        set(const set &) = delete;
        set &operator=(const set &) = delete;
        ~set() = default;

    public:
        // 迭代器, 注意: 取类模版里面的类型记得加上typename!
        typedef typename rb_tree<key, key, __set_key_of_value>::iterator iterator;
        iterator begin() { return __tree.begin(); }
        iterator end() { return __tree.end(); }

    public:
        std::pair<iterator, bool> insert(const key &k)
        {
            return __tree.Insert(k);
        }
    };
} // namespace yufc

#endif