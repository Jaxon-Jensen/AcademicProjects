from sklearn import datasets
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import Perceptron
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import LabelBinarizer
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression


iris = datasets.load_iris()
X = iris.data
y = iris.target
X = X[50:150]
y = y[50:150]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)
sc = StandardScaler()
sc.fit(X_train)
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

ppn = Perceptron()
ppn.fit(X_train_std, y_train)
y_pred = ppn.predict(X_test_std)

print('Accuracy: %.2f' % accuracy_score(y_test, y_pred))


confusion_matrix = confusion_matrix(y_test, y_pred)
print(confusion_matrix)
plt.matshow(confusion_matrix)
plt.title('Confusion matrix')
plt.colorbar()
plt.ylabel('True label')
plt.xlabel('Predicted label')



lb = LabelBinarizer()
y_train = np.array([number[0] for number in lb.fit_transform(y_train)])
precision = cross_val_score(ppn, X_train, y_train, cv=5, scoring='precision')
print('Precision', np.mean(precision), precision)
recall = cross_val_score(ppn, X_train, y_train, cv=5, scoring='recall')
print('Recall', np.mean(recall), recall)
f1 = cross_val_score(ppn, X_train, y_train, cv=5, scoring='f1')
print('F1', np.mean(f1), f1)
print('ROC_AUC : ', cross_val_score(ppn, X_train, y_train, cv=3, scoring='roc_auc'))
plt.show()
print("\n")