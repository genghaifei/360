#Problem:6.sysinfo_reconder
#author:genghaifei
#decription:I use the file /proc/stat to get the cpu information and through calculated,the cpu usage is got.

#!/bin/bash

sum1=`cat /proc/stat | sed -n '1p' | awk '{print $2" " $3" " $4" " $5" " $6" " $7" " $8" " $9" " $10}'`
idel_one=`cat /proc/stat | sed -n '1p' | awk '{print $5}'`

`sleep 1`

sum2=`cat /proc/stat | sed -n '1p' | awk '{print $2" " $3" " $4" " $5" " $6" " $7" " $8" " $9" " $10}'`
idel_two=`cat /proc/stat | sed -n '1p' | awk '{print $5}'`

idel_sum=`expr ${idel_two} - ${idel_one}`
sum_total_one=
sum_total_two=
for time in ${sum1}
do
	let sum_total_one=${sum_total_one}+${time}
done

for time in ${sum2}
do
	let sum_total_two=${sum_total_two}+${time}
done

let total_cpu_time=${sum_total_two}-${sum_total_one}

cpu_prac=`expr \( ${total_cpu_time} - ${idel_sum} \) \* 100`
cpu_prac2=`expr ${cpu_prac} \/ ${total_cpu_time}`
cpu_prac2=`expr ${cpu_prac2}'%'`


echo ${cpu_prac2}


