#pragma once

#include    <sys/types.h>
#include    <stdint.h>
#include    <string.h>

namespace nadia {

class object {
public:
    enum type {
        TYPE_STRING = 0,
        TYPE_INT = 1
    };

    object(type _type, char *_key, uint32_t _key_size,
            char *_data, uint32_t _data_size) :
        type_(_type), key_(_key), key_size_(_key_size),
        data_(_data), data_size_(_data_size) {
    }

    type get_type() {
        return type_;
    }

    char *get_key() {
        return key_;
    }

    uint32_t get_key_size() {
        return key_size_;
    }

    char *get_data() {
        return data_;
    }

    uint32_t get_data_size() {
        return data_size_;
    }

private:
    type type_;
    char *key_;
    uint32_t key_size_;
    char *data_;
    uint32_t data_size_;
    uint64_t timestamp_;    
};

}
