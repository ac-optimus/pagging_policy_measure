all: build run_performance_test

CC=gcc
DST=build
SRC=src
# path of project directory
# HOME=$(shell pwd)
# path to the implementations
# BINARIES=$(HOME)/build

build:
	@mkdir build
	@mkdir plots
	@mkdir summary

run_performance_test:build_performance_test
	@$(shell  ./scripts/run_analysis.sh)

build_performance_test:
	@echo "Building..."
	@gcc $(SRC)/performance_measure_lru.c -o $(DST)/lru
	@gcc $(SRC)/performance_measure_lru_approx.c -o $(DST)/lru_approx


clean:
	@echo "Cleaning..."
	@rm -r build plots summary