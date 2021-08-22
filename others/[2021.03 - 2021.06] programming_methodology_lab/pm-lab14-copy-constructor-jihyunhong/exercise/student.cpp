#include "student.h"
#include <iostream>
using namespace std;

char* Student::getStudentName(){
    return studentName;
} 

// delete -> 잘못 입력시 다시 입력하기 위함
void Student::setStudentName(const char* studentName){  // 1st input: hong, second input: hongji (in this case, this->studentName에 hong이 존재 그리서 지워야함)
    // this->student에 값이 있으면 지워주기
    if (this->studentName){
        delete[]this->studentName;
    }

    // 만약 parameter에 값이 들어오면 new로 동적 할당
    if (studentName){
        int len = strlen(studentName); 
        this->studentName = new char[len+1];  // dynamic allocation을 통해 heap에 할당
        strcpy(this->studentName, studentName);
    }
    else{   // parameter가 비어있으면 nullptr할당
        this->studentName = nullptr;
    }
}

void Student::setScores(int attendScore, int projectScore, int finalExamScore){
    if (attendScore < 0 || attendScore > 20 || projectScore < 0 || projectScore > 40 ||
        finalExamScore < 0 || finalExamScore > 40){
            cout << "Invalid scores." << endl;
    }
    else{
        this->attendScore = attendScore;
        this->projectScore = projectScore;
        this->finalExamScore = finalExamScore;
    }
}

int Student::getAttendScore(){
    return attendScore;
}

int Student::getProjectScore(){
    return projectScore;
}

int Student::getFinalExamScore(){
    return finalExamScore;
}

int Student::getTotalScore(){
    this->totalScore = attendScore + projectScore + finalExamScore;
    return totalScore;
}

void Student::printScores(){
    cout << "Name : " << getStudentName() << endl;
    cout << "AttendScore : " << getAttendScore() << endl;
    cout << "ProjectScore : " << getProjectScore() << endl;
    cout << "FinalExamScore : " << getFinalExamScore() << endl;
    cout << "TotalScore : " << getTotalScore() << endl;
}

Student::~Student(){
    delete []studentName;
}