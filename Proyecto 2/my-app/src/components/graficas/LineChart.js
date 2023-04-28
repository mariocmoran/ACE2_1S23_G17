import Chart from 'chart.js';
import React, { useRef, useEffect } from 'react';

function LineChart(props) {
    const chartRef = useRef();
    useEffect(() => {
        const myChartRef = chartRef.current.getContext('2d');
        new Chart(myChartRef, {
            type: 'line',
            data: {
                labels: props.label,
                datasets: [
                    {
                        data: props.data,
                        fill: false,
                        borderColor: 'rgb(75, 192, 192)',
                        tension: 0.1
                    },
                ],
            },
            options: {
                scales: {
                    yAxes: {
                        ticks: {
                            beginAtZero: true,
                        },
                    }
                },
                legend: {
                    display: false,
                },
                // otras opciones de la gráfica
            }
        });
    }, [props.data,props.label]);
    return (
        <div>
            <canvas id="myChart" ref={chartRef} style={{ margin: "auto", height: "20vh" }} />
        </div>
    );
}

export default LineChart