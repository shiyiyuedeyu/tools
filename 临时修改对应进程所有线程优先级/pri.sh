#!/bin/bash  
# 指定要查询的进程ID  
pri=$1
PID=$2
# 检查参数是否提供
if [ -z "$PID" ]; then
    echo "Usage: $0 <process_id>"
    exit 1
fi
# 检查进程是否存在  
if [ ! -d "/proc/$PID" ]; then
    echo "Process $PID does not exist."
    exit 1
fi
# 遍历/proc/$PID/task目录下的所有线程ID  
echo "Thread IDs for process $PID:"
for TID in $(ls /proc/$PID/task);
do
    # 提取线程ID（去掉路径前缀）  
#    TID=${TID##*/}
    # 输出线程ID  
    echo $TID
	chrt -p -r $pri $TID
done

# 使用方式 bash pri.sh 5 PID
