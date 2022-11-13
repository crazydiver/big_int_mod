//
// Created by Ivan Gorbachev on 24.10.2022.
//

#ifndef UNTITLED2_BIGINT_H
#define UNTITLED2_BIGINT_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class BigInt {
    // основание системы счисления (1 000 000 000)
    static const int BASE = 1000000000;

    // внутреннее хранилище числа
    std::vector<int> _digits;

    // знак числа
    bool _is_negative;

    void _remove_leading_zeros();
    void _shift_right();

public:
    // класс-исключение, бросаемое при делении на ноль
    class divide_by_zero: public std::exception {  };

    BigInt();
    BigInt(std::string);

    friend std::ostream& operator <<(std::ostream&, const BigInt&);
    operator std::string() const;
    const BigInt operator -() const;
    friend bool operator ==(const BigInt&, const BigInt&);
    friend bool operator <(const BigInt&, const BigInt&);
    friend const BigInt operator +(BigInt, const BigInt&);
    friend const BigInt operator -(BigInt, const BigInt&);

};



#endif //UNTITLED2_BIGINT_H
