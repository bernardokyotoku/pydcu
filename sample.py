import ueye
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

camera = ueye.camera(1)
camera.AllocImageMem()
camera.SetImageMem()
camera.SetImageSize()
camera.SetColorMode()
camera.CaptureVideo()
raw_input("enter to stop")
camera.CopyImageMem()
print np.sum(camera.data)
im = plt.imshow(camera.data, cmap=cm.gray, aspect='equal')
camera.StopLiveVideo()
camera.FreeImageMem()
camera.ExitCamera()
plt.show()
