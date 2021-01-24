#pragma once
#include <stdint.h>
#include "prototype.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "prototype.h"

#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include <string>
class Simulation;

class Graph
{
public:
    Graph();
    int grafica(Simulation& mysim);
    void printBlobs(Simulation& mysim);
    void Sound(void);
    bool get_info(void);
    bool getClose(void);
    int getModo(void);
    int getBlobNum(void);
    int getFoodCount(void);
    float getMaxSpeed(void);
    float getVelp(void);
    float getDead(int type);
    float getSmellRadius(void);
    float getRJL(void);

private:
    int inicializa(void);
    int seteo(ALLEGRO_DISPLAY* display);
    int carga_bitmaps(void);
    void VentanaPrincipal(void);
    void Pregunta(char* texto_ingresado);
    void cleaner(ALLEGRO_DISPLAY* ventana_a_borrar);
    void clean(ALLEGRO_DISPLAY* ventana_a_borrar);
    bool Ventanainicio(void);
    ALLEGRO_DISPLAY* display_principal;
    ALLEGRO_DISPLAY* display_entrada;
    ALLEGRO_SAMPLE* select_sample;
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* babyBlob;
    ALLEGRO_BITMAP* food;
    ALLEGRO_BITMAP* grownBlob;
    ALLEGRO_BITMAP* goodOldBlob;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT ev;
    bool close_display;
    bool show_demo_window;
    bool cerrar;
    bool close_window;
    bool show_another_window;
    bool running;
    bool running_inicio;
    float Death[3];
    float velp;
    float smellRadius;
    float randomJiggleLimit;
    float Vel_max;
    int foodCount;
    int modo;
    int cant_inicial_blobs;
};

