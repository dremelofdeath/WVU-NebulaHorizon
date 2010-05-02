/*
 * TextFileReader.h
 * Nebula Horizon
 *
 * Created by Zachary Murray on 4/30/2010 2:48:55 AM Eastern Daylight Time.
 *
 */

#ifndef NHZ_TEXTFILEREADER_H
#define NHZ_TEXTFILEREADER_H

#include <string>

class TextFileReader {
  public:
    TextFileReader(const char* filename);
    ~TextFileReader();
    const char* getFileContents();
  protected:
    void initialize(const char* filename);
  private:
    std::string _contents;
};

#endif
