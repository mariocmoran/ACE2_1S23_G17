import grafica.*;


PImage img, loc, cal;

//Datos
int temp, hrel, habs, vel, pre;

String dir = "N";

//Para la hora
int last_minute = 0;

// Botones
boolean overtemp = false, overhrel = false, overhabs = false,overdir = false, overvel = false, overpre = false;
boolean ctemp = false, chrel = false, chabs = false,cdir = false, cvel = false, cpre = false;
int size = 35;

//GRAFICAS
boolean tempgra = false, hrelgra = false, habsgra = false, dirgra = false, velgra = false, pregra = false;
GPointsArray tempdata, hreldata, habsdata, dirdata, veldata, predata;


void setup(){
  size(1140,540);
  background(#EAEDED);
  textFont(createFont("Arial",16));
  
  // FONDO
  img = loadImage("/src/fondo.jpg"); // Load the original image
  image(img, 0, 0, width/4, height); // Displays the image from point (0,0)
  
  // Cal
  cal = loadImage("/src/cal.png"); // Load the original image
  image(cal, 50, 50, 22, 22);
  
  fill(#17202A);
  textSize(16);
  
  text("Febrero "+day()+", 2023", 85, 65);
  
  
  // LOC
  loc = loadImage("/src/loc.png"); // Load the original image
  image(loc, 50, 85, 22, 22);
  
  text("Guatemala, Guatemala", 85, 100);
  
  textFont(createFont("Arial Bold",20));
  last_minute = minute();
  int h = hour();
  text(nf(h,2) + ":" + nf(last_minute,2), 225, 25);
  
  fill(255);
  textFont(createFont("Garamond Bold",60));
  text("PRAC 1", 50, height/2);
  
  // -------------------------------- PARA REFRESCAR DATO -------------------------------
  gotData();
}

void draw(){
  fill(#D5DBDB);
  stroke(#D5DBDB);
  rect(300,10,270,255,10);
  rect(580,10,270,255,10);
  rect(860,10,270,255,10);
  rect(300,275,270,255,10);
  rect(580,275,270,255,10);
  rect(860,275,270,255,10);
  
  fill(0);
  textFont(createFont("Garamond",30));
  text("Temperatura",355, 250);  
  text("Humedad Relativa",605, 250);
  text("Humedad Absoluta",885, 250); 
  text("Velocidad de Viento",315, 515); 
  text("Dirección de Viento",600, 515); 
  text("Presión Barométrica",880, 515);
  
  image(loadImage("/src/temp.png"), 510, 20, 50, 50);
  image(loadImage("/src/hrel.png"), 795, 20, 50, 50);
  image(loadImage("/src/habs.png"), 1080, 20, 50, 50);
  image(loadImage("/src/vel.png"), 305, 280, 50, 50);
  image(loadImage("/src/dir.png"), 585, 280, 50, 50);
  image(loadImage("/src/pre.png"), 870, 280, 50, 50);
  
  
  
  update();
  
  // BOTONES
  stroke(255);
  
  if(overtemp){
    fill(51);
  }else{
    fill(0);
  }
  rect(300,10,size,size,10);
  if(overhrel){
    fill(51);
  }else{
    fill(0);
  }
  rect(580,10,size,size,10);
  if(overhabs){
    fill(51);
  }else{
    fill(0);
  }
  rect(860,10,size,size,10);
  if(overvel){
    fill(51);
  }else{
    fill(0);
  }
  rect(535,275,size,size,10);
  if(overdir){
    fill(51);
  }else{
    fill(0);
  }
  rect(815,275,size,size,10);
  if(overpre){
    fill(51);
  }else{
    fill(0);
  }
  rect(1095,275,size,size,10);
  
  

  
  
  // --------------------------- DATOS ACTUALES ------------------------------------------
  //pre += 1;
  textFont(createFont("Garamond",85));
  //DATA
  if (!ctemp){
    text(nf(temp,2), 375, 160);
    tempgra = false;
  }else{
    graficarTemp();
    tempgra = true;
  }
  
  if (!chrel){
    text(nf(hrel,2), 665, 160);
    hrelgra = false;
  }else{
    graficarHrel();
    hrelgra = true;
  }
  
  if (!chabs){
    text(nf(habs,2), 925, 160);
    habsgra = false;
  }else{
    graficarHabs();
    habsgra = true;
  }
  
  if (!cvel){
    text(nf(vel,2), 365, 425);
    velgra = false;
  }else{
    graficarVel();
    velgra = true;
  }
  
  if (!cdir){
    text(dir, 675, 425);
  }
  
  if (!cpre){
    text(nf(pre,3), 885, 425);
    pregra = false;
  }else{
    graficarPre();
    pregra=true;
  }
  
  //Unidades
  textFont(createFont("Garamond",40));
  
  if (!ctemp){
    text("°C", 465, 160);
  }
  
  if (!chrel){
    text("°C", 760, 160);
  }
  
  if (!chabs){
    text("g/m3", 1020, 160);
  }
  
  if (!cvel){
    text("km/h", 455, 425);
  }
  
  if (!cpre){
    text("mmHg", 1010, 425);
  }
  
  
  
  
  // PARA CAMBIAR HORA
  int h = hour();
  int m = minute();
  if(m != last_minute){
    textFont(createFont("Arial",16));
    // FONDO
    img = loadImage("/src/fondo.jpg"); // Load the original image
    image(img, 0, 0, width/4, height); // Displays the image from point (0,0)
    
    // Cal
    cal = loadImage("/src/cal.png"); // Load the original image
    image(cal, 50, 50, 22, 22);
    
    fill(#17202A);
    textSize(16);
    text("Febrero "+day()+", 2023", 85, 65);
    
    
    // LOC
    loc = loadImage("/src/loc.png"); // Load the original image
    image(loc, 50, 85, 22, 22); 
    text("Guatemala, Guatemala", 85, 100);
    
    //titulo
    fill(255);
    textFont(createFont("Garamond Bold",60));
    text("PRAC 1", 50, height/2);
    
    fill(0);
    textFont(createFont("Arial Bold",20));
    text(nf(h,2) + ":" + nf(m,2), 225, 25);
    last_minute = m;
    
    // -------------------------------- PARA REFRESCAR DATO -------------------------------
    gotData();
  } 
}

void graficarTemp(){
  if(!tempgra){
    JSONArray data = loadJSONArray("http://127.0.0.1:5000/data");
  
    tempdata = new GPointsArray(data.size());
    
    for (int i = 0; i < data.size(); i++) {
      JSONObject dd = data.getJSONObject(i); 
      tempdata.add(i, dd.getInt("Temperatura_A"));
    }
  }
  GPlot plot = new GPlot(this);
  plot.setPos(350, 20);
  plot.setDim(120,100);
  // Set the plot title and the axis labels
  plot.getXAxis().setAxisLabelText("No.");
  plot.getYAxis().setAxisLabelText("Temperatura (°C)");
  // Add the points
  plot.setPoints(tempdata);
  // Draw it!
  plot.defaultDraw();
  
}

void graficarHrel(){
  if(!hrelgra){
    JSONArray data = loadJSONArray("http://127.0.0.1:5000/data");
  
    hreldata = new GPointsArray(data.size());
    
    for (int i = 0; i < data.size(); i++) {
      JSONObject dd = data.getJSONObject(i); 
      hreldata.add(i, dd.getInt("Humedad_R"));
    }
  }
  
  GPlot plot = new GPlot(this);
  plot.setPos(630, 20);
  plot.setDim(120,100);
  // Set the plot title and the axis labels
  plot.getXAxis().setAxisLabelText("No.");
  plot.getYAxis().setAxisLabelText("Húmedad Rel. (°C)");
  // Add the points
  plot.setPoints(hreldata);
  // Draw it!
  plot.defaultDraw();
  
}

void graficarHabs(){
  if(!habsgra){
    JSONArray data = loadJSONArray("http://127.0.0.1:5000/data");
  
    habsdata = new GPointsArray(data.size());
    
    for (int i = 0; i < data.size(); i++) {
      JSONObject dd = data.getJSONObject(i); 
      habsdata.add(i, dd.getInt("Humedad_A"));
    }
  }
  
  GPlot plot = new GPlot(this);
  plot.setPos(910, 20);
  plot.setDim(120,100);
  // Set the plot title and the axis labels
  plot.getXAxis().setAxisLabelText("No.");
  plot.getYAxis().setAxisLabelText("Húmedad Abs. (g/m3)");
  // Add the points
  plot.setPoints(habsdata);
  // Draw it!
  plot.defaultDraw();
  
}

void graficarVel(){
  if(!velgra){
    JSONArray data = loadJSONArray("http://127.0.0.1:5000/data");
  
    veldata = new GPointsArray(data.size());
    
    for (int i = 0; i < data.size(); i++) {
      JSONObject dd = data.getJSONObject(i); 
      veldata.add(i, dd.getInt("Velocidad_V"));
    }
  }
  
  GPlot plot = new GPlot(this);
  plot.setPos(305, 280);
  plot.setDim(120,100);
  // Set the plot title and the axis labels
  plot.getXAxis().setAxisLabelText("No.");
  plot.getYAxis().setAxisLabelText("Velocidad (km/h)");
  // Add the points
  plot.setPoints(veldata);
  // Draw it!
  plot.defaultDraw();
  
}

void graficarPre(){
  if(!pregra){
    JSONArray data = loadJSONArray("http://127.0.0.1:5000/data");
  
    predata = new GPointsArray(data.size());
    
    for (int i = 0; i < data.size(); i++) {
      JSONObject dd = data.getJSONObject(i); 
      predata.add(i, dd.getInt("Presion_B"));
    }
  }
  
  GPlot plot = new GPlot(this);
  plot.setPos(865, 280);
  plot.setDim(120,100);
  // Set the plot title and the axis labels
  plot.getXAxis().setAxisLabelText("No.");
  plot.getYAxis().setAxisLabelText("Presión B. (mmHg)");
  // Add the points
  plot.setPoints(predata);
  // Draw it!
  plot.defaultDraw();
  
}

void gotData(){
  JSONObject data = loadJSONObject("http://127.0.0.1:5000/nuevo");
  println(data);
  temp = data.getInt("Temperatura_A");
  habs = data.getInt("Humedad_A");
  hrel = data.getInt("Humedad_R");
  vel = data.getInt("Velocidad_V");
  dir = data.getString("Direccion_V");
  pre = data.getInt("Presion_B");
  
}

void update() {
    if ( overRect(300, 10, size, size) ) {
      overtemp = true;
      overhrel = overhabs = overvel = overdir = overpre = false;
    }else if (overRect(580, 10, size, size)){
      overhrel = true;
      overtemp = overhabs = overvel = overdir = overpre = false;
    }else if (overRect(860, 10, size, size)){
      overhabs = true;
      overtemp = overhrel = overvel = overdir = overpre = false;
    }else if (overRect(535, 275, size, size)){
      overvel = true;
      overtemp = overhrel = overhabs = overdir = overpre = false;
    }else if (overRect(815, 275, size, size)){
      overdir = true;
      overtemp = overhrel = overhabs = overvel = overpre = false;
    }else if (overRect(1095, 275, size, size)){
      overpre = true;
      overtemp = overhrel = overhabs = overvel = overdir = false;
    }else{
      overtemp = overhrel = overhabs = overvel = overdir = overpre = false;
    }  
  }
  
  boolean overRect(int x, int y, int width, int height)  {
    if (mouseX >= x && mouseX <= x+width && 
        mouseY >= y && mouseY <= y+height) {
      return true;
    } else {
      return false;
    }
  }
  
  void mousePressed() {
    if (overtemp) {
      if (ctemp){
        println("Temp Dato");
        ctemp = false;
      }else{
        ctemp = true;
        println("Temp Grafica");
      }      
    }
    
    if (overhrel) {
      if (chrel){
        println("H. Relativa Dato");
        chrel = false;
      }else{
        chrel = true;
        println("H. Relativa Grafica");
      } 
    }
    if (overhabs) {
      if (chabs){
        println("H- Absoluta Dato");
        chabs = false;
      }else{
        chabs = true;
        println("H- Absoluta Grafica");
      } 
    }
    if (overvel) {
      if (cvel){
        println("Velocidad Dato");
        cvel = false;
      }else{
        cvel = true;
        println("Velocidad Grafica");
      } 
    }
    if (overdir) {
      if (cdir){
        println("Direccion Dato");
        cdir = false;
      }else{
        cdir = true;
        println("Direccion Grafica");
      } 
    }
    if (overpre) {
      if (cpre){
        println("Presion Dato");
        cpre = false;
      }else{
        cpre = true;
        println("Presion Grafica");
      } 
    }
    
  }
