import os
import sys
import textwrap
from numpy import zeros,uint8,ctypeslib
from ctypes import byref,c_int,create_string_buffer,c_char_p,cdll,util,c_void_p
import IS

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




class image(object):
	def __init__(self,camera):
		self.cam = camera

	@property
	def size(self):
		height = self.cam.SetImageSize(x=IS.GET_IMAGE_SIZE_X)
		width =  self.cam.SetImageSize(x=IS.GET_IMAGE_SIZE_Y)
		return (width,height)

	@size.setter
	def size(self,value):
		if len(value) != 2:
			raise Exception ("Value len not equal 2.")
		(width,height) = value
		if width is None:
			width =  self.cam.SetImageSize(x=IS.GET_IMAGE_SIZE_X)
		if height is None:
			height = self.cam.SetImageSize(x=IS.GET_IMAGE_SIZE_Y)
		self.cam.SetImageSize(x=width,y=height)

	@property
	def position(self):
		y = self.cam.SetImagePos(IS.GET_IMAGE_POS_X)
		x =  self.cam.SetImagePos(IS.GET_IMAGE_POS_Y)
		return (x,y)
	
	@position.setter
	def position(self,value):
		if len(value) != 2:
			raise Exception ("Value len not equal 2.")
		(x,y) = value
		if x is None:
			x =  self.cam.SetImagePos(IS.GET_IMAGE_POS_X)
		if y is None:
			y = self.cam.SetImagePos(IS.GET_IMAGE_POS_Y)
		self.cam.SetImagePos(x,y)

class pycam:
	def __init__(self,camera_id = 0):
		self.cam = camera(camera_id)
		self.image = image(self.cam)

	def __del__(self):
		self.cam.ExitCamera()

	def take_snapshot(self):
		pass

class camera(HCAM):
	def __init__(self,camera_id=0):
		HCAM.__init__(self,0)
		r = CALL('InitCamera',byref(self),HWND(0))
		if r is not SUCCESS:
			raise Exception("Error %d"%r)
		self.width = 1024
		self.height = 768		
		self.seq = 0
		self.data = zeros((self.height,self.width),dtype=uint8)
		return None

	def CheckForSuccessError(self,return_value):
		if return_value is not SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return SUCCESS

	def CheckForNoSuccessError(self,return_value):
		if return_value is NO_SUCCESS:
			self.GetError()
			raise Exception(self.error_message.value)
		return return_value

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
		r = CALL('AddToSequence',self,self.image,self.id) 
		return self.CheckForSuccessError(r)

	def ClearSequence(self):
		"""
		ClearSequence() deletes all image memory from the sequence list
		that was inserted with AddToSequence(). After ClearSequence() no
		more image memory is active. To make a certain part of the image
		memory active, SetImageMem() and SetImageSize() have to be 
		executed.
		Not tested!
		"""
		r = CALL('ClearSequence',self)
		return self.CheckForSuccessError(r)
			
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
		r = CALL('LockSeqBuf',self,INT(number),self.image)
		return self.CheckForSuccessError(r)

	def UnlockSeqBuf(self,number):
		"""
		With UnlockSeqBuf() image acquisition is allowed in a previously
		locked image memory. The image memory is put to the previous 
		position in the sequence list.
		"""
		r = CALL('UnlockSeqBuf',self,INT(number),self.image)
		return self.CheckForSuccessError(r)

	def GetLastMemorySequence(self):
		"""
		The function GetLastMemorySequence() returns the ID of the last
		recorded sequence in the memory board. This parameter can then 
		be used in combination with the function TransferImage() to read
		images out of the camera memory.
		No memory board to test this, Not tested!
		"""
		r = CALL('GetLastMemorySequence',self,byref(self.id))
		return self.CheckForSuccessError(r)

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
		return self.CheckForSuccessError(r)
		
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
		r =  CALL('AllocImageMem',self,
			INT(width),
			INT(height),
			INT(bitpixel),
			byref(self.image),
			byref(self.id))
		return self.CheckForSuccessError(r)

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
		return self.CheckForSuccessError(r)
	
	def SetImageMem(self):
		"""
		SetImageMem() sets the allocated image memory to active memory.
		Only an active image memory can receive image data. After 
		calling SetImageMem() function SetImageSize() must follow to set
		the image size of the active memory. A pointer from function
		AllocImgMem() has to be given to parameter pcImgMem.
		"""
		r = CALL("SetImageMem",self,self.image,self.id)
		return self.CheckForSuccessError(r)
		
	def SetImageSize(self,x=IS.GET_IMAGE_SIZE_X_MAX,y=0):#non-zero ret
		"""
		Sets the image size.

		If x is configure to:
		IS.GET_IMAGE_SIZE_X     Retrieval of current width
		IS.GET_IMAGE_SIZE_X_MIN Smallest value for the AOI width
		IS.GET_IMAGE_SIZE_X_MAX Largest value for the AOI width
		IS.GET_IMAGE_SIZE_X_INC Increment for the AOI width
		IS.GET_IMAGE_SIZE_Y     Retrieval of current height
		IS.GET_IMAGE_SIZE_Y_MIN Smallest value for the AOI height
		IS.GET_IMAGE_SIZE_Y_MAX Largest value for the AOI height
		IS.GET_IMAGE_SIZE_Y_INC Increment for the AOI height
		y is ignored and the specified size is returned.
		"""
		r = CALL("SetImageSize",self,INT(x),INT(y))
		if x & 0x8000 == 0x8000:
			return self.CheckForNoSuccessError(r)
		return self.CheckForSuccessError(r)
		

	def FreeImageMem (self):
		"""
		FreeImageMem() deallocates previously allocated image memory.i
		For pcImgMem one of the pointers from AllocImgMem() has to be 
		used. All other pointers lead to an error message! The repeated
		handing over of the same pointers also leads to an error message
		"""
		r = CALL("FreeImageMem",self,self.image,self.id)
		return self.CheckForSuccessError(r)

	def SetAllocatedImageMem(self,width=1024,height=768,bitpixel=8):
		"""
		Set an allocated memory, that was not allocated using 
		AllocImageMem, to the driver so it can be used to store the 
		image that will be degitized. The allocated memory must be 
		globally locked.
		(Basically, use this if some non-driver function happens to have
		some memory already allocated, so you don't need to allocate more
		memory)
		Not Implemented!
		"""
		self.image = self.data.ctypes.data_as(c_char_p)
		self.id = INT()
		r = CALL('SetAllocatedImageMem',self,
			INT(width),
			INT(height),
			INT(bitpixel),
			self.data.ctypes.data,
			byref(self.id))
		return self.CheckForSuccessError(r)
		
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
		
	def FreezeVideo(self,wait=IS.WAIT):
		CALL("FreezeVideo",self,INT(wait))
		
	def CopyImageMem(self):
		"""
		CopyImageMem() copies the contents of the image memory, as
		described is pcSource and nID to the area in memory, which 
		pcDest points to.  
		"""
		r = CALL("CopyImageMem",self,self.image,self.id,self.data.ctypes.data)
		return self.CheckForSuccessError(r)

	def GetError(self):
		self.error = INT()
		self.error_message = c_char_p()
		return CALL("GetError",self,
			byref(self.error),
			byref(self.error_message))

	def SaveImage(self,file):
		r = CALL('SaveImage',self,None)
		return self.CheckForSuccessError(r)
		
	def SetImagePos(self,x=0,y=0):
		r = CALL("SetImagePos",self,INT(x),INT(y))
		if x & 0x8000 == 0x8000:
			return self.CheckForNoSuccessError(r)
		return self.CheckForSuccessError(r)
		
	def CaptureVideo(self,wait=IS.DONT_WAIT):
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
	 	IS.DONT_WAIT	This function synchronizes the image acquisition				of the V-SYNC, but returns immediately.
		IS.WAIT		This function synchronizes the image acquisition
				of the V-SYNC and only then does return (i.e.
				waits until image acquisition begins)
		10<wait<32768	Wait time in 10 ms steps. A maximum of 327.68 
				seconds (this is approx. 5 minutes and 20 
				seconds) can be waited. For 1 < Wait < 10 Wait 
				becomes equal to 10.
		(Exp.: Wait = 100 => wait 1 sec.)
		"""
		r = CALL("CaptureVideo",self,INT(wait))
		return self.CheckForSuccessError(r)
		
	def SetColorMode(self,color_mode=IS.SET_CM_Y8):
		r = CALL("SetColorMode",self,INT(color_mode))
		return self.CheckForNoSuccessError(r)
	
	def SetSubSampling(self,mode=IS.SUBSAMPLING_DISABLE):
		r = CALL("SetSubSampling",self,INT(mode))
		return self.CheckForSuccessError(r)
		
	def StopLiveVideo(self,wait=IS.DONT_WAIT):
		"""
		The StopLiveVideo() function freezes the image in the VGA card 
		or in the PC's system memory. The function is controlled with 
		the parameter Wait. The function has two modes: Using the first
		mode, the function immediately returns to the calling function 
		and grabs the image in the background. In the second mode the 
		function waits until the image has been completely acquired and
		only then does the function return.
		By the use of IS.FORCE_VIDEO_STOP a single frame recording which
		is started with FreezeVideo(IS.DONT_WAIT) can be terminated
		immediately.
		"""
		r = CALL("StopLiveVideo",self,INT(wait))
		return self.CheckForSuccessError(r)
		
	def ExitCamera (self):
		r = CALL("ExitCamera",self)
		return self.CheckForSuccessError(r)
	

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
		r = CALL('WriteEEPROM',self,INT(offset),pcString,INT(count))
		return self.CheckForSuccessError(r)
