import numpy as np
import pandas as pd
from tqdm import tqdm

def createConfusionMatrix(trueLabels, predictedLabels, classNames):
    # Convert one-hot encoded labels to indices if necessary
    if len(trueLabels.shape) > 1:  # Check if labels are one-hot encoded
        trueLabels = np.argmax(trueLabels, axis=1)
    
    numClasses = len(classNames)
    matrix = np.zeros((numClasses, numClasses), dtype=int)
    
    # Ensure trueLabels and predictedLabels are integers
    trueLabels = np.array(trueLabels, dtype=int)
    predictedLabels = np.array(predictedLabels, dtype=int)
    
    # Populate the confusion matrix
    for true, pred in zip(trueLabels, predictedLabels):
        matrix[pred, true] += 1  # Rows: Predicted, Columns: Actual
    
    return pd.DataFrame(matrix, index=classNames, columns=classNames)

def loadFile(filePath):
    data = []
    inputs = []
    labels = []
    
    # Load and preprocess the data in one go
    with open(filePath, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) < 2:
                continue
            
            label = parts[0]
            binaryString = parts[1]
            
            # Process the label and binary string
            labels.append(label)
            inputs.append([int(x) for x in binaryString])
    
    inputs = np.array(inputs)
    labels = np.array([ord(label) - ord('A') if label.isalpha() else ord(label) - ord('0') + 26 for label in labels])
    
    outputs = np.zeros((len(labels), 36))
    for i, label in enumerate(labels):
        outputs[i][label] = 1 
    
    return inputs, outputs

def trainNeuralNetwork(trainInputs, trainOutputs, layers, learningRate, iterations, errorTolerance, errorDeltaTolerance):
    weights = [np.random.rand(layers[i], layers[i + 1]) - 0.5 for i in range(len(layers) - 1)]
    biases = [np.random.rand(layers[i + 1]) - 0.5 for i in range(len(layers) - 1)]

    previousError = 1000000
    pbar = tqdm(total=iterations, desc="Training progress")
    
    for i in range(iterations):
        activations = [trainInputs]
        for j in range(len(weights)):
            netInput = np.dot(activations[-1], weights[j]) + biases[j]
            activation = 1 / (1 + np.exp(-netInput))
            activations.append(activation)

        output = activations[-1]
        
        backpropErrors = [trainOutputs - output]
        gradients = [(activations[-1] * (1 - activations[-1])) * backpropErrors[0]]
        
        for k in range(len(weights) - 1, 0, -1):
            error = np.dot(gradients[-1], weights[k].T)
            gradient = (activations[k] * (1 - activations[k])) * error
            backpropErrors.append(error)
            gradients.append(gradient)
        
        gradients = gradients[::-1]
        
        # Update weights and biases
        for q in range(len(weights)):
            weights[q] += learningRate * np.dot(activations[q].T, gradients[q])
            biases[q] += learningRate * np.sum(gradients[q], axis=0)
        
        # Calculate mean squared error
        meanSquaredError = np.mean((trainOutputs - output) ** 2)
        deltaError = abs(previousError - meanSquaredError)
        
        if deltaError <= errorDeltaTolerance and meanSquaredError <= errorTolerance:
            print(f"Converged at iteration {i}, Mean Squared Error: {meanSquaredError}")
            break
        
        previousError = meanSquaredError
        
        pbar.update(1)
    
    # Finalize the progress bar
    pbar.n = pbar.total
    pbar.last_print_n = pbar.total
    pbar.update(0)
    pbar.close()

    return weights, biases

def predict(weights, biases, testInputs):
    activations = [testInputs]
    for j in range(len(weights)):
        netInput = np.dot(activations[-1], weights[j]) + biases[j]
        activation = 1 / (1 + np.exp(-netInput))
        activations.append(activation)
    
    output = activations[-1]
    return np.argmax(output, axis=1)

def main():
    # Correct file paths
    trainingFilePath = "PatternRecognition\\NNtrain.dat"
    testFilePath = "PatternRecognition\\NNtest.dat"

    # Load and preprocess the data in one step
    trainInputs, trainOutputs = loadFile(trainingFilePath)
    testInputs, testOutputs = loadFile(testFilePath)

    # Network Configuration
    layers = [35, 36]
    learningRate = 0.01
    iterations = 10000 
    errorTolerance = 0.001
    errorDeltaTolerance = 0.001

    # Train neural network
    weights, biases = trainNeuralNetwork(trainInputs, trainOutputs, layers, learningRate, iterations, errorTolerance, errorDeltaTolerance)

    # Predict test labels
    testPredictedLabels = predict(weights, biases, testInputs)

    # Define class names for the confusion matrix
    classNames = [chr(i) for i in range(65, 91)] + [str(i) for i in range(10)]

    # Create the confusion matrix
    confusionMatrix = createConfusionMatrix(testOutputs, testPredictedLabels, classNames)

    # Display the confusion matrix
    print("\nConfusion Matrix:")
    print(confusionMatrix)

if __name__ == "__main__":
    main()
