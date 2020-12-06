import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

if sys.argv[1]== "RANDOM":
    FILENAME= "workload_random.csv"

elif sys.argv[1]== "80-20":
    FILENAME= "workload_80_20.csv"


elif sys.argv[1]== "LOOPING":
    FILENAME= "workload_looping.csv"
else:
    print("valid arguments-- RANDOM/ LOOPING/ 80-20")
    exit()

df= pd.read_csv(FILENAME)
plt.plot(df['RANDOM']/100, label='RANDOM')
plt.scatter(range(len(df)), df['LRU']/100, marker='o', s=10, label='LRU', color='yellow')
plt.scatter(range(len(df)), df['FIFO']/100, s=10, label='FIFO', color='orange')
plt.legend(loc='lower right')
plt.show()