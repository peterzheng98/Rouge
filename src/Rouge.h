//
// Created by Peter Zheng on 2019/12/29.
//

#ifndef ROUGE_ROUGE_H
#define ROUGE_ROUGE_H

#include <map>
#include <vector>
class Rouge {
private:
  std::vector<int> target, original;

private:
  std::map<std::string, int> wordLists;
  std::vector<std::string> wordListsInv;
  char splitWords = ' ';
  int currentIdx = 0;
  std::vector<int> _addWord(const std::string& rhs);
  void _clearList();

public:
  void setSplitWords(const char& rhs);
  void debug_addword(const std::string& rhs);

public:
  Rouge(){}
  Rouge(const std::vector<int> &target, const std::vector<int> &original);
  Rouge(const std::string &target, const std::string &original);
  void reset(const std::vector<int> &target, const std::vector<int> &original);
  void reset(const std::string &target, const std::string &original);
  float r1();
  float r2();

};

#endif // ROUGE_ROUGE_H
