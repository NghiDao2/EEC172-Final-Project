/*
 * InterruptBuffer.h
 *
 *  Created on: May 8, 2025
 *      Author: daomi
 */

#ifndef INTERRUPTBUFFER_H_
#define INTERRUPTBUFFER_H_


#include <stdint.h> // For fixed-width integer types
#include <stdbool.h> // For boolean type
#include <stddef.h> // For size_t
#include <stdlib.h>


#define DEFINE_INTERRUPT_BUFFER(TYPE, NAME)                          \
    typedef struct {                                                 \
        volatile TYPE* buffer;                                       \
        volatile size_t interrupt_pointer;                           \
        size_t read_pointer;                                         \
        size_t capacity;                                             \
    } NAME;                                                          \
                                                                     \
    static inline NAME* NAME##_new(size_t capacity) {                \
        NAME* buf = malloc(sizeof(NAME));                            \
        if (buf) {                                                   \
            buf->buffer = malloc(capacity * sizeof(TYPE));           \
            buf->interrupt_pointer = 0;                              \
            buf->read_pointer = 0;                                   \
            buf->capacity = capacity;                                \
            if (!buf->buffer) {                                      \
                free(buf);                                           \
                return NULL;                                         \
            }                                                        \
        }                                                            \
        return buf;                                                  \
    }                                                                \
                                                                     \
    static inline void NAME##_free(NAME* buf) {                      \
        if (buf) {                                                   \
            if (buf->buffer) {                                       \
                free((void*)buf->buffer);                            \
            }                                                        \
            free(buf);                                               \
        }                                                            \
    }                                                                \
                                                                     \
    static inline void NAME##_push(NAME* buf, TYPE value) {          \
        if (!buf) return;                                            \
        if (buf->interrupt_pointer == buf->read_pointer) {           \
            buf->read_pointer = 0;                                   \
            buf->interrupt_pointer = 0;                              \
        }                                                            \
        if (buf->interrupt_pointer >= buf->capacity-1) {             \
            return;                                                  \
        }                                                            \
        buf->buffer[buf->interrupt_pointer] = value;                 \
        buf->interrupt_pointer++;                                    \
    }                                                                \
                                                                     \
    static inline TYPE NAME##_pop(NAME* buf) {                       \
        TYPE value = buf->buffer[buf->read_pointer];                 \
        buf->read_pointer = (buf->read_pointer + 1) % buf->capacity; \
        return value;                                                \
    }                                                                \
                                                                     \
    static inline bool NAME##_isEmpty(const NAME* buf) {             \
        if (!buf) return true;                                       \
        return buf->read_pointer >= buf->interrupt_pointer;          \
    }



#endif /* INTERRUPTBUFFER_H_ */
