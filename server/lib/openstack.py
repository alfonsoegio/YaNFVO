#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Openstack class"""

class Openstack(object):

    def __init__(host, project, username, password, iversion):
        self.endpoints = [
            'http://{0}{1}'.format(host, iversion),
            'http://{0}:8004/v1'.format(host),
            'http://{0}:8774/v2.1'.format(host),
            'http://{0}:9696/v2.0'.format(host),
            'http://{0}:9292/v2.0'.format(host),
            'dns=8.8.8.8'
        ]
