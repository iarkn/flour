project('flour', 'c',
  version: '0.1.0',
  default_options: [
    'c_std=c17',
    'warning_level=3',
  ],
)

incdir = include_directories('include')

deps = []
deps += dependency('ncursesw', required: true)
deps += dependency('zlib', required: true)

subdir('src')

executable('flour', 'src/main.c',
  dependencies: deps,
  link_with: flour_lib,
  include_directories: incdir,
)
