#include <iostream>

struct Ingredient {
  int identifier{};     // id of this Ingredient
  float maxQuantity{};  // maxQuantity currently available >0
};

struct Item {
  Ingredient* ing1{};   // Ingredient 1
  Ingredient* ing2{};   // Ingredient 2
  float ing1_needed{};  // How much ing1 is needed to make 1 Item >0
  float ing2_needed{};  // How mush ing2 is needed to make 1 Item >0
  float utilityPerItem{}; // Utility gained per 1 item (positive number) >0
  float quantity{};     // quantity to make this Item >=0
                        // can also make non-integer quantities like 4.3
                        // quantity must be a positive number.
                        // should be decided by maximizeUtility function
};

void printSolution(const Item& item1, const Item& item2, float maxUtility) {
  std::cout << "Item 1 Quantity: " << item1.quantity << std::endl;
  std::cout << "Item 2 Quantity: " << item2.quantity << std::endl;
  std::cout << "Max utility gained: " << maxUtility << std::endl;
  std::cout << std::endl;
}

void maximizeUtility(Item& item1, Item& item2) {
  float maxUtility = 0.0;
  // TODO: Implement utility maximizing function

  float x = 0.0, y = 0.0;
  float a, b, c, d, M, N;
  float slope1 = 0.0, slope2 = 0.0, slope_util = 0.0;

  a = item1.ing1_needed;
  b = item2.ing1_needed;
  c = item1.ing2_needed;
  d = item2.ing2_needed;
  M = item1.ing1->maxQuantity;
  N = item1.ing2->maxQuantity;
  /*
  Want to maximize : item1.util * x + item2.util * y
  s.t.
  (1) x, y >= 0
  (2) a * x + b * y <= M
  (3) c * x + d * y <= N
  */
  slope1 = - a/b;
  slope2 = - c/d;
  slope_util = - item1.utilityPerItem / item2.utilityPerItem;
  // std::cout << slope1 << std::endl;
  // std::cout << slope2 << std::endl;
  // std::cout << slope_util << std::endl;
  
  if (slope1 < slope2){
    if (slope_util < slope1){
      x = std::min(M/a, N/c);
      y = 0;
    }
    else if (slope1 <= slope_util && slope_util < slope2){
      x = (d*M - b*N) / (a*d - b*c);
      y = (a*N - c*M) / (a*d - b*c);
    }
    else{
      x = 0;
      y = std::min(M/b, N/d);
    }
  }
  else { /* slope1 >= slope2 */
    if (slope_util < slope2){
      x = std::min(M/a, N/c);
      y = 0;
    }
    else if (slope2 <= slope_util && slope_util < slope1){
      x = (d*M - b*N) / (a*d - b*c);
      y = (a*N - c*M) / (a*d - b*c);
    }
    else{
      x = 0;
      y = std::min(M/b, N/d);
    }
  }
  maxUtility = item1.utilityPerItem * x + item2.utilityPerItem * y;

  item1.quantity = x;
  item2.quantity = y;
/*
  int x = 0, y = 0;
  float util = 0.0;
  //want to maximize
  util = item1.utilityPerItem * x + item2.utilityPerItem * y;
  //constraints
  x >= 0;
  y >= 0;
  item1.ing1->maxQuantity >= x * item1.ing1_needed + y * item2.ing1_needed;
  item1.ing2->maxQuantity >= x * item1.ing2_needed + y * item2.ing2_needed;
*/

  printSolution(item1, item2, maxUtility);
}


int main() {
  // Test Case 1
  Ingredient chocolate{1, 100.0};
  Ingredient flour{2, 150.0};

  Item cake{&chocolate, &flour, 5.0, 9.5, 9.0};
  Item cookie{&chocolate, &flour, 5.0, 5.1, 7.0};
  maximizeUtility(cake, cookie);
  // Test Case 2
  Ingredient copper{1, 2000.0};
  Ingredient zinc{2, 1200.0};

  Item wire{&copper, &zinc, 2.0, 0.5, 1.0};
  Item plate{&copper, &zinc, 15.0, 12.2, 10.0};
  maximizeUtility(wire, plate);

  // Test Case 3
  Ingredient wood{1, 1860.0};
  Ingredient plastic{2, 1980.0};

  Item table{&wood, &plastic, 10.0, 8.0, 8.0};
  Item chair{&wood, &plastic, 2.1, 2.2, 2.5};
  maximizeUtility(table, chair);
  // Test Case 4
  Ingredient water{1, 550.0};
  Ingredient wiskey{2, 250.0};
  
  Item drink1{&water, &wiskey, 2.4, 1.0, 5.0};
  Item drink2{&water, &wiskey, 4.8, 2.0, 8.0};
  maximizeUtility(drink1, drink2);
  return 0;
}
