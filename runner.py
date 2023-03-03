import os
import sys

if(os.system('cmake -B ./build')==1):
    print("error cmake")
    sys.exit()

if(os.system('cmake --build build --target run') == 1):
    print("error building")
    sys.exit()

os.system('build\Debug\\run.exe')

