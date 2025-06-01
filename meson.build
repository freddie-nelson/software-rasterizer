project('software-rasterizer', 'cpp', default_options: ['cpp_std=c++20'])

incdir = include_directories('include')
sdl3_dep = dependency('sdl3', version: '>=3.0.0', required: true)

executable('build', 'main.cpp', include_directories: incdir, dependencies: [sdl3_dep])