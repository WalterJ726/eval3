#include <string.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define WIN -1

class Page {
 private:
  std::vector<std::pair<size_t, std::string> > choices;
  std::vector<std::string> contents;
  bool pageIsReachable;
  char type;  // has a
  size_t pageNum;
  int a[4];
  // only used in step 4
  std::vector<std::pair<std::string, size_t> > choiceVars;
  std::vector<bool> isVarList;
  std::map<std::string, long> variables;
  std::vector<bool> isReachableVec;  // used for check unavailable choice

 public:
  void addChoices(size_t & des, std::string & s);
  void addVarChoices(size_t & des,
                     std::string & s,
                     size_t & varNum,
                     std::string & varStr);

  void addVariables(size_t & varNum, std::string & s);
  void addContents(std::string & line);
  void setType(char type_str);
  // void setPageToReachable(bool status);
  char getType();
  bool getPageReachable();
  size_t getChoiceSize();
  size_t getDesNum(size_t choiceNum);
  void setPageNum(size_t & num);
  size_t getPageNum();
  bool isReachable(size_t index);
  void changeStatus(std::map<std::string, long> & status);
  void printContents();
  void printChoices4step(const std::map<std::string, long> & status);
  void printChoices();
};
