project('EasyRP', 'cpp',
  version : '2.1',
  default_options : ['warning_level=3'])

compiler = meson.get_compiler('cpp')

threads = dependency('threads')
if host_machine.system() == 'Windows'
    discordrpc = compiler.find_library('discord-rpc', dirs: meson.source_root())
else
    discordrpc = compiler.find_library('libdiscord-rpc', dirs: meson.source_root())
endif

rpc_inc = include_directories('discord-rpc/include')

exe = executable('easyrp', 'main.cpp', 'config.cpp', 'discord.cpp',
  include_directories : rpc_inc,
  dependencies : [threads, discordrpc],
  install : false)
  
test('basic', exe)
