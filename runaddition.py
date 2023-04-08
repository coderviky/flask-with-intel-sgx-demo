import ctypes


def addition(a, b):
    # use ctypes to run sgx code

    # Load the shared object file
    myprogram = ctypes.CDLL('./app.so')

    # Define the types of the function parameters and return value
    myprogram.main.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_char_p))
    #myprogram.main.argtypes = (ctypes.c_int, ctypes.c_int)
    myprogram.main.restype = ctypes.c_int

    # Prepare the command-line arguments as a list of bytes strings
    arg1 = str(a).encode()
    arg2 = str(b).encode()

    argv = [b'app', arg1, arg2]

    # Call the main function with the arguments
    result = myprogram.main(len(argv), (ctypes.c_char_p * len(argv))(*argv))
    # result = myprogram.main(a, b)

    return result


# addition(2,3)