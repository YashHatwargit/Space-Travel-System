#!/bin/bash

g++ -c STS_classes.cpp
g++ -c Space_Travel_System.cpp
g++ -o STS STS_classes.o Space_Travel_System.o
./STS.exe
