#include "Page.hpp"

class Story {
 private:
  std::vector<Page *> pages;
  std::map<size_t, bool> pageStatusMap;
  int pageTypeArray[4];
  // only used in step 4
  std::map<std::string, long> varHashs;

 public:
  Story() {
    for (int i = 0; i < 4; i++) {
      pageTypeArray[i] = 0;
    }
  }

  ~Story() {
    for (size_t i = 0; i < pages.size(); i++) {
      delete pages[i];
    }
  }
  void addBlankPage(Page * pagePointer);
  Page * operator[](size_t index);
  size_t getPageSize();
  bool isPageNum(size_t num);
  void printSinglePG(size_t pagNum);
  void printSinglePG4step(size_t pagNum, const std::map<std::string, long> & status);
  void printStory();
  bool checkLoseAndWin();
  void addPageType(int num);
  bool isAllPageReachable();
  void setPageToReachable(size_t pageNum);
};
