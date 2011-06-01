import os
import sys
import textwrap
import numpy as np
from numpy import ctypeslib
from ctypes import byref,c_int,create_string_buffer,c_char_p,cdll,util,c_void_p
import warnings
import symbols as sym

from uc480_h import *

SUCCESS = 0
NO_SUCCESS = -1
INVALID_HANDLER = 1
HANDLE = c_void_p            
HCAM = HANDLE
HWND = c_void_p            
INT = c_int

if os.name=='nt':
	libname = 'uc480'
	include_uc480_h = os.environ['PROGRAMFILES']+'\\Thorlabs DCU camera\\Develop\\Include\\uc480.h'
if os.name=='posix':
	libname = 'ueye_api'
	include_uc480_h = "/usr/include/ueye.h"
lib = util.find_library(libname)
if lib is None:
	print 'uc480.dll not found'

		
libuc480 = cdll.LoadLibrary(lib)
if libuc480 is not None:
	uc480_h_name = 'uc480_h'
	try:
		uc480_h = "uc480_h"
		#from uc480_h import *
		#exec 'from %s import *' % (uc480_h_name)
	except ImportError:
		uc480_h = None
	if uc480_h is None:
		assert os.path.isfile (include_uc480_h), `include_uc480_h`
		d = {}
		l = ['# This file is auto-generated. Do not edit!']
		error_map = {}
		f = open (include_uc480_h, 'r')
		
		def is_number(s):
			try:
				float(s)
				return True
			except ValueError:
				return False
				
		for line in f.readlines():
			if not line.startswith('#define'): continue
			i = line.find('//')
			words = line[7:i].strip().split(None, 2)
			if len (words)!=2: continue
			name, value = words
			if value.startswith('0x'):
				exec '%s = %s' % (name, value)
				d[name] = eval(value)
				l.append('%s = %s' % (name, value))
			elif is_number(value):
				d[name] = eval(value)
				l.append('%s = %s' % (name, value))
			elif value.startswith('UC'):
				print value
				d[name] = unicode(value[3:-1])
				l.append('%s = unicode("%s")' % (name, value[3:-1]))
			elif d.has_key(value):
				d[name] = d[value]
				l.append('%s = %s' % (name, d[value]))
			else:
				d[name] = value
				l.append('%s = %s' % (name, value))
				pass
		l.append('error_map = %r' % (error_map))
		fn = os.path.join (os.path.dirname(os.path.abspath (__file__)), uc480_h_name+'.py')
		print 'Generating %r' % (fn)
		f = open(fn, 'w')
		f.write ('\n'.join(l) + '\n')
		f.close()
		print 'Please upload generated file %r to http://code.google.com/p/pylibuc480/issues' % (fn)
	else:
		pass

def is_value_return_function(funcname):
	EnableAutoExit #Actual settings when called with IS_GET_AUTO_EXIT_ENABLED(), else IS_SUCCESS or
	GetBusSpeed #IS_SUCCESS    USB 2.0 Controller available (hf=0)
			#IS_NO_SUCCESS no USB 2.0 Controller available (hf=0)
			#IS_USB_10     Controller port to which the camera is connected supports no USB 2.0
			#	      IS_USB_20     Camera is connected to a USB 2.0 controller
	GetCameraType # IS_CAMERA_TYPE_DCU_USB
	GetDLLVersion # Number of the version
	GetOsVersion # IS_OS_WIN2000, IS_OS_WINXP, IS_OS_WINSERVER2003
	GetImageHistogram #IS_SUCCESS
			#	IS_NO_SUCCESS
			#	IS_NULL_POINTER invalid array
			#	IS_INVALID_COLOR_FORMAT unsupported color format
			#	IS_INVALID_PARAMETER unknown parameter ColorMode
	InitCamera # IS_SUCCESS, error code (see header file)
	LoadImage # 
		#IS_SUCCESS                    Image is loaded error free.
		#IS_FILE_READ_INVALID_BMP_SIZE The image to be load is larger than the active image memory.
		#IS_FILE_READ_INVALID_BMP_ID   The file to be load does not have a valid bitmap format.
		#IS_FILE_READ_OPEN_ERROR       The file cannot be opene
	LoadImageMem  #	IS_SUCCESS (image is loaded error free)
		      #  IS_FILE_READ_INVALID_BMP_ID (the file to be loaded does not have a valid bitmap format)
		      #  IS_FILE_READ_OPEN_ERROR (the file cannot be opened)

	SaveImageMemEx 	# IS_SUCCESS, IS_NO_SUCCESS
			# IS_INVALID_PARAMETER (invalid file format or JPEG Quality)
	SetBadPixelCorrection # IS_SUCCESS, IS_NO_SUCCESS, the current mode in connection with IS_GET_BPC_MODE or the current level in connection with IS_GET_BPC_THRESHOLD
	SetBadPixelCorrectionTable # IS_SUCCESS, IS_NO_SUCCESS, or the number or coordinates in the list with IS_GET_LIST_SIZE
	SetBayerConversion # In connection with IS_GET_BAYER_CV_MODE the current settings are read, else IS_SUCCESS or IS_NO_SUCCESS.
	SetBinning # IS_SUCCESS, IS_NO_SUCCESS or the current settings with IS_GET_BINNING
	SetBlCompensation # IS_SUCCESS, IS_NO_SUCCESS, current settings with IS_GET_BL_COMPENSATION, or the preset offset with IS_GET_BL_OFFSET
	SetBrightness # In connection with IS_GET_CAMERA_ID the current ID is returned, else IS_SUCCESS or IS_NO_SUCCESS.
	SetCameraID # In connection with IS_GET_CAMERA_ID the current ID is returned, else IS_SUCCESS or IS_NO_SUCCESS.
	SetColorCorrection # Current settings when called with IS_GET_CCOR_MODE(), else IS_SUCCESS, IS_NO_SUCCESS
	is_SetColorMode # Current setting when called with IS_GET_COLOR_MODE, else IS_SUCCESS, IS_NO_SUCCESS.
	SetContrast # Current settings when called with IS_GET_CONTRAST else IS_SUCCESS, IS_NO_SUCCESS.
	SetConvertParam # IS_SUCCESS, IS_NO_SUCCESS, IS_INVALID_COLOR_FORMAT or IS_INVALID_PARAMETER
	SetDisplayMode # Current setting with IS_GET_DISPLAY_MODE, else IS_SUCCESS, IS_NO_SUCCESS
	SetErrorReport # Current setting when called with IS_GET_ERR_REP_MODE else IS_SUCCESS, IS_NO_SUCCESS.
	SetExternalTrigger # IS_SUCCESS, IS_NO_SUCCESS or current setting with IS_GET_EXTERNALTRIGGER IS_SET_TRIG_SOFTWARE | IS_SET_TRIG_HI_LO | IS_SET_TRIG_LO_HI using IS_GET_SUPPORTED_TRIGGER_MODE
	SetFlashDelay # IS_SUCCESS, IS_NO_SUCCESS, current settings in connection with IS_GET_FLASH_DELAY or IS_GET_FLASH_DURATION.
	SetFlashStrobe # IS_SUCCESS, IS_NO_SUCCESS, the current mode when used with IS_GET_FLASHSTROBE_MODE
	SetGainBoost # Current setting when called with IS_GET_GAINBOOST else IS_NOT_SUPPORTED, IS_SUCCESS or IS_NO_SUCCESS
	SetGamma # Current settings in connection with IS_GET_BRIGHTNESS, sonst IS_SUCCESS or IS_NO_SUCCESS
	SetHardwareGain # Current setting when called with IS_GET_MASTER_GAIN, IS_GET_RED_GAIN, IS_GET_ GREEN_GAIN, IS_GET_BLUE_GAIN else IS_SUCCESS or IS_NO_SUCCESS
	SetHardwareGamma # IS_SUCCESS, IS_NO_SUCCESS or IS_NOT_SUPPORTED
	SetHWGainFactor # Current settings in connection with IS_GET_MASTER_GAIN_FACTOR, IS_GET_RED_GAIN_FACTOR, IS_GET_ GREEN_GAIN_FACTOR, IS_GET_BLUE_GAIN_FACTOR.
	# Adjusted settings after the use of IS_SET_MASTER_GAIN_FACTOR, IS_SET_RED_GAIN_FACTOR, IS_SET_ GREEN_GAIN_FACTOR, IS_SET_BLUE_GAIN_FACTOR.
	# Standard settings after the use of IS_GET_DEFAULT_MASTER_GAIN_FACTOR, IS_GET_DEFAULT_RED_GAIN_FACTOR, IS_GET_DEFAULT_ GREEN_GAIN_FACTOR, IS_GET_DEFAULT_BLUE_GAIN_FACTOR.
	# Converted gain index after the use of IS_INQUIRE_ MASTER_GAIN_FACTOR, IS_INQUIRE_ RED_GAIN_FACTOR, IS_INQUIRE _ GREEN_GAIN_FACTOR, IS_INQUIRE _BLUE_GAIN_FACTOR.
	SetImagePos # Current settings when called with IS_GET_IMAGE_POS_X and IS_GET_IMAGE_POS_Y as a parameter for x, else IS_SUCCESS, IS_NO_SUCCESS
	SetImageSize # When used with IS_GET_IMAGE_SIZE_X and IS_GET_IMAGE_SIZE_Y the current settings are read, else IS_SUCCESS or IS_NO_SUCCESS.
	
	SetIO # IS_SUCCESS, IS_NO_SUCCESS, current settings in connection with IS_GET_IO.
	SetKeyColor # Colour value in connection with IS_GET_KC_RGB, IS_GET_KC_RED, IS_GET_KC_GREEN, IS_GET_KC_BLUE else IS_SUCCESS, IS_NO_SUCCESS
	SetPixelClock # Current settings when called with IS_GET_PIXEL_CLOCK, else IS_SUCCESS or IS_NO_SUCCESS
	SetRopEffect # IS_SUCCESS, IS_NO_SUCCESS or the current settings in connection with IS_SET_ROP_EFFECT
	SetSaturation # IS_SUCCESS, IS_NO_SUCCESS IS_INVALID_PARAMETER (invalid ChromU or ChromV value) Current settings in connection with IS_GET_SATURATION_U or IS_GET_SATURATION_V.
	SetSubSampling # Current setting when called with IS_GET_SUBSAMPLING else IS_SUCCESS, IS_NO_SUCCESS
	SetTestImage # In connection with IS_GET_TEST_IMAGE the current settings are read, else IS_SUCCESS or IS_NO_SUCCESS.
	SetTriggerDelay # IS_SUCCESS, IS_NO_SUCCESS, current settings in connection with IS_GET_TRIGGER_DELAY
	SetWhiteBalance # Current settings when called with IS_GET_WB_MODE(), else IS_SUCCESS, IS_NO_SUCCESS


def CHK(return_code, funcname, *args):
	if return_code is SUCCESS:
		return SUCCESS
	elif return_code is NO_SUCCESS:
		raise
	elif is_value_return_function(funcname):
		return return_code
	else:
		sys.stderr.write(sym.ERROR_CODE[error_code])
		raise

def CALL(name, *args):
	"""
	Calls libuc480 function "name" and arguments "args".
	"""
	funcname = 'is_' + name
	func = getattr(libuc480, funcname)
	new_args = []
	for a in args:		
		if isinstance (a, unicode):
			print name, 'argument',a, 'is unicode'
			new_args.append (str (a))
		else:
			new_args.append (a)
	return func(*new_args) 
#	if r is NO_SUCCESS:
#		raise Exception("NO_SUCCESS")
#	elif r is INVALID_HANDLER:
#		raise Exception("INVALID_HANDLER")
#	return r

class camera(HCAM):
	def __init__(self,camera_id=0):
		#self.id = camera_id
		HCAM.__init__(self,0)
		r = CALL('InitCamera',byref(self),HWND(0))
		if r is not SUCCESS:
			sys.stderr.write(sym.ERROR_CODE[r])
			raise
		self.width = 1024
		self.height = 768		
		self.seq = 0
		self.data = np.zeros((self.height,self.width),dtype=np.uint8)
		return None

	def AddToSequence(self):
		"""
		AddToSequence() inserts image memory into the image memory list,
		which is to be used for ring buffering. The image memory has to
		be allocated with AllocImageMem(). All image memory which is 
		used for ring buffering must have been allocated the same colour
		depth (i.e. bits per pixel). The number of image memories for a
		sequence (nID) is limited to the integer value range.  
		"""
		self.seq += 1
		return CALL('AddToSequence',self,self.image,self.id) 

	def ClearSequence(self):
		"""
		ClearSequence() deletes all image memory from the sequence list
		that was inserted with AddToSequence(). After ClearSequence() no
		more image memory is active. To make a certain part of the image
		memory active, SetImageMem() and SetImageSize() have to be 
		executed.
		Not tested!
		"""
		return CALL('ClearSequence',self)
			
	def LockSeqBuf(self,number):
		"""
		LockSeqBuf() can be used to disable the overwriting of the image
		memory with new image data. And thus it is possible to prevent
		images which are required for further processing from being 
		overwritten. Full access to the image memory is still available.
		Only one image memory can be disabled at the same time. To 
		access the image memory use function UnlockSeqBuf().
		Not tested!
		"""
		return CALL('LockSeqBuf',self,INT(number),self.image)

	def UnlockSeqBuf(self,number):
		"""
		With UnlockSeqBuf() image acquisition is allowed in a previously
		locked image memory. The image memory is put to the previous 
		position in the sequence list.
		"""
		return CALL('UnlockSeqBuf',self,INT(number),self.image)

	def GetLastMemorySequence(self):
		"""
		The function GetLastMemorySequence() returns the ID of the last
		recorded sequence in the memory board. This parameter can then 
		be used in combination with the function TransferImage() to read
		images out of the camera memory.
		No memory board to test this, Not tested!
		"""
		r = CALL('GetLastMemorySequence',self,byref(self.id))
		if r is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return r

	def TransferImage():
		"""
		Experiment to find out how it works
		TransferImage(self, INT nMemID, INT seqID, INT imageNr, INT reserved)
		Not in the user manual!
		Not implemented!
		"""
		CALL('TransferImage',self,INT(),INT(),INT(),INT())

	def TransferMemorySequence(): 
		"""
		Experiment to find out how it works
		TransferMemorySequence(HIDS hf, INT seqID, INT StartNr, INT nCount, INT nSeqPos);
		Not in the user manual!
		Not implemented!
		"""
		pass

	def GetMemorySequenceWindow(self,id):
		"""
		The function GetMemorySequenceWindow() can be used to check the window size of a
		specified memory board sequence. The assigned sequence ID is required as a parameter.
		Not tested!
		"""
		top    = INT() 
		left   = INT()
		right  = INT()
		bottom = INT()
		CALL('GetMemorySequenceWindow',self,INT(id),byref(left),byref(top),byref(right),byref(bottom))
		return (left.value,top.value,right.value,bottom.value)

	def GetActSeqBuf(self):
		"""
		With GetActSeqBuf() the image memory in which image acquisition
		(ppcMem) is currently taking place and the image memory which 
		was last used for image acquisition (ppcMemLast) can be deter-
		mined. This function is only available when the ring buffer is 
		active. If image acquisition is started for a ring buffer, 
		GetActSeqBuf returns 0 in pnNum as long as data is acquired to 
		the first image memory of the sequence. And thus pnNum receives
		the number of the sequence image memory, in which image acqui-
		sition is currently taking place. The number is not the ID of 
		the image memory which is provided from AllocImageMem(), but the
		running number in the sequence as defined in AddToSequence().
		"""
		aqID = INT()
		pcMem = c_char_p()
		pcMemLast = c_char_p()
		paqID = byref(aqID)
		ppcMem = byref(pcMem)
		ppcMemLast = byref(pcMemLast)
		r = CALL('GetActSeqBuf',self,paqID,ppcMem,ppcMemLast)
		if r is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return r

		
	def AllocImageMem(self,width=1024,height=768,bitpixel=8):
		"""
		AllocImageMem() allocates image memory for an image with width,
		width and height, height and colour depth bitspixel. Memory size
		is at least:

		size = [width * ((bitspixel + 1) / 8) + adjust] * height
		adjust see below

		Line increments are calculated with:

		line 	= width * [(bitspixel + 1) / 8]
		lineinc = line + adjust.
		adjust  = 0 when line without rest is divisible by 4
		adjust 	= 4 - rest(line / 4) 
				when line without rest is not divisible by 4


		The line increment can be read with the GetImgMemPitch() func-
		tion. The start address in the image memory is returned with 
		ppcImgMem. pid contains an identification number of the alloc-
		ated memory. A newly activated memory location is not directly 
		activated. In other words, images are not directly digitized to
		this new memory location. Before this can happen, the new memory
		location has to be activated with SetImageMem(). After 
		SetImageMem() an SetImageSize() must follow so that the image 
		conditions can be transferred to the newly activated memory 
		location. The returned pointer has to be saved and may be 
		reused, as it is required for all further ImageMem functions! 
		The freeing of the memory is achieved with FreeImageMem(). In 
		the DirectDraw modes, the allocation of an image memory is not 
		required!
		"""
		self.image = c_char_p()
		self.id = INT()
		return CALL('AllocImageMem',self,
			INT(width),
			INT(height),
			INT(bitpixel),
			byref(self.image),
			byref(self.id))

	def GetNumberOfMemoryImages(self):
		"""
		The function GetNumberOfMemoryImages() returns the number of 
		valid images that are currently located in the camera memory 
		within the specified sequence ID. This number can differ from 
		the originally recorded number of images because of overwriting.
		Not tested!

		"""
		number = INT()
		r = CALL('GetNumberOfMemoryImages',self,INT(self.seq),byref(number))
		if r is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return number.value
	
	def SetImageMem(self):
		"""
		SetImageMem() sets the allocated image memory to active memory.
		Only an active image memory can receive image data. After 
		calling SetImageMem() function is_SetImageSize() must follow to
		set the image size of the active memory. A pointer from function
		AllocImgMem() has to be given to parameter pcImgMem.
		"""
		return CALL("SetImageMem",self,self.image,self.id)
		
	def SetImageSize(self,x=IS_GET_IMAGE_SIZE_X_MAX,y=IS_GET_IMAGE_SIZE_X_MAX):
		"""
		Sets the image size.

		If x is configure to:
		IS_GET_IMAGE_SIZE_X     Retrieval of current width
		IS_GET_IMAGE_SIZE_X_MIN Smallest value for the AOI width
		IS_GET_IMAGE_SIZE_X_MAX Largest value for the AOI width
		IS_GET_IMAGE_SIZE_X_INC Increment for the AOI width
		IS_GET_IMAGE_SIZE_Y     Retrieval of current height
		IS_GET_IMAGE_SIZE_Y_MIN Smallest value for the AOI height
		IS_GET_IMAGE_SIZE_Y_MAX Largest value for the AOI height
		IS_GET_IMAGE_SIZE_Y_INC Increment for the AOI height
		y is ignored and the specified size is returned.
		"""
		return CALL("SetImageSize",self,INT(x),INT(y))

	def FreeImageMem (self):
		"""
		FreeImageMem() deallocates previously allocated image memory.i
		For pcImgMem one of the pointers from AllocImgMem() has to be 
		used. All other pointers lead to an error message! The repeated
		handing over of the same pointers also leads to an error message
		"""
		return CALL("FreeImageMem",self,self.image,self.id)

	def SetAllocatedImageMem(self):
		"""
		Set an allocated memory, that was not allocated using AllocImageMem,
		to the driver so it can be used to store the image that will be 
		degitized. The allocated memory must be globally locked.
		(Basically, use this if some non-driver function happens to have
		some memory already allocated, so you don't need to allocate more
		memory)
		Not Implemented!
		"""
	
	def GetActiveImageMem(self):
		"""
		GetActiveImageMem() returns the pointer to the beginning and the
		ID number of the active memory. If DirectDraw mode is active and
		image memory has been allocated, this function returns the 
		pointer and the ID of the image memory, which was activated with
		SetImageMem(). However, it should be noted that in DirectDraw 
		mode, this memory is not used for digitizing.
		Also see GetImgMem().
		Not tested!
		"""
		CALL('GetActiveImageMem',self,byref(self.image),byref(self.id))

	def GetImageMem(self):
		"""
		GetImageMem() returns the pointer to the start of the active
		image memory. In DirectDraw mode the pointer is returned to the
		back buffer (or the visible area - DirectDraw Primary Surface
		mode).
		"""
		CALL('GetImageMem',self,byref(self.image))
		
	def FreezeVideo(self,wait=IS_WAIT):
		CALL("FreezeVideo",self,INT(wait))
		
	def CopyImageMem(self):
		"""
		CopyImageMem() copies the contents of the image memory, as
		described is pcSource and nID to the area in memory, which 
		pcDest points to.  
		"""
		r = CALL("CopyImageMem",self,self.image,self.id,self.data.ctypes.data)
		if r is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return r

	def GetError(self):
		self.error = INT()
		self.error_message = c_char_p()
		return CALL("GetError",self,
			byref(self.error),
			byref(self.error_message))

	def SaveImage(self,file):
		return CALL('SaveImage',self,None)
		
	def SetImagePos(self,x=0,y=0):
		return CALL("SetImagePos",self,INT(x),INT(y))
		
	def CaptureVideo(self,wait=IS_DONT_WAIT):
		"""
		CaptureVideo() digitizes video images in real time and transfers
		the images to the previously allocated image memory. 
		Alternatively if you are using DirectDraw the images can be 
		transferred to the graphics board. The image acquisition (DIB 
		Mode) takes place in the memory which has been set by 
		SetImageMem() and AllocImageMem(). GetImageMem() determines 
		exactly where the start address in memory is. In case of ring 
		buffering, then image acquisition loops endlessly through all 
		image memeories added to the sequence.

		wait
	 	IS_DONT_WAIT	This function synchronizes the image acquisition				of the V-SYNC, but returns immediately.
		IS_WAIT		This function synchronizes the image acquisition
				of the V-SYNC and only then does return (i.e.
				waits until image acquisition begins)
		10<wait<32768	Wait time in 10 ms steps. A maximum of 327.68 
				seconds (this is approx. 5 minutes and 20 
				seconds) can be waited. For 1 < Wait < 10 Wait 
				becomes equal to 10.
		(Exp.: Wait = 100 => wait 1 sec.)
		"""
		r = CALL("CaptureVideo",self,INT(wait))
		if r is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return r
		
	def SetColorMode(self,color_mode=IS_SET_CM_Y8):
		return CALL("SetColorMode",self,INT(color_mode))
	
	def SetSubSampling(self,mode=IS_SUBSAMPLING_DISABLE):
		return CALL("SetSubSampling",self,INT(mode))
		
	def StopLiveVideo(self,wait=IS_DONT_WAIT):
		"""
		The StopLiveVideo() function freezes the image in the VGA card 
		or in the PC's system memory. The function is controlled with 
		the parameter Wait. The function has two modes: Using the first
		mode, the function immediately returns to the calling function 
		and grabs the image in the background. In the second mode the 
		function waits until the image has been completely acquired and
		only then does the function return.
		By the use of IS_FORCE_VIDEO_STOP a single frame recording which
		is started with FreezeVideo(IS_DONT_WAIT) can be terminated
		immediately.
		"""
		return CALL("StopLiveVideo",self,INT(wait))
		
	def ExitCamera (self):
		return CALL("ExitCamera",self)
	

	def ReadEEPROM(self,offset = 0, count = 64):
		"""
		There is a rewritable EEPROM in the camera which serves as a 
		small memory. Additionally to the information which is stored 
		in the EEPROM, 64 extra bytes can be written. With the 
		ReadEEPROM() command the contents of these 64 bytes can be read.
		See WriteEEPROM.
		"""
		if offset + count > 64:
			sys.stderr.write("offset + count too big, must be smaller or equal 64")
			raise
		buffer = create_string_buffer(count)
		CALL('ReadEEPROM',self,INT(offset),buffer,INT(count))
		return buffer.value

	def WriteEEPROM(self, content, offset = 0):
		"""	
		In the DCU camera there is a rewritable EEPROM, where 64 bytes 
		of information can be written. With the ReadEEPROM() function
		the contents of this 64 byte block can be read.
		"""
		count = len(content)
		if count + offset > 64:
			raise Exception("Content to long")
		pcString = c_char_p(content)
		return CALL('WriteEEPROM',self,INT(offset),pcString,INT(count))
