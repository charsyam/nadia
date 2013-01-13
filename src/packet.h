#pragma once

#include <list>
#include <string>

namespace nadia {

class Packet 
{
public:
    enum{ DEFAULT_SIZE = 10240 };
    packet( int _block_size = DEFAULT_SIZE ) : block_size_(_block_size), block_(NULL), 
        block_count_(1), length_(0), current_length_(0)
    {
        block_ = new char[_block_size];
        queue_.push_back(block_);
    }

    ~packet() {
        for( int i = 0; i < block_count_; i++ ) {
            delete [] queue_[i];
        }
    }

    int reserved() { 
        return block_size_ - current_length_; 
    }

    int length() {
        return length_;
    }

    int add( int _length ) {
        length_ += _length;
        current_length_ += _length;
    }

    void check_and_expand() {
        if( current_length_ == block_size_ ) {
            std::cout << "new alloc : " << count() << std::endl;
            alloc();
        } 
    }

    int block_size() {
        return block_size_;
    }

    int count() {
        return block_count_;
    }

    char *get(int _idx) {
        return &queue_[_idx][0];
    }

    char ch(int _idx) {
        int block_num = _idx/block_size_;
        int pos = _idx%block_size_;

        return queue_[block_num][pos];
    }

    char *current() {
        return &block_[current_length_];
    }

    void split_packet(int _length, Packet* _new_packet) {
        if( length() == 0 || length() <= _length )
        {
            return;
        }

        int size = length() - _length;
        if( size > 0 ) {
            int block_idx = _length / block_size_;
            char *ptr = get(block_idx);
            memcpy( _new_packet->current(), ptr, size );
            _new_packet->add( size );
        }
    }

private:
    void alloc() {
        block_ = new char[block_size_];
        queue_.push_back(block_);
        current_length_ = 0;
        block_count_++;
    }

private:
    std::vector<char *> queue_;
    char *block_;
    int block_size_;
    int block_count_;
    int capacity_;
    int length_;
    int current_length_;
};

}
