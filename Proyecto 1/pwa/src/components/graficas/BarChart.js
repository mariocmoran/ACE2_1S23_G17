import React, { useEffect, useState } from 'react';
import { v4 as uuidv4 } from 'uuid';

function BarChart(props) {
    const [canvasId] = useState(uuidv4());
    
    useEffect(() => {
        var myCanvas = document.getElementById(canvasId);
        myCanvas.width = 350;
        myCanvas.height = 300;
        var ctx = myCanvas.getContext("2d");

        var myBarchart = new BarChartObject({
            ctx: ctx,
            canvas: myCanvas,
            seriesName: props.name,
            padding: 50,
            gridStep: 5,
            gridColor: "black",
            data: props.data,
            colors: [props.color, props.color2, props.color3, props.color4],
            titleOptions: {
                align: "center",
                fill: "black",
                font: {
                    weight: "bold",
                    size: "18px",
                    family: "Lato"
                }
            }
        });
        myBarchart.draw();

    }, [props.data, canvasId, props.name, props.color, props.color2, props.color3, props.color4]); // El arreglo de dependencias está vacío

    return (
        <><canvas id={canvasId} style={{width:"100%"}}></canvas></>
    );
}

function drawLine(ctx, startX, startY, endX, endY, color) {
    ctx.save();
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.moveTo(startX, startY);
    ctx.lineTo(endX, endY);
    ctx.stroke();
    ctx.restore();
}

function drawBar(ctx, upperLeftCornerX, upperLeftCornerY, width, height, color, text, init, end) {
    ctx.save();
    ctx.fillStyle = color;
    ctx.fillRect(upperLeftCornerX, upperLeftCornerY, width, height);
    ctx.restore();
    //nombre de barra
    ctx.save();
    ctx.translate(upperLeftCornerX + 5, upperLeftCornerY);
    ctx.rotate(-(Math.PI / 4));
    ctx.fillStyle = 'black';
    ctx.textAlign = "left";
    ctx.fillText(text, 0, 0);
    ctx.restore();
    //inicio
    ctx.save();
    ctx.translate(upperLeftCornerX + 10, ctx.canvas.clientHeight)//ctx.canvas.clientHeight );
    ctx.rotate(-(Math.PI / 2));
    ctx.fillStyle = 'blue';
    ctx.textAlign = "rigth";
    ctx.fillText(init, 0, 0);
    ctx.restore();
    //fin
    ctx.save();
    ctx.translate(upperLeftCornerX + width - 5, ctx.canvas.clientHeight)//ctx.canvas.clientHeight );
    ctx.rotate(-(Math.PI / 2));
    ctx.fillStyle = 'blue';
    ctx.textAlign = "rigth";
    ctx.fillText(end, 0, 0);
    ctx.restore();
}

class BarChartObject {
    constructor(options) {
        this.options = options;
        this.canvas = options.canvas;
        this.ctx = options.ctx;
        this.colors = options.colors;
        this.titleOptions = options.titleOptions;
        this.maxValue = 120;
    }

    drawGridLines() {
        var canvasActualHeight = this.canvas.height - this.options.padding * 2;
        // var canvasActualWidth = this.canvas.width - this.options.padding * 2;

        var gridValue = 0;
        while (gridValue <= this.maxValue) {
            var gridY =
                canvasActualHeight * (1 - gridValue / this.maxValue) +
                this.options.padding;
            drawLine(
                this.ctx,
                0,
                gridY,
                this.canvas.width,
                gridY,
                '#DAAF'
            );

            drawLine(
                this.ctx,
                15,
                this.options.padding / 2,
                15,
                gridY + this.options.padding / 2,
                this.options.gridColor
            );

            // Writing grid markers
            this.ctx.save();
            this.ctx.fillStyle = this.options.gridColor;
            this.ctx.textBaseline = "bottom";
            this.ctx.font = "bold 10px Arial";
            this.ctx.fillText(gridValue, 0, gridY - 2);
            this.ctx.restore();

            gridValue += this.options.gridStep;
        }
    }

    drawBars() {
        var canvasActualHeight = this.canvas.height - this.options.padding * 2;
        var canvasActualWidth = this.canvas.width - this.options.padding * 2;
        var barIndex = 0;
        var numberOfBars = this.options.data.length;
        var barSize = canvasActualWidth / numberOfBars;
        var values = this.options.data;
        var currentPomodoro;
        for (let val of values) {
            if (val.pomId !== currentPomodoro) {
                drawLine(
                    this.ctx,
                    this.options.padding + barIndex * barSize,
                    this.options.padding,
                    this.options.padding + barIndex * barSize,
                    this.ctx.canvas.clientHeight,
                    "red"
                );
                currentPomodoro = val.pomId;
            }
            var barHeight = Math.round((canvasActualHeight * val.total) / this.maxValue);
            //console.log(barHeight);
            //console.log(val);
            if ((barIndex + 1) % 4 === 0 && barIndex !== 0) {
                drawBar(
                    this.ctx,
                    this.options.padding + barIndex * barSize,
                    this.canvas.height - barHeight - this.options.padding,
                    barSize,
                    barHeight,
                    this.colors[barIndex % this.colors.length],
                    //(barIndex%3==0),
                    val.name,
                    val.init,
                    val.end
                );
            } else {
                drawBar(
                    this.ctx,
                    this.options.padding + barIndex * barSize,
                    this.canvas.height - barHeight - this.options.padding,
                    barSize,
                    barHeight,
                    this.colors[barIndex % this.colors.length],
                    //(barIndex%3==0),
                    val.name,
                    val.init,
                    val.end
                );
            }
            barIndex++;
        }
    }

    drawLabel() {
        this.ctx.save();
        this.ctx.textBaseline = "bottom";
        this.ctx.textAlign = this.titleOptions.align;
        this.ctx.fillStyle = this.titleOptions.fill;
        this.ctx.font = `${this.titleOptions.font.weight} ${this.titleOptions.font.size} ${this.titleOptions.font.family}`;
        let xPos = this.canvas.width / 2;
        if (this.titleOptions.align === "left") {
            xPos = 10;
        }
        if (this.titleOptions.align === "right") {
            xPos = this.canvas.width - 10;
        }
        this.ctx.fillText(this.options.seriesName, xPos, 50);
        this.ctx.restore();
    }

    draw() {
        this.drawGridLines();
        this.drawBars();
        this.drawLabel();
    }
}

export default BarChart