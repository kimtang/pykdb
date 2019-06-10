args:.Q.def[`name`port!("test.q";8889);].Q.opt .z.x

/ remove this line when using in production
/ test.q:localhost:8889::
{ if[not x=0; @[x;"\\\\";()]]; value"\\p 8889"; } @[hopen;`:localhost:8889;0];


piq:`$":..\\piq\\Release\\piq";

py_initialize:piq 2:(`py_initialize;1);

set0:piq 2:(`set;2);
get0:piq 2:(`get;1);

eval3:piq 2:(`eval3;1);
exec3:piq 2:(`exec3;1);

py_initialize[];

exec3["import numpy,pandas,uuid"];

0N!enlist[a;] a ~ b:get0 set0["abc"] a:1000i;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:1000j;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:1000e;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:1000f;



0N!enlist[a;] a ~ b:get0 set0["abc"] a:10?1000i;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:10?1000j;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:10?1000e;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:10?1000f;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:(1;1f;1 2 3i);

0N!enlist[a;] a ~ b:get0 set0["abc"] a:.z.t;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:`second$.z.t;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:`minute$.z.t;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:`timespan$ .z.T;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:`datetime$.z.P;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:.z.d;
0N!enlist[a;] a ~ b:get0 set0["abc"] a:`month$.z.P;

0N!enlist[a;] a ~ b:get0 set0["abc"] a:`timestamp$.z.P;

/ Exception for symbols
0N!enlist[a;] string[a] ~ b:get0 set0["abc"] a:`abc;

/ Exception for char
0N!enlist[a;] a ~ first b:get0  set0["abc"] a:"a";
0N!enlist[a;] a ~ b:get0  set0["abc"] a:1f;
0N!enlist[a;] a ~ `real$b:get0  set0["abc"] a:1e;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:1;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:1i;
0N!enlist[a;] a ~ `short$b:get0  set0["abc"] a:1h;

/ set0["abc"] a:first 1?0ng

0N!enlist[a;] a ~ b:get0 set0["abc"]`byte$a:221i;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:1b;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:0b;

0N!enlist[a;] a ~ b:get0  set0["abc"] a:(1;1f;1b);
0N!enlist[a;] a ~ b:get0  set0["abc"] a:111000b;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:`byte$1 2 3 4h;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:10?1000i;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:10?1000j;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:10?1000e;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:10?1000f;

0N!enlist[a;] a ~ b:get0  set0["abc"] a:"abcdefg";
0N!enlist[a;] a ~ b:`$get0 set0["abc"] a:`ab`bb`cb`d;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:3?.z.P;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:`month$3?.z.P;

0N!enlist[a;] a ~ b:get0  set0["abc"] a:3?.z.d;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:3?.z.z;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:3?.z.n;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:`minute$3?.z.n;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:`second$3?.z.n;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:3?.z.t;
0N!enlist[a;] a ~ b:get0  set0["abc"] a:`a`bc!(1 2;2 2);
0N!enlist[a;] a ~ b:get0  set0["abc"] a:flip `a`bc!(1 2;2 2);
0N!enlist[a;] a ~ b:get0 set0["abc"] 2!a:flip `a`b`c!(1 2 3;2 2 2;3 4 5);
