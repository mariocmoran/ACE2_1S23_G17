
//Imagenes
var img, loc, cal, imgtemp, imghrel, imghabs, imgvel, imgdir, imgpre;
//Para la hora
let last_minute = 0;
let last_second = 0;
//Datos
let temp=0, hrel=0, habs=0, vel=0, pre=0;
let dir = "N";

// Botones
let overtemp = false, overhrel = false, overhabs = false,overdir = false, overvel = false, overpre = false;
let ctemp = false, chrel = false, chabs = false,cdir = false, cvel = false, cpre = false;
let size = 35;

//GRAFICAS
var tempgra = false, hrelgra = false, habsgra = false, dirgra = false, velgra = false, pregra = false;
var tempdata = [], hreldata= [], habsdata= [], veldata= [], predata= [];
var dirdata = [0,0,0,0];
var datos;


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
  last_second = second();
  let h = hour();
  text(nf(h,2) + ":" + nf(last_minute,2), 225, 25);
  
  fill(255);
  textFont('Garamond',60);
  textStyle(BOLD);
  text("PRAC 1", 50, height/2);
  
  loadJSON('http://127.0.0.1:5000/UltimoDato',gotData);
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
  textFont("Garamond",80);
  
  if (!ctemp){
    text(nf(round(temp,2),2,2), 325, 165);
    tempgra = false;
  }else{
    graficarTemp();
    tempgra = true;
  }
  
  if (!chrel){
    text(nf(round(hrel,2),2,2), 600, 165);
    hrelgra = false;
  }else{
    graficarHrel();
    hrelgra = true;
  }
  
  if (!chabs){
    text(nf(round(habs,3),1,3), 870, 165);
    habsgra = false;
  }else{
    graficarHabs();
    habsgra = true;
  }
  
  if (!cvel){
    text(nf(round(vel,2),2,2), 310, 425);
    velgra = false;
  }else{
    graficarVel();
    velgra = true;
  }
  
  if (!cdir){
    text(dir, 685, 425);
    dirgra = false;
  }else{
    graficarDir();
    dirgra=true;
  }
  
  fill(0);
  textFont("Garamond",80);
  if (!cpre){
    text(nf(round(pre,2),3,2), 890, 410);
    pregra = false;
  }else{
    graficarPre();
    pregra=true;
  }
  
  //Unidades
  
  textFont("Garamond",35);
  
  
  if (!ctemp){
    text("°C", 500, 165);
  }
  
  if (!chrel){
    text("°C", 780, 165);
  }
  
  if (!chabs){
    text("g/m3", 1045, 165);
  }
  
  if (!cvel){
    text("km/h", 485, 425);
  }
  
  if (!cpre){
    text("mmHg", 945, 445);
  }
  

  // ------------------------- -PARA CAMBIAR HORA ------------------------------------
  var h = hour();
  var m = minute();
  var s = second();
  
  if(s != last_second){
    // -------------------------------- PARA REFRESCAR DATO -------------------------------
    loadJSON('http://127.0.0.1:5000/UltimoDato',gotData);
    last_second = s;
    print("hola");
  }
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
  }
  
}

function graficarTemp(){
  if(!tempgra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);   
  }
  plot = new GPlot(this);
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

function graficarHrel(){
  if(!hrelgra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);
  }
  
  plot = new GPlot(this);
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

function graficarHabs(){
  if(!habsgra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);
  }
  
  plot = new GPlot(this);
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

function graficarVel(){
  if(!velgra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);
  }
  
  plot = new GPlot(this);
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

function graficarPre(){
  if(!pregra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);
  }
  
  plot = new GPlot(this);
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

function graficarDir(){
  if(!dirgra){
    loadJSON('http://127.0.0.1:5000/Datos',gotDataGraph);
  }
  
  var dataCirculo = [];
  var cantD = dirdata[0] + dirdata[1] + dirdata[2] + dirdata[3];
  
  for(var j = 0; j < 4; j++){
    dataCirculo[j] = (dirdata[j] / cantD)*360;
  }
  
  var lastAngle = 0;
  var vinit = 360;
  for (var i = 0; i < 4; i++) {
    var gray = map(i, 0, 4, 0, 255);
    fill(gray);
    arc(670, 400, 150, 150, lastAngle, lastAngle+radians(dataCirculo[i]));
    lastAngle += radians(dataCirculo[i]);
    rect(750, vinit, 10,10);
    fill(0);
    textFont("Garamond",15);
    
    var t;
    
    switch(i){
      case 0:
        t = "S";
      break;
      case 1:
        t = "N";
      break;
      case 2:
        t = "E";
      break;
      case 3:
        t = "O";
      break;
      default:
        t = "";
      break;
    }
    
    text(t + " (" + round(100*dataCirculo[i]/360, 2) + "%)", 765, vinit + 8);
    vinit += 20;
    
  }
  
}

function gotDataGraph(data){
  print(data);
  
  tempdata = [];
  habsdata = [];
  hreldata = [];
  veldata = [];
  predata = [];
  dirdata = [0,0,0,0];
  
  for (let i = 0; i < data.length; i++) {
      tempdata[i] = new GPoint(i, data[i].Temperatura_A);
      habsdata[i] = new GPoint(i, data[i].Humedad_A); 
      hreldata[i] = new GPoint(i, data[i].Humedad_R); 
      veldata[i] = new GPoint(i, data[i].Velocidad_V); 
      //tempdata[i] = new GPoint(i, data[i].Temperatura_A); 
      predata[i] = new GPoint(i, data[i].Presion_B); 
      
      switch(data[i].Direccion_V){
        case 1:
          dirdata[0] += 1;
        break;
        case 2:
          dirdata[1] += 1;
        break;
        case 3:
          dirdata[2] += 1;
        break;
        case 4:
          dirdata[3] += 1;
        break;
        default:
        break;
      }
      
  }
  
}

function gotData(data){
  print(data);
  temp = data.Temperatura_A;
  habs = data.Humedad_A;
  hrel = data.Humedad_R;
  vel = data.Velocidad_V;
  pre = data.Presion_B;
  
  switch(data.Direccion_V){
    case 1:
      dir = 'S';
    break;
    case 2:
      dir = 'N';
    break;
    case 3:
      dir = 'E';
    break;
    case 4:
      dir = 'O';
    break;
    default:
      dir = 'Er';
    break;
  }
  
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
