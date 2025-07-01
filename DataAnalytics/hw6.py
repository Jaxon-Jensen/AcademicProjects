from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn.datasets import load_digits
digits = load_digits()

outFile = open("DataAnalytics/HW6_outFile.txt", 'w')

X = digits.data
y = digits.target
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.20)

sc = StandardScaler()
sc.fit(X_train) #Apply the scaler to the X training and X-test data sets
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

acts = ['relu','tanh','identity','logistic']
neurons = [[20,10], [50,25], [100,60],
           [20,10,10], [50,30,30], [100,60,60],
           [20,10,10,20], [50,30,30,50], [100,60,60,100]]
iterations = [200,500,1000]
count = 1
for act in acts:
    for neuron in neurons:
        for iteration in iterations:
            mlp = MLPClassifier(hidden_layer_sizes=neuron, activation= act, max_iter=iteration)
            print(count, mlp) #print the parameters of the MLP classifier
            mlp.fit(X_train_std, y_train)
            y_pred = mlp.predict(X_test_std)
            #print(f'Test sample labels: \n { y_test, }\n Test samples classified as: \n{ y_pred }\n')
            c_matrix = confusion_matrix(y_test,y_pred)
            #print('Confusion_matrix:')
            ##print(c_matrix)
            outFile.write(f"{count}\t{len(neuron)}\t{neuron}\t{iteration}\t{accuracy_score(y_test,y_pred)}\t.0001\t{act}\n" )
            mlp = None
            y_pred = None
            c_matrix = None
            count += 1
            #for i in mlp.coefs_[1]:
                #print(i) 
                
