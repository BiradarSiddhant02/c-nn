import os
import pandas as pd

from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import cross_validate

data_path = os.path.join('.', 'data', 'data.csv')

data = pd.read_csv(data_path)
print(data_path)

print(data.head())

X = data.iloc[:, :-1]  
y = data.iloc[:, -1] 

classifier = RandomForestClassifier() 
 
# Run cross validation with 10 folds
scores = cross_validate(
    classifier, X, y, cv=10, 
    # measure score for a list of classification metrics
    scoring=['accuracy', 'precision', 'recall', 'f1']
)
 
scores = pd.DataFrame(scores)
print(scores.mean().round(4))

