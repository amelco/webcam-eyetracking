# Support Vector Machine (SVM)
# from https://www.superdatascience.com/machine-learning/ 

# Part 1 - Data Preprocessing

# Importing the libraries
import os
import glob
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

train_dir = os.path.join(os.path.curdir, "data/train")
validation_dir = os.path.join(os.path.curdir, "data/validate")

train_dirs = []
train_dirs.append(os.path.join(train_dir, "cima"))
train_dirs.append(os.path.join(train_dir, "baixo"))
train_dirs.append(os.path.join(train_dir, "esq"))
train_dirs.append(os.path.join(train_dir, "dir"))

validation_dirs = []
validation_dirs.append(os.path.join(validation_dir, "cima"))
validation_dirs.append(os.path.join(validation_dir, "baixo"))
validation_dirs.append(os.path.join(validation_dir, "esq"))
validation_dirs.append(os.path.join(validation_dir, "dir"))


# Preparando os dados de treinamento
X = []
y = []
for dir in train_dirs:
    classe = dir.rsplit('/')[-1]
    if classe == 'cima':
        classe_num = 0
    if classe == 'baixo':
        classe_num = 1
    if classe == 'esq':
        classe_num = 2
    if classe == 'dir':
        classe_num = 3
    
    files = os.listdir(dir)
    for file in files:
        image = cv.imread(dir+"/"+file, 0)
        # flatten transforma o array 2D de imagem em 1D
        X.append(image.flatten())
        y.append(classe_num)

X_train = np.array(X)
y_train = np.array(y)
print(X_train.shape)
print(y_train.shape)

# Preparando os dados de validação
X = []
y = []
for dir in validation_dirs:
    classe = dir.rsplit('/')[-1]
    if classe == 'cima':
        classe_num = 0
    if classe == 'baixo':
        classe_num = 1
    if classe == 'esq':
        classe_num = 2
    if classe == 'dir':
        classe_num = 3
    
    files = os.listdir(dir)
    for file in files:
        image = cv.imread(dir+"/"+file, 0)
        # flatten transforma o array 2D de imagem em 1D
        X.append(image.flatten())
        y.append(classe_num)

X_val = np.array(X)
y_val = np.array(y)
print(X_val.shape)
print(y_val.shape)


# Feature Scaling
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_val = sc.transform(X_val)
 
# Fitting SVM to the Training set
from sklearn.svm import SVC
from sklearn.pipeline import Pipeline

#classifier = SVC(kernel = 'linear', random_state = 0)
classifier = Pipeline((
("scaler", StandardScaler()),
("svm_clf", SVC(kernel="rbf", gamma=0.01, C=1000000))
))

classifier.fit(X_train, y_train)

# Predicting the Test set results
y_pred = classifier.predict(X_val)

print(y_val[0:35])
print(y_pred[0:35])
 
# Making the Confusion Matrix
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_val, y_pred)

# matriz de confusão
print(cm)

print("Score da validação: ", classifier.score(X_val, y_val))

# Salvando modelo
import joblib as jl

model_file = "svm_eyes.pkl"
jl.dump(classifier, model_file)
