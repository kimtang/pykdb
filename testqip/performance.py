import os

from shutil import copyfile

os.getcwd()

copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

import numpy, pandas,uuid
import qip

hdl = qip.open_connection(8888)

tmp = numpy.linspace(1., 100., int(1e7))

from datetime import datetime

start_time = datetime.now()

tmp = qip.execute(hdl,'{0N!x}',tmp)

time_elapsed = datetime.now() - start_time

print('Time elapsed (hh:mm:ss.ms) {}'.format(time_elapsed))
