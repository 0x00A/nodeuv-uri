#include <iostream>
#include <uri.h>

using namespace std;
using namespace uri;

int main() {

  string haystack = "http://user:password@www.google.com:80/path?search=foo&bar=bazz";

  for (int i = 0; i < 100000; i++) {
    ParseHttpUrl(haystack);
  }
}
