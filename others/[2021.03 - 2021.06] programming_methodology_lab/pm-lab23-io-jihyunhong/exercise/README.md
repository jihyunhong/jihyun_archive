430.211 프로그래밍 방법론 : Input and output (I/O)
========================================================
담당 조교 : 김종민\
이메일 : jongmin.kim@scale.snu.ac.kr\
조교 통합 메일: pm@scale.snu.ac.kr\
2020년 5월 21일 금요일 

## 실습 (IMDb parsing)

인터넷 영화 데이터베이스 (Internet Movie Database, 약칭 IMDb)는 영화, 배우, 텔레비전 드라마, 비디오 게임 등에 관한 정보를 제공하는 온라인 데이터베이스입니다. 
IMDb에서 역대 영화 top 250개의 데이터를 크롤링한 것이 "imdb\_top250.txt"입니다.

이 input 파일에서 Christopher Nolan 감독의 작품만 선정하여 출력하는 것이 이번 실습입니다.

input 파일은 각 줄이 영화 한 편이며, 순위/영화제목/점수/감독/배우들로 파일이 써져있습니다.

이 파일을 line by line으로 읽어 감독이 "Christopher Nolan"일 경우 output file인 nolan.txt에 주어진 형식으로 출력하면 됩니다.

출력 형식 : 순위(width: 3, 오른쪽 정렬) << "|" << 영화제목(width: 25, 왼쪽 정렬) << "|" << 점수(소수점 2자리까지 출력)

* ```using namespace std;```를 사용하셔도 됩니다.

### 힌트 (실행의 예시)

1. while(getline()) 의 형식으로 input파일의 한 line씩 받습니다.

2. 이 line을 stringstream에 넣습니다.

3. 순위, 영화제목, 점수, 감독에 대해서 data를 만듭니다.

4. stringstream에 들어있는 line을 getline에서 delimiter '/'를 이용하여 각 data들을 할당합니다.
  * ex) ```std::getline(ss, title, '/');```
  * getline으로 값을 할당할 때는 string만 사용가능합니다.

5. 순위와 점수는 int와 double로 받는 것이 편하므로, string으로 받은 값을 std::stoi와 std::stod를 통해 int와 double로 바꿔줍니다.
  * 이번 실습에서 순위는 그대로 string으로 끝까지 쓰셔도 됩니다.

6. 한 줄에 대한 작업이 끝났으면 stringstream을 비워줘야합니다. 아니면 매번 쌓입니다.
  * ex) ```ss.str("")```

7. 감독의 data가 "Christopher Nolan"인지 확인을 한 후, 맞다면 output file에 출력형식에 맞게 출력합니다.

8. 2~7번 과정은 while문을 통해 매 line마다 반복됩니다.


### 출력 파일 (nolan.txt)
```
  4|The Dark Knight          |8.97
 13|Inception                |8.72
 30|Interstellar             |8.53
 46|The Prestige             |8.46
 55|Memento                  |8.42
 71|The Dark Knight Rises    |8.33
129|Batman Begins            |8.19
```

* 위와 같은 결과가 출력되어야 합니다.

* shell에서 다음 command로 answer.txt와 일치하는지 확인하세요.
```shell
diff -s answer.txt nolan.txt
```





