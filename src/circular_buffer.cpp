/**
* circular_buffer.cpp
* @brief Implemets a generic circular buffer
* @author Dylan Knott
**/

#include <circular_buffer.hpp>
#include <cstring>

    /**
     * Returns whether the buffer is full or not
    */
    template <typename T>
    bool CircularBuffer<T>::is_full(void) {
        return curr_size = max_size;
    }

    /**
     * Returns whether the buffer is empty or not
    */
    template <typename T>
    bool CircularBuffer<T>::is_empty(void) {
        return (produce == (consume - 1) || (produce == 0 && consume == max_size));
    }
    
    /**
     * Returns the circular buffer as an array of values of size len
     * @param buffer Buffer to populate
     * @param len number of array elements to copy
    */
    template <typename T>
    void CircularBuffer<T>::to_array(T *dest_buffer, uint16_t len) {
        uint16_t start_count = consume;
        uint16_t end_count = max_size - consume;
        memcpy(&buff[consume], &dest_buffer[0], end_count * sizeof(T));
        memcpy(&buff[0], &dest_buffer[end_count], start_count * sizeof(T));
    }
    
    /**
     * Adds value to the end of the circular buffer
     * @param val value to add
    */
    template <typename T>
    bool CircularBuffer<T>::add(T *val) {
        if (is_full()) {
            return false;
        }

        //There is space, add to buffer
        std::memcpy(val, buff[produce], sizeof(T));
        produce = (produce + 1) % max_size;
        return true;
    }
    
    /**
     * Pops off a value from the front of circular buffer
     * @return Value popped from the front of the buffer
    */
    template <typename T>
    bool CircularBuffer<T>::pop(T *val) {
        if (is_empty()) {
            return false;
        }
        std::memcpy(buff[consume], val, sizeof(T));
        consume = (consume + 1) % max_size;
        return true;
    }

    /**
     * Shifts all elements of the circular buffer in a clockwise direction ([max_size - 1] -> [0])
     * @param shift_amount number of indeces to shift the values
     * @param reversed if true, shifts the buffer CCW, ([0] -> [max_size-1])
    */
    template <typename T>
    void CircularBuffer<T>::shift(bool reversed) {
        if (reversed) {
            produce = (produce + 1) % max_size;
            consume = (consume + 1) % max_size;
        }
        else {
            produce = ((produce + max_size) - 1) % max_size;
            consume = ((consume + max_size) - 1) % max_size;
        }
    }
    
    /**
     * Returns max size of the buffer
    */
    template <typename T>
    uint16_t CircularBuffer<T>::get_max_size(void) {
        return max_size;
    }