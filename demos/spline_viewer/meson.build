project('spline_viewer', 'cpp')

sources = [
    'src/growable_float_buffer.cpp',
    'src/load_shader.cpp',
    'src/main.cpp',
    'src/primitive_renderer.cpp',
    'src/spline.cpp',
    'src/vec2.cpp',
]

include_dir = include_directories('inc')

dependencies = [
    dependency('gl'),
    dependency('glew'),
    dependency('glfw3')
]

executable(
    'spline_viewer', 
    sources, 
    dependencies : dependencies,
    include_directories : include_dir)
