
#include "Story.hpp"

void Story::setPageToReachable(size_t pageNum) {
  pageStatusMap[pageNum] = true;
}

bool Story::isAllPageReachable() {
  for (size_t i = 1; i < pages.size(); i++) {
    if (pageStatusMap.find(i) == pageStatusMap.end()) {
      return false;
    }
  }
  return true;
}

void Story::addBlankPage(Page * pagePointer) {
  pages.push_back(pagePointer);
}

void Story::addPageType(int num) {
  pageTypeArray[num]++;
}

bool Story::checkLoseAndWin() {
  // check whether the story has at least one w and one lose page
  // N:0, L:1, W:2, other character: 3
  if (pageTypeArray[1] < 1) {
    return false;
  }
  else if (pageTypeArray[2] < 1) {
    return false;
  }
  else {
    return true;
  }
}

Page * Story::operator[](size_t index) {
  return pages[index];
}

size_t Story::getPageSize() {
  return pages.size();
}
bool Story::isPageNum(size_t num) {
  // A page declaration (num@filename) for a given page must
  // appear before anything else related to that page
  return num < pages.size();
}

void Story::printSinglePG(size_t pagNum) {
  Page * pg = pages[pagNum];
  char type = pg->getType();
  // printContents
  pg->printContents();
  if (type == 'N') {
    // print choices
    pg->printChoices();
  }
  else if (type == 'W') {
    // print win
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else {
    // print lose
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

void Story::printSinglePG4step(size_t pagNum,
                               const std::map<std::string, long> & status) {
  Page * pg = pages[pagNum];
  char type = pg->getType();
  // printContents
  pg->printContents();
  if (type == 'N') {
    // print choices
    pg->printChoices4step(status);
  }
  else if (type == 'W') {
    // print win
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else {
    // print lose
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

void Story::printStory() {
  for (size_t i = 0; i < pages.size(); i++) {
    std::cout << "Page " << i << std::endl;
    std::cout << "==========" << std::endl;
    printSinglePG(i);
  }
}
