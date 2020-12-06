#!/bin/bash
cd build
./lru RANDOM
./lru 80-20
./lru LOOPING
./lru_approx 80-20
echo plots saved in plots/
python ../scripts/plot_figure_lru.py RANDOM
python ../scripts/plot_figure_lru.py 80-20
python ../scripts/plot_figure_lru.py LOOPING
python ../scripts/plot_figure_lru_approx.py 80-20
