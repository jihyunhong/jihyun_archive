/* 직사각형의 가로와 세로 길이을 입력으로 받아서 넓이를 출력해주는 함수를 
   만들어 봅시다.
   */

#include <iostream>

int rectangle(int width, int height){
	int area;
    area = width * height;
    return area;
}

void print_area(int area){
      std::cout<< area << std::endl;
}

int main(){

	int w, h;

	std::cout << "enter the width and height of the rectangle" << std::endl;
	std:: cin >> w >> h;

	print_area(rectangle(w,h));
	return 0;
}
