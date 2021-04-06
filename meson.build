project('P2D', 'cpp', default_options:['cpp_std=gnu++2a'])

#Standard Deps
sfml = dependency('sfml-all')
lua = dependency('luajit')
#Replace 'lua' with whatever flavor you prefer, IE: luajit, lua, lua53, lua52, lua51 and so on,
#As long as sol2 supports it, it should work here.

#Meson Built-ins
thread = dependency('threads')

#Submodules
nlohmann_json = include_directories('libs/json/include')
json = declare_dependency(include_directories: nlohmann_json)

phd_sol2 = include_directories('libs/sol2/include')
sol2 = declare_dependency(include_directories: phd_sol2)


executable(
	'P2D',
	sources:[
		'src/Engine.cpp',
		'src/Main.cpp'
	],
	dependencies:[
	    sfml,
		json,
		lua,
		sol2,
		thread
	],
	link_args:[
	]
)