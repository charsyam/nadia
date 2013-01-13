#pragma once

#include    "object.h"
#include    <list>
#include    <stdint.h>

namespace nadia {

#define     HASH_INIT_SIZE      4

class store {
public:
    store() : mask_(HASH_INIT_SIZE), ht_(NULL) {
        alloc_hash_table(HASH_INIT_SIZE);
    }
    ~store() {
        if (ht_) {
            delete [] ht_;
            ht_ = NULL;
        }
    }

    int alloc_hash_table(int _size) {
        ht_ = new object_list[_size];
        return 1;
    }

    int insert(object::type _type, 
               char *_key, int _key_size, 
               char *_data, int _data_size) {
        int ret = 0; 
        object *obj = find(_key, _key_size);
        if (NULL == obj) {
            object *new_obj = new object(_type,
                                         _key, _key_size,
                                         _data, _data_size);
            insert(new_obj);
        }

        return ret;
    }

    int remove(char *_key, int _key_size) {
        int hash_value = hash(_key, _key_size);
        int idx = hash_value & (mask_ - 1);

        object_list *ht = &ht_[idx];
        object_list::iterator it = ht->begin();
        for ( ; it != ht->end(); it++) {
            if (_key_size == (*it)->get_key_size()) {
                if (memcmp(_key, (*it)->get_key(), _key_size) == 0) {
                    ht->erase(it);
                    return 1;
                }
            } 
        }

        return 0;
    }

    object *find(char *_key, int _key_size) {
        int hash_value = hash(_key, _key_size);
        int idx = hash_value & (mask_ - 1);

        object_list *ht = &ht_[idx];
        object_list::iterator it = ht->begin();
        for ( ; it != ht->end(); it++) {
            if (_key_size == (*it)->get_key_size()) {
                if (memcmp(_key, (*it)->get_key(), _key_size) == 0) {
                    return (*it);
                }
            } 
        }

        return NULL;
    }

private:
    int hash(char *_key, int _key_size) {
        int result = 0;
        for (int i = 0; i < _key_size; i++) {
            result = 31 * result + _key[i];
        }
        return result;
    }

    int insert(object *_object) {
        int ret = hash(_object->get_key(), _object->get_key_size());
        int idx = ret & (mask_-1);
        ht_[idx].push_back(_object);
    }

private:
    int mask_;

    typedef std::list<object *> object_list;
    object_list *ht_;
};

}
