#!/bin/bash


CURL=/usr/bin/curl

SERVER_IP_ADDRESS=$1

rtspurls=$(${CURL} --header "Content-Type: application/json" --request GET https://${SERVER_IP_ADDRESS}/bm/v1/bridges/info/all | jq -r .bridges[].rtspURL?)

for url in ${rtspurls}

do
    echo "Launch vlc for stream with url : ${url}"
    (vlc $url &)

done



