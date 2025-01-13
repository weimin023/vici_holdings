#include <iostream>
#include <array>

constexpr int getDayOfWeek(int year, int month, int day) {
    if (month <= 0 || month > 12) return -1;

    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int c = year / 100;
    int y = year % 100;

    int w = (y + y / 4 + c / 4 - 2 * c + (26 * (month + 1)) / 10 + day) % 7 - 1;
    w = (w % 7 + 7) % 7;

    return w;
}

constexpr bool is_ltd(int year, int month, int day) {
    constexpr std::array<int, 12> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    auto daysInMonthAdjusted = daysInMonth;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonthAdjusted[1] = 29;
    }

    int firstDay = getDayOfWeek(year, month, 1);
    int firstWedOffset = (3 - firstDay + 7) % 7;
    int thirdWed = 1 + firstWedOffset + 14;

    if (thirdWed > daysInMonthAdjusted[month - 1]) return false;

    return day == thirdWed;
}

int main() {
    std::cout<<is_ltd(2025, 1, 15)<<std::endl;
    std::cout<<is_ltd(2025, 2, 19)<<std::endl;
    std::cout<<is_ltd(2025, 3, 19)<<std::endl;
    std::cout<<is_ltd(2025, 3, 20)<<std::endl;
    std::cout<<is_ltd(2024, 7, 17)<<std::endl;
    std::cout<<is_ltd(2024, 9, 18)<<std::endl;
    std::cout<<is_ltd(2024, 9, 1)<<std::endl;

    std::cout<<is_ltd(2028, 3, 15)<<std::endl;
    std::cout<<is_ltd(2028, 3, 16)<<std::endl;
    return 0;
}