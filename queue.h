#ifndef QUEUE__QUEUE_H_
#define QUEUE__QUEUE_H_

#include <optional>
#include <memory>
#include <ostream>

template<class T>
class Queue {
public:
	Queue()
		: _array(std::make_unique<T[]>(0))
		, _capacity(0)
		, _front(0)
		, _size(0) {}

	Queue(const std::initializer_list<T>& list) : Queue() {
		reserve(list.size());
		for (T item : list) {
			pushBack(item);
		}
	}

	Queue(const Queue<T>& queue) : Queue() {
		reserve(std::min(queue._capacity, queue._front + queue._size));

		for (size_t i = 0; i < queue._size; ++i) {
			pushBack(queue[i]);
		}
	}

	T& front() const {
		if (_size == 0) {
			throw std::runtime_error("count is 0");
		}

		return _array[_front];
	}

	T& back() const {
		if (_size == 0) {
			throw std::runtime_error("count is 0");
		}

		return _array[(_front + _size - 1) % _capacity];
	}

	size_t size() const {
		return _size;
	}

	size_t capacity() const {
		return _capacity;
	}

	void pushBack(T value) {
		if (_size == _capacity) {
			reserve(_capacity + 1);
		}

		_array[(_front + _size) % _capacity] = std::move(value);
		++_size;
	}

	void popFront() {
		if (_size == 0) {
			return;
		}
		_front = (_front + 1) % _capacity;
		--_size;
	}

	void reserve(size_t capacity) {
		if (capacity == 0) {
			return;
		}

		size_t newCapacity = _capacity * 2;
		if (newCapacity == 0) {
			newCapacity = 2;
		}

		while (newCapacity < capacity) {
			newCapacity *= 2;
		}

		auto newArray = std::make_unique<T[]>(newCapacity);
		for (size_t i = 0; i < _size; ++i) {
			newArray[i] = std::move(_array[(_front + i) % _capacity]);
		}
		_array = std::move(newArray);
		_capacity = newCapacity;
		_front = 0;
	}

	T& operator[](size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("index is out of range");
		}

		return _array[(_front + index) % _capacity];
	}

	bool operator==(const Queue<T>& rhs) const {
		if (_size != rhs._size) {
			return false;
		}

		for (size_t i = 0; i < _size; ++i) {
			if (operator[](i) != rhs[i]) {
				return false;
			}
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
		os << '{';
		for (size_t i = 0; i < queue._size; ++i) {
			os << queue[i];
			if (i != queue._size - 1) {
				os << ", ";
			}
		}
		os << '}';
		return os;
	}

	Queue& operator=(Queue&& queue) noexcept {
		_array = std::move(queue._array);
		_capacity = queue._capacity;
		_front = queue._front;
		_size = queue._size;
		return *this;
	}

private:
	std::unique_ptr<T[]> _array;
	size_t _capacity;
	size_t _front;
	size_t _size;
};

#endif //QUEUE__QUEUE_H_
