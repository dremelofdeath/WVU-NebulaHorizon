/* 
 * TextFileReader.cpp
 * Nebula Horizon
 *
 * Created by Zachary Murray on 4/30/2010 2:53:37 AM Eastern Daylight Time
 *
 */

#include <fstream>

#include "TextFileReader.h"

TextFileReader::TextFileReader(const char* filename) {
  initialize(filename);
}

TextFileReader::~TextFileReader() {
}

const char* TextFileReader::getFileContents() {
  return _contents.c_str();
}

void TextFileReader::initialize(const char* filename) {
  std::ifstream file(filename);
  std::string line;
  while(std::getline(file, line)) {
    _contents += line + "\n";
  }
  file.close();
}
