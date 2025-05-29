#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector> // tik palyginimui

template <typename T>
class Vector {
public:
    // Member types
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    pointer data_;
    size_type sz_;
    size_type cap_;

    void reallocate(size_type new_cap) {
        pointer new_data = new value_type[new_cap];
        for (size_type i = 0; i < sz_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        cap_ = new_cap;
    }

public:
    // Constructors
    Vector() : data_(nullptr), sz_(0), cap_(0) {}
    Vector(size_type n, const T& val = T()) : data_(new T[n]), sz_(n), cap_(n) {
        std::fill(data_, data_ + n, val);
    }
    Vector(std::initializer_list<T> il) : Vector(il.size()) {
        std::copy(il.begin(), il.end(), data_);
    }
    Vector(const Vector& other) : data_(new T[other.cap_]), sz_(other.sz_), cap_(other.cap_) {
        std::copy(other.data_, other.data_ + sz_, data_);
    }
    Vector(Vector&& other) noexcept : data_(other.data_), sz_(other.sz_), cap_(other.cap_) {
        other.data_ = nullptr; other.sz_ = 0; other.cap_ = 0;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            sz_ = other.sz_;
            cap_ = other.cap_;
            data_ = new T[cap_];
            std::copy(other.data_, other.data_ + sz_, data_);
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            sz_ = other.sz_;
            cap_ = other.cap_;
            other.data_ = nullptr; other.sz_ = 0; other.cap_ = 0;
        }
        return *this;
    }
    ~Vector() { delete[] data_; }

    // Element access
    reference operator[](size_type i) { return data_[i]; }
    const_reference operator[](size_type i) const { return data_[i]; }
    reference at(size_type i) {
        if (i >= sz_) throw std::out_of_range("Vector::at");
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= sz_) throw std::out_of_range("Vector::at");
        return data_[i];
    }
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference back() { return data_[sz_ - 1]; }
    const_reference back() const { return data_[sz_ - 1]; }
    pointer data() noexcept { return data_; }
    const_pointer data() const noexcept { return data_; }

    // Iterators
    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    iterator end() noexcept { return data_ + sz_; }
    const_iterator end() const noexcept { return data_ + sz_; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    // Capacity
    bool empty() const noexcept { return sz_ == 0; }
    size_type size() const noexcept { return sz_; }
    size_type capacity() const noexcept { return cap_; }
    void reserve(size_type n) {
        if (n > cap_) reallocate(n);
    }
    void shrink_to_fit() {
        if (sz_ < cap_) reallocate(sz_);
    }

    // Modifiers
    void clear() noexcept { sz_ = 0; }
    void push_back(const T& val) {
        if (sz_ == cap_) reserve(cap_ == 0 ? 1 : cap_ * 2);
        data_[sz_++] = val;
    }
    void push_back(T&& val) {
        if (sz_ == cap_) reserve(cap_ == 0 ? 1 : cap_ * 2);
        data_[sz_++] = std::move(val);
    }
    void pop_back() {
        if (sz_ > 0) --sz_;
    }
    void resize(size_type n, const T& val = T()) {
        if (n > cap_) reserve(n);
        if (n > sz_) std::fill(data_ + sz_, data_ + n, val);
        sz_ = n;
    }
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(sz_, other.sz_);
        std::swap(cap_, other.cap_);
    }

    // Insert element at position
    iterator insert(const_iterator pos, const T& value) {
        size_type idx = pos - data_;
        if (sz_ == cap_) reserve(cap_ == 0 ? 1 : cap_ * 2);
        for (size_type i = sz_; i > idx; --i)
            data_[i] = std::move(data_[i - 1]);
        data_[idx] = value;
        ++sz_;
        return data_ + idx;
    }

    // Erase element at position
    iterator erase(const_iterator pos) {
        size_type idx = pos - data_;
        for (size_type i = idx; i + 1 < sz_; ++i)
            data_[i] = std::move(data_[i + 1]);
        --sz_;
        return data_ + idx;
    }

    // Assign n copies of value
    void assign(size_type n, const T& value) {
        if (n > cap_) reserve(n);
        std::fill(data_, data_ + n, value);
        sz_ = n;
    }

    // Assign from initializer_list
    void assign(std::initializer_list<T> il) {
        if (il.size() > cap_) reserve(il.size());
        std::copy(il.begin(), il.end(), data_);
        sz_ = il.size();
    }

    // Assign from iterator range
template <typename InputIt>
typename std::enable_if<!std::is_integral<InputIt>::value, void>::type
assign(InputIt first, InputIt last) {
    size_type n = std::distance(first, last);
    if (n > cap_) reserve(n);
    std::copy(first, last, data_);
    sz_ = n;
    }

    // Emplace back
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (sz_ == cap_) reserve(cap_ == 0 ? 1 : cap_ * 2);
        new (data_ + sz_) T(std::forward<Args>(args)...);
        ++sz_;
    }

    // Insert range [first, last) at position
    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type idx = pos - data_;
        size_type count = std::distance(first, last);
        if (sz_ + count > cap_) reserve(std::max(cap_ * 2, sz_ + count));
        for (size_type i = sz_ + count; i-- > idx + count; )
            data_[i] = std::move(data_[i - count]);
        for (size_type i = 0; i < count; ++i)
            data_[idx + i] = *(first++);
        sz_ += count;
        return data_ + idx;
    }

    // Insert initializer_list at position
    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    // Erase range [first, last)
    iterator erase(const_iterator first, const_iterator last) {
        size_type idx_first = first - data_;
        size_type idx_last = last - data_;
        size_type count = idx_last - idx_first;
        for (size_type i = idx_first; i + count < sz_; ++i)
            data_[i] = std::move(data_[i + count]);
        sz_ -= count;
        return data_ + idx_first;
    }

    // Emplace element at position
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_type idx = pos - data_;
        if (sz_ == cap_) reserve(cap_ == 0 ? 1 : cap_ * 2);
        for (size_type i = sz_; i > idx; --i)
            data_[i] = std::move(data_[i - 1]);
        new (data_ + idx) T(std::forward<Args>(args)...);
        ++sz_;
        return data_ + idx;
    }

    // get_allocator
    std::allocator<T> get_allocator() const { return std::allocator<T>(); }

    // Comparison operators
    bool operator==(const Vector& other) const {
        if (sz_ != other.sz_) return false;
        for (size_type i = 0; i < sz_; ++i)
            if (!(data_[i] == other.data_[i])) return false;
        return true;
    }
    bool operator!=(const Vector& other) const { return !(*this == other); }
    bool operator<(const Vector& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }
    bool operator>(const Vector& other) const { return other < *this; }
    bool operator<=(const Vector& other) const { return !(other < *this); }
    bool operator>=(const Vector& other) const { return !(*this < other); }
};

// Non-member swap
template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept {
    a.swap(b);
}

#endif // VECTOR_H