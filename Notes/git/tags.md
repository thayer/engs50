---
layout: page
title: Extra - Using Git Tags
---

### Students:

As a member of some project, you can add tags to your repository.
Tags are nice for adding annotations to your history.
Tags don’t change your commit history but they can be used as a sort of bookmark.
I often use tags for highlighting new versions or milestones in my projects.
When you submit `lab4` (the crawler), that is a sort of milestone that says "OK, I’ve finished the Crawler.
I’m ready to move on to the Indexer!" A couple of weeks (or months or years) from now you might be interested in revisiting the state of your code when you had finished the crawler, for example.
Rather than trying to remember some long git hash for your last commit of `lab4`, and to help us (and your future selves), we want you to add a `tag` to the project to indicate when the work is complete for `lab4`.
By default `git tag TAGNAME` will add a tag to the current `HEAD` of your working tree.

```
$ git tag lab4submit
```

You can also add a `tag` to a previous commit -- this might be useful if you charged ahead and made a few commits but want to go back and mark some commit in the past with a `tag`:

```
$ git tag oops d4fd63a
```

If you accidentally add a `tag` or add a `tag` to the wrong commit, you can always delete a `tag` by using the -d flag and identifying the `tag` by the name you gave it.

```
$ git tag -d oops
```

*This method only affects the local repository.*
If you have already pushed a tag to the remote, you need to run a specific command to remove that tag from the remote.
To remove tag `oops`,

```
$ git push --delete origin oops
```

Once you've pushed your tags to the remote, you should go to GitLab and verify that you can see any tags that you've created and pushed.
On the main page of your project (in GitLab) you should see buttons for *commits*, *branches*, and *tags*.
Click on *tags*.
Alternatively, you can click on the *commits* icon in the left navbar and it will take you to a screen where you can browse things like commits, branches, and tags.

An alternative way to delete an already-pushed tag is to visit the *tags* page in Gitlab and click on the trash-can icon to delete that tag.
That change affects the remote repo, but not your local repo, so you need to `git pull` in your Terminal to update your local repo from the remote.

To learn more about `git tag`, run `git help tag`.
It actually has a nice section about how to delete already-pushed tags or to 'move' a tag to a newer commit.

### Graders:

For the sake of transparency, let's take a quick look at how we, as graders, will use the tags you create to checkout appropriate versions of your code.
For example, we will do something akin to the following when we go to grade your lab4 submission (the crawler):

Clone the student repo.

```
$ git clone URL
```

List any/all existing tags—we should hopefully see the appropriate submission tag (e.g., lab4submit)

```
$ git tag -l
```

Now we can checkout the code that was in the repo at the time of that tag (i.e., the state of the code at the time of submitting lab4).

```
$ git checkout tags/lab4submit
```

We can create a new branch from the code base at the point of the specified tag; the grader can now freely edit the code and there are no concerns about messing up anything on the master branch.

```
$ git checkout tags/lab4submit -b lab4testing
```
