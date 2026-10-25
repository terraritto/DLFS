import pickle
import json
import numpy as np

with open("sample_weight.pkl", 'rb') as f:
    network = pickle.load(f)
    with open("sample_weight.json", 'w') as w:
        network['b1'] = network['b1'].tolist()
        network['b2'] = network['b2'].tolist()
        network['b3'] = network['b3'].tolist()
        network['W1'] = network['W1'].tolist()
        network['W2'] = network['W2'].tolist()
        network['W3'] = network['W3'].tolist()
        json.dump(network, w)