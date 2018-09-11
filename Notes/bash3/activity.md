--- 
layout: page
title: Activity - shell script
--- 

Read [backup-diff.sh]({{site.examples}}/backup-diff.sh).

What does it do?

Now, make a copy for yourself,

```bash
cp ~cs50/examples/backup-diff.sh .
```

or, to work on your laptop,

```bash
scp username@flume.cs.dartmouth.edu:~cs50/examples/backup-diff.sh .
```

and modify your copy so it **exits with zero status when there are no differences, and non-zero status when there are any missing backups or differing files.**
