#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
#include <sstream>

namespace uri {

  using namespace std;

  typedef map<string, string> qsmap;
  typedef vector<string> split;

  struct url {
    string protocol;
    string user;
    string password;
    string host;
    string path;
    string search;
    qsmap query;
    int port;
  };

  //--- Helper Functions -------------------------------------------------------------~
  static inline string TailSlice(string &subject, string delimiter, bool keep_delim=false) {
    // Chops off the delimiter and everything that follows (destructively)
    // returns everything after the delimiter
    auto delimiter_location = subject.find(delimiter);
    auto delimiter_length = delimiter.length();
    string output = "";

    if (delimiter_location < string::npos) {
      auto start = keep_delim ? delimiter_location : delimiter_location + delimiter_length;
      auto end = subject.length() - start;
      output = subject.substr(start, end);
      subject = subject.substr(0, delimiter_location);
    }
    return output;
  }

  static inline string HeadSlice(string &subject, string delimiter) {
    // Chops off the delimiter and everything that precedes (destructively)
    // returns everthing before the delimeter
    auto delimiter_location = subject.find(delimiter);
    auto delimiter_length = delimiter.length();
    string output = "";
    if (delimiter_location < string::npos) {
      output = subject.substr(0, delimiter_location);
      subject = subject.substr(
          delimiter_location + delimiter_length, 
          subject.length() - (delimiter_location + delimiter_length));
    }
    return output;
  }

  static inline split Split(const std::string& input, const string& separators, bool remove_empty = true) {
    split list;
    ostringstream word;
    for (size_t n = 0; n < input.size(); ++n) {
      if (string::npos == separators.find(input[n]))
        word << input[n];
      else {
        if (!word.str().empty() || !remove_empty) {
          list.push_back(word.str());
        }
        word.str("");
      }
    }
    if (!word.str().empty() || !remove_empty) {
      list.push_back(word.str());
    }
    return list;
  }

  //--- Extractors -------------------------------------------------------------------~
  static inline int ExtractPort(string &hostport) {
    int port;
    string portstring = TailSlice(hostport, ":");
    try { port = atoi(portstring.c_str()); }
    catch (exception e) { port = -1; }
    return port;
  }

  static inline string ExtractPath(string &in) { return TailSlice(in, "/", true); }
  static inline string ExtractProtocol(string &in) { return HeadSlice(in, "://"); }
  static inline string ExtractSearch(string &in) { return TailSlice(in, "?"); }
  static inline string ExtractPassword(string &userpass) { return TailSlice(userpass, ":"); }
  static inline string ExtractUserpass(string &in) { return HeadSlice(in, "@"); }


  //--- Public Interface -------------------------------------------------------------~
  static inline url ParseHttpUrl(string &in) {
    url ret;
    ret.port = -1;

    ret.protocol = ExtractProtocol(in);
    ret.search = ExtractSearch(in);
    ret.path = ExtractPath(in);
    string userpass = ExtractUserpass(in);
    ret.password = ExtractPassword(userpass);
    ret.user = userpass;
    ret.port = ExtractPort(in);
    ret.host = in;

    auto pairs = Split(ret.search, "&");

    for(auto &p : pairs) {
      auto pair = Split(p, "=");
      ret.query.insert({ pair[0], pair[1] });
    }
    return ret;
  }
}

