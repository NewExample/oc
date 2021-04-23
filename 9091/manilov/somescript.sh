#!/bin/bash
cd /home/kali/Desktop/
#sozdanie papki
mkdir 9091
cd 9091
mkdir manilov
cd manilov
#vivod date in fail
date > manilov.txt
#vivod date next Monday
date -d "2021-08-03 12:54:21" > filedate.txt
cat manilov.txt filedate.txt > result.txt
cat result.txt