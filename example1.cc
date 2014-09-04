#include <iostream>
#include <uri-parser.h>

using namespace std;
using namespace uri;

int main() {

  string haystack = "http://user:password@www.google.com:80/path?search";

  for (int i = 0; i < 100000; i++) {
    ParseHttpUrl(haystack);
  }
}
