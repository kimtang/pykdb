
PyKDB for communication between Python and KDB+
=====

PyKDB provides two modules to call kdb+ from python and vice-versa designed for both *efficiency* and *flexibility*. In its core PyKDB is just a wrapper around [k.h](https://github.com/KxSystems/kdb/blob/master/c/c/k.h) but it can automatically convert kdb+ objects to numpy/uuid/pandas objects. This makes it quite flexible to interact between kdb+ and python. Also pykdb is using [boost.python](https://www.boost.org/doc/libs/1_70_0/libs/python/doc/html/index.html) and [Boost.Python NumPy](https://www.boost.org/doc/libs/1_70_0/libs/python/doc/html/numpy/index.html) to enable seamless interoperability between kdb+ and the Python programming language. This also means that pykdb can be compiled on any platforms like win32/win64/macos and any unix systems.

qip (q in python)
--------


piq (python in q)
--------


Features
--------

License
-------
Licensed under MIT License.