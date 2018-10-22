#!/usr/bin/env python
import numpy as np
from PIL import Image

import random
#create a random Image
newImage = np.zeros((300,300,3), dtype="uint8")

for x in range(newImage.shape[0]):
    for y in range(newImage.shape[1]):
        newImage[x][y] = (random.randint(0,255),random.randint(0,255),random.randint(0,255))

testImage = Image.fromarray(newImage.astype("uint8"))
testImage.save('testImage.png')
