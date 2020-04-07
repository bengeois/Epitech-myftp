#!/bin/bash 

if [ "$#" -ne 2 ]; then
    echo "USAGE: $0 host port"
    exit 0
fi

USERNAME="Anonymous"
PASS=""

HOST=$1
PORT=$2
MKFIFO=`which mkfifo`
PIPE=fifo
OUT=outfile
TAIL=`which tail`
NC="`which nc` -C"
TIMEOUT=1 #max time before reading server response
PORT_TO_CONNECT=0

getcode()
{
  sleep $TIMEOUT
  local code=$1
  echo "Waiting for $code reply-code"
  local data=`$TAIL -n 1 $OUT |cat -e |grep "^$code.*[$]$" |wc -l`
  return $data
}

print_failed()
{
    echo "$1 test failed"
    echo "Expected reply-code: $2"
    echo "Received : ["`$TAIL -n 1 $OUT| cat -e`"]"
    echo "KO"
}

print_succeeded()
{
  echo "$1 test succeeded"
  echo "OK"  
  kill_client 2>&1 >/dev/null
}

get_port()
{
    local result_ip=`cat -e $OUT | grep -oP '\(\K[^\)]+'`
    local PORT1=$(echo $result_ip | cut -d ',' -f 5- | cut -d ',' -f 1)
    local PORT2=$(echo $result_ip | cut -d ',' -f 6-)
    PORT_TO_CONNECT=$(expr $PORT1 \* 256 + $PORT2)
}

launch_client()
{
  local host=$1
  local port=$2

  $MKFIFO $PIPE
  ($TAIL -f $PIPE 2>/dev/null | $NC $host $port &> $OUT &) >/dev/null 2>/dev/null

  echo "Connecting to $host : $port"
  sleep $TIMEOUT
  getcode 220
  if [[ $? -eq 1 ]]; then
    echo "Reply-code OK"
    return 1
  else
    echo "Connection to $host:$port failed"
    echo "Expected reply-code: 220"
    echo "Received : ["`tail -n 1 $OUT |cat -e`"]"
    return 0
  fi  
}

launch_test()
{
  local test_name=$1
  local cmd=$2
  local code=$3

  echo "Sending [$cmd^M$]"
  echo "$cmd" >$PIPE
  getcode $code
  if [[ ! $? -eq 1 ]]; then
    print_failed "$test_name" "$code"
    kill_client
    clean
  fi
  echo "Reply-code OK"
}

kill_client()
{
  local nc=`which nc`

  if [ `pidof $TAIL | wc -l` -ne 0 ]
  then
    killall $TAIL &>/dev/null
  fi
  if [ `pidof $nc | wc -l` -ne 0 ]
  then
    killall $nc &>/dev/null
  fi  
  rm -f $PIPE $OUT &> /dev/null
}

clean()
{
  rm -f $PIPE $OUT log &>/dev/null
}

# Simple authentication with USER + PASS command
test00()
{
  local test_name="Authentication"

  local cmd1="USER $USERNAME"
  local cmd2="PASS $PASS"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230

  print_succeeded "$test_name"
  return
}

test01()
{
  local test_name="QUIT CONNECTION"

  local cmd1="QUIT"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 221

  print_succeeded "$test_name"
  return
}

test02()
{
  local test_name="UNKNOWN COMMAND"

  local cmd1="USER $USERNAME"
  local cmd2="PASS $PASS"
  local cmd3="WHAT"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  return
}

test03()
{
  local test_name="COMMAND WITHOUT LOGGED IN"

  local cmd1="NOOP"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530

  print_succeeded "$test_name"
  return
}

test04()
{
  local test_name="HELP"

  local cmd1="HELP"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="HELP"
  local cmd5="HELP QUIT"
  local cmd6="HELP ABC"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 214
  launch_test "$test_name" "$cmd5" 214
  launch_test "$test_name" "$cmd6" 214

  print_succeeded "$test_name"
  return
}

test05()
{
  local test_name="PWD"

  local cmd1="PWD"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="PWD"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 257

  print_succeeded "$test_name"
  return
}

test06()
{
  local test_name="DELE"
  touch file_to_delete
  mkdir folder_to_delete

  local cmd1="DELE"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="DELE file_to_delete"
  local cmd5="DELE file_to_delete"
  local cmd6="DELE folder_to_delete"
  local cmd7="DELE folder_to_delete"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 250
  launch_test "$test_name" "$cmd5" 550
  launch_test "$test_name" "$cmd6" 250
  launch_test "$test_name" "$cmd7" 550

  print_succeeded "$test_name"
  return
}

test07()
{
  local test_name="CWD"

  local cmd1="CWD"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="CWD .."
  local cmd5="CWD .."
  local cmd6="CWD /home/bourgeois"
  local cmd7="CWD Downloads"
  local cmd8="CWD Desktop"
  local cmd9="CWD ../Desktop"
  local cmd10="CWD /"
  local cmd11="CWD /home/bourgeois/Downloads/../Desktop"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 250
  launch_test "$test_name" "$cmd5" 250
  launch_test "$test_name" "$cmd6" 250
  launch_test "$test_name" "$cmd7" 250
  launch_test "$test_name" "$cmd8" 550
  launch_test "$test_name" "$cmd9" 250
  launch_test "$test_name" "$cmd10" 250
  launch_test "$test_name" "$cmd11" 250

  print_succeeded "$test_name"
  return
}

test08()
{
  local test_name="CDUP"

  local cmd1="CDUP"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="CDUP"
  local cmd5="PWD"
  local cmd6="CDUP"
  local cmd7="PWD"
  local cmd8="CWD /home/bourgeois/Downloads/../Desktop"
  local cmd9="PWD"
  local cmd10="CDUP"
  local cmd11="PWD"
  local cmd12="CDUP"
  local cmd13="PWD"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 250
  launch_test "$test_name" "$cmd5" 257
  launch_test "$test_name" "$cmd6" 250
  launch_test "$test_name" "$cmd7" 257
  launch_test "$test_name" "$cmd8" 250
  launch_test "$test_name" "$cmd9" 257
  launch_test "$test_name" "$cmd10" 250
  launch_test "$test_name" "$cmd11" 257
  launch_test "$test_name" "$cmd12" 250
  launch_test "$test_name" "$cmd13" 257

  print_succeeded "$test_name"
  return
}

test09()
{
  local test_name="PASV"

  local cmd1="PASV"
  local cmd2="USER $USERNAME"
  local cmd3="PASS $PASS"
  local cmd4="PASV"

  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi

  launch_test "$test_name" "$cmd1" 530
  launch_test "$test_name" "$cmd2" 331
  launch_test "$test_name" "$cmd3" 230
  launch_test "$test_name" "$cmd4" 227

  print_succeeded "$test_name"
  return
}

./myftp 3100 . &

test00
test01
test02
test03
test04
test05
test06
test07
test08
test09
clean
kill -9 %1