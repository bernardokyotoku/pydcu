def test_find_lib():
	import ctypes.util
	import os
	if os.name=='nt':
		libname = 'uc480'
	if os.name=='posix':
		libname = 'ueye_api'
	lib = ctypes.util.find_library(libname)
	assert lib is not None
	return lib

class Test_lib():
	def setUp(self):
		self.lib = test_find_lib()

	def test_load_lib(self):
		import ctypes
		library = ctypes.cdll.LoadLibrary(self.lib)
		assert library._name is not None
