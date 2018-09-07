---
layout: page
title: Activity - malloc
---

Starting with [names7.c]({{site.examples}}/names7.c), replace the line at the end of `main()`

```c
   // here we are lazy and do not free the list.
```

with a loop that calls `free()` on every malloc'd pointer in the list - so all malloc'd memory is free.
Be careful!

<!--
### Solution

[names8.c]({{site.examples}}/names8.c)

### Note
In class we only covered
[names3.c]({{site.examples}}/names3.c)
and
[names5.c]({{site.examples}}/names5.c)
so many groups worked from
[names5.c]({{site.examples}}/names5.c)
in developing their solution.
The same loop works for them as seen in
[names8.c]({{site.examples}}/names8.c).
-->
