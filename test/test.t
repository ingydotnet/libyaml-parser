#!/bin/bash

got=$(mktemp)

count=0
for test in test/*.yaml; do
  want=${test//yaml/events}
  ./libyaml-parser $test > $got
  rc=0
  diff=$(diff -u $want $got) || rc=$?
  if [[ $rc -eq 0 ]]; then
    echo "ok $((++count))"
  else
    echo "not ok $((++count))"
    diff=${diff//$'\n'/$'\n'# }
    echo "# $diff"
  fi
done

echo "1..$count"
