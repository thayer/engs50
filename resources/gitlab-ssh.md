---
layout: page
title: Gitlab with SSH
---

In CS50 we use the Git revision-control system, and specifically, our own [Gitlab](http://gitlab.cs.dartmouth.edu) server.
Connections between Gitlab and your computer - whether that be your laptop, or one of the CS Linux servers - are conducted over a secure connection, either using the **HTTPS** or **SSH** protocols.
Although it takes a little bit more set-up effort, SSH is the preferred choice and we find that it works better for students once it is set up.

### Instructions

1. Visit [Gitlab](http://gitlab.cs.dartmouth.edu) and click on your personal icon in the upper-right corner; pick *Settings* from the pop-up menu.
2. Click on *SSH Keys* in the list of panes across the top.
3. Log in to your account on the CS Linux server.
4. Check to see whether you already have an ssh key.
If so, it lives in the `.ssh` subdirectory of your home directory.
Try `cat ~/.ssh/id_rsa.pub`.
If you have a key, it will print out.
If not, you'll get an error `No such file or directory`.
4.
```bash
[kotz@flume ~]$ cat ~/.ssh/id_rsa.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDY035+DErTm2wKVK9OFgwpyGRjkEMXHyNPZ6gHmb+SQEmljyGwcJB6mQWIQZrII59m427gP81nvR3COD1iMH9SG67+odMlc4TL4959zkGJ7ycL8wmyLq1V7CTyE8mN0oYXD6YBve6C+38BAxdz5H2KWwem/45uwtJz8a5oIpVT6QY7clY2qinD8VCO6IUi4WBCFINYbp6PtV12bJYID8LMOShpljm4oyD3RFt4Ht+85/N2yCBLHydMO25MfLDxlIYav9Ky3S8LT+aojfb96W54h3r9YKG2KD/JQGnBzcZVTYPrFlEa2rLBUwqVo5ZjbKi9P/+HmtDAJOxrD+3038sV dfk@topdog.cs.dartmouth.edu
```

5. If you do *not* have an ssh key, generate one:
```
ssh-keygen -t rsa -C "YourUsername@cs.dartmouth.edu" -b 4096
```
then try `cat ~/.ssh/id_rsa.pub`.
6. Use your mouse to select the whole output of `cat`. Copy it to your clipboard.
7. Go back to your browser - still at the *SSH Keys* page on Gitlab - and paste your clipboard into that big box.
8. Click the *Add Key* button.
9. You should now use the SSH-style URL when cloning repos from Gitlab.
If you'd already cloned a repo with the HTTPS-style URL, see below.

Whenever you `git pull` or `git push` or other operations that involve the remote, you will need to enter the passphrase you provided when you generated the ssh keypair -- *not* your Gitlab password -- because you need to give `ssh` permission to use your private key to authenticate yourself to the remote Gitlab server.

### MacOS users

If you use a MacOS laptop and want to be able to clone from Gitlab repos to your Mac, copy your ssh keys to your laptop.

```bash
$ scp YourUsername@flume.cs.dartmouth.edu:.ssh/id_rsa     ~/.ssh/
$ scp YourUsername@flume.cs.dartmouth.edu:.ssh/id_rsa.pub ~/.ssh/
```

### Switching from HTTPS to SSH

If you already cloned a repo using the HTTPS-style URL and now want to use the SSH method, set up for SSH first, as above.
Then `cd` to the directory holding your clone.
You should see something like this.

```bash
$ git remote -v
origin	https://dfkotz@gitlab.cs.dartmouth.edu/dfkotz/demonstration.git (fetch)
origin	https://dfkotz@gitlab.cs.dartmouth.edu/dfkotz/demonstration.git (push)
```

Visit your repo's home page on Gitlab and find the box that holds the URL.
Click the pop-up next to that box, and choose SSH.
Copy the URL to your clipboard, and tell Git to set that URL as your `origin` instead:

```bash
$ git remote set-url origin git@gitlab.cs.dartmouth.edu:dfkotz/demonstration.git
$ git remote -v
origin	git@gitlab.cs.dartmouth.edu:dfkotz/demonstration.git (fetch)
origin	git@gitlab.cs.dartmouth.edu:dfkotz/demonstration.git (push)
```

### More help

See the [Gitlab SSH help](https://gitlab.cs.dartmouth.edu/help/ssh/README).
