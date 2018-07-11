project('EasyRP', 'cpp',
  version : '0.3',
  default_options : ['warning_level=3'])

threads_dep = dependency('threads')
rpc_inc = include_directories('discord-rpc/include')
if build_machine.system() == 'Windows'
    rpc_dep = meson.get_compiler('cpp').find_library('discord-rpc', dirs: meson.current_source_dir())
else
    rpc_dep = meson.get_compiler('cpp').find_library('libdiscord-rpc', dirs: meson.current_source_dir())
endif

exe = executable('easyrp', 'main.cpp', 'config.cpp', 'discord.cpp',
  include_directories : rpc_inc,
  dependencies : [threads_dep, rpc_dep],
  install : false)
  
test('basic', exe)
