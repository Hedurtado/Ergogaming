import tkinter as tk

mapping = {
    "INDEX1": "R",
    "INDEX2": "F",
    "INDEX3": "V",
    "MIDDLE1": "E",
    "MIDDLE2": "D",
    "MIDDLE3": "C",
    "RING1": "W",
    "RING2": "S",
    "RING3": "X",
    "PINKY1": "Q",
    "PINKY2": "A",
    "PINKY3": "Z",
    "THUMB": " "
}


class GuanteApp(tk.Tk):
    def __init__(self):
        super().__init__()

        # Configurar la ventana principal
        self.title("Configuración del guante")
        self.geometry("400x200")

        # Crear un botón para iniciar la configuración
        self.btn_configurar = tk.Button(self, text="Configurar", command=self.abrir_ventana_configuracion)
        self.btn_configurar.pack(pady=20)

        # Crear una etiqueta para mostrar el estado de la configuración
        self.lbl_estado = tk.Label(self, text="Esperando configuración")
        self.lbl_estado.pack()

        # Mostrar la ventana principal
        self.mainloop()

    def abrir_ventana_configuracion(self):
        # Crear una nueva ventana para la configuración
        ventana_configuracion = tk.Toplevel(self)
        ventana_configuracion.title("Asignar teclas a botones")
        ventana_configuracion.geometry("400x400")

        # Aquí iría el código para crear la interfaz de configuración de botones

        # Cuando se cierre la ventana de configuración, actualizar la etiqueta de estado
        ventana_configuracion.protocol("WM_DELETE_WINDOW", self.actualizar_estado_completo)

    def actualizar_estado_completo(self):
        self.lbl_estado.config(text="Configuración completa")


if __name__ == '__main__':
    GuanteApp()
