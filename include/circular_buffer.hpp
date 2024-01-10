/**
* circular_buffer.hpp
* @brief Defines a generic circular buffer
* @author Dylan Knott
**/

#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cstdlib>

template <typename T>
class CircularBuffer {
public:

    /**
     * Returns whether the buffer is full or not
    */
    bool is_full(void);

    /**
     * Returns whether the buffer is empty or not
    */
    bool is_empty(void);
    
    /**
     * Returns the circular buffer as an array of values of size len
     * @param buffer Buffer to populate
     * @param len number of array elements to copy
    */
    void to_array(T *buffer, uint16_t len);
    
    /**
     * Adds value to the end of the circular buffer
     * @param val value to add
    */
    bool add(T *val);
    
    /**
     * Pops off a value from the front of circular buffer
     * @return Value popped from the front of the buffer
    */
    bool pop(T *val);

    /**
     * Shifts all elements of the circular buffer in a clockwise direction ([max_size - 1] -> [0])
     * @param shift_amount number of indeces to shift the values
     * @param reversed if true, shifts the buffer CCW, ([0] -> [max_size-1])
    */
    void shift(bool reversed);
    
    /**
     * Returns max size of the buffer
    */
    uint16_t get_max_size(void);

    CircularBuffer(void) : CircularBuffer(500) {}

    CircularBuffer(uint16_t size) {
        max_size = size;
        produce = 0;
        consume = 0;
        curr_size = 0;

        buff = (T*)std::malloc(sizeof(T) * max_size);
    }
    ~CircularBuffer(void) {
        free(buff);
    }

private:
    //Add pointer
    uint32_t produce;
    
    //Read pointer
    uint32_t consume;
    
    //Count of currently filled elements
    uint16_t curr_size;
    
    //Maximum buffer size
    uint16_t max_size;

    //Internal buffer to store values
    T *buff;
};
#endif