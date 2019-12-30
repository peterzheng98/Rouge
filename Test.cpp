//
// Created by 郑文鑫 on 2019/12/29.
//
#include <iostream>
#include "src/Rouge.h"
Rouge rouge;
int main() {
  std::string r1("Hello, World! fw23r132dcx!R werfdeea e飞机快让我扶额 arg fwefew fwefew few fewafgg"), r2("Hello, World! werfdeea ewargewa gewafg eawf ewa waefwga gawegree fw2额");
  rouge.reset(r2, r1);
  std::cout << "Rouge-1 Score: " << rouge.r1() << std::endl << "Rouge-2 Score: " << rouge.r2() << std::endl << "Rouge-L Score: " << rouge.rl(0.1);
  return 0;
}