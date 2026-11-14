#pragma once
#include <algorithm>
#include <cctype>
#include <string>

class Plain {
public:
    explicit Plain(std::string s) : value_(std::move(s)) {}
    std::string myValue() const { return value_; }
private:
    std::string value_;
};

class Reversed {
public:
    explicit Reversed(std::string s) : value_(s.rbegin(), s.rend()) {}
    std::string myValue() const { return value_; }
private:
    std::string value_;
};

class Upper {
public:
    explicit Upper(std::string s) : value_(std::move(s)) {}
    std::string myValue() const {
        std::string r = value_;
        std::transform(r.begin(), r.end(), r.begin(),
                       [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
        return r;
    }
private:
    std::string value_;
};

class Constant {
public:
    std::string myValue() const { return "const"; }
};

class AsciiCodes {
public:
    explicit AsciiCodes(std::string s) : value_(std::move(s)) {}
    std::string myValue() const {
        std::string r = "[";
        for (std::size_t i = 0; i < value_.size(); ++i) {
            if (i) r += ' ';
            r += std::to_string(static_cast<unsigned char>(value_[i]));
        }
        return r + "]";
    }
private:
    std::string value_;
};
