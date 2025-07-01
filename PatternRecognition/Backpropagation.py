import numpy as np
import pandas as pd
from tqdm import tqdm

def matrixCreation(trueLabels, predictedLabels, classNames):
    if trueLabels.ndim > 1:
        trueLabels = np.argmax(trueLabels, axis=1)
    
    numClasses = len(classNames)
    confusionMatrix = np.zeros((numClasses, numClasses), dtype=int)
    
    for true, pred in zip(trueLabels, predictedLabels):
        confusionMatrix[pred, true] += 1 
    
    return pd.DataFrame(confusionMatrix, index=classNames, columns=classNames)


def loadFile(path):
    data = []
    features = []
    labels = []
    
    with open(path, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) < 2:
                continue
            
            label = parts[0]
            num = parts[1]
            
            labels.append(label)
            features.append([int(x) for x in num])
    
    features = np.array(features)
    labels = np.array([ord(label) - 65 if label.isalpha() else ord(label) - 22 for label in labels])
    
    targets = np.zeros((len(labels), 36))
    for i, label in enumerate(labels):
        targets[i][label] = 1 
    
    return features, targets

def train(trainFeatures, trainTargets, layers, learningRate, iterations, errorTolerance, errorDeltaTolerance):
    weights = [np.random.rand(layers[i], layers[i + 1]) - 0.5 for i in range(len(layers) - 1)]
    biases = [np.random.rand(layers[i + 1]) - 0.5 for i in range(len(layers) - 1)]

    prevErr = 81503
    pbar = tqdm(total=iterations, desc="Training progress")
    
    for i in range(iterations):
        activations = [trainFeatures]
        for j in range(len(weights)):
            netInput = np.dot(activations[-1], weights[j]) + biases[j]
            activation = 1 / (1 + np.exp(-netInput))
            activations.append(activation)

        output = activations[-1]
        
        backpropErrors = [trainTargets - output]
        gradients = [(activations[-1] * (1 - activations[-1])) * backpropErrors[0]]
        
        for k in range(len(weights) - 1, 0, -1):
            error = np.dot(gradients[-1], weights[k].T)
            gradient = (activations[k] * (1 - activations[k])) * error
            backpropErrors.append(error)
            gradients.append(gradient)
        
        gradients = gradients[::-1]
        
        for l in range(len(weights)):
            weights[l] += learningRate * np.dot(activations[l].T, gradients[l])
            biases[l] += learningRate * np.sum(gradients[l], axis=0)
        
        meanSquaredError = np.mean((trainTargets - output) ** 2)
        deltaError = abs(prevErr - meanSquaredError)
        
        if deltaError <= errorDeltaTolerance and meanSquaredError <= errorTolerance:
            print(f"Converged at iteration {i}, Mean Squared Error: {meanSquaredError}")
            break
        
        prevErr = meanSquaredError
        pbar.update(1)
    
    pbar.n = pbar.total
    pbar.last_print_n = pbar.total
    pbar.update(0)
    pbar.close()

    return weights, biases

def predict(weights, biases, features):
    for weight, bias in zip(weights, biases):
        features = 1 / (1 + np.exp(-(np.dot(features, weight) + bias)))  # Apply sigmoid activation
    return np.argmax(features, axis=1)

def getUserInputs():
    while True:
        try:
            layers = input("Enter the neural network layers as a comma-separated list (e.g., 35,20,36): ")
            layers = [int(layer.strip()) for layer in layers.split(",")]
            if any(layer <= 0 for layer in layers):
                raise ValueError("All layer sizes must be positive integers.")
            if len(layers) < 2:
                raise ValueError("At least two layers are required.")
            break
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a valid list of positive integers.")
        
    while True:
        try:
            learningRate = float(input("Enter the learning rate (e.g., 0.01): "))
            if learningRate <= 0:
                raise ValueError("Learning rate must be a positive number.")
            break
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a positive float.")

    while True:
        try:
            iterations = int(input("Enter the maximum number of iterations (e.g., 10000): "))
            if iterations <= 0:
                raise ValueError("Iterations must be a positive integer.")
            break
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a positive integer.")

    while True:
        try:
            errorTolerance = float(input("Enter the error tolerance (e.g., 0.001): "))
            if errorTolerance <= 0:
                raise ValueError("Error tolerance must be a positive number.")
            break
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a positive float.")

    while True:
        try:
            errorDeltaTolerance = float(input("Enter the error delta tolerance (e.g., 0.001): "))
            if errorDeltaTolerance <= 0:
                raise ValueError("Error delta tolerance must be a positive number.")
            break
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a positive float.")

    
    return layers, learningRate, iterations, errorTolerance, errorDeltaTolerance

def main():
    trainingFilePath = "PatternRecognition\\NNtrain.dat"
    testFilePath = "PatternRecognition\\NNtest.dat"

    trainFeatures, trainTargets = loadFile(trainingFilePath)
    testFeatures, testTargets = loadFile(testFilePath)

    print("Please provide the neural network configuration.")
    weights, biases = train(trainFeatures, trainTargets, *getUserInputs())

    testPredictedLabels = predict(weights, biases, testFeatures)

    classNames = [chr(i) for i in range(65, 91)] + [str(i) for i in range(10)]

    confusionMatrix = matrixCreation(testTargets, testPredictedLabels, classNames)

    print(f"\nConfusion Matrix:\n{confusionMatrix}")

if __name__ == "__main__":
    main()
