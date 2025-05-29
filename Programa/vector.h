#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <memory>

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

    // TODO: insert, erase, assign, emplace, emplace_back, operator==, operator!=, operator<, operator>, operator<=, operator>= ir kt.
};

#endif // VECTOR_H