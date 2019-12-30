//
// Created by Peter Zheng on 2019/12/29.
//

#include "Rouge.h"
#include <iostream>
#include <string>
void Rouge::_clearList() {
  auto tmp = std::map<std::string, int>();
  this->wordLists.swap(tmp);
}

void Rouge::setSplitWords(const char &rhs) { this->splitWords = rhs; }

void Rouge::debug_addword(const std::string &rhs) { this->_addWord(rhs); }

std::vector<int> Rouge::_addWord(const std::string &rhs) {
  std::string tmp(rhs);
  int totalWords = 0;
  std::vector<int> returnVec;
  while (tmp.find(this->splitWords) != std::string::npos) {
    int idx = tmp.find(this->splitWords);
    std::string word = tmp.substr(0, idx);
    // Debug:
    // std::cout << '[' << word << ']' << std::endl;
    if(this->wordLists.count(word) == 0) {
      this->wordLists[word] = this->currentIdx;
      this->currentIdx++;
      this->wordListsInv.push_back(word);
    }
    returnVec.push_back(this->wordLists[word]);
    tmp = tmp.substr(idx + 1);
    totalWords++;
  }
  if (tmp.length() != 0) {
    // Debug:
    // std::cout << '[' << tmp << ']' << std::endl;
    if(this->wordLists.count(tmp) == 0) {
      this->wordLists[tmp] = this->currentIdx;
      this->currentIdx++;
      this->wordListsInv.push_back(tmp);
    }
    returnVec.push_back(this->wordLists[tmp]);
    totalWords++;
  }
  std::cout << "Debug: Add " << totalWords << " words." << std::endl;
  return returnVec;
}

Rouge::Rouge(const std::vector<int> &target, const std::vector<int> &original)
    : target(target), original(original) {}

void Rouge::reset(const std::vector<int> &target,
                  const std::vector<int> &original) {
  this->original = original;
  this->target = target;
}
Rouge::Rouge(const std::string &target, const std::string &original) {
  this->target = std::move(_addWord(target));
  this->original = std::move(_addWord(original));
}
void Rouge::reset(const std::string &target, const std::string &original) {
  this->target = std::move(_addWord(target));
  this->original = std::move(_addWord(original));
}
float Rouge::r1() {
  std::map<int, int> targetMap, originalMap;
  for (auto &elem : target)
    if (targetMap.count(elem) == 0)
      targetMap[elem] = 1;
    else
      targetMap[elem]++;
  for (auto &elem : original)
    if (originalMap.count(elem) == 0)
      originalMap[elem] = 1;
    else
      originalMap[elem]++;
  int totalWords = 0, matchedWords = 0;
  for (auto &it : originalMap) {
    totalWords += it.second;
    matchedWords += std::min(targetMap[it.first], it.second);
  }
  return 100. * matchedWords / totalWords;
}

float Rouge::r2(){
  std::map<std::pair<int, int>, int> targetMap, originalMap;
  for(size_t idx = 0; idx < target.size() - 1; ++idx){
    auto pairData = std::pair<int, int>(target[idx], target[idx + 1]);
    if(targetMap.count(pairData) == 0) targetMap[pairData] = 1;
    else targetMap[pairData]++;
  }

  for(size_t idx = 0; idx < original.size() - 1; ++idx){
    auto pairData = std::pair<int, int>(original[idx], original[idx + 1]);
    if(originalMap.count(pairData) == 0) originalMap[pairData] = 1;
    else originalMap[pairData]++;
  }

  int totalPhrases = 0, matchedPhrases = 0;
  for(auto &it : originalMap){
    totalPhrases += it.second;
    matchedPhrases += std::min(targetMap[it.first], it.second);
  }
  return 100. * matchedPhrases / totalPhrases;
}
float Rouge::rn(const int &n) {
  if(n == 1) return r1();
  if(n == 2) return r2();
  std::map<std::vector<int>, int> targetMap, originalMap;
  if(n >= target.size() || n >= original.size()){
    std::cerr << "Unable to calculate the Rouge-N score since the input sentence is not enough." << std::endl;
    return -1;
  }
  for(size_t idx = 0; idx < target.size() - n + 1; ++idx){
    auto targetElem = std::vector<int>(n);
    for(size_t idx2 = 0; idx2 < targetElem.size(); ++idx2) targetElem[idx2] = target[idx + idx2];
    if(targetMap.count(targetElem) == 0) targetMap[targetElem] = 1;
    else targetMap[targetElem]++;
  }

  for(size_t idx = 0; idx < original.size() - n + 1; ++idx){
    auto originalElem = std::vector<int>(n);
    for(size_t idx2 = 0; idx2 < originalElem.size(); ++idx2) originalElem[idx2] = original[idx + idx2];
    if(originalMap.count(originalElem) == 0) originalMap[originalElem] = 1;
    else originalMap[originalElem]++;
  }
  int totalPhrases = 0, matchedPhrases = 0;
  for(auto &it : originalMap){
    totalPhrases += it.second;
    matchedPhrases += std::min(targetMap[it.first], it.second);
  }
  return 100. * matchedPhrases / totalPhrases;
}
int Rouge::_lcs() {
  // Time Complexity: O(mn)
  // Space Complexity: O(min(m, n))
  int save = 0;
  auto dp = std::vector<int>(std::min(target.size(), original.size()) + 7);
  for(int i = 0; i < std::min(target.size(), original.size()) + 7; ++i) dp[i] = 0;
  int la = std::max(target.size(), original.size());
  int lb = std::min(target.size(), original.size());
  bool flag = target.size() > original.size();
  for(size_t idx = 0; idx < la; ++idx){
    save = dp[0];
    for(size_t idx2 = 0; idx2 < lb; ++idx2){
      int k = dp[idx2 + 1];
      if(flag && target[idx] == original[idx2]) dp[idx2 + 1] = save + 1;
      else if(!flag && target[idx2] == original[idx]) dp[idx2 + 1] = save + 1;
      else dp[idx2 + 1] = std::max(dp[idx2], dp[idx2 + 1]);
      save = k;
    }
  }
  return dp[lb];
}
float Rouge::rl(const float &beta) {
  int lcsLength = _lcs();
  float Rlcs = 1.0 * lcsLength / target.size();
  float Plcs = 1.0 * lcsLength / original.size();
  float Flcs = ((1.0 + beta * beta) * Rlcs * Plcs) / (Rlcs + beta * beta * Plcs);
  return Flcs;
}
