#include <cstring>

#include "cyoa_story.hpp"

int main(int argc, char ** argv) {
  // not just the directory name
  if (argc != 2) {
    printErrorMsg("Usage DirectoryName");
  }
  std::stringstream ss1;
  ss1 << argv[1];
  ss1 << "/story.txt";
  std::ifstream ifs;
  ifs.open(ss1.str().data(), std::ios::in);
  if (!ifs.is_open()) {
    printErrorMsg("fail to open");
  }
  Story s1;
  std::vector<char *> fileList;
  fileList = readStory(ifs, s1);
  ifs.close();

  // start reading pages
  for (size_t i = 0; i < fileList.size(); i++) {
    // std::cout << fileList[i] << std::endl;
    std::stringstream ss;
    ss << argv[1];
    ss << '/' << fileList[i];
    ifs.open(ss.str().data(), std::ios::in);

    if (!ifs.is_open()) {
      std::cerr << "fail to open" << std::endl;
      exit(EXIT_FAILURE);
    }
    readPage(ifs, s1, i);
    ifs.close();
    free(fileList[i]);
  }

  // Story must have at least one win and lose
  if (!s1.checkLoseAndWin()) {
    printErrorMsg("Story must have at least one win and lose");
  }

  // all the pages must be reachable
  if (!s1.isAllPageReachable()) {
    printErrorMsg("Not all the pages are reachable");
  }

  // print first page
  Page * pg = s1[0];
  s1.printSinglePG(0);
  std::string s;
  while (getline(std::cin, s)) {
    const char * choice_str = s.c_str();
    size_t choiceNum = isInteger(choice_str);
    // the page they go to must be kept in the pages
    if (choiceNum > pg->getChoiceSize() || choiceNum == 0) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    size_t pageDes = pg->getDesNum(choiceNum - 1);
    if (s1.isPageNum(pageDes)) {
      // check if there exist;
      pg = s1[pageDes];
      s1.printSinglePG(pageDes);
      if (pg->getType() == 'W' || pg->getType() == 'L') {
        return EXIT_SUCCESS;
        //    exit(EXIT_SUCCESS);
      }
    }
  }
  delete pg;
  return EXIT_SUCCESS;
}
