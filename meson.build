project('EasyRP', 'cpp',
  version : '3.0',
  default_options : ['warning_level=3', 'cpp_std=c++14', 'b_ndebug=if-release'])

compiler = meson.get_compiler('cpp')

if host_machine.system() == 'windows'
  windows = import('windows')
  win_resources = windows.compile_resources('EasyRP.rc')
  discordrpc = compiler.find_library('discord-rpc', dirs: meson.source_root())
  src = ['main.cpp', 'config.cpp', 'discord.cpp', win_resources]
else
  discordrpc = compiler.find_library('libdiscord-rpc', dirs: meson.source_root())
  src = ['main.cpp', 'config.cpp', 'discord.cpp']
endif

rpc_inc = include_directories('discord-rpc/include')

exe = executable('easyrp', src,
  include_directories : rpc_inc,
  dependencies : [discordrpc],
  install : false)
  
test('basic', exe)
