import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
df = pd.read_excel('DataAnalytics/HW2/iris.xlsx')

x = np.array(df[df.columns[0:3]])
y = np.array(df[df.columns[4]])
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.20)
lr = LogisticRegression(max_iter=200) 
print(lr.fit(x_train, y_train))
y_predictions = lr.predict(x_test)
print(f'Length(rows) of dataset : {df.shape[0]}\n\
Columns used as features (explanatory variables): 0 - 3\n\
Target (label) column: 4 - The "Species"\n\
         y_test\t\t\t\t y_prediction\n')
for i in range(0, len(y_predictions), 1):
    print(i,' \t', y_test[i], '   \t\t', y_predictions[i])
print('\nR-squared: %.4f' %lr.score(x_test, y_test))