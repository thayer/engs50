---
layout: page
title: Activity - Crawler
---

### Goals

* to start thinking about a design for the *Crawler*

### Activity

In your group, consider the following informal description of the **Crawler**:

* It takes three parameters: the URL for a web page to use as a starting point (*seed*) for the crawl, the *maximum depth* it should crawl from that seed, and the name of a *directory* where it can cache copies of the web pages it crawls.
* It should start from a given URL called the *seed*.
The web page at that URL is said to be at depth 0.
* It should *explore* that URL; that is, it should download the web page at that URL, and scan that page's HTML for embedded links to URLs.
(Assume you are given a function that can pick URLs out of HTML.)  When exploring a page at depth *d*, its embedded URLs refer to pages that are said to be at depth *d+1*.
* Ignore URLs that don't point at HTML.
* Ignore URLs at depth greater than *maxDepth*.
* Explore each non-ignored URL by downloading its HTML and scanning that HTML for URLs, as above.
* For each page it explores, it should create one file that contains the URL of that page, its depth in the crawl, and the HTML for that page.

***Discuss how you could structure a crawler to accomplish the above goals -- probably two nested loops -- and leverage your Lab 3 data structures.***
