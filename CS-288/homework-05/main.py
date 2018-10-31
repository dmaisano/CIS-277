import os
import random
import string
import json

with open('data.json', 'w') as outfile:
    json.dump([1, 2, 3], outfile)
