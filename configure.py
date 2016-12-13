#!/bin/env python3
from PyQt5.QtCore import PYQT_CONFIGURATION as pyqt_config
from distutils import sysconfig
import os, sipconfig, sys
import site
class HostPythonConfiguration(object):
    def __init__(self):
        self.platform=sys.platform
        self.version=sys.hexversion>>8

        self.inc_dir=sysconfig.get_python_inc()
        self.venv_inc_dir=sysconfig.get_python_inc(prefix=sys.prefix)
        self.module_dir=sysconfig.get_python_lib(plat_specific=1)

        if sys.platform=='win32':
            self.data_dir=sys.prefix
            self.lib_dir=sys.prefix+'\\libs'
        else:
            self.data_dir=sys.prefix+'/share'
            self.lib_dir=sys.prefix+'/lib'

class TargetQtConfiguration(object):
    def __init__(self, qmake):
        pipe=os.popen(' '.join([qmake, '-query']))

        for l in pipe:
            l=l.strip()

            tokens=l.split(':', 1)
            if isinstance(tokens, list):
                if len(tokens) != 2:
                    error("Unexpected output from qmake: '%s'\n" % l)

                name,value=tokens
            else:
                name=tokens
                value=None

            name=name.replace('/', '_')
            setattr(self, name, value)

        pipe.close()        

if __name__=="__main__":
    from argparse import ArgumentParser

    parser=ArgumentParser(description="Configure QOnScreenKeyboard library.")
    parser.add_argument(
        '-q', '--qmake',
        dest="qmake",
        type=str,
        default="qmake",
        help="Path to qmake executable"
    )
    parser.add_argument(
        '-s', '--sip-extras',
        dest="sip_extras",
        type=str,
        default="",
        help="Extra arguments to sip"
    )
    parser.add_argument(
        '--lib-path',
        dest="lib_path",
        type=str,
        default="",
        help="Add path to the built QOnScreenKeyboard library. This will disable building it",
    )
    args=parser.parse_args()
    if not args.lib_path:
        qmake_exe=args.qmake
        if not qmake_exe.endswith('qmake'):
            qmake_exe=os.path.join(qmake_exe,'qmake')

        if os.system(' '.join([qmake_exe, '-v']))!=0:
        
            if sys.platform=='win32':
                print("Make sure you have a working Qt qmake on your PATH.")
            else:
                print(
                    "Use the --qmake argument to explicitly specify a "
                    "working Qt qmake."
                )
            exit(1)

    sip_args=args.sip_extras
    rundir=os.path.dirname(sys.argv[0])
    if not rundir:
        rundir="."
    pyconfig=HostPythonConfiguration()
    py_sip_dir=os.path.join(pyconfig.data_dir, 'sip', 'PyQt5')
    sip_inc_dir=pyconfig.venv_inc_dir

    qtconfig=TargetQtConfiguration(qmake_exe)

    inc_dir=os.path.abspath(os.path.join(rundir,"src"))
    if not args.lib_path:
        lib_dir=inc_dir
    else:
        lib_dir=args.lib_path
    dest_pkg_dir=site.getsitepackages()[0] + "/PyQOnScreenKeyboard"

    sip_files_dir = os.path.abspath(os.path.join(rundir,"sip"))
    output_dir = os.path.abspath(os.path.join(".", "modules"))
    build_file = "PyQOnScreenKeyboard.sbf"
    build_path = os.path.join(output_dir, build_file)
      
    if not os.path.exists(output_dir): os.mkdir(output_dir)
    sip_file = os.path.join(sip_files_dir, "PyQOnScreenKeyboard.sip")

    config=sipconfig.Configuration()    
    config.default_mod_dir=( "/usr/local/lib/python%i.%i/dist-packages" %
                               ( sys.version_info.major, sys.version_info.minor ) )

    cmd=" ".join([
        config.sip_bin,
        pyqt_config['sip_flags'],
        sip_args,
        '-I', sip_files_dir,
        '-I', py_sip_dir,
        '-I', config.sip_inc_dir,
        '-I', inc_dir,
        "-c", output_dir,
        "-b", build_path,
        "-w",
        "-o",
        sip_file,
    ])

    print(cmd)
    if os.system(cmd)!=0: sys.exit(1)

    makefile=sipconfig.SIPModuleMakefile(
        config,
        build_file,
        dir=output_dir,
        install_dir=dest_pkg_dir
    )

    makefile.extra_defines+=['MYQONSCREENKEYBOARD_LIBRARY','QT_CORE_LIB', 'QT_GUI_LIB', 'QT_WIDGETS_LIB']
    makefile.extra_include_dirs+=[os.path.abspath(inc_dir), qtconfig.QT_INSTALL_HEADERS]
    makefile.extra_lib_dirs+=[qtconfig.QT_INSTALL_LIBS, os.path.join(rundir,'src')]
    makefile.extra_libs+=['QOnScreenKeyboard']

    if sys.platform=='linux':
        makefile.extra_cxxflags+=['-F'+qtconfig.QT_INSTALL_LIBS]        
        makefile.extra_include_dirs+=[
            os.path.join(qtconfig.QT_INSTALL_HEADERS,'QtCore'),
            os.path.join(qtconfig.QT_INSTALL_HEADERS,'QtGui'),
            os.path.join(qtconfig.QT_INSTALL_HEADERS,'QtWidgets'),
        ]

        makefile.extra_lflags+=[      
            '-L'+qtconfig.QT_INSTALL_ARCHDATA,
            '-lQt5Widgets',
            '-lQt5Core',
        ]

    elif sys.platform=='win32':
        makefile.extra_include_dirs+=[
            os.path.join(qtconfig.QT_INSTALL_HEADERS, "QtCore"),
            os.path.join(qtconfig.QT_INSTALL_HEADERS,'QtGui'),
            os.path.join(qtconfig.QT_INSTALL_HEADERS, "QtWidgets"),
        ]
        makefile.extra_lib_dirs+=[os.path.join(rundir,'src','release')]
        makefile.extra_libs+=['Qt5Core','Qt5Gui','Qt5Widgets']
    
    makefile.generate()
    if not args.lib_path:
        sipconfig.ParentMakefile(
            configuration = config,
            subdirs = ["src", output_dir],
        ).generate()

        os.chdir("src")    
        qmake_cmd=qmake_exe
        if sys.platform=="win32": qmake_cmd+=" -spec win32-msvc2010"
        os.system(qmake_cmd)
    else:
        sipconfig.ParentMakefile(
            configuration = config,
            subdirs = [output_dir],
        ).generate()
    sys.exit()
