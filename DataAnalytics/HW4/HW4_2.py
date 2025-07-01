import numpy as np
from sklearn.cluster import KMeans
from scipy.spatial.distance import cdist
import pandas as pd

from yellowbrick.cluster import KElbowVisualizer
x = pd.read_excel('DataAnalytics/HW4/iris.xlsx')
X = np.array(x[x.columns[0:4]])
# Instantiate a scikit-learn K-Means model
model = KMeans(random_state=0,n_init=10)
# Instantiate the KElbowVisualizer with the number of clusters and the metric
visualizer = KElbowVisualizer(model, k=(2,10), metric='silhouette', timings=False)
# Fit the data and visualize
visualizer.fit(X) # X is the dataset
visualizer.poof()