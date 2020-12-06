import sys
import pandas as pd
import matplotlib.pyplot as plt

if sys.argv[1]== "RANDOM":
    FILENAME= "workload_random.csv"

elif sys.argv[1]== "80-20":
    FILENAME= "workload_80_20.csv"


elif sys.argv[1]== "LOOPING":
    FILENAME= "workload_looping.csv"

else:
    FILENAME= "P.csv"

df= pd.read_csv(FILENAME)
plt.plot(df)
plt.show()