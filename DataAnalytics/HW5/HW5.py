from sklearn.neighbors import KNeighborsClassifier
import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt
import time

iris = datasets.load_iris()
iris_data = iris.data
iris_labels = iris.target
np.random.seed(int(time.time()))
indices = np.random.permutation(len(iris_data))
n_training_samples = 9
learnset_data = iris_data[indices[:-n_training_samples]]
learnset_labels = iris_labels[indices[:-n_training_samples]]
testset_data = iris_data[indices[-n_training_samples:]]
testset_labels = iris_labels[indices[-n_training_samples:]]

knn = KNeighborsClassifier()
knn.fit(learnset_data, learnset_labels)
#minkowski metric
KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='euclidean', n_jobs=1, n_neighbors=5, p=2, weights='uniform')
print("Predictions form the classifier:")
print(knn.predict(testset_data))
print("Target values:")
print(testset_labels)
a = 1
b = 2
c = 3

X = []
for i in range(3):
    X.append([[], [], []])
    for j in range(len(learnset_data)):
        if learnset_labels[j] == i:
            X[i][0].append(learnset_data[j][a])
            X[i][1].append(learnset_data[j][b])
            X[i][2].append(learnset_data[j][c])
Y = []
for i in range(3):
    Y.append([[], [], []])
    for j in range(len(testset_data)):
        if testset_labels[j] == i:
            Y[i][0].append(testset_data[j][a])
            Y[i][1].append(testset_data[j][b])
            Y[i][2].append(testset_data[j][c])
colors = ("r", "g", "y", "c", "m", "b")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

for i in range(3):
    ax.scatter(X[i][0], X[i][1], X[i][2], c=colors[i])
for i in range(3):
    ax.scatter(Y[i][0], Y[i][1], Y[i][2], c=colors[i+3])

labels=['Iris-setosa', 'Iris-versicolor', 'Iris-virginica', 'test Iris-setosa', 'test Iris-versicolor', 'test Iris-virginica']
plabel = ['$Sepal-length$', '$Sepal-width$', '$Petal-length$', '$Petal-width$']
ax.set_xlabel(plabel[a])
ax.set_ylabel(plabel[b])
ax.set_zlabel(plabel[c])
ax.set_title('KNN classification')
plt.legend(labels,loc='upper left')
plt.show()