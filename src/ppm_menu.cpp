#include <iostream>
#include <ctime>
#include "image_menu.h"

int main() {
    std::srand(std::time(0));
    // assignment1(std::cin, std::cout);
    // return assignment2(std::cin, std::cout);
    // return four_square(std::cin, std::cout);
    return imageMenu(std::cin, std::cout);
}

// 14
// Tests: https://dixie.instructure.com/courses/589605/assignments/7069521?module_item_id=10765454
// Description: http://cit.dixie.edu/cs/3005/assignments/assignment_13_opengl/
