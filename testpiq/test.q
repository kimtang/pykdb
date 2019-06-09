args:.Q.def[`name`port!("test.q";8888);].Q.opt .z.x

/ remove this line when using in production
/ test.q:localhost:8888::
{ if[not x=0; @[x;"\\\\";()]]; value"\\p 8888"; } @[hopen;`:localhost:8888;0];


piq:`$":..\\piq\\Release\\piq";

py_initialize:piq 2:(`py_initialize;1);

set0:piq 2:(`set;2);
get0:piq 2:(`get;1);

eval3:piq 2:(`eval3;1);
exec3:piq 2:(`exec3;1);

py_initialize[];

exec3["import numpy,pandas,uuid"];

a ~ b:get0 set0["abc"] a:1000i
a ~ b:get0 set0["abc"] a:1000j
a ~ b:get0 set0["abc"] a:1000e
a ~ b:get0 set0["abc"] a:1000f



a ~ b:get0 set0["abc"] a:10?1000i
a ~ b:get0 set0["abc"] a:10?1000j
a ~ b:get0 set0["abc"] a:10?1000e
a ~ b:get0 set0["abc"] a:10?1000f
a ~ b:get0 set0["abc"] a:(1;1f;1 2 3i)

a ~ b:get0 set0["abc"] a:.z.t
a ~ b:get0 set0["abc"] a:`second$.z.t
a ~ b:get0 set0["abc"] a:`minute$.z.t
a ~ b:get0 set0["abc"] a:`timespan$ .z.T
a ~ b:get0 set0["abc"] a:`datetime$.z.P
a ~ b:get0 set0["abc"] a:.z.d
a ~ b:get0 set0["abc"] a:`month$.z.P

a ~ b:get0 set0["abc"] a:`timestamp$.z.P

/ Exception for symbols
string[a] ~ b:get0 set0["abc"] a:`abc

/ Exception for char
a ~ first b:get0  set0["abc"] a:"a"
a ~ b:get0  set0["abc"] a:1f
a ~ `real$b:get0  set0["abc"] a:1e
a ~ b:get0  set0["abc"] a:1
a ~ b:get0  set0["abc"] a:1i
a ~ `short$b:get0  set0["abc"] a:1h

/ set0["abc"] a:first 1?0ng

a ~ b:get0 set0["abc"]`byte$a:221i

a ~ b:get0  set0["abc"] a:1b
a ~ b:get0  set0["abc"] a:0b

a ~ b:get0  set0["abc"] a:(1;1f;1b)

a ~ b:get0  set0["abc"] a:111000b

a ~ b:get0  set0["abc"] a:`byte$1 2 3 4h

a ~ b:get0  set0["abc"] a:10?1000i
a ~ b:get0  set0["abc"] a:10?1000j
a ~ b:get0  set0["abc"] a:10?1000e
a ~ b:get0  set0["abc"] a:10?1000f

a ~ b:get0  set0["abc"] a:"abcdefg"
a ~ b:`$get0 set0["abc"] a:`ab`bb`cb`d

a ~ b:get0  set0["abc"] a:3?.z.P
a ~ b:get0  set0["abc"] a:`month$3?.z.P

a ~ b:get0  set0["abc"] a:3?.z.d
a ~ b:get0  set0["abc"] a:3?.z.z
a ~ b:get0  set0["abc"] a:3?.z.n
a ~ b:get0  set0["abc"] a:`minute$3?.z.n
a ~ b:get0  set0["abc"] a:`second$3?.z.n
a ~ b:get0  set0["abc"] a:3?.z.t
a ~ b:get0  set0["abc"] a:`a`bc!(1 2;2 2)
a ~ b:get0  set0["abc"] a:flip `a`bc!(1 2;2 2)
a ~ b:get0 set0["abc"] 2!a:flip `a`b`c!(1 2 3;2 2 2;3 4 5)
