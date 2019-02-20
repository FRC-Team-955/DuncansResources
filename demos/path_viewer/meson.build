project('path_viewer', 'cpp')

sources = [
    'src/spline.cpp',
    'src/growable_float_buffer.cpp',
    'src/spline_parametric.cpp',
    'src/tank_drive.cpp',
    'src/load_shader.cpp',
    'src/main.cpp',
    'src/vec2.cpp',
    'src/primitive_renderer.cpp'
]

include_dir = include_directories('inc')

dependencies = [
    dependency('gl'),
    dependency('glew'),
    dependency('glfw3')
]

executable(
    'path_animation', 
    sources, 
    dependencies : dependencies,
    include_directories : include_dir)
