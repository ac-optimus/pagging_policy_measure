all: build run plot

CC=gcc

build:
	@mkdir plots
	@mkdir summary

run: build_performance_test
	@./work_load_performance RANDOM
	@./work_load_performance LOCAL
	@./work_load_performance LOOP
	@./work_load_performance LOCAL USE_LRU_APPROX

build_performance_test:
	@echo "Building..."
	@echo "Building tests. Run: make test"
	@$(CC) checker.c -o test
	@$(CC) main.c -o work_load_performance

test: build_performance_test
	@./test

plot: build_performance_test
	@echo "plots saved in plots/"
	@python scripts/plot_figure_lru.py RANDOM
	@python scripts/plot_figure_lru.py LOCAL
	@python scripts/plot_figure_lru.py LOOP
	@python scripts/plot_figure_lru_approx.py LOCAL

clean:
	@echo "Cleaning..."
	@rm -r plots summary work_load_performance test
