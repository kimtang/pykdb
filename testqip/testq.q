args:.Q.def[`name`port!("test.q";8888);].Q.opt .z.x

/ remove this line when using in production
/ test.q:localhost:8888::
{ if[not x=0; @[x;"\\\\";()]]; value"\\p 8888"; } @[hopen;`:localhost:8888;0];


(::)N:((type 0#0)$10 xexp) 1

date:asc N?.z.d;time:asc N?.z.t;dtime:`datetime$asc ptime:(N?1000000)+date+time;sym:N?`a`bb`ccc;prx:N?100+0.01*1+N?100;qty:1+N?1000;b:N?10b

{([]mon:x)}mon:`month$dtime
{([]yea:x)}yea: `year$dtime
{([]minu:x)}minu:`minute$dtime
{([]sec:x)}sec:`second$dtime
{([]tim:x)}tim:(N?1000000)+`timespan$dtime

(::)t:([]sym;date;time;dtime;ptime;prx;qty;b)

cons:flip `address`userid`handle`arg!()

.z.po:{0N!"Port opened\n";0N!r:(.z.a;.z.u;.z.w;x);`cons insert r;}
.z.pc:{0N!"Port closed\n";0N!r:(.z.a;.z.u;.z.w;x);delete from `cons where handle = x;x}
.z.ps:{[x]0N!(`zps;x);value x}
.z.pg:{[x]0N!(`zpg;x);value x}
