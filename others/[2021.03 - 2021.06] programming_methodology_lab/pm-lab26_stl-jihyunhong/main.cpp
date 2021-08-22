#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

struct Student {
  string name;
  string university;
  int testScore;

  bool operator<(const Student &s) const {
    if (name == s.name)
      return testScore < s.testScore;
    return name < s.name;
  }
};

int main() {
  vector<Student> studentVector;
  ifstream ifs{"grades.txt"};
  string line, name, university;
  int testScore;
  vector<string> strbuf;
  while (getline(ifs, line)) {
    stringstream ss(line);
    ss >> name >> university >> testScore;
    Student student{name, university, testScore};
    studentVector.push_back(student);
  }

  vector<int> SNUUniversityScoreVector;
  set<Student> KoreaUniversityScoreSet;
  map<string, int> YonseiUniversityMap;

  // Implement here
  // Insert Student data to container vector, set, map.
  for (auto i : studentVector) {
    if (i.university == "SNU") {
      SNUUniversityScoreVector.push_back(i.testScore);
    } else if (i.university == "Korea") {
      KoreaUniversityScoreSet.insert(i);
    } else if (i.university == "Yonsei") {
      YonseiUniversityMap.insert(std::pair<string, int>(i.name, i.testScore));
    }
  }

  // Implement here
  // Caculate SNU University's Total score
  int SNUTotalScore{0};
  SNUTotalScore = accumulate(SNUUniversityScoreVector.begin(), SNUUniversityScoreVector.end(), 0);

  // Implement here
  // Caculate Korea University's Total score
  int KoreaTotalScore{0};
  for (auto i : KoreaUniversityScoreSet){
    KoreaTotalScore += i.testScore;
  }

  // Implement here
  // Caculate Yonsei University's Total score
  int YonseiTotalScore{0};
  for (auto i : YonseiUniversityMap){
    YonseiTotalScore += i.second;
  }

  cout << "SNUTotalScore : " << SNUTotalScore << endl;
  cout << "KoreaTotalScore : " << KoreaTotalScore << endl;
  cout << "YonseiTotalScore : " << YonseiTotalScore << endl;
  return 0;
}
