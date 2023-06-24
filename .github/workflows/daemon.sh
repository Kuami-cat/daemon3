#!/bin/bash

case "$1" in
        start)
                echo "$(date) service started" >> daemon.txt
		gcc -o firstdaemon daemon.c
		./firstdaemon &
                echo $!>firstdaemon.pid
                read pod<firstdaemon.pid
                echo "started"
                ;;
        stop)
                echo "$(date) service stopped" >> daemon.txt
                read pod<firstdaemon.pid
		kill $pod
		echo "27">firstdaemon.pid
                echo "stopped"
                ;;
	status)
		read pod<firstdaemon.pid
                if [[ "$pod" == "27" ]]; then
                	echo "daemon is NOT running"
                        exit 1
			
                else
                        echo "daemon is running"
                fi
                ;;
        *)
                echo "Usage: $0 {start|stop|status}"
                ;;
esac
exit 0
