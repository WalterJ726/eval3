#include "Page.hpp"

void Page::addChoices(size_t & des, std::string & s) {
  std::pair<size_t, std::string> pr = std::make_pair(des, s);
  choices.push_back(pr);

  // used for step4
  std::string tempVar;
  std::pair<std::string, size_t> pr1 = std::make_pair(tempVar, 0);
  choiceVars.push_back(pr1);
  isVarList.push_back(false);
  isReachableVec.push_back(true);
}

void Page::addVarChoices(size_t & des,
                         std::string & s,
                         size_t & varNum,
                         std::string & varStr) {
  // add choices with varibale(in step4)
  std::pair<size_t, std::string> pr = std::make_pair(des, s);
  choices.push_back(pr);

  // used for step4
  std::pair<std::string, size_t> pr1 = std::make_pair(varStr, varNum);
  choiceVars.push_back(pr1);
  isVarList.push_back(true);
  isReachableVec.push_back(true);
}

void Page::addVariables(size_t & varNum, std::string & s) {
  variables[s] = varNum;
}

void Page::addContents(std::string & line) {
  contents.push_back(line);
}

void Page::setType(char type_str) {
  type = type_str;
}

char Page::getType() {
  return type;
}

bool Page::getPageReachable() {
  return pageIsReachable;
}

size_t Page::getChoiceSize() {
  return choices.size();
}

size_t Page::getDesNum(size_t choiceNum) {
  return choices[choiceNum].first;
}
void Page::setPageNum(size_t & num) {
  pageNum = num;
}

size_t Page::getPageNum() {
  return pageNum;
}

bool Page::isReachable(size_t index) {
  return isReachableVec[index];
}

void Page::changeStatus(std::map<std::string, long> & status) {
  std::map<std::string, long>::iterator it = variables.begin();
  while (it != variables.end()) {
    std::string var_temp = (*it).first;
    long num_temp = (*it).second;
    status[var_temp] = num_temp;
    ++it;
  }
}

void Page::printContents() {
  for (size_t i = 0; i < contents.size(); i++) {
    std::cout << contents[i] << std::endl;
  }
  std::cout << std::endl;
}

void Page::printChoices4step(const std::map<std::string, long> & status) {
  // print choices for step4
  std::cout << "What would you like to do?" << std::endl;
  std::cout << std::endl;
  for (size_t i = 0; i < choices.size(); i++) {
    if (isVarList[i]) {
      std::string var_temp = choiceVars[i].first;
      long num_temp = choiceVars[i].second;
      std::map<std::string, long>::const_iterator it = status.find(var_temp);
      if (it == status.end()) {
        if (num_temp == 0) {
          // variable equals to default value
          std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
        }
        else {
          std::cout << " " << i + 1 << ". "
                    << "<UNAVAILABLE>" << std::endl;
          isReachableVec[i] = false;
        }
      }
      else {
        if ((*it).second == num_temp) {
          std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
        }
        else {
          std::cout << " " << i + 1 << ". "
                    << "<UNAVAILABLE>" << std::endl;
          isReachableVec[i] = false;
        }
      }
    }
    else {
      std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
    }
  }
}

void Page::printChoices() {
  std::cout << "What would you like to do?" << std::endl;
  std::cout << std::endl;
  for (size_t i = 0; i < choices.size(); i++) {
    std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
  }
}
