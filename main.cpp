#include <iostream>
#include <fstream>
#include <string>
#include "BigInt.h"


/*
1234.5678
1234.567897

123456.78967
1234.56789

123456.7897
1234.78987
*/


std::string mod(std::string n1, std::string n2){
    int d1 = 0, d2 = 0;
    if (n1.find('.') != std::string::npos){
        d1 = n1.length() - n1.find('.') - 1;
        n1.erase(n1.find('.'), 1);
    }
    std::cout << d1 << '\n';
    if (n2.find('.') != std::string::npos){
        d2 = n2.length() - n2.find('.') - 1;
        n2.erase(n2.find('.'), 1);
    }
    std::cout << d2 << '\n';


    if (d1 > d2)
        for (int i = 0; i < d1 - d2; ++i){
            n2 = n2 + '0';
        }
    std::cout << n2 << '\n';
    if(d2 > d1)
        for (int i = 0; i < d2 - d1; ++i){
            n1 = n1 + '0';
        }
    std::cout << n1 << '\n';


    BigInt a = BigInt(n1), b = BigInt(n2);
    std::cout << a << ' ' << b << '\n' << '\n';
    while (b < a){
        a = a - b;
        std::cout << a << '\n';
    }

    std::string res = std::string(a);
    res.insert(res.length() - std::max(d1, d2), ".");
    return res;

}

int main(){

    std::string n1, n2;
    std::ifstream fi("input", std::ifstream::in);
    fi >> n1 >> n2;
    fi.close();
    std::cout << '\n' << n1 << ' ' << n2 << '\n';
    std::string res = mod(n1, n2);

    std::ofstream fo("output", std::ofstream::out);
    fo << res;
    fo.close();

    return 0;
}