import uc480

def test_init():
	camera = uc480.camera()
	camera.ExitCamera()
class Testuc480:
	def setUp(self):
		self.camera = uc480.camera()

	def tearDown(self):
		self.camera.ExitCamera()

	def test_writeEEPROM(self):
		self.camera.WriteEEPROM("test")
