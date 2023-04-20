#!/bin/bash
# 请注意app名称，需要通过app运行时的进程名来判断是否进程挂了，所以需检查进程名
SCRIPT_PATH="$(
  # shellcheck disable=SC2164
  cd -- "$(dirname "$0")" >/dev/null 2>&1
  pwd -P
)"
PROJ_ROOT="${SCRIPT_PATH}/.."
cd $PROJ_ROOT

restart_count=0
while :
do
  sleep 1
  ret=`ps |egrep 'krider_multiperception'| wc -l`
  echo $ret
  if [ $ret -gt 1 ]; then
    echo "ok"
  else
    sh ./launch/launch_multiperception_j5_cam.sh
  fi
  echo "$restart_count"
  let restart_count++
done
