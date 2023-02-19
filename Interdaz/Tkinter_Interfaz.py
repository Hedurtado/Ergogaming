import tkinter as tk


class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.crear_widgets()

    def crear_widgets(self):
        # Etiqueta para mostrar qué botón se está configurando
        self.lbl_boton = tk.Label(self)
        self.lbl_boton["text"] = "Configurando botón: "
        self.lbl_boton.pack(side="top")

        # Lista de botones del guante
        self.botones = []
        for i in range(13):
            btn = tk.Button(self, text="Botón " + str(i + 1), command=lambda i=i: self.configurar_boton(i))
            self.botones.append(btn)
            btn.pack(side="left")

    def configurar_boton(self, boton):
        # Actualizar la etiqueta para mostrar qué botón se está configurando
        self.lbl_boton["text"] = "Configurando botón: " + str(boton + 1)
        # Esperar a que el usuario presione una tecla del teclado
        self.master.bind("<Key>", lambda event: self.asignar_tecla(boton, event.keysym))

    def asignar_tecla(self, boton, tecla):
        # Asignar la tecla al botón correspondiente
        botones_guante[boton] = tecla
        # Actualizar la etiqueta para mostrar qué botón se ha configurado
        self.lbl_boton["text"] = "Tecla asignada al botón " + str(boton + 1) + ": " + tecla


# Inicializar la aplicación
root = tk.Tk()
app = Application(master=root)
app.mainloop()
