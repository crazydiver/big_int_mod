//
// Created by Ivan Gorbachev on 24.10.2022.
//

#include "BigInt.h"



BigInt::BigInt() {
    this->_is_negative = false;
}

BigInt::BigInt(std::string str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_is_negative = true;
        }
        else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        this->_remove_leading_zeros();
    }
}

void BigInt::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}
bool operator <(const BigInt& left, const BigInt& right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    }
    else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        }
        else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

const BigInt operator +(BigInt left, const BigInt& right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right._is_negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= BigInt::BASE;
        if (carry != 0) left._digits[i] -= BigInt::BASE;
    }

    return left;
}

BigInt::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

bool operator ==(const BigInt& left, const BigInt& right) {
    // числа разных знаков точно не равны
    if (left._is_negative != right._is_negative) return false;
    // поскольку у нас два представления нуля, нужно это особо обработать
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }
    // так как у нас нет ведущих нулей, то в числах должно быть одинаковое количество цифр (разрядов)
    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

const BigInt operator -(BigInt left, const BigInt& right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += BigInt::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

const BigInt BigInt::operator -() const {
    BigInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}