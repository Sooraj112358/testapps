#!/bin/bash


#BM test functions

bm_bridge_stop_test()
{
    ip=$1
    delay=$2
    msg "bm_bridge_stop_test $ip $delay"
    #Get the list of bridges running
    bridge_list_before=$(pgrep bridge-rtsp)
    array=( $bridge_list_before )
    bridge_count_before=${#array[@]}
    if [ "$bridge_count_before" -eq "0" ]; then
        msg_red "Bridges not running, count=$bridge_count_before "
        return 1
    fi
    curl --header "Content-Type: application/json" --request POST --data '{"bridges":[]}' http://$ip:9200/bm/v1/bridges/stop
    duration=$((delay * bridge_count_before))
    msg_yellow "Wait for $duration secs for result"
    sleep $duration
    bridge_list_after=$(pgrep bridge-rtsp)
    array=( $bridge_list_after )
    bridge_count_after=${#array[@]}
    if [ $bridge_count_after -eq 0 ]
    then
        msg_green "Test $i iternation of bm_bridge_stop_test passed"
    else
        msg_red "Test $i iternation of bm_bridge_stop_test failed"
        msg_yellow "bridge pid list before $bridge_list_before and count $bridge_count_before"
        msg_yellow "bridge pid list after $bridge_list_after and count $bridge_count_after"
    fi
    msg_green "bm_bridge_stop_test done"

}


bm_bridge_restart_test()
{
    ip=$1
    delay=$2
    loops=$3
    msg "bm_bridge_restart_test $ip $delay $loops"
    for i in $(seq 1 $loops)
    do
        #Get the list of bridges running
        bridge_list_before=$(pgrep bridge-rtsp)
        bridge_array_before=( $bridge_list_before )
        bridge_count_before=${#bridge_array_before[@]}
        if [ "$bridge_count_before" -eq "0" ]; then
            msg_red "Bridges not running, count=$bridge_count_before "
            return 1
        fi
        msg_yellow "Test $i "
        curl --header "Content-Type: application/json" --request POST --data '{"bridges":[]}' http://$ip:9200/bm/v1/bridges/restart
        duration=$((delay * bridge_count_before))
        msg_yellow "Wait for $duration secs for result"
        sleep $duration
        #Confirm all the brideges are back
        bridge_list_after=$(pgrep bridge-rtsp)
        bridge_array_after=( $bridge_list_after )
        bridge_count_after=${#bridge_array_after[@]}
        if [ $bridge_count_before -eq $bridge_count_after ]
        then
            for idx in "${bridge_array_before[@]}"
            do
                if [ ${#bridge_array_before[@]} -eq ${#bridge_array_after[@]} ]; then
                    msg_yellow "Test $idx ${bridge_array_before[$idx]} - ${bridge_array_after[$idx]}  "
                fi
            done
            msg_green "Test $i iternation of bm_bridge_restart_test passed"
        else
            msg_red "Test $i iternation of bm_bridge_restart_test failed"
            msg_yellow "bridge pid list before $bridge_list_before and count $bridge_count_before"
            msg_yellow "bridge pid list after $bridge_list_after and count $bridge_count_after"
        fi
    done
    msg_green "bm_bridge_restart_test done"

}

bm_bridge_info_all()
{
    ip=$1
    delay=$2
    loops=$3
    msg "bm_bridge_info_all"
    for i in $(seq 1 $loops)
    do
        msg_yellow "Test $i "
        curl --header "Content-Type: application/json" --request GET http://$ip:9200/bm/v1/bridges/info/all
        sleep $delay
    done
    msg_green "bm_bridge_info_all done"
}

bm_test_all()
{
    #Verify if ewc-backend, e2c-server and bridge-manager are running
    backend_pid=$(pgrep ewc-backend)
    server_pid=$(pgrep e2c-server)
    bm_pid=$(pgrep bridge-manager)
    if [[ -z $backend_pid || -z $server_pid || -z $bm_pid ]]; then
        msg_red "one of the process ewc-backend, e2c-server and bridge-manager is not runing"
        msg_red "ewc-backend pid: $backend_pid"
        msg_red "e2c-server pid: $server_pid"
        msg_red "bridge-manager pid: $bm_pid"
        return 1
    fi
    msg_green "ewc-backend pid: $backend_pid"
    msg_green "e2c-server pid: $server_pid"
    msg_green "bridge-manager pid: $bm_pid"
    #Run all the tests
    msg "bm_test_all"
    ip=127.0.0.1
    #bm_bridge_info_all $ip 2 2
    bm_bridge_restart_test $ip 8 1 
    msg_green "bm_test_all executed"
}


#################################################################################
# Main Script
#################################################################################

if [[ $_ == $0 ]]; then
    { echo "Failure, reason : This script must be sourced" ; return 1; }
fi


