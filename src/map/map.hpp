#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <map>
namespace Map {
    // Map interface that includes insertion, deletion, and search methods
    template <class K, class V>
    class Map {
        public:
            virtual void insert(K key, V value) = 0;
            virtual void remove(K key) = 0;
            virtual int search(K key) = 0;
    };
};
#endif
