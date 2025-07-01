import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt

x1 = pd.read_excel('DataAnalytics/HW4/iris.xlsx')
for clstr in range(2,7):
    print('\n\n\n\n')
    for i in range(0,4):
        for j in range(i+1,4):
            X1 = np.array(x1[x1.columns[i]])
            plt.xlabel(x1.columns[i])
            X2 = np.array(x1[x1.columns[j]])
            plt.ylabel(x1.columns[j])

            X = np.array(list(zip(X1, X2))).reshape(len(X1), 2)
            kmeans = KMeans(n_clusters=clstr, random_state=0, n_init=10,tol=.0001).fit(X)
            print(f'\n\nX Axis: {x1.columns[i]}\nY Axis: {x1.columns[j]} \nNumber of Clusters: {clstr}')
            print(kmeans.cluster_centers_)
            print(kmeans.labels_)
            print("silhouette score:",silhouette_score(X, kmeans.labels_))
            plt.scatter(X[:50, 0], X[:50, 1], c='blue', marker='.')
            plt.scatter(X[50:100, 0], X[50:100, 1], c='yellow', marker='D')
            plt.scatter(X[100:150, 0], X[100:150, 1], c='green', marker='v')
            plt.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], c='red', marker='*',s=175)
            plt.title('Data points and cluster centroids')
            plt.show()
            