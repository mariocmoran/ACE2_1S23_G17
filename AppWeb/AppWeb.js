

//Imagenes
var img, loc, cal, imgtemp, imghrel, imghabs, imgvel, imgdir, imgpre;
//Para la hora
let last_minute = 0;
//Datos
let temp=0, hrel=0, habs=0, vel=0, pre=0;
let dir = "N";

// Botones
let overtemp = false, overhrel = false, overhabs = false,overdir = false, overvel = false, overpre = false;
let ctemp = false, chrel = false, chabs = false,cdir = false, cvel = false, cpre = false;
let size = 35;


function preload() {
  img = loadImage('src/fondo.png'); // Load the original image
  cal = loadImage("src/cal.png"); // Load the original image
  loc = loadImage("src/loc.png"); // Load the original image
  imgtemp = loadImage("/src/temp.png");
  imghrel = loadImage("/src/hrel.png");
  imghabs = loadImage("/src/habs.png");
  imgvel = loadImage("/src/vel.png");
  imgdir = loadImage("/src/dir.png");
  imgpre = loadImage("/src/pre.png");
}

function setup() {
  createCanvas(1140,540);
  background('#EAEDED');
  
  
  //FONDO
  image(img, 0, 0, 285, 540); // Displays the image from point (0,0)
  
  //CALENDARIO
  image(cal, 50, 50, 22, 22);
  
  textFont('Arial',16);
  fill('#17202A');
  
  text("Febrero "+day()+", 2023", 85, 65);
  
  //UBICACION
  image(loc, 50, 85, 22, 22);
  text("Guatemala, Guatemala", 85, 100);
  
  
  textFont('Arial',20);
  textStyle(BOLD);
  last_minute = minute();
  let h = hour();
  text(nf(h,2) + ":" + nf(last_minute,2), 225, 25);
  
  fill(255);
  textFont('Garamond',60);
  textStyle(BOLD);
  text("PRAC 1", 50, height/2);
  
  loadJSON('http://127.0.0.1:5000/nuevo',gotData);
}


function draw() {
  
  // Cuadros, Textos e Imagenes
  fill('#D5DBDB');
  stroke('#D5DBDB');
  rect(300,10,270,255,10);
  rect(580,10,270,255,10);
  rect(860,10,270,255,10);
  rect(300,275,270,255,10);
  rect(580,275,270,255,10);
  rect(860,275,270,255,10);
  
  fill(0);
  textFont('Garamond',30);
  textStyle(NORMAL);
  text("Temperatura",355, 250);  
  text("Humedad Relativa",605, 250);
  text("Humedad Absoluta",885, 250); 
  text("Velocidad de Viento",315, 515); 
  text("Dirección de Viento",600, 515); 
  text("Presión Barométrica",880, 515);
  
  image(imgtemp, 510, 20, 50, 50);
  image(imghrel, 795, 20, 50, 50);
  image(imghabs, 1080, 20, 50, 50);
  image(imgvel, 305, 280, 50, 50);
  image(imgdir, 585, 280, 50, 50);
  image(imgpre, 870, 280, 50, 50);
  
  update();
  
  // --------------------------------------- BOTONES ------------------------
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
  //Data
  textFont("Garamond",85);
  
  if (!ctemp){
    text(nf(temp,2), 375, 160);
  }
  if (!chrel){
    text(nf(hrel,2), 665, 160);
  }
  if (!chabs){
    text(nf(habs,2), 925, 160);
  }
  
  if (!cvel){
    text(nf(vel,2), 365, 425);
  }
  if (!cdir){
    text(dir, 675, 425);
  }
  if (!cpre){
    text(nf(pre,3), 885, 425);
  }
  
  //Unidades
  
  textFont("Garamond",40);
  
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
  

  // ------------------------- -PARA CAMBIAR HORA ------------------------------------
  var h = hour();
  var m = minute();
  if(m != last_minute){
    
    //FONDO
    image(img, 0, 0, 285, 540); // Displays the image from point (0,0)
    
    //CALENDARIO
    image(cal, 50, 50, 22, 22);
    
    fill(0);
    stroke(0);
    textFont('Arial',16);
    textStyle(NORMAL);
    
    text("Febrero "+day()+", 2023", 85, 65);
    
    //UBICACION
    image(loc, 50, 85, 22, 22);
    text("Guatemala, Guatemala", 85, 100);
    
    
    textFont('Arial',20);
    textStyle(BOLD);
    last_minute = minute();
    let h = hour();
    text(nf(h,2) + ":" + nf(last_minute,2), 225, 25);
    
    fill(255);
    textFont('Garamond',60);
    textStyle(BOLD);
    text("PRAC 1", 50, height/2);
    

    last_minute = m;
    
    // -------------------------------- PARA REFRESCAR DATO -------------------------------
    loadJSON('http://127.0.0.1:5000/nuevo',gotData);
  }
}

function gotData(data){
  print(data);
  temp = data.Temperatura_A;
  habs = data.Humedad_A;
  hrel = data.Humedad_R;
  vel = data.Velocidad_V;
  dir = data.Direccion_V;
  pre = data.Presion_B;
  
}

function update() {
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
  
  function overRect(x, y, width, height)  {
    if (mouseX >= x && mouseX <= x+width && 
        mouseY >= y && mouseY <= y+height) {
      return true;
    } else {
      return false;
    }
  }
  
  function mousePressed() {
    if (overtemp) {
      if (ctemp){
        print("Temp Dato");
        ctemp = false;
      }else{
        ctemp = true;
        print("Temp Grafica");
      }      
    }
    
    if (overhrel) {
      if (chrel){
        print("H. Relativa Dato");
        chrel = false;
      }else{
        chrel = true;
        print("H. Relativa Grafica");
      } 
    }
    if (overhabs) {
      if (chabs){
        print("H- Absoluta Dato");
        chabs = false;
      }else{
        chabs = true;
        print("H- Absoluta Grafica");
      } 
    }
    if (overvel) {
      if (cvel){
        print("Velocidad Dato");
        cvel = false;
      }else{
        cvel = true;
        print("Velocidad Grafica");
      } 
    }
    if (overdir) {
      if (cdir){
        print("Direccion Dato");
        cdir = false;
      }else{
        cdir = true;
        print("Direccion Grafica");
      } 
    }
    if (overpre) {
      if (cpre){
        print("Presion Dato");
        cpre = false;
      }else{
        cpre = true;
        print("Presion Grafica");
      } 
    }
    
  }
