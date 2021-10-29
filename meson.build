project('P2D', 'cpp', default_options:['cpp_std=gnu++2a']) #Use the most recent C++ standard aka 2a

sources = ['src/Engine.cpp',
           'src/Main.cpp',
           'src/utils/Flagger.cpp',
           'src/utils/Canvas.cpp',
           'src/utils/LuaProcessor.cpp',
           'src/utils/MicroLuaProcessor.cpp',
           'src/utils/entity/Manager.cpp',
           'src/utils/entity/Entity.cpp',
           'src/utils/entity/SpriteComponent.cpp',
           'src/utils/draw/Sprite.cpp',
           'src/utils/draw/atlas/Atlas.cpp',
           'src/utils/draw/atlas/AtlasMan.cpp'
]

dependencies = []
link_args = []

xorg = dependency('x11', required: false)
if xorg.found()
    dependencies += xorg
    add_project_arguments('-DX11', language: 'cpp')
endif

#Standard Deps
sfml = dependency('sfml-all')
dependencies += sfml
lua = dependency('luajit') #<----
dependencies += lua
#Replace 'lua' with whatever flavor you prefer, IE: luajit, lua/lua54, lua53, lua52, lua51 and so on,
#As long as sol2 supports it, it should work here.

#Meson Built-ins
thread = dependency('threads')
dependencies += thread

#Submodules
phd_sol2 = include_directories('libs/sol2/include')
sol2 = declare_dependency(include_directories: phd_sol2)
dependencies += sol2

executable(
	'P2D',
	sources: sources,
	dependencies: dependencies,
	link_args: link_args
)
