
set(PATH_CLASS1 /home/danila/LABS_3SEM/3lab.2/Class_Table)
set(PATH_CLASS2 /home/danila/LABS_3SEM/3lab.2/Class_Table/cmake-build-debug)

find_path(CLASS_INCLUDE_DIR Table.h
        PATHS ${PATH_CLASS1})

find_library(CLASS_LIBRARY
        NAMES 3lab.2
        PATHS ${PATH_CLASS2})