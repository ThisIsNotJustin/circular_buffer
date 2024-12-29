# Circular Buffer Implementation

This is a simple implementation of a circular (ring) buffer, allowing for efficient storage and retrieval of data in a fixed-size buffer. The circular buffer follows a FIFO principle, making it ideal for temporary data storage like in a real-time system/producer-consumer scenario.

## Features

- Fixed-size buffer: The buffer has a defined maximum capacity.
- Efficient Enqueue and Dequeue: Allows constant-time insertion and removal of data.
- Circular behavior: When the buffer reaches its maximum capacity, new elements overwrite the oldest ones.
- Error handling: Functions return error codes in cases like overflows or underflows.
- Simple API: Provides an easy-to-use interface for managing the buffer.