#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <cstring>

class Student
{
private:
    char* studentName = nullptr;  // 학생 이름
    int attendScore;    // 출석 점수 최대 20점
    int projectScore;   // 프로젝트 점수 최대 40점
    int finalExamScore; // 기말고사 점수 최대 40점
    int totalScore;

public:
    char* getStudentName();
    void setStudentName(const char* studentName);
    void setScores(int attendScore, int projectScore, int finalExamScore);
    int getAttendScore();
    int getProjectScore();
    int getFinalExamScore();
    int getTotalScore();
    void printScores();
    ~Student();
};

#endif