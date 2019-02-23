project('strip_detector', 'cpp')

sources = [
    'src/main.cpp',
]

include_dir = include_directories('inc')

dependencies = [
    dependency('opencv4')
]

executable(
    'strip_detector', 
    sources, 
    dependencies : dependencies,
    include_directories : include_dir)
