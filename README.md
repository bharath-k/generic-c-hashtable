generic-c-hashtable
===================

Here's a generic implementation of hashtable based on APR(Apache Portable Runtime) for a pure C program. This works on both windows as well as unix provided apr packages are installed. Please refer to the APR documentation for installation in both windows and unix.

Build:
------
$ make

$ ./main

Notes:
------

The following links have some interesting questions I followed to choose APR over glib2. The main reason being portability to windows is well documented in apr compared to glib2.

http://programmers.stackexchange.com/questions/193733/a-simple-c-library-filling-the-gaps-in-standard-c-posix-libraries

http://programmers.stackexchange.com/questions/116650/is-there-any-boost-equivalent-library-for-c

http://tech.shantanugoel.com/2008/05/03/smart-programming-in-c-using-glib.html

http://www.drdobbs.com/cpp/general-purpose-c-libraries-limited-opti/231000967

Using apr:

http://people.apache.org/~rooneg/talks/portable-c-with-apr/apr.html

http://apr.apache.org/docs/apr/2.0/group__apr__hash.html

Using glib2:

http://www.gtk.org/

http://www.ibm.com/developerworks/linux/tutorials/l-glib/
