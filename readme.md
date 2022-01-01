# Simple Download Application

## Overview

The objective of this application is to develop a simple FTP client that retrieves a specified file using the FTP protocol as described in RFC959.

It should take an argument that adopts the URL syntax, as described in RFC1738.

#### Features:

- Describe client ⇄ server concept and its peculiarities in TCP/IP
- Characterize application protocols in general, characterize URL, describe in detail the behaviour of FTP
- Locate and read RFCs
- Implement a simple FTP client in C language
- Use sockets and TCP in C language
- Understand the service provided DNS and use it within a client program

## QUICK START

#### Usage:

`$ ftp://[<user>:<password>@]<host>/<url-path> -[mode]`
  
*Options:*
-A: Active mode
-P: Passive mode

*Example:* 

`$ ./download ftp://ftp.up.pt/pub/kodi/timestamp.txt -A`

*Note:* The server is in the lab, to access it you need to be connected through the FEUP VPN.