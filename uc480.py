__all__ = [ ]

import os
import sys
import textwrap
import numpy as np
from numpy import ctypeslib
import ctypes
from uc480_types import *
import ctypes.util
import warnings
import symbols as sym

from uc480_h import *

SUCCESS = 0
NO_SUCCESS = -1

#class CAMINFO(ctypes.Structure):
#	_fields_ = [("SerNo[12]    ",ctypes.c_char*12),  # (11 char)   
#	            ("ID[20]       ",ctypes.c_char*20),  # e.g. "Company Name"      
#	            ("Version[10]  ",ctypes.c_char*10),  # e.g. "V1.00"  (9 char)      
#	            ("Date[12]     ",ctypes.c_char*12),  # e.g "11.03.2004" (11 char)      
#	            ("Select       ",ctypes.c_byte	 ),  # 0 (contains camera select number for multi camera support)
#	            ("Type         ",ctypes.c_byte	 ),  # 1 (contains camera type)
#	            ("Reserved[8]  ",ctypes.c_char*8 )]  # (7 char)    
##} CAMINFO, *PCAMINFO;
#PCAMINFO = ctypes.POINTER(CAMINFO)
#
#class SENSORINFO(ctypes.Structure):
#	_fields_ = [("SensorID        " , WORD   ),  # e.g. IS_SENSOR_C0640R13M
#                ("strSensorName	  " , IS_CHAR),  # e.g. "C0640R13M"  	
#                ("nColorMode      " , c_char ),  # e.g. IS_COLORMODE_BAYER  
#                ("nMaxWidth       " , DWORD  ),  # e.g. 1280  
#                ("nMaxHeight      " , DWORD  ),  # e.g. 1024  
#                ("bMasterGain     " , BOOL   ),  # e.g. FALSE  
#                ("bRGain          " , BOOL   ),  # e.g. TRUE  
#                ("bGGain          " , BOOL   ),  # e.g. TRUE  
#                ("bBGain          " , BOOL   ),  # e.g. TRUE  
#                ("bGlobShutter    " , BOOL   ),  # e.g. TRUE  
#                ("Reserved[16]    " , c_char*8)]  #  not used 				
##typedef struct _SENSORINFO{
##} SENSORINFO, *PSENSORINFO;
#PSENSORINFO = ctypes.POINTER(SENSORINFO)
#
#class REVISIONINFO(ctypes.Structure):
##{
#	_fields_ = [("size            ", WORD  ),       # 2
#				("Sensor          ", WORD  ),       # 2
#				("Cypress         ", WORD  ),       # 2
#				("Blackfin        ", DWORD ),       # 4
#				("DspFirmware     ", WORD  ),       # 2
#				("USB_Board       ", WORD  ),       # 2
#				("Sensor_Board    ", WORD  ),       # 2
#				("Processing_Board", WORD  ),       # 2
#				("Memory_Board    ", WORD  ),       # 2
#				("Housing         ", WORD  ),       # 2
#				("Filter          ", WORD  ),       # 2
#				("Timing_Board    ", WORD  ),       # 2
#				("Product         ", WORD  ),       # 2
#				("reserved[100]   ", BYTE*100  )]       # --128
##} REVISIONINFO, *PREVISIONINFO;
#PREVISIONINFO = ctypes.POINTER(REVISIONINFO)
#
#class UC480_CAMERA_INFO(ctypes.Structure):
#	_fields_ = [("dwCameraID   	",DWORD  ),	# this is the user defineable camera ID
#				("dwDeviceID   	",DWORD  ),	# this is the systems enumeration ID
#				("dwSensorID   	",DWORD  ),	# this is the sensor ID e.g. IS_SENSOR_C0640R13M
#				("dwInUse      	",DWORD  ),	# flag, whether the camera is in use or not
#				("SerNo[16]    	",IS_CHAR*16),	# serial numer of the camera
#				("Model[16]    	",IS_CHAR*16),	# model name of the camera
#				("dwReserved[16]",DWORD  *16)] #
##}UC480_CAMERA_INFO, *PUC480_CAMERA_INFO;
#PUC480_CAMERA_INFO = ctypes.POINTER(UC480_CAMERA_INFO)

if os.name=='nt':
	libname = 'uc480'
	include_uc480_h = os.environ['PROGRAMFILES']+'\\Thorlabs DCU camera\\Develop\\Include\\uc480.h'
if os.name=='posix':
	libname = 'ueye_api'
	include_uc480_h = "/usr/include/ueye.h"
    # UNTESTED: Please report results to http://code.google.com/p/pylibuc480/issues
lib = ctypes.util.find_library(libname)
if lib is None:
	print 'uc480.dll not found'

		
libuc480 = ctypes.cdll.LoadLibrary(lib)
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
			# elif name.startswith('DAQmxError') or name.startswith('DAQmxWarning'):
				# assert value[0]=='(' and value[-1]==')', `name, value`
				# value = int(value[1:-1])
				# error_map[value] = name[10:]
			# elif name.startswith('DAQmx_Val') or name[5:] in ['Success','_ReadWaitMode']:
				# d[name] = eval(value)
				# l.append('%s = %s' % (name, value))
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
		#d = uc480_h.__dict__
	
#	for name, value in d.items():
#		if name.startswith ('_'): continue
#		exec '%s = %r' % (name, value)


# def CHK(return_code, funcname, *args):
    # """
    # Return ``return_code`` while handle any warnings and errors from
    # calling a libuc480 function ``funcname`` with arguments
    # ``args``.
    # """
    # if return_code==0: # call was succesful
        # pass
    # else:
        # buf_size = default_buf_size
        # while buf_size < 1000000:
            # buf = ctypes.create_string_buffer('\000' * buf_size)
            # try:
                # r = libuc480.DAQmxGetErrorString(return_code, ctypes.byref(buf), buf_size)
            # except RuntimeError, msg:
                # if 'Buffer is too small to fit the string' in str(msg):
                    # buf_size *= 2
                # else:
                    # raise
            # else:
                # break
        # if r:
            # if return_code < 0:
                # raise RuntimeError('%s%s failed with error %s=%d: %s'%\
                                       # (funcname, args, error_map[return_code], return_code, repr(buf.value)))
            # else:
                # warning = error_map.get(return_code, return_code)
                # sys.stderr.write('%s%s warning: %s\n' % (funcname, args, warning))                
        # else:
            # text = '\n  '.join(['']+textwrap.wrap(buf.value, 80)+['-'*10])
            # if return_code < 0:
                # raise RuntimeError('%s%s:%s' % (funcname,args, text))
            # else:
                # sys.stderr.write('%s%s warning:%s\n' % (funcname, args, text))
    # return return_code

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
	r = func(*new_args) 
	if r is NO_SUCCESS:
		raise
	return r
		
class camera(HCAM):
	def __init__(self,camera_id=0):
		#self.id = camera_id
		HCAM.__init__(self,0)
		r = CALL('InitCamera',ctypes.byref(self),HWND(0))
		if r is not SUCCESS:
			sys.stderr.write(sym.ERROR_CODE[r])
			raise
		self.width = 1024
		self.height = 768		
		self.data = np.zeros((self.height,self.width),dtype=np.int8)
		return None

	def AddToSequence(self):# not done
		return CALL('AddToSequence', ) 
		
		
	def SaveImage(self,file):
		return CALL('SaveImage',self,None)
		
	def AllocImageMem(self,width=1024,height=768,bitpixel=8):
		self.image = c_char_p()
		self.id = c_int()
		CALL('AllocImageMem',self,c_int(width),c_int(height),c_int(bitpixel),ctypes.byref(self.image),ctypes.byref(self.id))
	
	def FreeImageMem (self):
		CALL("FreeImageMem",self,self.image,self.id)
		
	def FreezeVideo(self,wait=IS_WAIT):
		CALL("FreezeVideo",self,INT(wait))
		
	def CopyImageMem(self):
		r = CALL("CopyImageMem",self,self.image,self.id,self.data.ctypes.data)
		if r == -1:
			self.GetError()
			sys.stderr.write(self.err)
			sys.stderr.write(self.errMessage.value)
		return 

	def GetError(self):
		self.err = ctypes.c_int()
		self.errMessage = ctypes.c_char_p()
		return CALL("GetError",self,ctypes.byref(self.err),ctypes.byref(self.errMessage))
		
	def SetImageMem (self):
		return CALL("SetImageMem",self,self.image,self.id)
		
	def SetImageSize(self,x=IS_GET_IMAGE_SIZE_X_MAX,y=IS_GET_IMAGE_SIZE_X_MAX):
		return CALL("SetImageSize",self,c_int(x),c_int(y))
		
	def SetImagePos(self,x=0,y=0):
		return CALL("SetImagePos",self,c_int(x),c_int(y))
		
	def CaptureVideo(self,wait=IS_DONT_WAIT):
		return CALL("CaptureVideo",self,c_int(wait))
		
	def SetColorMode(self,color_mode=IS_SET_CM_Y8):
		return CALL("SetColorMode",self,c_int(color_mode))
	
	def SetSubSampling(self,mode=IS_SUBSAMPLING_DISABLE):
		return CALL("SetSubSampling",self,c_int(mode))
		
	def StopLiveVideo(self,wait=IS_WAIT):
		return CALL("StopLiveVideo",self,c_int(wait))
		
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
		buffer = ctypes.create_string_buffer(count)
		r = CALL('ReadEEPROM',self,INT(offset),buffer,INT(count))
		if r is not SUCCESS:
			raise
		return buffer.value

	def WriteEEPROM(self, content, offset = 0):
		"""	
		In the DCU camera there is a rewritable EEPROM, where 64 bytes 
		of information can be written. With the ReadEEPROM() function
		the contents of this 64 byte block can be read.
		"""
		count = len(content)
		if count + offset > 64:
			sys.stderr.write("Content to long.")
			raise
		pcString = ctypes.c_char_p(content)
		r = CALL('WriteEEPROM',self,INT(offset),pcString,INT(count))
		if r is not SUCCESS:
			raise
		return r
