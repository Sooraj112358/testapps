import os
import time
import sys
import argparse
import uuid
import json

from pathlib import Path
import requests
from base64 import b64encode
from urllib.error import HTTPError
import urllib3


from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization


#disable InsecureRequestWarning
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)


JWT = ''

parser = argparse.ArgumentParser(prog="preauth", usage='sudo $(prog)s [options]', description="Prepare Preauth data for smarthingCloud")

parser.add_argument("-c", "--count", help="number of devices to pre-authorize, default 500")
parser.add_argument("-s", "--server", help="server url, default https://localhost")
parser.add_argument("-ft", "--fleet_type", help="type of fleet, possible values VSAAS or VMS")
parser.add_argument("-cn", "--config_name", help="configuration name to bind")
parser.add_argument("-fn", "--flavor_name", help="configuration flavor to bind")
parser.add_argument("-d", "--decommission", help="decommission simulated devices", action="count", default=0)
parser.add_argument("-pa", "--preauth", help = "preauthorize devices", action="count", default=0)


count = 100  # default nummber of devices
fleet_type = ''
config_name = ''
flavor_name = ''
#server = "https://ewm-preprod-saas.edgeway.io"
#server = "https://localhost"
#server = "https://ewm-preprod-mt.edgeway.io"
server = "https://10.27.15.75"

SC2_SERVER = server
SC2_LOGIN_EP = "/api/management/v1/useradm/auth/login"
SC2_CREATE_USER_EP = "/api/management/v1/useradm/users"
SC2_DEVICES_EP = "/api/management/v2/devauth/devices"
SC2_TENANTMAP_EP = "/api/management/v1/tenantadm/tdmap"
SC2_TENANTMAP_UUID_EP = "/api/management/v1/tenantadm/tdmap/devices"
SC2_TENANTS_EP = "/api/management/v1/tenantadm/tenants"
SC2_TENANTS_COUNT_EP = "/api/management/v1/tenantadm/tenants/count"
SC2_PREFERENCES_EP = "/api/management/v1/preferences/"
SC2_INFRA_MANAGER_EP = "/api/management/v1/infra_manager/infra"
SC2_INSTANCECONFIG_EP = "/api/management/v1/instanceConfig"

def get_url(service):
    global server
    if service == 'login':
        return server + SC2_LOGIN_EP
    elif service =='create_user':
        return server + SC2_CREATE_USER_EP
    elif service =='devices':
        return server + SC2_DEVICES_EP
    elif service =='tenantmap':
        return server + SC2_TENANTMAP_EP
    elif service =='tenantmap_uuid':
        return server + SC2_TENANTMAP_UUID_EP
    elif service == 'tenants':
        return server + SC2_TENANTS_EP
    elif service == 'tenants_count':
        return server + SC2_TENANTS_COUNT_EP
    elif service == 'preferences':
        return server + SC2_PREFERENCES_EP
    elif service == 'infra_manager':
        return server + SC2_INFRA_MANAGER_EP
    elif service == 'instanceconfig':
        return server + SC2_INSTANCECONFIG_EP

def login():
    #username = input('Enter the server {} login Username: '.format(server))
    #password = input('Possword: ')

    #username = 'admin@jio.com'
    #password = 'Chawandi@99'

    #username = 'admin@airtel.com'
    #password = 'Chawandi@99'
    username = 'sysadmin@ewm.com'
    password = 'admin456'

    hdr = '{}:{}'.format(username, password)
    hdr = b64encode(hdr.encode('utf-8'))

    headers = { "Authorization": "Basic "+ hdr.decode() }
    try:
        global JWT
        response = requests.post(get_url('login'), headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
        return http_err
    except Exception as err:
        print('Other error occured: {}'.format(err))
        return err
    else:
        if response.status_code == 200:
            print("logged in user {}".format(username))
            JWT = response.text
            print('*' * 80 + 'JWT' + '*' * 80)
            print(JWT)
            print('*' * 80 + 'JWT' + '*' * 80)
        else:
            return response.status_code
    return 0



def create_infrastructure(name, i):
    headers = { 'Authorization': 'Bearer '+ JWT,
                'Content-Type': 'application/json'  }

    payload = json.dumps({
            "name" : name,
            "instance_id": i,
            "public_ip": "10.23.01.200",
            "onvif_port_range" : {
                "start" : 7399,
                "end" : 7499
            },
            "rtsp_port_range" : {
                "start" : 7500,
                "end" : 7599
            }
    })

    try:
        rsp = requests.post(get_url('infra_manager'), headers=headers, data=payload,  verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
        if rsp.status_code >= 200 and rsp.status_code < 299:
            print("infrastructure created")
        else:
            print("failed to create infrastructure")
            print(rsp.text)
    return ""

def update_infrastructure(id):
    headers = { 'Authorization': 'Bearer '+ JWT,
                'Content-Type': 'application/json'  }

    payload = json.dumps({
            "onvif_port_range" : {
                "start" : 7499,
                "end" : 7499
            },
            "rtsp_port_range" : {
                "start" : 7500,
                "end" : 7500
            }
        })

    try:
        rsp = requests.put(get_url('infra_manager')+'/'+ id, headers=headers, data=payload,  verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
        if rsp.status_code >= 200 and rsp.status_code < 299:
            print("infrastructure updated")
            
        else:
            print("failed to update infrastructure")
            print(rsp.text)
        return rsp.text
    return ""



def get_infrastrucuture(identity):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('infra_manager')+"/"+identity, headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(json.dumps(server, indent = 3))
    return ""

def get_infrastrucuture_by_instance_id(identity):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('infra_manager')+"/instance/"+identity, headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(server.text)
    return ""

def get_infrastructure_count():
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('infra_manager')+"/servers/count", headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(server.text)
    return ""


def delete_infrastructure(identity):
    headers = { 'Authorization': 'Bearer '+ JWT }

    try:
        rsp = requests.delete(get_url('infra_manager')+"/"+identity, headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
        print("deleted infrastructure: {} ".format(identity))

def get_infrastrucutures():
    allInfras = []
    headers = { "Authorization": "Bearer "+ JWT }

    while True:
        try:
            #servers = requests.get(get_url('preferences')+"servers?page="+str(page)+"&per_page=20", headers=headers, verify=False)
            servers = requests.get(get_url('infra_manager'), headers=headers, verify=False)
        except HTTPError  as http_err:
             print('HTTP error occured: {}'.format(http_err))
        except Exception as err:
            print('Other error occured: {}'.format(err))
        else:
            try:
                servers.links["next"] == ""
            except KeyError as key_err:
                allInfras.extend(servers.json())
                return allInfras
            else:
                page = int(page) + 1
                allInfras.extend(servers.json())
    return ""

def get_users():
    headers = { "Authorization": "Bearer "+ JWT }

    try:
        #servers = requests.get(get_url('preferences')+"servers?page="+str(page)+"&per_page=20", headers=headers, verify=False)
        users = requests.get('https://ewm-preprod-mt.edgeway.io/api/management/v1/useradm/users', headers=headers, verify=False)
    except HTTPError  as http_err:
         print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
        print(users)
    return ""

def get_instance():
    headers = { "Authorization": "Bearer "+ JWT }

    try:
        config = requests.get(get_url('instanceconfig')+"/"+identity, headers=headers, verify=False)
        #users = requests.get('https://ewm-preprod-mt.edgeway.io/api/instanceConfig', headers=headers, verify=False)
    except HTTPError  as http_err:
         print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
        print(config)
    return ""


def main():
    err = login()
    if  err:
        print("failed to login, try agian!", err)
        return
    #get_infrastructure_count()
    #get_infrastrucutures()
    #get_infrastrucuture()
    #get_users()
    get_instance()

if __name__ == "__main__":
    main()

