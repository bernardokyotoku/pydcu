from PyQt4 import QtGui, QtCore
import gobject, sys
import uc480
import numpy

class Viewer(QtGui.QMainWindow):
    def __init__(self, *args):
        super(Viewer, self).__init__(*args)
        self.setup_graphics_view()
        self.setup_camera()

    def setup_graphics_view(self):
        self.graphics = QtGui.QGraphicsView()
        self.setCentralWidget(self.graphics)
        self.scene = QtGui.QGraphicsScene()
        self.graphics.setScene(self.scene)
#        self.pixmap = QtGui.QPixmap()
#        self.scene.addPixmap(self.pixmap)

    def setup_camera(self):
        self.camera = uc480.camera(1)
        self.camera.AllocImageMem()
        self.camera.SetImageMem()
        self.camera.SetImageSize()
        self.camera.SetColorMode()
        self.camera.CaptureVideo()

        self.timer = QtCore.QTimer()
        self.connect(self.timer, QtCore.SIGNAL("timeout()"), self.update_image)
        self.timer.start(1000)
        
    def update_image(self):
        self.camera.CopyImageMem()
        image = gray2qimage(self.camera.data)
        self.scene.addPixmap(QtGui.QPixmap.fromImage(image))
        self.timer.start(1000)

    def closeEvent(self, event):
        self.camera.StopLiveVideo()
        self.camera.FreeImageMem()
        self.camera.ExitCamera()

def gray2qimage(gray):
    """Convert the 2D numpy array `gray` into a 8-bit QImage with a gray
    colormap.  The first dimension represents the vertical image axis.
    http://www.mail-archive.com/pyqt@riverbankcomputing.com/msg17961.html"""
    if len(gray.shape) != 2:
        raise ValueError("gray2QImage can only convert 2D arrays")

    gray = numpy.require(gray, numpy.uint8, 'C')

    h, w = gray.shape

    result = QtGui.QImage(gray.data, w, h, QtGui.QImage.Format_Indexed8)
    result.ndarray = gray
    for i in range(256):
        result.setColor(i, QtGui.QColor(i, i, i).rgb())
    return result



if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    main_window = Viewer()
    main_window.show()
    app.exec_()
