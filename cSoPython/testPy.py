import ctypes

test = ctypes.CDLL("lib.so") #or ../../../lib.so // path

test.main()
