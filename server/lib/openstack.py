#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Openstack class"""

import requests

class Openstack(object):

    def __init__(self, host, project, username, password, iversion):
        self.endpoints = {
            'identity': 'http://{0}{1}'.format(host, iversion),
            'orch': 'http://{0}:8004/v1'.format(host),
            'compute': 'http://{0}:8774/v2.1'.format(host),
            'network': 'http://{0}:9696/v2.0'.format(host),
            'image': 'http://{0}:9696/v2.0'.format(host)
            }
        self.host = host
        self.project = project
        self.username = username
        self.password = password
        self.iversion = iversion
        print self.auth_token()

    def auth_token(self):
        auth_template = {'auth': 
                         {'identity': 
                          {'methods': ['password'], 
                           'password': {'user': {'name': self.username, 
                                                 'domain': {'name': self.project},
                                                 'password': self.password}}}}}
        resp = requests.post('{0}/auth/tokens'.format(self.endpoints['identity']),
                             headers={'Content-Type': 'application/json'},
                             json=auth_template)
        if resp.status_code == 201:
            return resp.headers['X-Subject-Token']
        else:
            return resp.status_code
