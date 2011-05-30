class Testuc480:
	def setUp(self):
		camera = uc480.initCamera()

	def tearDown(self):
		camear.exitCamera()

	def test_writeEEPROM(self):
		camera.writeEEPROM("test")
