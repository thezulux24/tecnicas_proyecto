# 🕹️ Battle of Codes

**Battle of Codes** es un videojuego de consola inspirado en *Slay the Spire*, desarrollado en lenguaje C. El jugador avanza a través de niveles con distintos tipos de eventos: combates, descansos y tiendas, construyendo su mazo de cartas para derrotar enemigos y completar el juego.

---

## 🎮 Características

- Jugabilidad basada en cartas con estadísticas (Ataque, Defensa, Vida, Energía).
- Mecánica de turnos con energía limitada por ronda.
- Elección de nuevas cartas al finalizar combates.
- Eventos especiales: descanso y tienda.
- Sistema de niveles progresivo hasta el nivel 10.
- Múltiples dificultades de juego.

---

## 📁 Estructura del Proyecto

```bash
.
├── Models/               # Definición de estructuras y lógica de juego
├── Text/                 # Archivos .txt con niveles según dificultad
├── main.c                # Archivo principal del juego
├── CMakeLists.txt        # Configuración de compilación con CMake
└── README.md             # Documentación del proyecto
```

---

## ⚙️ Compilación y Ejecución

1. Asegúrate de tener instalado un compilador de C (como `gcc`) y `cmake`.

2. Compila el proyecto:

```bash
cmake .
make
```

3. Ejecuta el juego:

```bash
./tecnicas_proyecto
```

---

## 🧠 Cómo Jugar

1. Ingresa tu nombre.
2. Selecciona la dificultad (1: fácil, 2: medio, 3: difícil).
3. En combate:
   - Usa tus cartas sabiamente: cada una consume energía.
   - Derrota al enemigo antes de que tu vida llegue a cero.
4. Tras cada victoria:
   - Elige una de tres cartas nuevas para mejorar tu mazo.
5. Avanza niveles hasta alcanzar el nivel 10... ¡y gana el juego!

---

## 🛠️ Créditos

Desarrollado por Brayan Zuluaga  
Proyecto final del curso **Técnicas de Programación**  
2025

---

## 📌 Notas

- Los niveles se leen desde archivos `.txt` ubicados en la carpeta `Text/`.
- El proyecto usa estructuras como listas enlazadas y pilas implementadas manualmente.
- Algunas decisiones del juego (como ataques enemigos o recompensas) usan números aleatorios.

---

¿Listo para dominar el código y convertirte en el campeón de *Battle of Codes*? 💻⚔️
