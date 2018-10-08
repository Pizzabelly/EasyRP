project('EasyRP', 'c',
  version : '4.0',
  default_options : ['warning_level=3', 'c_std=c99'])

compiler = meson.get_compiler('c')

src = ['parser.c', 'discord.c', 'main.c']

if host_machine.system() == 'windows'
  windows = import('windows')
  win_resources = windows.compile_resources('EasyRP.rc')
  src += [win_resources]
  discordrpc = compiler.find_library('discord-rpc', dirs: meson.source_root())
else
   discordrpc = compiler.find_library('libdiscord-rpc', dirs: meson.source_root())
endif

rpc_inc = include_directories('discord-rpc/include')

exe = executable('easyrp', src,
  include_directories : rpc_inc,
  dependencies : discordrpc,
  install : false)
  
test('basic', exe)
