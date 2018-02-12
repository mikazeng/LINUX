#!/bin/bash
#str="hello world"
#var=100
#mystr=$var
#echo str=$str
#echo var=$var
#echo mystr=$mystr
#echo "hello world hello shell"
#echo PATH=$PATH
#echo HOME=$HOME
#echo line= $line
#echo input
#read line
echo input
read line
case "$line" in 
	[Yy][eE][s])echo yes;;
	no)	echo no;;
	*) echo ******;;
esac
exit 0

