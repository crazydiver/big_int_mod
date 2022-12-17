#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "BigInt.h"

std::string mod(std::string n1, std::string n2){
    int d1 = 0, d2 = 0;
    if (n1.find('.') != std::string::npos){
        d1 = n1.length() - n1.find('.') - 1;
        n1.erase(n1.find('.'), 1);
    }
    if (n2.find('.') != std::string::npos){
        d2 = n2.length() - n2.find('.') - 1;
        n2.erase(n2.find('.'), 1);
    }

    if (d1 > d2)
        for (int i = 0; i < d1 - d2; ++i){
            n2 = n2 + '0';
        }
    if(d2 > d1)
        for (int i = 0; i < d2 - d1; ++i){
            n1 = n1 + '0';
        }
    std::cout << '\n'<< n1 << '\n' << n2 << '\n' << d1 << ' ' << d2 << '\n';

    BigInt a = BigInt(n1), b = BigInt(n2);
    BigInt resb = a - b;

    std::string res = std::string(resb);
    res.insert(res.length() - std::max(d1, d2), ".");
    return res;

}

int main(){

    unsigned int start_time = clock();
    std::ifstream fi;


    std::string n1, n2;
    fi.exceptions(std::fstream::badbit );
    fi.open("/Users/ivangorbachev/CLionProjects/untitled2/inp");
    if(fi.is_open()&& fi.good() )
    {
        fi >> n1 >> n2;
    }

//    std::getline(fi, n1);
//    std::getline(fi, n2);
//    246913953086394913580499.4938271372839864046913633
    fi.close();
//    std::cin >> n1 >> n2;
    std::cout << "Первое число: " << n1 << "\nВторое число: " << n2 << '\n';
    std::string res = mod(n1, n2);
    std::cout << "Результат: " << res << '\n';
    std::ofstream fo("/Users/ivangorbachev/CLionProjects/untitled2/output", std::fstream::out);
    fo << res;
    fo.close();
    std::cout << "Время работы программы: " << clock() - start_time << " мс\n\n";
    return 0;
}