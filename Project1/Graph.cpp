#include "Graph.h"
#include "simulation.h"

//Constructor
Graph::Graph() {
    Death[0] = PROBABILIDAD_MUERTE_BABY;
    Death[1] = PROBABILIDAD_MUERTE_GROWN;
    Death[2] = PROBABILIDAD_MUERTE_OLD;
    velp = PORCENTAJE_INICIAL_VEL;
    smellRadius = SMELLRADIUS_INICIAL;
    foodCount = FOOD_COUNT_INICIAL;
    randomJiggleLimit = DIR_INICIAL;
    Vel_max = INIC_VEL;
    cant_inicial_blobs = INIC_BLOBS;
    display_principal = NULL;
    queue = NULL;
    close_display = false;
    show_demo_window = false;
    show_another_window = false;
    running = true;
    running_inicio = true;
    cerrar = false;
    close_window = false;
}


bool Graph::get_info(void)
{
    // Setup Allegro
    if (inicializa())
    {
        printf("Error de inicializacion \n");
        return -1;
    }

    // Crea el display
    display_entrada = al_create_display(TAMANIO_PANTALLA_X_ENTRADA, TAMANIO_PANTALLA_Y_ENTRADA);
    if (!display_entrada)
    {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    al_set_window_title(display_entrada, "Inputs de datos");
    al_set_new_display_flags(ALLEGRO_RESIZABLE);


    //crea cola de eventos y conecta al display entrada con la gui
    if (seteo(display_entrada) == - 1)
    {
        return -1;
    }

    //siempre que no se haya tocado x
    while (running_inicio)
    {
        while (al_get_next_event(queue, &ev))
        {
            ImGui_ImplAllegro5_ProcessEvent(&ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                running_inicio = false;
                cerrar = true;
            }
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display_entrada);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
        }
        // Start the Dear ImGui frame
        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        //Esta funcion se encarga de generar la parte de los botones de la gui
        if (Ventanainicio())
            running_inicio = false;

        // Rendering de imgui
        ImGui::Render();
        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

        //Mostramos en pantalla
        al_flip_display();
    }
    //liberamos memoria utilizada
    cleaner(display_entrada); 
    return cerrar;
}

// Primera funcion a llamar antes de empezar a usar allegro .
int Graph::inicializa(void)
{
    if (!al_init())
    {
        fprintf(stderr, " failed to initialize allegro !\n");
        return -1;
    }
    if (!al_install_mouse())
    {
        fprintf(stderr, " failed to initialize the mouse !\n");
        return -1;
    }
    if (!al_install_keyboard())
    {
        fprintf(stderr, " failed to initialize the keyboard !\n");
        return -1;
    }
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, " failed to initialize the primitives !\n");
        return -1;
    }
    if (!al_init_image_addon()) {

        fprintf(stderr, " failed to initialize the imageaddon !\n");
        return -1;
    }
    if (!al_init_acodec_addon()) {

        fprintf(stderr, " failed to initialize the imageaddon !\n");
        return -1;
    }
    // incializa el audio en allegro
    if (!al_install_audio())
    {
        fprintf(stderr, "Could not init sound!\n");
        return 1;
    }
    al_reserve_samples(1);
    select_sample = al_load_sample("blob_merge.wav");
    return 0;
}


int Graph::seteo(ALLEGRO_DISPLAY* display)
{
    //cola de eventos
    queue = al_create_event_queue();

    // Controla que la cola de eventos se haya generado
    if (!queue)
    {
        fprintf(stderr, " failed to create event_queue !\n");
        al_destroy_display(display);
        return -1;
    }

    //le indico al queue que eventos importan
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplAllegro5_Init(display);

    return 0;
}


int Graph::grafica(Simulation& mysim)
{
    // Intenta crear display 
    display_principal = al_create_display(TAMANIO_PANTALLA_X, TAMANIO_PANTALLA_Y);
    //al_set_window_position(display_principal, 0, 0);
    if (!display_principal)
    {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    al_set_window_title(display_principal, "Simulacion Blobeana"); 
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    //creo los bitmap
    if (carga_bitmaps()==-1)
    {
        return -1;
    }
    
    seteo(display_principal);

    // Main loop
    while (running)
    {
        while (al_get_next_event(queue, &ev))
        {
            ImGui_ImplAllegro5_ProcessEvent(&ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                running = false;
                close_window = true;
            }
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display_principal);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
        }


        // Start the Dear ImGui frame
        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        //Esta funcion se encarga de generar la parte de los botones de la gui
        VentanaPrincipal();

        // Rendering
        ImGui::Render();
        
       // mysim.tick++;
        //mysim.getData(*(this));                           
        //mysim.gameLoop();
        mysim.Simulate(*(this));
        if (mysim.sound == MUST_SOUND)
        {
            Graph::Sound();
        }
        Graph::printBlobs(mysim);     //funcion que dibuja blobs,back y comida

        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
        al_flip_display();
    }

    // Clean se encarga de limpiar osea de borrar todos los objetos creados por allegro.
    clean(display_principal);
    return 0;
}


void Graph::Sound(void)
{
    al_play_sample(select_sample, 15, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}


int Graph::carga_bitmaps()
{
    background = al_load_bitmap("background.jpg");
    if (!background) {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    babyBlob = al_load_bitmap("babyblob.png");
    if (!babyBlob) {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    goodOldBlob = al_load_bitmap("goodoldblob.png");
    if (!goodOldBlob) {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    grownBlob = al_load_bitmap("grownblob.png");
    if (!grownBlob) {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
    food = al_load_bitmap("food.png");
    if (!food) {
        fprintf(stderr, " failed to create display !\n");
        return -1;
    }
}


void Graph::printBlobs(Simulation& mysim) {    



    al_draw_scaled_bitmap(background, 0.0f, 0.0f, al_get_bitmap_width(background), al_get_bitmap_height(background), BACKG_X, BACKG_Y, TAMANIO_PANTALLA_X, TAMANIO_PANTALLA_Y , 0);

    int i;

    double posX, posY;



    for (i = 0; i < mysim.blobNum; i++) {

        posX = mysim.blobPtr[i]->getX();
        posY = mysim.blobPtr[i]->getY() +BACKG_Y;
        posX > TAMANIO_PANTALLA_X ? posX = 0.0f : posX = posX;
        posX < 0 ? posX = TAMANIO_PANTALLA_X : posX = posX;

        posY > TAMANIO_PANTALLA_Y ? posY = BACKG_Y : posY = posY;
        posY < 250.0f ? posY = TAMANIO_PANTALLA_Y : posY = posY;



        switch (mysim.blobPtr[i]->getGroup()) {

        case BABYGROUP: al_draw_bitmap(babyBlob, posX, posY, 0);
            if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(babyBlob)) && posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(babyBlob))) {

                al_draw_bitmap_region(babyBlob, (TAMANIO_PANTALLA_X - posX), (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(babyBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(babyBlob) - (TAMANIO_PANTALLA_Y - posY), 0.0f,BACKG_Y, 0);

            }
            else if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(babyBlob))) {

                al_draw_bitmap_region(babyBlob, (TAMANIO_PANTALLA_X - posX), 0.0f, al_get_bitmap_width(babyBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(babyBlob), 0.0f, posY, 0);

            }
            else if (posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(babyBlob))) {

                al_draw_bitmap_region(babyBlob, 0.0f, (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(babyBlob), al_get_bitmap_height(babyBlob) - (TAMANIO_PANTALLA_Y - posY), posX, BACKG_Y, 0);

            }
            break;

        case GROWNGROUP:al_draw_bitmap(grownBlob, posX, posY, 0);
            if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(grownBlob)) && posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(grownBlob))) {


                al_draw_bitmap_region(grownBlob, (TAMANIO_PANTALLA_X - posX), (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(grownBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(grownBlob) - (TAMANIO_PANTALLA_Y - posY), 0.0f, BACKG_Y, 0);


            }
            else if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(grownBlob))) {

                al_draw_bitmap_region(grownBlob, (TAMANIO_PANTALLA_X - posX), 0.0f, al_get_bitmap_width(grownBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(grownBlob), 0.0f, posY, 0);

            }
            else if (posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(grownBlob))) {

                al_draw_bitmap_region(grownBlob, 0.0f, (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(grownBlob), al_get_bitmap_height(grownBlob) - (TAMANIO_PANTALLA_Y - posY), posX, BACKG_Y, 0);

            }
            break;

        case GOODOLDGROUP:al_draw_bitmap(goodOldBlob, posX, posY, 0);
            if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(goodOldBlob)) && posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, (TAMANIO_PANTALLA_X - posX), (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(goodOldBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(goodOldBlob) - (TAMANIO_PANTALLA_Y - posY), 0.0f, BACKG_Y, 0);

            }
            else if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, (TAMANIO_PANTALLA_X - posX), 0.0f, al_get_bitmap_width(goodOldBlob) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(goodOldBlob), 0.0f, posY, 0);

            }
            else if (posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, 0.0f, (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(goodOldBlob), al_get_bitmap_height(goodOldBlob) - (TAMANIO_PANTALLA_Y - posY), posX, BACKG_Y, 0);

            }
            break;

        }





    }
    for (i = 0; i < mysim.foodNum; i++)
    {
        posX = mysim.foodPtr[i]->getFoodPosX();
        posY = mysim.foodPtr[i]->getFoodPosY()+BACKG_Y;
       
        al_draw_bitmap(food, posX, posY, 0);
        if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(food)) && posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(food))) {

            al_draw_bitmap_region(food,(TAMANIO_PANTALLA_X - posX), (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(food) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(food) - (TAMANIO_PANTALLA_Y - posY), 0.0f, BACKG_Y, 0);

        }
        else if (posX > (TAMANIO_PANTALLA_X - al_get_bitmap_width(food))) {

            al_draw_bitmap_region((food), (TAMANIO_PANTALLA_X - posX), 0.0f, al_get_bitmap_width(food) - (TAMANIO_PANTALLA_X - posX), al_get_bitmap_height(food), 0.0f, posY, 0);

        }
        else if (posY > (TAMANIO_PANTALLA_Y - al_get_bitmap_height(food))) {

            al_draw_bitmap_region(food, 0.0f, (TAMANIO_PANTALLA_Y - posY), al_get_bitmap_width(food), al_get_bitmap_height(food) - (TAMANIO_PANTALLA_Y - posY), posX, 250.0f, 0);

        }
        
    }
    
}


void Graph::cleaner(ALLEGRO_DISPLAY* ventana_a_borrar)
{
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(ventana_a_borrar);
}


void Graph::clean(ALLEGRO_DISPLAY* ventana_a_borrar)
{
    al_destroy_bitmap(background);
    al_destroy_bitmap(babyBlob);
    al_destroy_bitmap(grownBlob);
    al_destroy_bitmap(goodOldBlob);
    al_destroy_bitmap(food);
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_display(ventana_a_borrar);
    al_shutdown_image_addon();
}


//La idea es crear el simbolo ? que aparece al costado de los widgets para seleccion
void Graph::Pregunta(char* texto_ingresado)
{
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(texto_ingresado);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


//configuramos la gui de la ventana de inicio
bool Graph::Ventanainicio(void)
{
    //Para indicarle al programa si ya se apreto el boton ok
    bool todo_ok = false;   
    
    //los siguientes flags son para indicarle a imgui que no se debe poder mover ni cerrar los menus de gui
    ImGuiWindowFlags window_flag = 0;
    window_flag |= ImGuiWindowFlags_NoResize;
    window_flag |= ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Ingrese los Parametros iniciales", NULL, window_flag);                         
    
    ImGui::Text("Inserte Modo ");
    //seteamos las opciones del combo del modo y lo creamos
    const char* items[] = { "1", "2" };
    static const char* item_current = items[0];            
    if (ImGui::BeginCombo("<-", item_current, 0)) 
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (item_current == items[n]);
            if (ImGui::Selectable(items[n], is_selected))
                item_current = items[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();  
        }
        ImGui::EndCombo();
    }
    Pregunta("En el Modo 1 los blobs comparten la misma velocidad. \nEn el modo 2, cada blob tiene una velocidad máxima distinta aleatoria entre 0 y el valor maximo. \nTodas comparten la velocidad porcentual");
    modo = std::stoi(item_current);      //guardamos la variable modo como numero
    
    ImGui::Text("Inserte Velocidad Maxima");
    ImGui::DragFloat("pixeles/tick", &Vel_max, 0.0005, 0.0001, 0.1);
    Pregunta("Luego podra modificar la velocidad deseada para los Blobs desde los ajustes en la simulacion");
    
    ImGui::Text("Cantidad Inicial de Blobs");
    ImGui::DragInt("BabyBlobs", &cant_inicial_blobs, 0.03, 0, 1000000);
    Pregunta("La simulacion inicia con la cantidad deseada de babyBlobs configurada con este parametro");
    
    ImGui::Text("Cantidad de Comida Inicial");
    ImGui::DragInt("Comidas", &foodCount, 0.03, 0, 1000000);
    Pregunta("Este parametro refiere a la cantidad de comida que existira en todo momento en la simulacion, tranquilo, a este parametro podes modificarlo mas tarde");
    
    ImGui::Text("");
    if (ImGui::Button("Ok a simular"))                           
        todo_ok = true;
    
    ImGui::End();
    return todo_ok;
}


//configuramos la gui de la ventana principal
void Graph::VentanaPrincipal(void)
{
    //los siguientes flags son para indicarle a imgui que no se debe poder mover ni cerrar los menus de gui
    ImGuiWindowFlags window_flag = 0;
    window_flag |= ImGuiWindowFlags_NoResize;
    window_flag |= ImGuiWindowFlags_NoCollapse;
    
    ImGui::Begin("Parametros", NULL, window_flag);

    ImGui::Text("Inserte Vel Porcentual ");
    ImGui::SliderFloat("%", &velp, 0.0f, 100.0f);            
    Pregunta("Que porcentaje de la velocidad maxima utilizara en ese momento");
    
    ImGui::Text("SmellRadius");
    ImGui::InputFloat("", &smellRadius, 10.0f, 1.0f, "%.3f");
    Pregunta("SmellRadius refiere a el radio en el cual el blob buscara su alimento, fuera de ese radio de deteccion no lo huele");
    
    ImGui::Text("RandomJiggleLimit");
    ImGui::SliderFloat("°", &randomJiggleLimit, 0.0f, 360.0f);
    Pregunta("Al chocar 2 o mas blobs del mismo grupo etario la direccion del blob resultante es la suma de las direcciones mas un valor aleatorio entre 0 y este valor introducido");
    
    ImGui::Text("Death %");
    ImGui::SliderFloat3("", Death, 0.0f, 1.0f);
    Pregunta("Cada valor corresponde a la probabilidad de muerte de cada grupo etario en el orden: BabyBlob, GrownBlob, GoodOldBlob");
    
    ImGui::Text("Cantidad de Comida %");
    if (ImGui::Button("Disminuir"))                           
        if (foodCount > 0)
            foodCount--;
    ImGui::SameLine();
    if (ImGui::Button("Aumentar"))                           
        foodCount++;
    ImGui::SameLine();
    ImGui::Text("Cantidad = %d", foodCount);
    Pregunta("Cantidad de comida que sera visible en pantalla y podran atrapar los Blobs");

    ImGui::End();
}


//GETTERS


int Graph:: getModo(void) {            

    return modo;
}
int Graph::getBlobNum(void) {

    return cant_inicial_blobs;
}
bool Graph::getClose(void) {

    return close_window;
}
int Graph::getFoodCount(void) {

    return foodCount;
}
float Graph:: getMaxSpeed(void) {
    return Vel_max;
}
float Graph:: getVelp(void) {
    return velp;
}
float Graph::getDead(int type) {

    enum gruop{BABY,GROWN,GOODOLD};
    float deadp;
    switch (type) {
         case BABY:
                 deadp = Death[BABY];
             break;
         case GROWN:
             deadp = Death[GROWN];
             break;
         case GOODOLD:
             deadp = Death[GOODOLD];
             break;

    }
    return deadp;
    
}

float Graph::getSmellRadius(void) {
    return smellRadius;
}
float Graph:: getRJL(void) {
    return randomJiggleLimit;
}