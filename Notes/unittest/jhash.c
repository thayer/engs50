/* =========================================================================
 * jhash.c - Jenkins' Hash, maps from string to integer
 *
 * ========================================================================= 
 */

#include <string.h>
#include "jhash.h" 

// JenkinsHash - see header file for usage
unsigned long
JenkinsHash(const char *str, unsigned long mod)
{
    if (str == NULL || mod <= 1)
      return 0;

    size_t len = strlen(str);
    unsigned long hash, i;

    for (hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}

#ifdef UNIT_TEST
#include <stdio.h>
#include "unittest.h"

int main()
{
  START_TEST_CASE("jhash");
  EXPECT(JenkinsHash(NULL, 1) == 0);
  EXPECT(JenkinsHash("", 1) == 0);
  EXPECT(JenkinsHash("CS50", 0) == 0);
  EXPECT(JenkinsHash("CS50", 1) == 0);
  EXPECT(JenkinsHash("CS50", 99999) == JenkinsHash("CS50", 99999));
  EXPECT(JenkinsHash("CS50", 99999) == 18704);
  EXPECT(JenkinsHash("This is a very long string and it will make it hard to read this test; fortunately, the function does not care.", 99999) == 86041);
  
  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST
