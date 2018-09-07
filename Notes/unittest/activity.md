---
layout: page
title: Activity - Unit testing
---

Consider the simple one-function `jhash` module used in Lab3 and the TSE.
It comprises [jhash.c]({{site.labs}}/Lab3/starter/hashtable/jhash.c) and [jhash.h]({{site.labs}}/Lab3/starter/hashtable/jhash.h) and implements the `JenkinsHash()` function below.

1. With your group, list all the tests a good unit test should run against this unit.
* Can you spot the bug?  (I just noticed one I'd overlooked before.)
* If you have time,
	* download the above files, or copy them:
	* `cp ~cs50/public_html/Labs/Lab3/starter/hashtable/jhash.[ch] .`
	* extend `jhash.c` with a unit test like those we saw demonstrated in class today; you can `#include "unittest.h"` and copy that file from `~cs50/examples/unittest.h` for your testing.

```c
unsigned long
JenkinsHash(const char *str, unsigned long mod)
{
    if (str == NULL)
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
```

<!--
## Solution

The bug is actually a failure to be defensive in regards to the arguments.
If a caller passes `mod = 0` then this function will divide by zero and the program will crash.
The caller cannot pass a negative `mod` -- because the parameter is of `unsigned` type.
(It's worth considering whether `mod = 1` should be allowed -- with `mod = 1` the hash would always be zero.)

You could create some unit tests by adding the following to the bottom of `jhash.c`:

```c
#ifdef UNIT_TEST
#include <stdio.h>
#include "unittest.h"

int main()
{
  START_TEST_CASE("jhash");
  EXPECT(JenkinsHash(NULL, 1) == 0);
  EXPECT(JenkinsHash("", 1) == 0);
  EXPECT(JenkinsHash("CS50", 1) == 0);
  EXPECT(JenkinsHash("CS50", 99999) == JenkinsHash("CS50", 99999));
  EXPECT(JenkinsHash("CS50", 99999) == 18704);
  EXPECT(JenkinsHash("This is a very long string and it will make it hard to read this test; fortunately, the function does not care.", 99999) == 86041);

  END_TEST_CASE;
  return TEST_RESULT;
}

#endif // UNIT_TEST
```

I did not test the `mod = 0` case because I don't want to crash the program.
If I fix that bug by changing the first lines of the function:

```c
    if (str == NULL || mod <= 1)
      return 0;
```

I could then add another test case.

```c
  EXPECT(JenkinsHash("CS50", 0) == 0);
```

Here's the final [jhash.c](jhash.c).

-->
