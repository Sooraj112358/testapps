import base64
import requests
import urllib
from urllib.error import HTTPError

def login():
    #username = input('Enter the server {} login Username: '.format(server))
    #password = input('Possword: ')

    username = 'dp@SmarDTVEngineering.com'
    password = 'Aveiro35510!'

    hdr = '{}:{}'.format(username, password)
    print("1:", hdr)
    print("2:", hdr.encode('utf-8'))
    print("3:", base64.b64encode(hdr.encode('utf-8')))
    hdr = base64.b64encode(hdr.encode('utf-8'))
    print("4:", hdr)

    headers = { "Authorization": "Basic "+ hdr.decode() }
    print(headers)
    try:
        global JWT
        print("Post request")
        response = requests.post('https://ewm-preprod-mt.edgeway.io/api/management/v1/useradm/auth/login', headers=headers, verify=False)
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
            print("status_code:", response.status_code)
            return response.status_code
    return 0

login()