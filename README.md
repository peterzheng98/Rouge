# Rouge

Implement of Rouge Metrics(Under development)

## Progress

- [x] Rouge-1
- [x] Rouge-2
- [x] Rouge-N
- [x] Rouge-L
- [ ] Rouge-W

## Usage(C++):
### Constructor:
1. ``` Rouge(const std::vector<int> &target, const std::vector<int> &original);```  
Construct the Rouge with two sentences where the words are represented in numbers.  
2. ```Rouge(const std::string &target, const std::string &original);```  
[RECOMMENDED]Construct the Rouge with two sentences and generate the corresponding numerical representation by splitting the sentence with ``splitWords``(See Members[7]).
### Members
1. `void reset(const std::vector<int> &target, const std::vector<int> &original);`  
Reset the sentence pairs with numerical representation.  
2. `void reset(const std::string &target, const std::string &original);`  
Reset the sentence pairs with real sentence strings and generate the corresponding numerical representation by splitting the sentence with ``splitWords``(See Members[7]).   
3. `float r1();`  
Calculate the Rouge-1 score, the sentence should be reseted or constructed before using `r1()`.  
4. `float r2();`  
Calculate the Rouge-2 score, the sentence should be reseted or constructed before using `r2()`.  
5. `float rn(const int& n);`  
Calculate the Rouge-N score, the sentence should be reseted or constructed before using `rn(const int& n)`. Recall that if n is one or two then it will call `r1()` or `r2()` directly. Nothing will be done if the sentence length is smaller than n.   
6. `float rl(const float& beta = 1);`  
Calculate the Rouge-L score with given beta.
7. `void setSplitWords(const char& rhs);`  
Used for setting up the split char in **Constructor[2] and Members[2]**.

## License
GPL-3.0

## Reference
[1] Lin, C.-Y. Rouge: A package for automatic evaluation of summaries. City, 2004.

## Future
Make a python version.