#include "cyoa_story.hpp"

void printErrorMsg(const char * errorStr) {
  // print error message
  std::cerr << errorStr << std::endl;
  exit(EXIT_FAILURE);
}

size_t isInteger4(const char * line) {
  // check the integer is valid
  char * ptr;
  long result = strtol(line, &ptr, 10);
  if (*ptr != '\0') {
    printErrorMsg("encounter some character before number");
  }
  if (result == 0 && *(ptr - 1) != '0') {
    printErrorMsg("there is no digits at all");
  }
  return result;
}

size_t isInteger(const char * line) {
  // check the integer is valid
  char * ptr;
  long result = strtol(line, &ptr, 10);
  if (*ptr != '\0') {
    printErrorMsg("encounter some character before number");
  }
  if (result == 0 && *(ptr - 1) != '0') {
    printErrorMsg("there is no digits at all");
  }
  if (result < 0) {
    printErrorMsg("result is not a valid number");
  }
  return result;
}

int isType(char * type_str) {
  // check the correct type
  // N:0, L:1, W:2, other character: 3
  if (strlen(type_str) != 1) {
    return 3;
  }
  else if (*type_str == 'N') {
    return 0;
  }
  else if (*type_str == 'L') {
    return 1;
  }
  else if (*type_str == 'W') {
    return 2;
  }
  else {
    return 3;
  }
}

void readPage(std::istream & is, Story & s1, size_t pageNum) {
  // read page to story class
  std::string s;
  Page * pg = s1[pageNum];
  while (getline(is, s)) {
    pg->addContents(s);
  }
}

std::vector<char *> readStory(std::istream & is, Story & s1) {
  // start reading
  std::string s;
  std::vector<char *> filenameVector;
  while (getline(is, s)) {
    const char * line = s.c_str();
    const char * at;
    const char * colon_first;
    if ((at = strchr(line, '@')) != NULL) {
      // deal with pages
      char * pagenum_str = strndup(line, at - line);
      size_t pagenum_temp = isInteger(pagenum_str);
      // pageNum must be sequential
      if (pagenum_temp != s1.getPageSize()) {
        printErrorMsg("pageNum is not sequential");
      }
      const char * type_colon = strchr(at, ':');
      if (type_colon == NULL) {
        printErrorMsg("is not a valid type");
      }
      char * type_str = strndup(at + 1, type_colon - (at + 1));
      // check type_str is N, L, W
      int isTypeNum = isType(type_str);
      if (isTypeNum == 3) {
        printErrorMsg("The page is not N or L or W");
      }
      char * filename = strdup(type_colon + 1);
      filenameVector.push_back(filename);
      Page * newPage = new Page();
      newPage->setPageNum(pagenum_temp);
      newPage->setType(*type_str);
      s1.addBlankPage(newPage);
      s1.addPageType(isTypeNum);
      free(type_str);
      free(pagenum_str);
    }
    else if ((colon_first = strchr(line, ':')) != NULL) {
      // deal with choices
      char * pagenum_str = strndup(line, colon_first - line);
      size_t pagenum_temp = isInteger(pagenum_str);
      if (!s1.isPageNum(pagenum_temp)) {
        printErrorMsg("we have not create that page");
      }
      const char * des_colon = strchr(colon_first + 1, ':');
      if (des_colon == NULL) {
        printErrorMsg("there is no des page");
      }
      char * des_str = strndup(colon_first + 1, des_colon - (colon_first + 1));
      size_t desNum = isInteger(des_str);
      char * choice_str = strdup(des_colon + 1);
      std::stringstream ss;
      std::string choiceString(choice_str);
      free(choice_str);
      free(des_str);
      Page * pg = s1[pagenum_temp];
      if (pg->getType() != 'N') {
        printErrorMsg("win and lose page should not have choice");
      }
      pg->addChoices(desNum, choiceString);
      s1.setPageToReachable(desNum);
      free(pagenum_str);
    }
    else if (s.size() == 0) {
      // empty line
      continue;
    }
    else {
      // invalid character
      printErrorMsg("can not read line");
    }
  }
  return filenameVector;
  // read files contents
}

std::vector<char *> readStory4Step4(std::istream & is, Story & s1) {
  // read pages for step 4
  std::string s;
  std::vector<char *> filenameVector;
  //int times = 0;
  while (getline(is, s)) {
    const char * line = s.c_str();
    const char * at;
    const char * colon_first;
    const char * dollar_first;
    const char * bracket_first;

    if ((at = strchr(line, '@')) != NULL) {
      // deal with pages
      char * pagenum_str = strndup(line, at - line);
      size_t pagenum_temp = isInteger(pagenum_str);
      const char * type_colon = strchr(at, ':');
      // pageNum must be sequential
      if (pagenum_temp != s1.getPageSize()) {
        printErrorMsg("pageNum is not sequential");
      }
      if (type_colon == NULL) {
        printErrorMsg("is not a valid type");
      }
      char * type_str = strndup(at + 1, type_colon - (at + 1));
      // check type_str is N, L, W
      int isTypeNum = isType(type_str);
      if (isTypeNum == 3) {
        printErrorMsg("The page is not N or L or W");
      }
      char * filename = strdup(type_colon + 1);
      filenameVector.push_back(filename);
      Page * newPage = new Page();
      newPage->setPageNum(pagenum_temp);
      newPage->setType(*type_str);
      s1.addBlankPage(newPage);
      s1.addPageType(isTypeNum);
      free(type_str);
      free(pagenum_str);
    }
    else if ((bracket_first = strchr(line, '[')) != NULL) {
      // deal with condition choices
      char * bracket_pagenum_str = strndup(line, bracket_first - line);
      size_t bracket_pagenum_temp = isInteger(bracket_pagenum_str);
      if (!s1.isPageNum(bracket_pagenum_temp)) {
        printErrorMsg("we have not create that page");
      }
      const char * bracket_des_equal = strchr(bracket_first + 1, '=');
      if (bracket_des_equal == NULL) {
        printErrorMsg("there is no variable name");
      }
      char * bracket_varStr =
          strndup(bracket_first + 1, bracket_des_equal - (bracket_first + 1));
      std::string bracketVarString(bracket_varStr);
      // get variable num
      const char * bracket_second = strchr(bracket_des_equal + 1, ']');
      if (bracket_second == NULL) {
        printErrorMsg("there is no close bracket");
      }
      char * bracket_varNum_str =
          strndup(bracket_des_equal + 1, bracket_second - (bracket_des_equal + 1));
      size_t bracket_varNum = isInteger4(bracket_varNum_str);

      // get destination page number
      const char * bracket_colon_first = strchr(bracket_second + 1, ':');
      if (bracket_colon_first == NULL) {
        printErrorMsg("there is no left colon");
      }
      const char * bracket_colon_second = strchr(bracket_colon_first + 1, ':');
      if (bracket_colon_second == NULL) {
        printErrorMsg("there is no right colon");
      }
      char * bracket_desStr = strndup(bracket_colon_first + 1,
                                      bracket_colon_second - (bracket_colon_first + 1));
      size_t bracket_desNum = isInteger(bracket_desStr);
      char * bracket_choiceStr = strdup(bracket_colon_second + 1);

      // add varible restriction, destination pg number, and choice str into Page class
      std::string bracket_choiceString(bracket_choiceStr);
      Page * pg = s1[bracket_pagenum_temp];
      if (pg->getType() != 'N') {
        printErrorMsg("win and lose page should not have choice");
      }
      pg->addVarChoices(
          bracket_desNum, bracket_choiceString, bracket_varNum, bracketVarString);
      s1.setPageToReachable(bracket_desNum);
      free(bracket_choiceStr);
      free(bracket_desStr);
      free(bracket_varNum_str);
      free(bracket_varStr);
      free(bracket_pagenum_str);
    }
    else if ((colon_first = strchr(line, ':')) != NULL) {
      // deal with choices
      char * pagenum_str = strndup(line, colon_first - line);
      size_t pagenum_temp = isInteger(pagenum_str);
      if (!s1.isPageNum(pagenum_temp)) {
        printErrorMsg("we have not create that page");
      }
      const char * des_colon = strchr(colon_first + 1, ':');
      if (des_colon == NULL) {
        printErrorMsg("there is no des page");
      }
      char * des_str = strndup(colon_first + 1, des_colon - (colon_first + 1));
      size_t desNum = isInteger(des_str);
      char * choice_str = strdup(des_colon + 1);
      std::stringstream ss;
      std::string choiceString(choice_str);
      free(choice_str);
      free(des_str);
      Page * pg = s1[pagenum_temp];
      if (pg->getType() != 'N') {
        printErrorMsg("win and lose page should not have choice");
      }
      pg->addChoices(desNum, choiceString);
      s1.setPageToReachable(desNum);
      free(pagenum_str);
    }
    else if ((dollar_first = strchr(line, '$')) != NULL) {
      // deal with conditional variable
      char * var_pagenum_str = strndup(line, dollar_first - line);
      size_t var_pagenum_temp = isInteger(var_pagenum_str);
      if (!s1.isPageNum(var_pagenum_temp)) {
        printErrorMsg("we have not create that page");
      }
      const char * des_equal = strchr(dollar_first + 1, '=');
      if (des_equal == NULL) {
        printErrorMsg("there is no variable name");
      }
      char * variable_str = strndup(dollar_first + 1, des_equal - (dollar_first + 1));
      char * variable_num_str = strdup(des_equal + 1);
      size_t variableNum = isInteger4(variable_num_str);
      // add varible number into map
      std::string variableString(variable_str);
      free(variable_str);
      free(variable_num_str);
      Page * pg = s1[var_pagenum_temp];
      if (pg->getType() != 'N') {
        printErrorMsg("win and lose page should not have choice");
      }
      pg->addVariables(variableNum, variableString);
      free(var_pagenum_str);
    }
    else if (s.size() == 0) {
      // deal with empty line
      continue;
    }
    else {
      printErrorMsg("can not read line");
    }
  }
  return filenameVector;
  // read files contents
}

void traversePages(size_t curPageNum,
                   Story & s1,
                   std::vector<std::pair<size_t, size_t> > path,
                   std::vector<std::vector<std::pair<size_t, size_t> > > & allPaths,
                   std::vector<bool> & isVisited) {
  // start find the path

  // current page has visited
  if (isVisited[curPageNum])
    return;
  // base case, meet the lose or win page
  isVisited[curPageNum] = true;
  char curType = s1[curPageNum]->getType();
  if (curType == 'L') {
    return;
  }
  if (curType == 'W') {
    // Because the choice number must be positive
    // I define the WIN to be -1. It's convenient for me to deal with win page
    std::pair<size_t, size_t> winPgae = std::make_pair(curPageNum, WIN);
    path.push_back(winPgae);
    allPaths.push_back(path);
    return;
  }
  size_t choiceNum = s1[curPageNum]->getChoiceSize();
  for (size_t i = 0; i < choiceNum; i++) {
    // get the destination page
    size_t desNum = s1[curPageNum]->getDesNum(i);
    std::pair<size_t, size_t> nextPg = std::make_pair(curPageNum, i + 1);
    path.push_back(nextPg);
    traversePages(desNum, s1, path, allPaths, isVisited);
    path.pop_back();
  }
}
