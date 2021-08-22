#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
  std::ifstream inFile;
  std::ofstream outFile;

  inFile.open("imdb_top250.txt");
  outFile.open("nolan.txt");

  if (!inFile)
  {
    std::cerr << "Couldn’t open input file\n";
    exit(1);
  }

  if (!outFile)
  {
    std::cerr << "Couldn’t open output file\n";
    exit(1);
  }

  std::string line;
  std::stringstream ss;

  /* 
    Input file에서 Christopher Nolan 감독의 작품을 선별하여 순위, 영화제목, 점수를 출력하세요.
    answer.txt와 똑같은 결과를 nolan.txt에  출력하세요.

    string을 int로 바꿀 때는std::stoi(string), double로 바꿀 때는 std::stod(string)을 쓰는 것을 추천합니다.
    출력의 크기(width)는 순위는 3, 영화제목은 25이고 점수는 따로 width를 지정하지 않아도 됩니다.
    순위는 오른쪽 정렬, 영화제목은 왼쪽 정렬, 그리고 점수는 소숫점 아래 둘째짜리까지 출력하세요.
    각 항목은 '|' 기호로 구분합니다.
  */

  // (To Do) Implement here
  if (inFile.is_open()){
    while (!inFile.eof()){
      std::getline(inFile, line);
      ss << line;
      //std::cout << ss.str() << std::endl;
      
      std::string data;
        
      // 1. 순위
      std::getline(ss, data, '/');
      int rank = std::stoi(data);
      //std::cout << rank << ' ';
        
      // 2. 영화제목
      std::getline(ss, data, '/');
      std::string movie_name = data;
      //std::cout << movie_name << ' ';
        
      // 3. 점수
      std::getline(ss, data, '/');
      double score = std::stod(data);
      //std::cout << score << ' ';
        
      // 4. 감독
      std::getline(ss, data, '/');
      std::string director = data;
      //std::cout << director << std::endl;
       
      if (director == "Christopher Nolan") {
        outFile << std::setw(3) << std::right << rank << '|' << std::setw(25) << std::left << movie_name  << '|' << std::fixed << std::setprecision(2) << score << '\n';
      }
        
      ss.str("");
    }
  }

  inFile.close();
  outFile.close();

  return 0;
}