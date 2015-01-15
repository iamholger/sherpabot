#!/usr/bin/env python


def mkTStamp():
    import time
    ts = time.time()
    import datetime
    return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d')

def mkTarget(base):
    import os
    return os.path.join(base,mkTStamp())+"/"

def mkRsync(base, inputs, host="hschulz@hschulz-openstack3"):
    cmd = "rsync -Pravdtze ssh "
    for i in inputs:
        cmd += "%s "%i
    cmd += host+":"+mkTarget(base)
    return cmd

import os, sys

cmd=mkRsync(sys.argv[1], sys.argv[2:])
print cmd
os.system(cmd)


