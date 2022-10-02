#pragma once

#include <cstdint>
#include <cstdio>
#include <array>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

namespace std {
/**
 * @brief std::hash definition for the std::array
 * @details implemented using boost::hash_range from boost/container_hash/hash.hpp
 * @tparam T Array's elements type
 * @tparam N Size of the array
 * @param arr Array
 */
template<typename T, size_t N>
struct hash<std::array<T, N>> {
    std::size_t operator()(const std::array<T, N>& arr) const {
        return boost::hash_range(arr.begin(), arr.end());
    }
};
}  // namespace std

template<size_t Dimension, typename T, T DefaultValue>
class Matrix {
 public:
    using KeyType = std::array<T, Dimension>;
    using ValueType = T;

    class Submatrix {
     public:
        explicit Submatrix(Matrix* matrix) : matrix_(matrix) {}

        Submatrix& operator[] (size_t idx) {
            assert(idx_ < Dimension);

            key_[idx_++] = idx;
            return *this;
        }

        Submatrix& operator= (ValueType value) {
            assert(idx_ == Dimension);

            matrix_->setValueAt(key_, value);
            return *this;
        }

        operator ValueType() const {
            assert(idx_ == Dimension);

            return matrix_->getValueAt(key_);
        }

     private:
        KeyType key_;
        size_t idx_{0};
        Matrix* matrix_;
    };

 public:
    Submatrix operator[] (size_t idx) {
        Submatrix sub_mat(this);
        return sub_mat[idx];
    }

    ValueType getValueAt(const KeyType& key) const {
        if (!storage_.count(key)) {
            return DefaultValue;
        }

        return storage_.at(key);
    }

    void setValueAt(const KeyType& key, ValueType value) {
        storage_[key] = value;
    }

    size_t getSize() const {
        return storage_.size();
    }

    auto begin() const {
        return storage_.begin();
    }

    auto end() const {
        return storage_.end();
    }

 private:
    std::unordered_map<KeyType, ValueType> storage_;
};
