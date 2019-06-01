import os

from shutil import copyfile

os.getcwd()
copyfile('..\\x64\\Release\\qip.dll','qip.pyd')

from datetime import datetime
import numpy, pandas,uuid
import qip

# tmp = numpy.repeat(numpy.datetime64(datetime.now(),'D'),int(1e7))

nnows = dict(zip(["s","m","ms","ns"],[numpy.datetime64(datetime.now(),dtype0) for dtype0 in ["s","m","ms","ns"] ]))

hdl = qip.open_connection(8888)

def measure(dtype0):
    tmp = numpy.linspace(1., 100., int(1e7), dtype=dtype0)
    start_time = datetime.now()
    result = qip.execute(hdl,'{0N!x}',tmp)
    time_elapsed = datetime.now() - start_time
    isSame = result  == tmp
    print('Time elapsed for {} : {} : {}'.format(str(dtype0), time_elapsed, isSame.any()))

def measure1(dtype0):
    tmp = numpy.linspace(1, int(1e7), int(1e7), dtype=dtype0)
    start_time = datetime.now()
    result = qip.execute(hdl,'{0N!x}',tmp)
    time_elapsed = datetime.now() - start_time
    isSame = result  == tmp
    print('Time elapsed for {} : {} : {}'.format(str(dtype0), time_elapsed, isSame.any()))


def measure2(dtype0):
    tmp = numpy.repeat(numpy.datetime64(datetime.now(),dtype0),int(1e7))
    start_time = datetime.now()
    result = qip.execute(hdl,'{0N!x}',tmp)
    time_elapsed = datetime.now() - start_time
    isSame = abs((result  -  tmp).astype(int)) < 1000
    print('Time elapsed for {} : {} : {} '.format(str(tmp.dtype.name), time_elapsed, isSame.any()))


def measure3(dtype0):
    tmp =  numpy.repeat(numpy.datetime64(datetime.now(),dtype0),int(1e7)) - nnows[dtype0]
    start_time = datetime.now()
    result = qip.execute(hdl,'{0N!x}',tmp)
    time_elapsed = datetime.now() - start_time
    isSame = abs((result  -  tmp).astype(int)) < 1000
    print('Time elapsed for {} : {} : {} '.format(str(tmp.dtype.name), time_elapsed, isSame.any()))


# tmp = numpy.repeat(numpy.datetime64(datetime.now(),"ms"),int(1e7))
# result = qip.execute(hdl,'{0N!x}',tmp)


# tmp.astype("numpy.int64")

measure3("s")
measure3("m")
measure3("ms")
measure3("ns")

measure2("D")
measure2("M")
measure2("us")
measure2("ms")
measure2("ns")

measure(numpy.float64)
measure(numpy.float32)

measure1(numpy.int64)
measure1(numpy.int32)
measure1(numpy.int16)
measure1(numpy.int8)
measure1(numpy.bool)
