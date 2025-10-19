//
// Created by alice on 19.10.2025.
//
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

class IPv4 {
private:
    std::uint8_t part_1;
    std::uint8_t part_2;
    std::uint8_t part_3;
    std::uint8_t part_4;

public:
    IPv4() : part_1(0), part_2(0), part_3(0), part_4(0) {}

    IPv4(std::uint8_t p1, std::uint8_t p2, std::uint8_t p3, std::uint8_t p4)
            : part_1(p1), part_2(p2), part_3(p3), part_4(p4) {}

    IPv4& operator++() {
        if (part_4 < 255) {
            ++part_4;
        } else {
            part_4 = 0;
            if (part_3 < 255) {
                ++part_3;
            } else {
                part_3 = 0;
                if (part_2 < 255) {
                    ++part_2;
                } else {
                    part_2 = 0;
                    if (part_1 < 255) {
                        ++part_1;
                    } else {
                        part_1 = 255;
                        part_2 = 255;
                        part_3 = 255;
                        part_4 = 255;
                    }
                }
            }
        }
        return *this;
    }

    IPv4 operator++(int) {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    IPv4& operator--() {
        if (part_4 > 0) {
            --part_4;
        } else {
            part_4 = 255;
            if (part_3 > 0) {
                --part_3;
            } else {
                part_3 = 255;
                if (part_2 > 0) {
                    --part_2;
                } else {
                    part_2 = 255;
                    if (part_1 > 0) {
                        --part_1;
                    } else {
                        part_1 = 0;
                        part_2 = 0;
                        part_3 = 0;
                        part_4 = 0;
                    }
                }
            }
        }
        return *this;
    }

    IPv4 operator--(int) {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
        return lhs.part_1 == rhs.part_1 &&
               lhs.part_2 == rhs.part_2 &&
               lhs.part_3 == rhs.part_3 &&
               lhs.part_4 == rhs.part_4;
    }

    friend bool operator!=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
        if (lhs.part_1 != rhs.part_1) return lhs.part_1 < rhs.part_1;
        if (lhs.part_2 != rhs.part_2) return lhs.part_2 < rhs.part_2;
        if (lhs.part_3 != rhs.part_3) return lhs.part_3 < rhs.part_3;
        return lhs.part_4 < rhs.part_4;
    }

    friend bool operator>(const IPv4& lhs, const IPv4& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const IPv4& lhs, const IPv4& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
        os << static_cast<int>(ip.part_1) << '.'
           << static_cast<int>(ip.part_2) << '.'
           << static_cast<int>(ip.part_3) << '.'
           << static_cast<int>(ip.part_4);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        int p1, p2, p3, p4;
        char d1, d2, d3;

        if (is >> p1 >> d1 >> p2 >> d2 >> p3 >> d3 >> p4) {
            if (d1 == '.' && d2 == '.' && d3 == '.' &&
                p1 >= 0 && p1 <= 255 &&
                p2 >= 0 && p2 <= 255 &&
                p3 >= 0 && p3 <= 255 &&
                p4 >= 0 && p4 <= 255) {
                ip.part_1 = static_cast<std::uint8_t>(p1);
                ip.part_2 = static_cast<std::uint8_t>(p2);
                ip.part_3 = static_cast<std::uint8_t>(p3);
                ip.part_4 = static_cast<std::uint8_t>(p4);
            } else {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }
};

int main() {

    IPv4 ip1;
    std::cout << "Default IP: " << ip1 << std::endl;

    IPv4 ip2(192, 168, 1, 1);
    std::cout << "Custom IP: " << ip2 << std::endl;

    IPv4 ip3(192, 168, 1, 254);
    std::cout << "Original: " << ip3 << std::endl;
    std::cout << "Prefix ++: " << ++ip3 << std::endl;
    std::cout << "Postfix ++: " << ip3++ << std::endl;
    std::cout << "After postfix ++: " << ip3 << std::endl;

    IPv4 ip4(192, 168, 2, 1);
    std::cout << "Original: " << ip4 << std::endl;
    std::cout << "Prefix --: " << --ip4 << std::endl;
    std::cout << "Postfix --: " << ip4-- << std::endl;
    std::cout << "After postfix --: " << ip4 << std::endl;

    IPv4 ip5(10, 0, 0, 1);
    IPv4 ip6(10, 0, 0, 2);
    std::cout << ip5 << " == " << ip6 << ": " << (ip5 == ip6) << std::endl;
    std::cout << ip5 << " < " << ip6 << ": " << (ip5 < ip6) << std::endl;
    std::cout << ip5 << " > " << ip6 << ": " << (ip5 > ip6) << std::endl;

    IPv4 ip7;
    std::cout << "Enter IP address xxx.xxx.xxx.xxx: ";
    std::cin >> ip7;
    if (std::cin.fail()) {
        std::cout << "Invalid input!" << std::endl;
        std::cin.clear();
    } else {
        std::cout << "You entered: " << ip7 << std::endl;
    }

    return 0;
}