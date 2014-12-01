#pragma once

template <int _BUF_SIZE_>
class BufferQueue {
public:
	BufferQueue()
		:begin(0), length(0) {
	}

	bool push(
		const char* const buf,
		const size_t size) {
		
		if (size < 1 || length + size > _BUF_SIZE_)
			return false;
		if (end + size > _BUF_SIZE_) {
			size_t remain = _BUF_SIZE_ - end;
			memcpy_s(buffer + end, remain, buf, remain);
			memcpy_s(buffer, size - remain, buf, size - remain);
		}
		else {
			memcpy_s(buffer + end, size, buf, size);
		}
		length += size;
		end = (end + size) % _BUF_SIZE_;
		return true;
	}

	bool pop(
		char* const buf,
		const size_t size) {
		if (!peek(buf, size))
			return false;
		length -= size;
		begin = (begin + size) % _BUF_SIZE_;
		return true;
	}

	bool peek(
		char* const buf,
		const size_t size) const {
		if (size < 1 || length < size)
			return false;
		if (begin + size > _BUF_SIZE_) {
			size_t remain = _BUF_SIZE_ - begin;
			memcpy_s(buf, remain, buffer + begin, remain);
			memcpy_s(buf, size - remain, buffer, size - remain);
		}
		else {
			memcpy_s(buf, size, buffer + begin, size);
		}
		return true;
	}

	size_t getLength() const { return length; }
	bool isEmpty() const { return length == 0; }
	bool isFull() const { return length == _BUF_SIZE_; }

private:
	char buffer[_BUF_SIZE_];
	
	// pop할 위치: 첫 원소 위치
	size_t begin;
	// push할 위치: 마지막 원소 다음 위치
	size_t end;
	// 채워진 양
	size_t length;
};