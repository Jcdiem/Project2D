project('P2D', 'cpp')

SDL2 =  dependency('SDL2')
SDL2_image =  dependency('SDL2_image')
nlohmann_json =  include_directories('libs/json/include')
json = declare_dependency(include_directories: nlohmann_json)
chai = dependency('chaiscript')
thread = dependency('threads')

executable(
	'P2D',
	sources:[
		'src/JParser.cpp',
		'src/TextureHandler.cpp',
		'src/Canvas_LayerData.cpp',
		'src/Canvas.cpp',
		'src/Engine.cpp',
		'src/Main.cpp'
	],
	dependencies:[
		SDL2,
		SDL2_image,
		json,
		chai,
		thread
	],
	link_args:[
		'-ldl'
	]
)
