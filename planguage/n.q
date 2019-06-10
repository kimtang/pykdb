args:.Q.def[`name`port!("n.q";8890);].Q.opt .z.x

/ remove this line when using in production
/ n.q:localhost:8890::
{ if[not x=0; @[x;"\\\\";()]]; value"\\p 8890"; } @[hopen;`:localhost:8890;0];


if[not `bt in key `;system "l bt.q"];

\d .n
dll:`:C:/q/nlanguage/w32/piq

init:dll 2:(`py_initialize;1);

.n.set:dll 2:(`set;2);
.n.get:dll 2:(`get;1);

.n.eval:dll 2:(`eval3;1);
.n.exec:dll 2:(`exec3;1);

con:{distinct `$ ssr[;"`";""] each res where {x like "`*"} res:{raze y vs/:x} over enlist[enlist x]," $(,~=<-)"}

e:{ {.n.set[string x]value x }@'t:.n.con x ;.n.exec ssr[;"`";""] x}

/ .n.con "plt.plot(`t,`s)"


\d .


.n.init[];

n)import pandas,numpy,uuid
n)import matplotlib
n)matplotlib.use('TkAgg')
n)import matplotlib.pyplot as plt
n)import numpy as np


n)t = np.arange(0.0, 2.0, 0.01)
n)s = 1 + np.sin(2 * np.pi * t)

a:.n.get "t"
b:.n.get "s"

n)fig, ax = plt.subplots()
n)plt.plot(`a, `b)

n)ax.set(xlabel='time (s)', ylabel='voltage (mV)',title='About as simple as it gets, folks')
n)ax.grid()

n)fig.savefig("test.png")
n)plt.show()
