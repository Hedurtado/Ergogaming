# Ergogaming
Esto es un clone de la mano de Azeron.

Este trabajo recompila multiples trabajos, por lo cual este proyecto no me lo puedo atribuir solo. No obstante, hay modificaciones realizados para mejorar ciertos aspectos del codigo.

En este proyecto usamos el arduino pro micro con la siguiente configuracion de pines

![image](https://user-images.githubusercontent.com/104462132/219963287-d3fe0b2e-c5e9-4534-94aa-99d0ed62d221.png)

Este es el esquema que utilizamos para la conexion de todos los pines

![image](https://user-images.githubusercontent.com/104462132/219963368-5138b287-b6d4-485e-9ae1-d781fab5bdd7.png)

# Codigo propio

Aqui nosotros con @daseg666, teniamos la idea de hacer la mano solamente con 13 botones, el ultimo boton seria para el dedo gordo, debido a que no encontrabamos el analog dpad para usar el codigo que ya habian compartido otras personas.

https://github.com/Hedurtado/Ergogaming/blob/master/Arduino/guante_optimazao.ino

En el codigo XboxControl.py intentamos usar la mano como un control para un mando de xbox, no obstante, no hemos probado aun si esto funciona.

Hay mas archivos subidos, pueden echarle un ojo y ver si les sirve o si pueden modificarlo. Estare muy feliz si me comentan lo que han podido hacer con esto.

# Modificaciones realizadas
 
 Usamos uno de los codigos proporcionados en las referencias y lo intentamos mejorar para el movimiento del joystick pueda leer los movimientos en diagonal.
 
https://github.com/Hedurtado/Ergogaming/blob/master/Arduino/guantes_joystick.ino


# Carpetas Interdaz, build y archivos Script.py, setup.py

El proposito de estas carpetas es para crear un software que nos permita modificar desde la computadora las teclas asignadas a cada boton de la mano. Por el momento solo tenemos el interfaz para una mano de 13 botones, como arriba ya se menciono.

Los archivos Script.py y setup.py son archivos para crear el archivo ejecutable de la interfaz, sin embargo, no hemos tenido la oportunidad de probarlo aun.

En la carpeta build esta el archivo ejecutable.

# Comentarios

Este proyecto lo empezamos para un trabajo de la universidad, no obstante, fue muy divertido el realizarlo, por lo tanto, planeamos seguir añadiendo mas cosas y mejorando el codigo en el futuro. Por el momento, queremos hacer que la interfaz tambien permita modificar las teclas asignadas al joystick.

Muchas gracias por su atencion y estaremos atentos a sus comentarios y forks.


# Referencias
https://github.com/Chris--A/Keypad 

https://github.com/AnonEngineering/Azeron-Clone-Controller 

https://www.instructables.com/Azeron-Game-Pad-DIY-Under-35/

https://sites.google.com/view/alvaro-rosati/azeron-keypad-diy-tutorial

https://www.thingiverse.com/thing:4682563

https://www.thingiverse.com/thing:4832101
