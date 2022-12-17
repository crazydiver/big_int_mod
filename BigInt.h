#ifndef UNTITLED2_BIGINT_H
#define UNTITLED2_BIGINT_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class BigInt {
    static const int BASE = 1000000000;

    std::vector<int> _digits;

    bool _is_negative;

    void _remove_leading_zeros();

public:
    class divide_by_zero: public std::exception {  };

    BigInt();
    BigInt(std::string);
    std::string toStr();
    friend std::ostream& operator <<(std::ostream&, const BigInt&);
    explicit operator std::string() const;
    BigInt operator -() const;
    friend bool operator ==(const BigInt&, const BigInt&);
    friend bool operator <(const BigInt&, const BigInt&);
    friend BigInt operator +(BigInt, const BigInt&);
    friend BigInt operator -(BigInt, const BigInt&);

};



#endif