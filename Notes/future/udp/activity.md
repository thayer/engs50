---
layout: page
title: Activity - Networking with UDP
---

Log in to one of the Linux servers and go to the demo directory:

```
cd ~cs50/demo/client-server-udp-select
```

One person in your group should run the `chatserver2` and the others in your group should run `chatclient2` to connect to it and write some encouraging remarks.

What happens when several clients connect to the same server?

What happens when the server exits and the chatclients keep sending it datagrams?

What happens when the client exits but the chatserver keeps sending it datagrams?

### Tweak!

One person should grab a copy of the example UDP client-server code in [examples/client-server-udp-select]({{site.examples}}/client-server-udp-select) or copy it from `~cs50/examples/client-server-udp-select`.

Edit `chatserver2.c` to comment out one line (*just one line*) inside the `handle_socket()` function:

```c
      if (themp->sin_family != AF_INET)
```

Compile with `make` and run this new `chatserver2`, and ask your groupmates to use the unchanged `chatclient2` to chat with your new server.
How does the behavior change? Why?

### MacOS

If you run the server on your Mac, remember that you can look up the current IP address for your Mac with the following command;

	ifconfig | grep 'inet '
	
you want the IP address that is not 127.0.0.1 (aka *localhost*).
The `chatclient` is happy to take an IP address where it expects a `hostname` argument.
