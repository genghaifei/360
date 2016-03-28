#!/bin/bash -x

list=`crontab -l | awk -F' ' '{print $NF}'`
proc=$( basename $0)
function usage(){
	printf "Usage: $proc crontab task [ (--stop) | (--start) | (--list)] \n"
}

function server_stop(){
	for name in ${list}
	do
		[[ $1 -eq ${name} ]]
			`crontab -l | grep ${name} > _file`
			`crontab -r name`
	done
}

function server_start(){
	for name in ${list}
	do
		[[ $1 -eq ${name} ]]
			local who=${whoami}
			`cat _file >> /var/spool/cron/$(who)`
	done
}
function server_list(){
	for name in ${list}
	do
		echo ${name}
	done
}


[[ $# -ne 2 ]] && {
	printf "your message is bad    warning!!!\n"
	usage
	exit 1
}

case $2 in
	'--stop')
		server_stop
	;;
	'--start')
		server_start
	;;
	'--list')
		server_list
	;;
	* )
		usage
	;;
esac

