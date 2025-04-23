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
SC2_VCAMLOGIC_EP = "/api/management/v1/vcamlogic/devices"

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
    elif service == 'vcamlogic':
        return server + SC2_VCAMLOGIC_EP

def login():
    #username = input('Enter the server {} login Username: '.format(server))
    #password = input('Possword: ')

    #username = 'admin@jio.com'
    #password = 'Chawandi@99'

    # username = 'admin@airtel.com'
    # password = 'Chawandi@99'
    username = 'sysadmin@ewm.com'
    password = 'admin456'
    # username = 'admin@blr.com'
    # password = 'admin@blr.com'

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


def get_tenant_vcamlogic_devices(tenant_id):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('tenants')+"/"+tenant_id+"/vcamlogic/devices", headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            #print(server.json())
            return server.json()
    return ""

def get_tenant_vcamlogic_devices_by_device_id(tenant_id, device_id):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('tenants')+"/"+tenant_id+"/vcamlogic/devices/"+device_id, headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            #print(server.json())
            return server.json()
    return ""

def get_devices():
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('vcamlogic'), headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            #print(server.json())
            return server.json()
    return ""

def get_device_by_device_id(device_id):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('vcamlogic')+"/"+device_id, headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            #print(server.json())
            return server.json()
    return ""


def get_device_by_device_id_mac_slot_id(device_id, mac, slot_id):
    headers = { "Authorization": "Bearer "+ JWT }
    try:
        server = requests.get(get_url('vcamlogic')+"/"+device_id+"/camera/"+mac+"/slots/"+str(slot_id), headers=headers, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            #print(server.json())
            return server.json()
    return ""

def update_device_camera_slots_info_by_device_id(device_id):
    headers = { 'Authorization': 'Bearer '+ JWT,
                'Content-Type': 'application/json'  }

    payload = json.dumps(
        {
            "vcams":[ 
                {
                   "deviceId": device_id,
                    "mac": "a0:bd:1d:e0:7c:be",
                    "info": [
                        {
                            "slotIndex"    :  4,
#                            "uptime"		: round(time.time()),
                            "restartCount"	: 1,
                            "type"			: "STATUS",
                            "command"		: "STOP",
                            "status"		: "NOK",
                            "error"			: 
                            {
                                "state"	: "NO_DATA",
                                "msg"	: "Nodata for the past 10 seconds"
                            }
                        }
                    ]
                }
            ]
        })

    try:
        server = requests.put(get_url('vcamlogic'), headers=headers, data=payload, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(server.status_code)
    return ""


def update_tenant_vcamlogic_device_camera_slots_info_by_device_id(tenant_id, device_id):
    headers = { 'Authorization': 'Bearer '+ JWT,
                'Content-Type': 'application/json'  }

    payload = json.dumps(
        {
            "vcams":[ 
                {
                   "deviceId": device_id,
                    "mac": "a0:bd:1d:e0:7c:be",
                    "info": [
                        {
                            "slotIndex"    :  4,
#                            "uptime"		: round(time.time()),
                            "restartCount"	: 1,
                            "type"			: "STATUS",
                            "command"		: "",
                            "status"		: "OK",
                            "error"			: 
                            {
                                "state"	: "NO_DATA",
                                "msg"	: "Nodata for the past 10 seconds"
                            }
                        },
                    ]
                },
                                {
                   "deviceId": device_id,
                    "mac": "00:07:5f:b3:e7:77",
                    "info": [
                        {
                            "slotIndex"    :  7,
#                            "uptime"		: round(time.time()),
                            "restartCount"	: 1,
                            "type"			: "STATUS",
                            "command"		: "",
                            "status"		: "OK",
                            "error"			: 
                            {
                                "state"	: "NO_DATA",
                                "msg"	: "Nodata for the past 10 seconds"
                            }
                        },
                    ]
                }
            ]
        })

    try:
        server = requests.put(get_url('tenants')+"/"+tenant_id+"/vcamlogic/devices", headers=headers, data=payload, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(server.status_code)
    return ""


def send_device_camera_command_by_device_id(device_id):
    headers = { 'Authorization': 'Bearer '+ JWT,
                'Content-Type': 'application/json'  }

    payload = json.dumps( {
        "command": "RESTART",
        "command_type" : "VCAM",
        "vcams":[
            {
            "mac": "a0:bd:1d:e0:7c:be",
            "slotIndex"    :  4,
            "port" :"1000"
            },
            {
            "mac": "00:07:5f:b3:e7:77",
                "slotIndex": 7,
                "port": "0101"
            }
        ]
        })
#     payload = json.dumps(
#         {
#             "vcams":[ 
#                 {
#                    "deviceId": device_id,
#                     "mac": "a0:bd:1d:e0:7c:be",
#                     "info": [
#                         {
#                             "slotIndex"    :  4,
# #                            "uptime"		: round(time.time()),
#                             "restartCount"	: 1,
#                             "type"			: "STATUS",
#                             "command"		: "RESTART",
#                             "status"		: "OK",
#                             "error"			: 
#                             {
#                                 "state"	: "NO_DATA",
#                                 "msg"	: "Nodata for the past 10 seconds"
#                             }
#                         }
#                     ]
#                 }
#             ]
#         })

    try:
        server = requests.put(get_url('vcamlogic')+"/"+device_id+"/vcams/commands", headers=headers, data=payload, verify=False)
    except HTTPError  as http_err:
        print('HTTP error occured: {}'.format(http_err))
    except Exception as err:
        print('Other error occured: {}'.format(err))
    else:
            print(server.status_code)
    return ""


def main():
    err = login()
    if  err:
        print("failed to login, try agian!", err)
        return

    #create_infrastructure(name="ewd", i="4")

    #get_infrastrucuture("5f9027d9c5b3c200018eec0d")

    #update_infrastructure("5fcdee7761e63b0001535e7f")

    #update_device_camera_slots_info_by_device_id("60080ea5358b1700013631aa")

    #dev = get_device_by_device_id("60080ea5358b1700013631aa")
    #print(json.dumps(dev, indent = 3))

    #dev = get_devices()
    #print(json.dumps(dev, indent = 3))

    # slot_info = get_device_by_device_id_mac_slot_id("60080ea5358b1700013631aa", "a0:bd:1d:e0:7c:be", 4)
    # print(json.dumps(slot_info, indent = 3))

    #slot_info = get_device_by_device_id_mac_slot_id("60080ea5358b1700013631aa", "00:40:8c:ec:70:a1", 1)
    #print(json.dumps(slot_info, indent = 3))

    #send_device_camera_command_by_device_id("6012b264a4631d000129e221")

    #update_device_camera_slots_info_by_device_id("60080ea5358b1700013631aa")

    # count = get_infrastructure_count()
    # print(count)

    # #delete_infrastructure("5fce268f3af7fb0001ca170d")

    # print("*" * 100)
    #devices = get_tenant_vcamlogic_devices("253b2f39-a9a3-4e4c-abc8-79ecafbef1a0")
    #print(devices)
    # print(json.dumps(devices, indent = 3))
    # print("*" * 100)

    #update_tenant_vcamlogic_device_camera_slots_info_by_device_id("eca6911a-c98c-41f2-8029-8390f78005c1", "6012b264a4631d000129e221")

    #device = get_tenant_vcamlogic_devices_by_device_id("253b2f39-a9a3-4e4c-abc8-79ecafbef1a0", "601a4a693bf1a300014e348b")
    device = get_tenant_vcamlogic_devices_by_device_id("9c649cb9-f274-40ef-8dfc-4e546af1a759", "602a3900e454a9000143fc72")
    print(json.dumps(device, indent = 3))


if __name__ == "__main__":
    main()

