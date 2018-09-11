---
layout: page
title: Activity - strings are arrays
---

In C, a string is actually an array of characters, which (by convention) is terminated by a null (`\0`) character.

Examine this program, in `overflow.c`:

```c
...
int main() {
  int buflen = 16;
  char buf1[buflen];
  char buf2[buflen];
  int example = 0;

  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  // assign a constant to each buffer
  strcpy(buf1, "hello");  // like buf1 = "hello"
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  strcpy(buf2, "class!");  // like buf2 = "class!"
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  // assign a longer constant to each buffer
  strcpy(buf1, "hellohellohello"); // 15 characters
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  strcpy(buf2, "class!class!class!");  // 18 characters
  printf("%d: buf1='%s', buf2='%s'\n", example++, buf1, buf2);

  putchar ('\n');
  for (int i = 0; i < buflen; i++) {
    printf("buf1[%d] = '%c'\n", i, buf1[i]);
  }

  return 0;
}
```

Explain its output, below, which may not be what you expected!

```
0: buf1=W?P?', buf2='?V?P?'
1: buf1='hello', buf2='?V?P?'
2: buf1='hello', buf2='class!'
3: buf1='hellohellohello', buf2='class!'
4: buf1='s!', buf2='class!class!class!'

buf1[0] = 's'
buf1[1] = '!'
buf1[2] = ''
buf1[3] = 'l'
buf1[4] = 'o'
buf1[5] = 'h'
buf1[6] = 'e'
buf1[7] = 'l'
buf1[8] = 'l'
buf1[9] = 'o'
buf1[10] = 'h'
buf1[11] = 'e'
buf1[12] = 'l'
buf1[13] = 'l'
buf1[14] = 'o'
buf1[15] = ''
```
