
import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas
import qip

hdl = qip.open_connection(8888)

e = qip.execute(hdl,'1')

k = qip.execute(hdl,'1 1')

k

k = qip.execute(hdl,'([]a:1 1)')

k = qip.execute(hdl,'`a`b! (1 2;`a`b! 1 2)')

k

k = qip.execute(hdl,'1+abc')

qip.execute(hdl,"{0N!x}",1)
