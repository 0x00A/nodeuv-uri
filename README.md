# SYNOPSIS
a little C++ library that parses URLs into bite-sized pieces.

# EXAMPLE
```cpp
#include <iostream>
#include <nodeuv-uri.h>

using namespace std;
using namespace uri;

int main() {

  string haystack = "http://user:password@www.google.com:80/path?search=foo&bar=bazz";

  auto u = ParseHttpUrl(haystack);
 
  cout << "Protocol:       " << u.protocol << "\n"
       << "User:           " << u.user << "\n"
       << "Password:       " << u.password << "\n"
       << "Host:           " << u.host << "\n"
       << "Port:           " << u.port << "\n"
       << "Path:           " << u.path << "\n"
       << "Search:         " << u.search << "\n"
       << "Query (search): " << u.query.at("search") << "\n"
       << "Query (bar):    " << u.query.at("bar") << "\n" << endl;
}
```

This is based on the url spec defined in 
[RFC 1738](http://www.ietf.org/rfc/rfc1738.txt).e

# License
This code is licensed under the [MIT License](http://opensource.org/licenses/MIT). See `LICENSE.txt`.

