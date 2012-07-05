import ctypes
BOOLEAN = ctypes.c_long          
BOOL = ctypes.c_long          
INT = ctypes.c_long          
UINT = ctypes.c_ulong         
LONG = ctypes.c_long          
LPVOID = ctypes.c_void_p            
ULONG = ctypes.c_ulong         
                           
UINT64 = ctypes.c_ulonglong         
__int64 = ctypes.c_longlong          
LONGLONG = ctypes.c_longlong          
DWORD = ctypes.c_ulong         
WORD = ctypes.c_uint         
                           
BYTE = ctypes.c_ubyte    
CHAR = ctypes.c_char             
TCHAR = ctypes.c_char             
UCHAR = ctypes.c_ubyte    
                           
LPTSTR = ctypes.c_char_p          
LPCTSTR = ctypes.c_char_p    
LPCSTR = ctypes.c_char_p    
WPARAM = ctypes.c_ulong         
LPARAM = ctypes.c_ulong         
LRESULT = ctypes.c_ulong         
HRESULT = ctypes.c_ulong         
                           
HWND = ctypes.c_void_p            
HGLOBAL = ctypes.c_void_p            
HINSTANCE = ctypes.c_void_p            
HDC = ctypes.c_void_p            
HMODULE = ctypes.c_void_p            
HKEY = ctypes.c_void_p            
HANDLE = ctypes.c_void_p            
                           
LPBYTE = ctypes.c_char_p            
PDWORD = ctypes.POINTER(ctypes.c_ulong)           
PVOID = ctypes.c_void_p            
PCHAR = ctypes.c_char_p            

c_char = ctypes.c_byte
c_char_p = ctypes.POINTER(ctypes.c_byte)
c_int_p = ctypes.POINTER(ctypes.c_int)
from ctypes import c_int
IS_CHAR = ctypes.c_byte 
HCAM = HANDLE
