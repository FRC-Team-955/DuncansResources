project('realsense_easy', 'cpp')

sources = [
    'src/bgrd_frame_source.cpp',
    'src/main.cpp',
    'src/realsense_bgrdfs.cpp',
]

include_dir = include_directories('inc')

dependencies = [
    dependency('opencv4'),
    dependency('realsense2')
]

executable(
    'realsense_easy', 
    sources, 
    dependencies : dependencies,
    include_directories : include_dir)
