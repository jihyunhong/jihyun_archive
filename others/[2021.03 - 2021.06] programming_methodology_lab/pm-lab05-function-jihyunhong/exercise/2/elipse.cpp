/*타원의 장축과 단축의 길이을 입력으로 받아서 넓이를 출력해주는 함수를 만들어 보세요.*/

#include <iostream>

const float PI = 3.141592;

/*
implement function elipse() and print_area()
*/
float eclipse(float lo, float sh){
    float area;
    area = PI * (lo/2) * (sh/2);
    return area;
}

void print_area(float area){
    std::cout << area << std::endl;
}


int main(){

	float major, minor;

	std::cout << "enter the major axis and minor axis of the elipse" << std::endl;
	std:: cin >> major >> minor;

    //call function elipse and print area here
	print_area(eclipse(major,minor));
	return 0;
}
