
import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas,uuid
import qip

hdl = qip.open_connection(8888)

atoms = qip.execute(hdl,'atoms')

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
