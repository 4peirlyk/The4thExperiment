# -*- coding: utf-8 -*-
"""PredictingEnergyConsumption_F.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1QW6GBGfsK_NnflULwWaroNPkZr7Hu1dr
"""

import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import math
from sklearn.ensemble import RandomForestRegressor
from sklearn.neighbors import KNeighborsRegressor
from math import sqrt
from sklearn.metrics import mean_squared_error

import warnings
warnings.filterwarnings("ignore")

trainpd = pd.read_csv("/content/1measuresf.csv")

print(trainpd)

from sklearn.model_selection import train_test_split

train,test = train_test_split(trainpd, test_size=0.2, random_state=5,shuffle = False)


x=["HofD","OutTemp", "OutHum", "InTemp", "InHum"]
ytrain = train["KcalPerHour"]  #ytrain is the column Kcal/h of train set
ytest = test["KcalPerHour"]
print(ytest.head(24))
print(ytest)
xtrain = train[x]
xtest = test[x]
print(xtrain)
print(xtest)

# Y is going to be used for calculating the error
Y=0
count=0
for i in ytest.values:
  if i!=0:
    count += 1
    Y = Y + i
Y = Y/count

"""K Nearest Neighbors"""

knn = KNeighborsRegressor()
knn.fit(xtrain,ytrain)
ypredrf = knn.predict(xtest)

rmserf = math.sqrt(mean_squared_error(ypredrf, ytest))

cvrmsrf= (rmserf/Y)*100
print("The CV(RMSE) for the knn is ",cvrmsrf,"%")

plt.plot(ytest.values, color = "red")
plt.plot(ypredrf, color = "yellow")
#print(b.head(50))
plt.ylabel('Kcal/h')
plt.xlabel('index')
plt.xticks([])
plt.title("KNN  prediction")
plt.show()

"""RandomForest"""

rf= RandomForestRegressor()  #δημιουργία αντικειμένου rf για να χρησιμοποιήσουμε τον RandomForestRegressor
rf.fit(xtrain,ytrain)
ypredrf = rf.predict(xtest)

rmserf = sqrt(mean_squared_error(ypredrf, ytest))

cvrmsrf= (rmserf/Y)*100
print("The CV(RMSE) for the rf is ",cvrmsrf,"%")

plt.plot(ytest.values, color = "red")
plt.plot(ypredrf, color = "yellow")
#print(b.head(50))
plt.ylabel('Kcal/h')
plt.xlabel('Index')
plt.xticks([])
plt.title("RF  prediction")
plt.show()