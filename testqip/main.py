
import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas,uuid
import qip

hdl = qip.open_connection(8888)
guid = qip.execute(hdl,'0N!first 1?0ng')

guid

lguid = qip.execute(hdl,'0N!3?0ng')

lguid

abc = qip.execute(hdl,'{0N!x}',guid)

abc

atoms = qip.execute(hdl,'atoms')

atoms

guid
larray = qip.execute(hdl,'{0N!x}',guid)

type(larray)

qip.execute(hdl,'{1=x}',tmp)

qip.execute(hdl,'{1=x}',tmp)

k = qip.execute(hdl,'1 1')

k

k = qip.execute(hdl,'([]a:1 1)')

k = qip.execute(hdl,'`a`b! (1 2;`a`b! 1 2)')

k

# k = qip.execute(hdl,'1+abc')

# qip.execute(hdl,"{0N!x}",1)
