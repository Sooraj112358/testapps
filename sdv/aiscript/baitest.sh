#!/bin/bash

# This file needs to be sourced by sbs_edgeway.sh for prints to work


source sbs_misc.sh

#BAI test functions

bm_bai_test()
{
    ip=$1
    delay=$2
    loops=$3
    msg "bm_bai_test ip:$ip delay:$delay loops:$loops"
    for i in $(seq 1 $loops)
    do
        msg_yellow "Test $i "
        curl --header "Content-Type: application/json" --request POST --data '{"name":"xyz","email":"xyz@gmail.com"}' http://$ip:80/ai-event
		if [[ $delay != 0 ]]; then
			msg_yellow "Wait for $delay secs"
			sleep $delay
		fi
    done
    msg_green "bm_bai_test done"

}

bai_test_all()
{
    #Run all the tests
    ip=$1
    delay=0
    loops=1111
    bm_bai_test $ip $delay $loops

    msg_green "bm_test_all executed"
}


#################################################################################
# Main Script
#################################################################################

if [[ $_ == $0 ]]; then
    { echo "Failure, reason : This script must be sourced" ; return 1; }
fi


