
import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas,uuid
import qip

hdl = qip.open_connection(8888)

qip.execute(hdl,'{x}',ndata)

 atoms = qip.execute(hdl,'atoms')

t = atoms[['name','data']]

t['from_kdb'] = [ qip.execute(hdl,'{x}',row['data']) for _,row in t.iterrows() ]

t['isSame'] = t['data'] == t['from_kdb']

print(
    "Number of error: {}".format(len(t[~t['isSame']]))
    )

t = atoms[['name','ldata']]


for _ , row in t.iterrows() :
    print(qip.execute(hdl,'{x}',row['ldata']))


ldata = row['ldata']

ldata.item()



data = t['ldata'].iloc[4]

data.__class__.__name__

data.dtype.name

data.size

data.item(2)

t['ldata'].iloc[0]

qip.execute(hdl,'{x}',t['ldata'].iloc[4])



ValueError: The truth value of an array with more than one element is ambiguous. Use a.any() or a.all()

t['isSame'] = t['data'] == t['from_kdb']
