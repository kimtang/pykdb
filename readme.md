
PyKDB for communication between Python and KDB+
=====

PyKDB provides two modules to call kdb+ from python and vice-versa designed for both *efficiency* and *flexibility*. In its core PyKDB is just a wrapper around [k.h](https://github.com/KxSystems/kdb/blob/master/c/c/k.h) but it can automatically convert kdb+ objects to numpy/uuid/pandas objects. This makes it quite flexible to interact between kdb+ and python. Also pykdb is using [boost.python](https://www.boost.org/doc/libs/1_70_0/libs/python/doc/html/index.html) and [Boost.Python NumPy](https://www.boost.org/doc/libs/1_70_0/libs/python/doc/html/numpy/index.html) to enable seamless interoperability between kdb+ and the Python programming language. This also means that pykdb can be compiled on any platforms like win32/win64/macos and any unix systems.

qip (q in python)
--------
![qip in action](https://bitbucket.org/kuentang/pykdb/src/master/gif/piq.gif)

```
$ python                                                                                                                                                  
Python 3.6.7 (default, Feb 28 2019, 07:28:18) [MSC v.1900 64 bit (AMD64)] on win32                                                                        
Type "help", "copyright", "credits" or "license" for more information.                                                                                    
>>> import qip,numpy,pandas,uuid                                                                                                                          
>>> hdl = qip.open_connection(8888)                                                                                                                       
>>> hdl                                                                                                                                                   
996                                                                                                                                                       
>>> qip.execute(hdl,'1')                                                                                                                                  
1                                                                                                                                                         
>>> qip.execute(hdl,'1f')                                                                                                                                 
1.0                                                                                                                                                       
>>> qip.execute(hdl,'til 10')                                                                                                                             
array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], dtype=int64)                                                                                                        
>>> qip.execute(hdl,'{til x}',10)                                                                                                                         
array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], dtype=int64)                                                                                                        
>>> vec = qip.execute(hdl,'{til x}',10)                                                                                                                   
>>> vec = qip.execute(hdl,'{x + til count x}',vec)                                                                                                        
>>> vec                                                                                                                                                   
array([ 0,  2,  4,  6,  8, 10, 12, 14, 16, 18], dtype=int64)                                                                                              
>>> qip.execute(hdl,'.z.D + til 10 ')                                                                                                                     
array(['2019-06-12', '2019-06-13', '2019-06-14', '2019-06-15',                                                                                            
       '2019-06-16', '2019-06-17', '2019-06-18', '2019-06-19',                                                                                            
       '2019-06-20', '2019-06-21'], dtype='datetime64[D]')                                                                                                
>>> qip.execute(hdl,'.z.P + til 10 ')                                                                                                                     
array(['2019-06-12T12:30:03.909487000', '2019-06-12T12:30:03.909487001',                                                                                  
       '2019-06-12T12:30:03.909487002', '2019-06-12T12:30:03.909487003',                                                                                  
       '2019-06-12T12:30:03.909487004', '2019-06-12T12:30:03.909487005',                                                                                  
       '2019-06-12T12:30:03.909487006', '2019-06-12T12:30:03.909487007',                                                                                  
       '2019-06-12T12:30:03.909487008', '2019-06-12T12:30:03.909487009'], dtype='datetime64[ns]')                                                         
>>> qip.execute(hdl,'.z.t + til 10 ')                                                                                                                     
array([37807949, 37807950, 37807951, 37807952, 37807953, 37807954,                                                                                        
       37807955, 37807956, 37807957, 37807958], dtype='timedelta64[ms]')                                                                                  
>>> qip.execute(hdl,'`a`b! 1 2')                                                                                                                          
{'a': 1, 'b': 2}                                                                                                                                          
>>> qip.execute(hdl,'`a`b! (til 10; 2)')                                                                                                                  
{'a': array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], dtype=int64), 'b': 2}                                                                                         
>>> qip.execute(hdl,'flip `a`b! (til 10; 3+til 10)')                                                                                                      
   a   b                                                                                                                                                  
0  0   3                                                                                                                                                  
1  1   4                                                                                                                                                  
2  2   5                                                                                                                                                  
3  3   6                                                                                                                                                  
4  4   7                                                                                                                                                  
5  5   8                                                                                                                                                  
6  6   9                                                                                                                                                  
7  7  10                                                                                                                                                  
8  8  11                                                                                                                                                  
9  9  12                                                                                                                                                  
>>> tbl = qip.execute(hdl,'flip `a`b! (til 10; 3+til 10)')                                                                                                
>>> qip.execute(hdl,'{x}',tbl)                                                                                                                            
   a   b                                                                                                                                                  
0  0   3                                                                                                                                                  
1  1   4                                                                                                                                                  
2  2   5                                                                                                                                                  
3  3   6                                                                                                                                                  
4  4   7                                                                                                                                                  
5  5   8                                                                                                                                                  
6  6   9                                                                                                                                                  
7  7  10                                                                                                                                                  
8  8  11                                                                                                                                                  
9  9  12                                                                                                                                                  
```

piq (python in q)
--------
![piq in action](https://bitbucket.org/kuentang/pykdb/src/master/gif/piq.gif)

```
$ C:\q\w32\q.exe
KDB+ 3.6 2018.12.24 Copyright (C) 1993-2018 Kx Systems
w32/ 24()core 4095MB kuent desktop-u2c0ace 192.168.56.1 NONEXPIRE

q)piq:`$"C:\\q\\nlanguage\\w32\\piq"
q)py_initialize:piq 2:(`py_initialize;1);
q)set0:piq 2:(`set;2);
q)get0:piq 2:(`get;1);
q)eval3:piq 2:(`eval3;1);
q)exec3:piq 2:(`exec3;1);
q)py_initialize[];
q)exec3["import numpy,pandas,uuid"];
q)0N!enlist[;a;b] a ~ b:get0 set0["abc"] a:1000i;
(1b;1000i;1000i)
q)0N!enlist[;a;b] a ~ b:get0 set0["abc"] a:1000f;
(1b;1000f;1000f)
q)0N!enlist[;a;b] a ~ b:get0 set0["abc"] a:til 3;
(1b;0 1 2;0 1 2)
q)0N!enlist[;a;b] a ~ b:get0  set0["abc"] a:flip `a`bc!(1 2;2 2);
(1b;+`a`bc!(1 2;2 2);+`a`bc!(1 2;2 2))
```

Features
--------

License
-------
Licensed under MIT License.