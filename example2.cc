#include <iostream>
#include <uri.h>

using namespace std;
using namespace uri;

int main() {

  cout << endl;

  string haystack = "http://user:password@www.google.com:80/path?search=http://foo.com&bar=bazz";

  cout << haystack << endl << endl;

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

