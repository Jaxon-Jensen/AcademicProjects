import pandas as panda
import matplotlib.pyplot as plt 

s1 = panda.read_excel('DataAnalytics/HW2/iris.xlsx')
s2 = panda.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet2')
s3 = panda.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet3')
s4 = panda.read_excel('DataAnalytics/HW2/iris.xlsx', sheet_name='Sheet4')

def analysis(df):
    print(f'The means are: {df.loc[:,"Sepal length"].mean():.2f}    {df.loc[:,"Sepal width"].mean():.2f}   {df.loc[:,"Petal length"].mean():.2f}   {df.loc[:,"Petal width"].mean():.2f}')
    print(f'The medians are: {df.loc[:,"Sepal length"].median():.2f}    {df.loc[:,"Sepal width"].median():.2f}   {df.loc[:,"Petal length"].median():.2f}   {df.loc[:,"Petal width"].median():.2f}')
    print(f'The standard deviations are: {df.loc[:,"Sepal length"].std():.2f}    {df.loc[:,"Sepal width"].std():.2f}   {df.loc[:,"Petal length"].std():.2f}   {df.loc[:,"Petal width"].std():.2f}')
    print(f'The variances are: {df.loc[:,"Sepal length"].var():.2f}    {df.loc[:,"Sepal width"].var():.2f}   {df.loc[:,"Petal length"].var():.2f}   {df.loc[:,"Petal width"].var():.2f}')
    print(f'The correlation coefficients are:\n\
                       Sepal length  Sepal width  Petal length  Petal width\n\
          Sepal length {df.loc[:,"Sepal length"].corr(df.loc[:,"Sepal length"]):.8f}    {df.loc[:,"Sepal length"].corr(df.loc[:,"Sepal width"]):.8f}   {df.loc[:,"Sepal length"].corr(df.loc[:,"Petal length"]):.8f}    {df.loc[:,"Sepal length"].corr(df.loc[:,"Petal width"]):.8f}\n\
          Sepal width  {df.loc[:,"Sepal width"].corr(df.loc[:,"Sepal length"]):.8f}    {df.loc[:,"Sepal width"].corr(df.loc[:,"Sepal width"]):.8f}   {df.loc[:,"Sepal width"].corr(df.loc[:,"Petal length"]):.8f}    {df.loc[:,"Sepal width"].corr(df.loc[:,"Petal width"]):.8f}\n\
          Petal length {df.loc[:,"Petal length"].corr(df.loc[:,"Sepal length"]):.8f}    {df.loc[:,"Petal length"].corr(df.loc[:,"Sepal width"]):.8f}   {df.loc[:,"Petal length"].corr(df.loc[:,"Petal length"]):.8f}    {df.loc[:,"Petal length"].corr(df.loc[:,"Petal width"]):.8f}\n\
          Petal width  {df.loc[:,"Petal width"].corr(df.loc[:,"Sepal length"]):.8f}    {df.loc[:,"Petal width"].corr(df.loc[:,"Sepal width"]):.8f}   {df.loc[:,"Petal width"].corr(df.loc[:,"Petal length"]):.8f}    {df.loc[:,"Petal width"].corr(df.loc[:,"Petal width"]):.8f}\n')

def minmax(df, num):
    minima = []
    maxima = []
    for y in range(0,4):
        minima.clear()
        maxima.clear()
        minima = [df.iloc[0,y],df.iloc[1,y],df.iloc[2,y],df.iloc[3,y],df.iloc[4,y]]
        maxima = [df.iloc[0,y],df.iloc[1,y],df.iloc[2,y],df.iloc[3,y],df.iloc[4,y]]
        minima.sort(reverse=True)
        maxima.sort()
        for x in range(5,50):
            if df.iloc[x,y] > maxima[0]:
                maxima.pop(0)
                maxima.append(df.iloc[x,y])
                maxima.sort()
                continue
            elif df.iloc[x,y] < minima[0]:
                minima.pop(0)
                minima.append(df.iloc[x,y])
                minima.sort(reverse=True)
        print(f'For column {y} - {df.columns.tolist()[y]} of Sheet{num}\n\
              The minima are: {minima}\n\
              The maxima are: {maxima}\n')


#Search by index
while True:
    rowNum = input('Enter row (0 - 149): ')
    colNum = input('Enter column (0 - 4): ')
    if rowNum.isdigit() and colNum.isdigit():
        rowNum = int(rowNum)
        colNum = int(colNum)
        if rowNum < 150 and colNum < 5:
            break
        else:
            print("\nInvalid try again \n")
    else:
        print("\nInvalid try again \n")
print(f'The data at row {rowNum} and column {colNum} is', s1.iat[rowNum,colNum])
print('\n\n\n')


#Search by value
while True:    
    searchEle = input('Enter a value to search (0.0 - 10.0): ')
    try:
        searchEle = float(searchEle)
        if searchEle >= 0 and searchEle <= 10:
            break
        else:
            print('\nInvalid try agian\n')
    except ValueError:
        print('\nInvalid try again\n')
duplicate = panda.DataFrame(s1)
count = 0
for x in range(0,150):
    for y in range(0,4):
        if s1.iat[x,y] == searchEle:
            duplicate.iat[x,y] = 'NaN'
            count += 1
            print(f'{count} A value {searchEle} is found in row {x} and column {y}\n  The value {searchEle} is changed to NaN')      
write = panda.ExcelWriter('DataAnalytics/HW2/out.xlsx')
duplicate.to_excel(write, sheet_name='sheet1')
write.close()
print('\n\n\n')

#Data analysis
#Sheet 1
analysis(s1)
minmax(s1, 1)

#Sheet 2
analysis(s2)
minmax(s2,2)

#Sheet 3
analysis(s3)
minmax(s3,3)

#Sheet 4
analysis(s4)
minmax(s4,4)

#Graphing
fig1 = plt.figure()
ax1 = fig1.add_subplot(111)
ax1.scatter(s2.loc[:,'Petal length'], s2.loc[:,'Petal width'], s=10, c='b', marker="s", label='Iris-setosa')
ax1.scatter(s3.loc[:,'Petal length'], s3.loc[:,'Petal width'], s=10, c='r', marker="o", label='Iris-versicolor')
ax1.scatter(s4.loc[:,'Petal length'], s4.loc[:,'Petal width'], s=10, c='y', marker="d", label='Iris-virginica')
plt.legend(loc='lower right')
plt.xlabel('Petal length')
plt.ylabel('Petal width')
plt.show()

fig2 = plt.figure()
ax1 = fig2.add_subplot(111)
ax1.scatter(s2.loc[:,'Sepal length'], s2.loc[:,'Sepal width'], s=10, c='b', marker="s", label='Iris-setosa')
ax1.scatter(s3.loc[:,'Sepal length'], s3.loc[:,'Sepal width'], s=10, c='r', marker="o", label='Iris-versicolor')
ax1.scatter(s4.loc[:,'Sepal length'], s4.loc[:,'Sepal width'], s=10, c='y', marker="d", label='Iris-virginica')
plt.legend(loc='lower right')
plt.xlabel('Sepal length')
plt.ylabel('Sepal width')
plt.show()

fig3 = plt.figure()
ax1 = fig3.add_subplot(111)
ax1.scatter(s2.loc[:,'Sepal length'], s2.loc[:,'Petal length'], s=10, c='b', marker="s", label='Iris-setosa')
ax1.scatter(s3.loc[:,'Sepal length'], s3.loc[:,'Petal length'], s=10, c='r', marker="o", label='Iris-versicolor')
ax1.scatter(s4.loc[:,'Sepal length'], s4.loc[:,'Petal length'], s=10, c='y', marker="d", label='Iris-virginica')
plt.legend(loc='lower right')
plt.xlabel('Sepal length')
plt.ylabel('Petal length')
plt.show()

fig4 = plt.figure()
ax1 = fig4.add_subplot(111)
ax1.scatter(s2.loc[:,'Sepal width'], s2.loc[:,'Petal width'], s=10, c='b', marker="s", label='Iris-setosa')
ax1.scatter(s3.loc[:,'Sepal width'], s3.loc[:,'Petal width'], s=10, c='r', marker="o", label='Iris-versicolor')
ax1.scatter(s4.loc[:,'Sepal width'], s4.loc[:,'Petal width'], s=10, c='y', marker="d", label='Iris-virginica')
plt.legend(loc='lower right')
plt.xlabel('Sepal width')
plt.ylabel('Petal width')
plt.show()