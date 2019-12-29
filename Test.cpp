//
// Created by 郑文鑫 on 2019/12/29.
//
#include <iostream>
#include "src/Rouge.h"
Rouge rouge;
int main() {
  std::string r1("Hello, World! werfdee fw23r132@!R e飞机快让我扶额"), r2("Hello, World! werfdee fw2额");
  rouge.reset(r2, r1);
  std::cout << "Rouge-1 Score: " << rouge.r1() << std::endl << "Rouge-2 Score: " << rouge.r2();
  return 0;
}