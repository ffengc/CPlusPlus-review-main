

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
        map() {}
        map(const std::initializer_list<std::pair<key, value>> &init_lst)
        {
            __make_by_iter(init_lst.begin(), init_lst.end());
        }
        template <class InputIterator>
        map(InputIterator first, InputIterator last)
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
        // 拷贝构造还没实现，不支持
        map(const map &) = delete;
        map &operator=(const map &) = delete;
        ~map() = default;
    public:
        // 迭代器, 注意: 取类模版里面的类型记得加上typename!
        typedef typename rb_tree<key, std::pair<key, value>, __map_key_of_value>::iterator iterator;
        iterator begin() { return __tree.begin(); }
        iterator end() { return __tree.end(); }

    public:
        // 只有map需要套一层[]
        value &operator[](const key &k)
        {
            std::pair<iterator, bool> ret = insert(std::make_pair(k, value()));
            // 如果有就是插入成功，如果没有就会返回已经有的那个节点
            return ret.first->second;
        }

    public:
        std::pair<iterator, bool> insert(const std::pair<key, value> &kv)
        {
            return __tree.Insert(kv);
        }
    };
} // namespace yufc

#endif