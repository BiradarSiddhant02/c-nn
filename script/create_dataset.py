import argparse
from sklearn.datasets import make_classification
import pandas as pd
import os

def create_directory(directory_name):
    
    script_dir = os.path.dirname(os.path.abspath(__file__))

    parent_dir = os.path.dirname(script_dir)

    new_dir = os.path.join(parent_dir, directory_name)

    try:
        os.mkdir(new_dir)
    except FileExistsError:
        pass
    except Exception as e:
        print(f"An error occurred: {e}")

def generate_dataset(n_samples, n_features, n_useful_features, n_classes):
    X, y = make_classification(
        n_samples=n_samples,
        n_features=n_features,
        n_informative=n_useful_features,
        n_redundant=n_features - n_useful_features,
        n_classes=n_classes,
        random_state=999
    )

    # Create DataFrame with features as columns
    dataset = pd.DataFrame(X)

    # Give custom names to the features
    dataset.columns = [f'X{i}' for i in range(1, n_features + 1)]

    # Now add the label as a column
    dataset['y'] = y

    return dataset

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate synthetic classification dataset and save as CSV file.')
    parser.add_argument('--s', type=int, default=1000, help='Number of samples in the dataset')
    parser.add_argument('--f', type=int, default=7, help='Number of total features')
    parser.add_argument('--uf', type=int, default=3, help='Number of useful features')
    parser.add_argument('--c', type=int, default=2, help='Number of classes')
    parser.add_argument('--o', type=str, default='data.csv', help='Output CSV file path')
    args = parser.parse_args()

    directory_path = "../data/"
    create_directory(directory_path)

    dataset = generate_dataset(args.s, args.f, args.uf, args.c)
    dataset.to_csv(directory_path + args.o, index=False)
