#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Main"""

from flask import Flask, request
import threading
import os
import sys
from lib.openstack import Openstack

HOST = 'localhost'
PORT = 8887
ENDPOINT = '/test'
URL = 'http://{0}:{1}{2}'.format(HOST,
                                 PORT,
                                 ENDPOINT)

openstack = {}
vdu = {}
router = {}
network = {}

if __name__ == "__main__":

    if len(sys.argv) < 2:
        print 'Usage: {0} source.py\n'.format(sys.argv[0])
        exit(0)

    APP = Flask(__name__)

    @APP.route(ENDPOINT, methods=['GET'])
    def main():
        return 'OK'

    with open(sys.argv[1]) as fhandle:
        for x in fhandle.readlines():
            exec(x)


    def flask_thread():
        print "Starting {0}".format(URL)
#        APP.run(debug=False, host=HOST, port=PORT)
    log_thread = threading.Thread(target=flask_thread)
    log_thread.start()

    print 'Server in bg mode'
