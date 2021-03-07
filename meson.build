project('El_Tercero', 'c', default_options : ['warning_level=3', 'c_std=c99', 'debug=false', 'buildtype=release'])

add_global_arguments(language : 'c')
c = meson.get_compiler('c')

#mainsource
srcs = ['src/etr.c', 'src/filecreation.c', 'src/language.c']

executable('etr', srcs, install : true, install_dir : '/usr/bin/')
