#include "student.h"

int main(void)
{
    int menu;
    Student student;
    while (1)
    {
        std::cout << std::endl << "Select Menu." << std::endl;
        std::cout << "1. Student Name , 2. Write Scores , 3. Check Scores, 4. Exit: ";
        std::cin >> menu;

        if (menu == 1) // 1. Student Name 
        {
            std::string name;
            std::cout << "Write student's name : ";
            std::cin >> name;
            student.setStudentName(name.c_str());
        }
        else if (menu == 2) // 2. Write Scores
        {
            int attendScore, projectScore, finalExamScore;
            std::cout << "Write your Scores" << std::endl;
            std::cout << "AttendScore(0~20) = ";
            std::cin >> attendScore;
            std::cout << "projectScore(0~40) = ";
            std::cin >> projectScore;
            std::cout << "finalExamScore(0~40) = ";
            std::cin >> finalExamScore;
            student.setScores(attendScore, projectScore, finalExamScore);
        }
        else if (menu == 3) // 3. Check Scores
        {
            student.printScores();
        }
        else if (menu == 4) // 4. Exit
            break;
        else {
            std::cout << "wrong number. please write a correct number" << std::endl;
        }
    }
    return 0;
}
