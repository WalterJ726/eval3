#include <cstring>

#include "cyoa_story.hpp"

int main(int argc, char ** argv) {
  // not just the directory name
  if (argc != 2) {
    printErrorMsg("Usage DirectoryName");
  }
  //
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
  // read pages
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

  // start find the path
  std::vector<std::vector<std::pair<size_t, size_t> > > allPaths;
  std::vector<std::pair<size_t, size_t> > path;
  std::vector<bool> isVisited(s1.getPageSize(), false);

  traversePages(0, s1, path, allPaths, isVisited);

  if (allPaths.size() == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
    return EXIT_SUCCESS;
  }

  for (size_t i = 0; i < allPaths.size(); i++) {
    std::vector<std::pair<size_t, size_t> > printPath = allPaths[i];
    for (size_t j = 0; j < printPath.size(); j++) {
      if (j != printPath.size() - 1) {
        std::cout << printPath[j].first << "(" << printPath[j].second << "),";
      }
      else {
        std::cout << printPath[j].first << "(win)" << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
