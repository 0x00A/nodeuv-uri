#include <iostream>
#include <UriParser.h>

using namespace std;
using namespace uri;

int main() {

  string haystack = "http://user:password@www.google.com:80/path?search";

  auto parsed = ParseHttpUrl(haystack);
  
  cout << "Protocol: " << parsed.protocol << "\n"
       << "User:     " << parsed.user << "\n"
       << "Password: " << parsed.password << "\n"
       << "Host:     " << parsed.host << "\n"
       << "Port:     " << parsed.port << "\n"
       << "Path:     " << parsed.path << "\n"
       << "Search:   " << parsed.search << std::endl;
}

