from cx_Freeze import setup, Executable

setup(name='Ergogaming Controller',
      version='0.1.5',
      description='Controlador para el tecaldo Ergogaming',
      executables=[Executable('Script.py')])
