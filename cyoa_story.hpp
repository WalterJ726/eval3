#include "Story.hpp"

std::vector<char *> readStory(std::istream & is, Story & s1);
void readPage(std::istream & is, Story & s1, size_t pageNum);
void printErrorMsg(const char * errorStr);
size_t isInteger(const char * line);
void traversePages(size_t curPageNum,
                   Story & s1,
                   std::vector<std::pair<size_t, size_t> > path,
                   std::vector<std::vector<std::pair<size_t, size_t> > > & allPaths,
                   std::vector<bool> & isVisited);
std::vector<char *> readStory4Step4(std::istream & is, Story & s1);
