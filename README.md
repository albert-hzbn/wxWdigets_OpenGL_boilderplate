# wxWidgets OpenGL Boilerplate

This repository contains a simple boilerplate code for a C++ application that uses wxWidgets and OpenGL. The application demonstrates how to set up an OpenGL context using wxWidgets, render a triangle, and change its color.

## Prerequisites

To build and run the code, you'll need the following:

- A C++ compiler with support for C++11 or later
- wxWidgets library (>= 3.0)
- OpenGL library

## Building the Application

To build the application, follow these steps:

1. Install the required libraries and development headers for your platform. On Ubuntu, you can use the following command:

```
sudo apt-get install libwxgtk3.0-dev libglew-dev libglfw3-dev
```

2. Compile the main.cpp file:

```
g++ main.cpp `wx-config --libs gl,core,base` `wx-config --cxxflags` -lGLEW -lglfw -lGL -o myapp
```

3. Run the compiled application:

```
./my_app
```


## Application Features
The application displays a simple OpenGL canvas with a triangle. The color of the triangle can be changed by clicking the "Change Color" button. You can also create a new triangle by selecting "New Triangle" from the "File" menu.

## Code Overview

- `MyApp` class: The main application class derived from `wxApp`. It initializes the application and creates a `MyFrame` instance.

- `MyFrame` class: The main application window derived from `wxFrame`. It contains a menu bar with a "New Triangle" menu item, a "Change Color" button, and a `MyGLCanvas` instance.

- `MyGLCanvas` class: The custom OpenGL canvas derived from `wxGLCanvas`. It sets up an OpenGL context, initializes GLEW, and handles rendering the triangle and changing its color.
