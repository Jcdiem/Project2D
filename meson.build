project('P2D', 'cpp')

SDL2 =  dependency('SDL2')
SDL2_image =  dependency('SDL2_image')
nlohmann_json =  include_directories('libs/json/include')
json = declare_dependency(include_directories: nlohmann_json)
mono = dependency('mono')

executable(
	'P2D',
	sources:[
		'src/JParser.cpp',
		'src/TextureHandler.cpp',
		'src/Canvas.cpp'
		'src/TextureMap.cpp',
		'src/Engine.cpp',
		'src/Main.cpp'
	],
	dependencies:[
		SDL2,
		SDL2_image,
		json,
		mono
	],
	link_args:[
		'-ldl',
		'-lpthread'
	]
)