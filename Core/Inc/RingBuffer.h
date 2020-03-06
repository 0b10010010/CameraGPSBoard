/*
 * circularBuffer.h
 *
 *  Created on: Feb 23, 2020
 *      Author: alexk
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <stdint.h>

#define PACKED __attribute__((packed))

#ifdef __cplusplus
class RingBuffer {
public:
	RingBuffer(uint32_t size);
	~RingBuffer(void);

	// Returns the number of bytes received in RX buffer
	uint32_t available(void) const;

	void clear(void);

	uint32_t space(void) const;

    // true if available() is zero
    bool empty(void) const;

    // write bytes to ringbuffer. Returns number of bytes written
    uint32_t write(const uint8_t *data, uint32_t len);

    // read bytes from ringbuffer. Returns number of bytes read
    uint32_t read(uint8_t *data, uint32_t len);

    // read a byte from ring buffer. Returns true on success, false otherwise
    bool read_byte(uint8_t *data);

    /*
      update bytes at the read pointer. Used to update an object without
      popping it
    */
    bool update(const uint8_t *data, uint32_t len);

    // return size of ringbuffer
    uint32_t get_size(void) const { return size; }

    // set size of ringbuffer, caller responsible for locking
    bool set_size(uint32_t size);

    // advance the read pointer (discarding bytes)
    bool advance(uint32_t n);

    // Returns the pointer and size to a contiguous read of the next available data
    const uint8_t *readptr(uint32_t &available_bytes);

    // peek one byte without advancing read pointer. Return byte
    // or -1 if none available
    int16_t peek(uint32_t ofs) const;

    /*
      read len bytes without advancing the read pointer
    */
    uint32_t peekbytes(uint8_t *data, uint32_t len);

    // Similar to peekbytes(), but will fill out IoVec struct with
    // both parts of the ring buffer if wraparound is happening, or
    // just one part. Returns the number of parts written to.
    struct IoVec {
        uint8_t *data;
        uint32_t len;
    };
    uint8_t peekiovec(IoVec vec[2], uint32_t len);

    // Reserve `len` bytes and fills out `vec` with both parts of the
    // ring buffer (if wraparound is happening), or just one contiguous
    // part. Returns the number of `vec` elements filled out. Can be used
    // with system calls such as `readv()`.
    //
    // After a call to 'reserve()', 'write()' should never be called
    // until 'commit()' is called!
    uint8_t reserve(IoVec vec[2], uint32_t len);

    /*
     * "Releases" the memory previously reserved by 'reserve()' to be read.
     * Committer must inform how many bytes were actually written in 'len'.
     */
    bool commit(uint32_t len);


private:
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint8_t *buf;
};
#endif
#endif /* INC_CIRCULARBUFFER_H_ */
