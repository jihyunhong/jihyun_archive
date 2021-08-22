/* 
  Implementation of Calculator..
*/

#include <iostream>
#include <iomanip>


int main()
{

  int caseNum;
  double num1, num2; 
  double ret;
  std::cout<<"1.add 2.minus 3.multiply 4.divide"<<std::endl;
  std::cout<<"You should print error message if your operation num is invalid"<<std::endl;
  std::cout <<"what operation will be performed?: ";
  std::cin >> caseNum;

  switch(caseNum){
    case 1:
      std::cout << "Select the numbers to be calculated: ";
      std::cin >> num1 >> num2;
      //implement the addition here
      std::cout << num1+num2 << std::endl;

      break;
    case 2:
      std::cout << "Select the numbers to be calculated: ";
      std::cin >> num1 >> num2;
      //implement the subtraction here
      std::cout << num1-num2 << std::endl;
      

      break;
    case 3:
      std::cout << "Select the numbers to be calculated: ";
      std::cin >> num1 >> num2;
      //implement the multiplication here
      std::cout << num1*num2 << std::endl;

      break;
    case 4:
      std::cout << "Select the numbers to be calculated: ";
      std::cin >> num1 >> num2;
      //implement the division here
      //You must remind that
      //if num2=0 you should print error message
      //divide by zero error
      if (num2==0){
        std::cout << "divide by zero error" << std::endl;
      }
      else{
        std::cout << num1/num2 << std::endl;
      }
      break;

    default:
      //print warning message
      //wrong operation
    if (caseNum != 1 || caseNum != 2 || caseNum != 3 || caseNum != 4){
      std::cout << "wrong operation" << std::endl;
      }
  }
  
  return 0;
}
