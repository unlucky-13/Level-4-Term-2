from PIL import  Image
import numpy as np
from scipy import ndimage

def getImage(name):
    im = Image.open(name)
    p = np.array(im)
    return  p


def block_mean(ar, fact):
    assert isinstance(fact, int), type(fact)
    sx, sy = ar.shape
    X, Y = np.ogrid[0:sx, 0:sy]
    regions = sy/fact * (X/fact) + Y/fact
    res = ndimage.mean(ar, labels=regions, index=np.arange(regions.max() + 1))
    res.shape = (sx/fact, sy/fact)
    return res


def HierarchySearch()



if __name__=='__main__':
    test = getImage("test.bmp")
    HierarchySearch(test,ref,cx,cy)
