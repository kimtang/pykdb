
import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas,uuid
import qip

hdl = qip.open_connection(8888)

atoms = qip.execute(hdl,'atoms')

tmp = 1,2

abc = qip.execute(hdl,'{} 1')

abc==None

qip.execute(hdl,'{0N!x}',tmp)

fatoms = qip.execute(hdl,'`ndata _ flip atoms')

fatoms.keys()

fatoms['ldata'][1:4]

qip.execute(hdl,'{0N!x}',fatoms)

qip.execute(hdl,'{0N!x}',fatoms['ldata'])


1

t = atoms[['name','data']]

t['from_kdb'] = [ qip.execute(hdl,'{x}',row['data']) for _,row in t.iterrows() ]

t['isSame'] = t['data'] == t['from_kdb']

print(
    "Number of error: {}".format(len(t[~t['isSame']]))
    )

t = atoms[['name','ldata']]

t['from_kdb'] = [ qip.execute(hdl,'{x}',row['ldata']) for _,row in t.iterrows() ]

t['isSame'] = t['ldata'] == t['from_kdb']

print(
    "Number of error: {}".format(len(t[~t['isSame']]))
    )
