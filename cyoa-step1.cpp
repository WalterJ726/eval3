
#include "cyoa_story.hpp"

int main(int argc, char ** argv) {
  // input more than two param
  if (argc != 2) {
    printErrorMsg("Usage DirectoryName");
  }
  // start to read pages
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

  // Read pages
  for (size_t i = 0; i < fileList.size(); i++) {
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

  s1.printStory();
}
