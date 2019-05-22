
import os
from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import qip

i = qip.khp('',8888)

k = qip.k2(i,'10 2 11 1 1 1 1f ')

# print qip.n(k)

# print qip.print0(i,'10 2 11 1 1 1 1f ')

print( "testing float")

for _ in qip.lF(k) : print(_)

print( k.t)

l = qip.ktn(9,10)

print( l.r)

l = qip.r1(l)

print( l.r)

print( qip.n(l))

print( range(10))

l.assignF(range(10))

for _ in qip.lF(l) : print( _)

qip.k3(i,"{0N!x}",l)

print( l.r)

l = qip.ktn(9,10)

# for f in qip.rangeF(k) :
#    print f
#

# print k.t

# k = qip.k0()


# k.k0
# print k.a
# print k.t
# print k.u
# print k.r
# print k.g
# print k.h
# print k.i
# print k.j
# print k.e
# print k.f
#
# qip.n(k)

# print k.s

# exit()
