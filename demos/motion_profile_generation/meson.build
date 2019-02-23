project('motion_generation', 'cpp')

sources = [
    'src/main.cpp',
    'src/spline.cpp',
    'src/spline_parametric.cpp',
    'src/tank_drive.cpp',
    'src/vec2.cpp',
]

include_dir = include_directories('inc')

dependencies = [
    dependency('gl'),
    dependency('glew'),
    dependency('glfw3')
]

executable(
    'motion_generation', 
    sources, 
    dependencies : dependencies,
    include_directories : include_dir)
