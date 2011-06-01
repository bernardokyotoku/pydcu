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
		cam = self.camera
		cam.AllocImageMem()
		cam.SetImageMem()
		assert cam.SetImageSize(x = 300,y = 200) == 0
		assert cam.SetImageSize(x = uc480.IS_GET_IMAGE_SIZE_X) == 300
		assert cam.SetImageSize(x = uc480.IS_GET_IMAGE_SIZE_Y) == 200

	def test_CaptureVideo(self):
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		assert self.camera.CaptureVideo() == 0

	def test_StopLiveVideo(self):
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		self.camera.CaptureVideo() 
		assert self.camera.StopLiveVideo() == 0

	def test_GetError(self):
		try:
			self.camera.CaptureVideo()
		except Exception:
			self.camera.GetError()
			error_message = self.camera.error_message.value 
		assert error_message == "There is no activated image memory"

	def test_CopyImageMem(self):
		import numpy 
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		self.camera.CaptureVideo(uc480.IS_WAIT) 
		self.camera.StopLiveVideo(uc480.IS_WAIT)
		assert self.camera.CopyImageMem() == 0
		assert numpy.sum(self.camera.data) > 0

	def test_AddToSequence(self):
		self.camera.AllocImageMem()
		assert self.camera.AddToSequence() == 0

	def test_CopyImageMem_from_Sequence(self):
		import numpy 
		self.camera.AllocImageMem()
		self.camera.AddToSequence()
		self.camera.SetImageMem()
		self.camera.CaptureVideo(uc480.IS_WAIT) 
		self.camera.StopLiveVideo(uc480.IS_WAIT)
		assert self.camera.CopyImageMem() == 0
		assert numpy.sum(self.camera.data) > 0

	def test_ClearSequence(self):
		assert self.camera.ClearSequence() == 0

	def test_LockSeqBuf(self):
		self.camera.AllocImageMem()
		self.camera.AddToSequence()
		assert self.camera.LockSeqBuf(1) == 0

	def test_UnlockSeqBuf(self):
		self.camera.AllocImageMem()
		assert self.camera.UnlockSeqBuf(1) == 0
		#test with number = 0 done

	def test_GetLastMemorySequence(self):
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		self.camera.AddToSequence()
		self.camera.CaptureVideo(uc480.IS_WAIT) 
		self.camera.StopLiveVideo(uc480.IS_WAIT)
		assert self.camera.GetLastMemorySequence() == 0

	def test_GetActSeqBuf(self):
		self.camera.AllocImageMem()
		self.camera.AddToSequence()
		assert self.camera.GetActSeqBuf() == 0

	def test_GetNumberOfMemoryImages(self):
		self.camera.AllocImageMem()
		self.camera.SetImageMem()
		self.camera.AddToSequence()
		assert self.camera.GetNumberOfMemoryImages() == 0

def test_init():
	camera = uc480.camera()
	camera.ExitCamera()
