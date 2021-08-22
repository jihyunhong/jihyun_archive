# Input and output (I/O)
담당조교 : 김종민 \
이메일 : jongmin.kim@scale.snu.ac.kr \
2021년 5월 21일 금요일

참고자료: learncpp.com Ch.23
## 1. Input and output (I/O) streams

* Input/output 기능은 C++에서 기본적으로 제공하는 것이 아닌, C++ standard library를 통해 제공됨. 여태껏 ```#include <iostream>```을 통해서 기본적인 I/O를 수행했었음.


* **Stream**: 순서대로 접근할 수 있는 Byte의 시퀀스.


* **Input Stream**: 키보드, 파일, 네트워크 등으로부터의 input(입력)들을 hold하고 있는 stream.


* **Output Stream**: 모니터, 파일, 프린터 등으로의 output(출력)들을 hold하고 있는 stream.


* 이러한 stream의 장점은 프로그래머들이 input/output device들과 무관하게 stream (인터페이스)만 알면 이런 device들과 통신할 수 있다는 것


* **istream**: C++의 input stream 관련 class. **Extraction operator (>>)** 는 stream에서 값들을 없앨 때 사용됨. 즉 프로그램이 stream에 있는 input data들을 추출하는 것.


* **ostream**: C++의 output stream 관련 class. **Insertion  operator (<<)** 는 값들을 stream에 넣을 때 사용됨. 즉 stream에 데이터를 넣으면, data consumer(output device)가 이를 사용함.


* **iostream**: Input과 output을 모두 다루는 class


* Standard streams in C++
  * **Standard stream** 이란 프로그램에 제공되는 이미 연결되어 있는 stream
  * **cin**: Standard input (주로 키보드)
  * **cout**: Standard output (주로 모니터)
  * **cerr**: Standard error, unbuffered output (주로 모니터)
  * **clog**: Standard error, buffered output (주로 모니터)

## 2. Input with istream

* **std::cin.get()**: Input stream으로 부터 하나의 character를 get함
  * 그냥 ```cin >>``` 으로는 whitespace를 얻을 수 없는데, get()은 가능


* **std::cin.getline()**: Input stream으로 부터 하나의 line을 get함
  * newline(```\n```)까지 읽을 수 있음

* **std::cin.gcount()**: 마지막으로 호출된 getline()의 charater 수를 출력

* 추가로 getline()은 ```istream & getline ( istream & is, string & s, char delimiter = ‘\n’);```의 형태로 선언되어 있음. Delimiter란 구획 문자. Default는 newline('\n')으로 한 번에 읽을 양을 구분하지만, 이를 바꿀 수 있음. 즉, 쉼표(,)를 기준으로 어떤 stringstream 혹은 file을 읽고 싶을 때 ```getline(inf, inStr, ',')```로 가능.
  * 이는 cin뿐만 아니라, stringstream, file에도 적용됨

## 3. Output with ostream and ios

* Formatting은 flag를 사용하는 것과 manipulator를 사용하는 것, 두 가지가 있음. 일반적으로는 manipulator가 더 많이 사용되고, 쓰기 쉬움. 단, flag로만 가능하거나, manipulator로만 가능한 동작들도 있음.

* **std::cout.setf()**: std::ios 의 flag들을 on

* **std::cout.unsetf()**: std::ios 의 flag들을 off


* **Manipulator**: input/output들을 formatting할 때 사용. Extraction operator (>>) 나 insertion operator (<<)와 함께 사용하여 stream을 변형시킴.


* C++ iomanip library에 포함되어 있을 수도 있음
  * ```#include <iomanip>```로 사용


* Manipulator는 기본적으로 formatting하고 싶은 값의 "**앞**"에 넣어줘야함


* 유용한 manipulators
  * std::dec
    * 값을 10진법으로
  * std::hex
    * 값을 16진법으로
  * std::fixed
    * Fixed point로 표현
    * Fixed, showpoint, scientific 관련 더 자세한 사항은 LearnCPP의 "18.3 - Output with ostream and ios"를 참고
  * std::setprecision(int)
    * 다음 floating point 숫자를 n자리 수의 precision으로 설정
    * iomanip.h에 정의되어 있음
  * std::setw(int)
    * 다음 insertion의 filed width를 n characters로 설정
    * iomanip.h에 정의되어 있음
    * 다음 하나의 output statement에만 적용됨
  * std::setfill(char)
    * setwidth-manipulated value들을 특정한 character로 채우도록 설정
    * iomanip.h에 정의되어 있음
  * std::left
    * Field width내에서 값들을 left alignment(정렬)
  * std::right
    * Field width내에서 값들의 right alignment(정렬)

* 사용 예시

```c++
#include <iostream>
#include <iomanip>

int main()
{
  std::cout << std::hex << 27 << '\n';
  // 1b
  std::cout << 28 << '\n';
  // 1c
  std::cout << std::dec << 29 << '\n';
  // 29


  std::cout << std::setprecision(2) << 123.456 << '\n';
  // 1.2e+02
  std::cout << std::setprecision(3) << 123.456 << '\n';
  // 123
  std::cout << std::setprecision(4) << 123.456 << '\n';
  // 123.5

  std::cout << std::fixed << '\n';
  std::cout << std::setprecision(2) << 123.456 << '\n';
  // 123.46
  std::cout << std::setprecision(3) << 123.456 << '\n';
  // 123.456
  std::cout << std::setprecision(4) << 123.456 << '\n';
  // 123.4560


  std::cout << -12345 << '\n';
  // -12345
  std::cout << std::setw(10) << -12345 << '\n';
  //     -12345
  std::cout << std::setw(10) << left << -12345 << '\n';
  // -12345
  std::cout << std::setw(10) << right << -12345 << '\n';
  //     -12345

  std::cout << std::setfill('*');
  std::cout << -12345 << '\n';
  // -12345
  std::cout << std::setw(10) << -12345 << '\n';
  // ****-12345
  std::cout << std::setw(10) << left << -12345 << '\n';
  // -12345****
  std::cout << std::setw(10) << right << -12345 << '\n';
  // ****-12345

}
```

## 4. Stream classes for strings

* **String Stream**
  * string으로도 << 와 >> operator들을 사용할 수 있는 stream
  * iostream처럼 직접적으로 키보드로 입력하거나, 모니터로 출력되는 것은 아님
  * ```#include <sstream>```으로 사용

* Insertion (<<) operator 혹은 str(string) function으로 stringstream에 data를 넣을 수 있음

* Extraction (>>) operator 혹은 str() function으로 stringstream에서 data를 꺼낼 수 있음
  * str()은 stream의 전체 값을 꺼내지만, >> operator는 연속된 값만 꺼냄.

* ```os.str("")``` 혹은 ```os.str(std::string{})``` 를 통해 stringstream의 buffer를 비울 수 있음.

  * 사용 예시

```c++
  #include <iostream>
  #include <sstream>

  int main()
  {
    std::stringstream os;
    os << "12345 67.89";

    std::string strValue;
    os >> strValue;

    std::string strValue2;
    os >> strValue2;

    std::cout << os.str() << '\n';
    // 12345 67.89
    std::cout << strValue << " - " << strValue2 << '\n';
    // 12345 - 67.89
  }
```


## 5. Basic file I/O

* File I/O는 일반적인 I/O와 비슷함.
  * insertion (<<) or extraction (>>) operator로 file에 data를 읽거나 씀.
  * 다만, cout, cin과 달리 프로그래머가 file stream을 직접 정해줘야함.
    * 특정한 파일과 연동시켜야 한다는 뜻

* File output (write) 예시

```c++
#include <fstream>
#include <iostream>

int main()
{
    // ofstream은 file에 write를 할 때 쓰는 class
    // "Sample.dat"라는 파일을 생성
    // 다른 디렉토리에 있는 파일을 열고 싶다면 "../../Sample.dat" 처럼 경로를 넣어주면 됨.
    std::ofstream outf{ "Sample.dat" };

    /*
    // 아래처럼 파일을 여는 경우도 일반적
    std::ofstream outf;
    outf.open("Sample.dat")
    */

    // 파일이 제대로 열렸는지 확인
    if (!outf)
    {
        // cerr을 이용하여 에러 메시지 출력 후 프로그램 종료
        std::cerr << "Uh oh, Sample.dat could not be opened for writing!" << std::endl;
        return 1;
    }

    // 파일에 두 줄을 write
    outf << "This is line 1" << '\n';
    outf << "This is line 2" << '\n';

    outf.close();

    return 0;

    // outf.close()를 하지 않았을 경우, outf가 여기서 scope를 벗어날 때 ofstream destructor가 파일을 닫음.
}
```

* File input (read) 예시

```c++
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    // ifstream은 file을 read를 할 때 쓰는 class
    // "Sample.dat"라는 파일을 열음.
    // 이 때 Sample.dat이라는 파일이 없다면 에러가 남
    // 다른 디렉토리에 있는 파일을 열고 싶다면 "../../Sample.dat" 처럼 경로를 넣어주면 됨.
    std::ifstream inf{ "Sample.dat" };

    // 파일이 제대로 열렸는지 확인
    if (!inf)
    {
        // cerr을 이용하여 에러 메시지 출력 후 프로그램 종료
        std::cerr << "Uh oh, Sample.dat could not be opened for reading!\n";
        return 1;
    }

    /*
    // 이렇게 읽는 것도 가능. 다만 string이 한 번에 whitespace, newline등등을 기준으로 연속된 값만 추출하기 때문에 line 전체를 읽는 것이 아님.
    // 이렇게 "<<" 로 읽을 경우 다양한 data type으로 읽을 수 있음.
    while (inf)
    {
        std::string strInput;
        inf >> strInput;
        std::cout << strInput << '\n';
    }
    */

    // 파일에 있는 모든 내용을 읽을 때까지 while문이 동작함.
    while (inf)
    {
        // getline을 통해 파일을 한 줄을 읽고 이를 출력함.
        std::string strInput;
        std::getline(inf, strInput);
        std::cout << strInput << '\n';
    }

    inf.close();

    return 0;

    // outf.close()를 하지 않았을 경우, outf가 여기서 scope를 벗어날 때 ofstream destructor가 파일을 닫음.
}
```


* 일반적으로 ostream으로 파일을 생성하면, 똑같의 이름의 파일이 존재할 시 이를 덮어 씌움. 덮어 쓰지말고 기존의 파일에 내용을 추가하고 싶을 때는 ios file mode 중 하나인 **app** (append)으로 파일을 열어야 함.

* app 사용 예시

```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream outf{ "Sample.dat", std::ios::app };

    if (!outf)
    {
        std::cerr << "Uh oh, Sample.dat could not be opened for writing!\n";
        return 1;
    }

    outf << "This is line 3" << '\n';
    outf << "This is line 4" << '\n';

    return 0;
}
```
