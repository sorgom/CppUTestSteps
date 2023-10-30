--  ============================================================
--  Makefile build rules for premake5
--  > tests.make->  bin/tests
--  ============================================================
workspace 'tests'
    configurations { 'ci' }
    language    'C++'
    objdir      'obj/%{prj.name}'

    includedirs {
        '../TestStepper/include'
    }

    buildoptions { '-std=c++98 -pedantic-errors' }

    project 'tests'
        kind        'ConsoleApp'
        targetdir   'bin'

        files { 
            '../TestStepper/src/*.cpp',
            '../samples/*.cpp'
        }

        defines { 'NDEBUG' }
        optimize 'On'
        links { 'CppUTest', 'CppUTestExt' }
