#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Main"""

from flask import Flask, request
import threading
import os

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
    print "Starting {0}".format(URL)
    APP = Flask(__name__)
    @APP.route(ENDPOINT, methods=['GET'])
    def main():
        return 'OK'
    def flask_thread():
        APP.run(debug=False, host=HOST, port=PORT)
    log_thread = threading.Thread(target=flask_thread)
    log_thread.start()
    print 'Server in bg mode'
