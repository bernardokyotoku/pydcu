import uc480
import sys

class Testuc480:
	def setUp(self):
		self.camera = uc480.camera()

	def tearDown(self):
		self.camera.ExitCamera()

	def test_ReadEEPROM(self):
		self.camera.WriteEEPROM("test")
		content = self.camera.ReadEEPROM(count=len("test"))
		assert content == "test"

	def test_WriteEEPROM(self):
		self.camera.WriteEEPROM("test")

	def test_AllocImageMem(self):
		assert self.camera.AllocImageMem() == 0

	def test_FreeImageMem(self):
		self.camera.AllocImageMem()
		assert self.camera.FreeImageMem() == 0

	def test_SetImageMem(self):
		self.camera.AllocImageMem()
		assert self.camera.SetImageMem() == 0

	def test_SetImageSize(self):
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		assert self.camera.SetImageSize(x = 300,y = 200) == 0
		assert self.camera.SetImageSize(x = uc480.IS_GET_IMAGE_SIZE_X) == 300
		assert self.camera.SetImageSize(x = uc480.IS_GET_IMAGE_SIZE_Y) == 200

def test_init():
	camera = uc480.camera()
	camera.ExitCamera()
