// Uri encode and decode.
// RFC1630, RFC1738, RFC2396
//
// Based (heavily) on an article from CodeGuru
// http://www.codeguru.com/cpp/cpp/string/conversions/article.php/c12759

#include <string>
#include <assert.h>

namespace uri {


//////////////////////////////////////////////////////////////
// Test codes start
#ifndef NDEBUG

class UriCodecTest
{
public:
    UriCodecTest();
};

static UriCodecTest test;   // auto run the test

#include <stdlib.h>
#include <time.h>

UriCodecTest::UriCodecTest()
{
    assert(UriEncode("ABC") == "ABC");
    
    const std::string ORG("\0\1\2", 3);
    const std::string ENC("%00%01%02");
    assert(UriEncode(ORG) == ENC);
    assert(UriDecode(ENC) == ORG);

    assert(UriEncode("\xFF") == "%FF");
    assert(UriDecode("%FF") == "\xFF");
    assert(UriDecode("%ff") == "\xFF");

    // unsafe chars test, RFC1738
    const std::string UNSAFE(" <>#{}|\\^~[]`");
    std::string sUnsafeEnc = UriEncode(UNSAFE);
    assert(std::string::npos == sUnsafeEnc.find_first_of(UNSAFE));
    assert(UriDecode(sUnsafeEnc) == UNSAFE);

    // random test
    const int MAX_LEN = 128;
    char a[MAX_LEN];
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < MAX_LEN; j++)
            a[j] = rand() % (1 << 8);
        int nLen = rand() % MAX_LEN;
        std::string sOrg(a, nLen);
        std::string sEnc = UriEncode(sOrg);
        assert(sOrg == UriDecode(sEnc));
    }
}
#endif  // !NDEBUG
// Test codes end
//////////////////////////////////////////////////////////////

}

