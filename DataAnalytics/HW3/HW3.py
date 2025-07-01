import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
import mlxtend
s1 = pd.read_excel('DataAnalytics/HW2/iris.xlsx')
s2 = pd.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet2')
s3 = pd.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet3')
s4 = pd.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet4')

while True:#gets sheetNum
    sheetNum = input("Enter the sheet number(range 1 - 4) of the dataset to be analyzed: ")
    try:
        sheetNum = int(sheetNum)
        if sheetNum<5 and sheetNum>0:
            break
        print("Error Invalid. Try again")
    except(ValueError):
        print("Error Invalid. Try again")
if sheetNum == 1:
    df = s1
elif sheetNum == 2:
    df = s2
elif sheetNum == 3:
    df = s3
else:
    df = s4

x = np.array(df[df.columns[0:3]]) # use columns x as explanatory data
y = np.array(df[df.columns[3]]) # target data
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.20)
regressor = LinearRegression()
regressor.fit(x_train, y_train)
y_predictions = regressor.predict(x_test)
print("length(rows) of dataset : ", df.shape[0], '\n\
Columns used in training dataset (explanatory variables): 0 - 2\n\
Target estimation (response variable) data in column: 3 - The "Petal width"\n\n\
y_test  y_prediction')
for i in range(len(y_predictions)):
    print(f"{y_test[i]: .2f}   {y_predictions[i]:.5f}")
print('\nR-squared:', regressor.score(x_test, y_test))
